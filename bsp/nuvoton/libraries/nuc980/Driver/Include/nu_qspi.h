/**************************************************************************//**
 * @file     qspi.h
 * @brief    NUC980 series QSPI driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_QSPI_H__
#define __NU_QSPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup QSPI Serial Peripheral Interface Controller(QSPI)
    Memory Mapped Structure for QSPI Controller
@{ */

typedef struct
{


    /**
     * @var QSPI_T::CTL
     * Offset: 0x00  QSPI Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |QSPIEN    |QSPI Transfer Control Enable Bit
     * |        |          |In Master mode, the transfer will start when there is data in the FIFO buffer after this bit is set to 1
     * |        |          |In Slave mode, this device is ready to receive data when this bit is set to 1.
     * |        |          |0 = Transfer control Disabled.
     * |        |          |1 = Transfer control Enabled.
     * |        |          |Note: Before changing the configurations of QSPIx_CTL, QSPIx_CLKDIV, QSPIx_SSCTL and QSPIx_FIFOCTL registers, user shall clear the QSPIEN (QSPIx_CTL[0]) and confirm the QSPIENSTS (QSPIx_STATUS[15]) is 0.
     * |[1]     |RXNEG     |Receive on Negative Edge
     * |        |          |0 = Received data input signal is latched on the rising edge of QSPI bus clock.
     * |        |          |1 = Received data input signal is latched on the falling edge of QSPI bus clock.
     * |[2]     |TXNEG     |Transmit on Negative Edge
     * |        |          |0 = Transmitted data output signal is changed on the rising edge of QSPI bus clock.
     * |        |          |1 = Transmitted data output signal is changed on the falling edge of QSPI bus clock.
     * |[3]     |CLKPOL    |Clock Polarity
     * |        |          |0 = QSPI bus clock is idle low.
     * |        |          |1 = QSPI bus clock is idle high.
     * |[7:4]   |SUSPITV   |Suspend Interval (Master Only)
     * |        |          |The four bits provide configurable suspend interval between two successive transmit/receive transaction in a transfer
     * |        |          |The definition of the suspend interval is the interval between the last clock edge of the preceding transaction word and the first clock edge of the following transaction word
     * |        |          |The default value is 0x3
     * |        |          |The period of the suspend interval is obtained according to the following equation.
     * |        |          |(SUSPITV[3:0] + 0.5) * period of QSPICLK clock cycle
     * |        |          |Example:
     * |        |          |SUSPITV = 0x0 .... 0.5 QSPICLK clock cycle.
     * |        |          |SUSPITV = 0x1 .... 1.5 QSPICLK clock cycle.
     * |        |          |.....
     * |        |          |SUSPITV = 0xE .... 14.5 QSPICLK clock cycle.
     * |        |          |SUSPITV = 0xF .... 15.5 QSPICLK clock cycle.
     * |[12:8]  |DWIDTH    |Data Width
     * |        |          |This field specifies how many bits can be transmitted / received in one transaction
     * |        |          |The minimum bit length is 8 bits and can up to 32 bits.
     * |        |          |DWIDTH = 0x08 .... 8 bits.
     * |        |          |DWIDTH = 0x09 .... 9 bits.
     * |        |          |.....
     * |        |          |DWIDTH = 0x1F .... 31 bits.
     * |        |          |DWIDTH = 0x00 .... 32 bits.
     * |[13]    |LSB       |Send LSB First
     * |        |          |0 = The MSB, which bit of transmit/receive register depends on the setting of DWIDTH, is transmitted/received first.
     * |        |          |1 = The LSB, bit 0 of the QSPI TX register, is sent first to the QSPI data output pin, and the first bit received from the QSPI data input pin will be put in the LSB position of the RX register (bit 0 of QSPI_RX).
     * |[14]    |HALFDPX   |QSPI Half-duplex Transfer Enable Bit
     * |        |          |This bit is used to select full-duplex or half-duplex for QSPI transfer
     * |        |          |The bit field DATDIR (QSPIx_CTL[20]) can be used to set the data direction in half-duplex transfer.
     * |        |          |0 = QSPI operates in full-duplex transfer.
     * |        |          |1 = QSPI operates in half-duplex transfer.
     * |[15]    |RXONLY    |Receive-only Mode Enable Bit (Master Only)
     * |        |          |This bit field is only available in Master mode
     * |        |          |In receive-only mode, QSPI Master will generate QSPI bus clock continuously for receiving data bit from QSPI slave device and assert the BUSY status.
     * |        |          |0 = Receive-only mode Disabled.
     * |        |          |1 = Receive-only mode Enabled.
     * |[16]    |TWOBIT    |2-bit Transfer Mode Enable Bit (Only Supported in QSPI0)
     * |        |          |0 = 2-Bit Transfer mode Disabled.
     * |        |          |1 = 2-Bit Transfer mode Enabled.
     * |        |          |Note: When 2-Bit Transfer mode is enabled, the first serial transmitted bit data is from the first FIFO buffer data, and the 2nd serial transmitted bit data is from the second FIFO buffer data
     * |        |          |As the same as transmitted function, the first received bit data is stored into the first FIFO buffer and the 2nd received bit data is stored into the second FIFO buffer at the same time.
     * |[17]    |UNITIEN   |Unit Transfer Interrupt Enable Bit
     * |        |          |0 = QSPI unit transfer interrupt Disabled.
     * |        |          |1 = QSPI unit transfer interrupt Enabled.
     * |[18]    |SLAVE     |Slave Mode Control
     * |        |          |0 = Master mode.
     * |        |          |1 = Slave mode.
     * |[19]    |REORDER   |Byte Reorder Function Enable Bit
     * |        |          |0 = Byte Reorder function Disabled.
     * |        |          |1 = Byte Reorder function Enabled
     * |        |          |A byte suspend interval will be inserted among each byte
     * |        |          |The period of the byte suspend interval depends on the setting of SUSPITV.
     * |        |          |Note: Byte Reorder function is only available if DWIDTH is defined as 16, 24, and 32 bits.
     * |[20]    |DATDIR    |Data Port Direction Control
     * |        |          |This bit is used to select the data input/output direction in half-duplex transfer and Dual/Quad transfer
     * |        |          |0 = QSPI data is input direction.
     * |        |          |1 = QSPI data is output direction.
     * |[21]    |DUALIOEN  |Dual I/O Mode Enable Bit (Only Supported in QSPI0)
     * |        |          |0 = Dual I/O mode Disabled.
     * |        |          |1 = Dual I/O mode Enabled.
     * |[22]    |QUADIOEN  |Quad I/O Mode Enable Bit (Only Supported in QSPI0)
     * |        |          |0 = Quad I/O mode Disabled.
     * |        |          |1 = Quad I/O mode Enabled.
     * @var QSPI_T::CLKDIV
     * Offset: 0x04  QSPI Clock Divider Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |DIVIDER   |Clock Divider
     * |        |          |The value in this field is the frequency divider for generating the peripheral clock, fspi_eclk, and the QSPI bus clock of QSPI Master
     * |        |          |The frequency is obtained according to the following equation.
     * |        |          |where
     * |        |          |is the peripheral clock source, which is defined in the clock control register, CLK_CLKSEL2.
     * @var QSPI_T::SSCTL
     * Offset: 0x08  QSPI Slave Select Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SS        |Slave Selection Control (Master Only)
     * |        |          |If AUTOSS bit is cleared to 0,
     * |        |          |0 = set the QSPIx_SS line to inactive state.
     * |        |          |1 = set the QSPIx_SS line to active state.
     * |        |          |If the AUTOSS bit is set to 1,
     * |        |          |0 = Keep the QSPIx_SS line at inactive state.
     * |        |          |1 = QSPIx_SS line will be automatically driven to active state for the duration of data transfer, and will be driven to inactive state for the rest of the time
     * |        |          |The active state of QSPIx_SS is specified in SSACTPOL (QSPIx_SSCTL[2]).
     * |[2]     |SSACTPOL  |Slave Selection Active Polarity
     * |        |          |This bit defines the active polarity of slave selection signal (QSPIx_SS).
     * |        |          |0 = The slave selection signal QSPIx_SS is active low.
     * |        |          |1 = The slave selection signal QSPIx_SS is active high.
     * |[3]     |AUTOSS    |Automatic Slave Selection Function Enable Bit (Master Only)
     * |        |          |0 = Automatic slave selection function Disabled
     * |        |          |Slave selection signal will be asserted/de-asserted according to SS (QSPIx_SSCTL[0]).
     * |        |          |1 = Automatic slave selection function Enabled.
     * |[4]     |SLV3WIRE  |Slave 3-wire Mode Enable Bit (Only Supported in QSPI0)
     * |        |          |Slave 3-wire mode is only available in QSPI0
     * |        |          |In Slave 3-wire mode, the QSPI controller can work with 3-wire interface including QSPI0_CLK, QSPI0_MISO and QSPI0_MOSI pins.
     * |        |          |0 = 4-wire bi-direction interface.
     * |        |          |1 = 3-wire bi-direction interface.
     * |[5]     |SLVTOIEN  |Slave Mode Time-out Interrupt Enable Bit (Only Supported in QSPI0)
     * |        |          |0 = Slave mode time-out interrupt Disabled.
     * |        |          |1 = Slave mode time-out interrupt Enabled.
     * |[6]     |SLVTORST  |Slave Mode Time-out Reset Control (Only Supported in QSPI0)
     * |        |          |0 = When Slave mode time-out event occurs, the TX and RX control circuit will not be reset.
     * |        |          |1 = When Slave mode time-out event occurs, the TX and RX control circuit will be reset by hardware.
     * |[8]     |SLVBEIEN  |Slave Mode Bit Count Error Interrupt Enable Bit
     * |        |          |0 = Slave mode bit count error interrupt Disabled.
     * |        |          |1 = Slave mode bit count error interrupt Enabled.
     * |[9]     |SLVURIEN  |Slave Mode TX Under Run Interrupt Enable Bit
     * |        |          |0 = Slave mode TX under run interrupt Disabled.
     * |        |          |1 = Slave mode TX under run interrupt Enabled.
     * |[12]    |SSACTIEN  |Slave Select Active Interrupt Enable Bit
     * |        |          |0 = Slave select active interrupt Disabled.
     * |        |          |1 = Slave select active interrupt Enabled.
     * |[13]    |SSINAIEN  |Slave Select Inactive Interrupt Enable Bit
     * |        |          |0 = Slave select inactive interrupt Disabled.
     * |        |          |1 = Slave select inactive interrupt Enabled.
     * |[31:16] |SLVTOCNT  |Slave Mode Time-out Period (Only Supported in QSPI0)
     * |        |          |In Slave mode, these bits indicate the time-out period when there is bus clock input during slave select active
     * |        |          |The clock source of the time-out counter is Slave peripheral clock
     * |        |          |If the value is 0, it indicates the slave mode time-out function is disabled.
     * @var QSPI_T::PDMACTL
     * Offset: 0x0C  QSPI PDMA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TXPDMAEN  |Transmit PDMA Enable Bit
     * |        |          |0 = Transmit PDMA function Disabled.
     * |        |          |1 = Transmit PDMA function Enabled.
     * |        |          |Note: In QSPI Master mode with full duplex transfer, if both TX and RX PDMA functions are enabled, RX PDMA function cannot be enabled prior to TX PDMA function
     * |        |          |User can enable TX PDMA function firstly or enable both functions simultaneously.
     * |[1]     |RXPDMAEN  |Receive PDMA Enable Bit
     * |        |          |0 = Receive PDMA function Disabled.
     * |        |          |1 = Receive PDMA function Enabled.
     * |[2]     |PDMARST   |PDMA Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset the PDMA control logic of the QSPI controller. This bit will be automatically cleared to 0.
     * @var QSPI_T::FIFOCTL
     * Offset: 0x10  QSPI FIFO Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RXRST     |Receive Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset receive FIFO pointer and receive circuit
     * |        |          |The RXFULL bit will be cleared to 0 and the RXEMPTY bit will be set to 1
     * |        |          |This bit will be cleared to 0 by hardware about 3 system clock cycles + 2 peripheral clock cycles after it is set to 1
     * |        |          |User can read TXRXRST (QSPIx_STATUS[23]) to check if reset is accomplished or not.
     * |[1]     |TXRST     |Transmit Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset transmit FIFO pointer and transmit circuit
     * |        |          |The TXFULL bit will be cleared to 0 and the TXEMPTY bit will be set to 1
     * |        |          |This bit will be cleared to 0 by hardware about 3 system clock cycles + 2 peripheral clock cycles after it is set to 1
     * |        |          |User can read TXRXRST (QSPIx_STATUS[23]) to check if reset is accomplished or not.
     * |        |          |Note: If TX underflow event occurs in QSPI Slave mode, this bit can be used to make QSPI return to idle state.
     * |[2]     |RXTHIEN   |Receive FIFO Threshold Interrupt Enable Bit
     * |        |          |0 = RX FIFO threshold interrupt Disabled.
     * |        |          |1 = RX FIFO threshold interrupt Enabled.
     * |[3]     |TXTHIEN   |Transmit FIFO Threshold Interrupt Enable Bit
     * |        |          |0 = TX FIFO threshold interrupt Disabled.
     * |        |          |1 = TX FIFO threshold interrupt Enabled.
     * |[4]     |RXTOIEN   |Slave Receive Time-out Interrupt Enable Bit
     * |        |          |0 = Receive time-out interrupt Disabled.
     * |        |          |1 = Receive time-out interrupt Enabled.
     * |[5]     |RXOVIEN   |Receive FIFO Overrun Interrupt Enable Bit
     * |        |          |0 = Receive FIFO overrun interrupt Disabled.
     * |        |          |1 = Receive FIFO overrun interrupt Enabled.
     * |[6]     |TXUFPOL   |TX Underflow Data Polarity
     * |        |          |0 = The QSPI data out is keep 0 if there is TX underflow event in Slave mode.
     * |        |          |1 = The QSPI data out is keep 1 if there is TX underflow event in Slave mode.
     * |        |          |Note:
     * |        |          |1. The TX underflow event occurs if there is no any data in TX FIFO when the slave selection signal is active.
     * |        |          |2. When TX underflow event occurs, QSPIx_MISO pin state will be determined by this setting even though TX FIFO is not empty afterward
     * |        |          |Data stored in TX FIFO will be sent through QSPIx_MISO pin in the next transfer frame.
     * |[7]     |TXUFIEN   |TX Underflow Interrupt Enable Bit
     * |        |          |When TX underflow event occurs in Slave mode, TXUFIF (QSPIx_STATUS[19]) will be set to 1
     * |        |          |This bit is used to enable the TX underflow interrupt.
     * |        |          |0 = Slave TX underflow interrupt Disabled.
     * |        |          |1 = Slave TX underflow interrupt Enabled.
     * |[8]     |RXFBCLR   |Receive FIFO Buffer Clear
     * |        |          |0 = No effect.
     * |        |          |1 = Clear receive FIFO pointer
     * |        |          |The RXFULL bit will be cleared to 0 and the RXEMPTY bit will be set to 1
     * |        |          |This bit will be cleared to 0 by hardware about 1 system clock after it is set to 1.
     * |        |          |Note: The RX shift register will not be cleared.
     * |[9]     |TXFBCLR   |Transmit FIFO Buffer Clear
     * |        |          |0 = No effect.
     * |        |          |1 = Clear transmit FIFO pointer
     * |        |          |The TXFULL bit will be cleared to 0 and the TXEMPTY bit will be set to 1
     * |        |          |This bit will be cleared to 0 by hardware about 1 system clock after it is set to 1.
     * |        |          |Note: The TX shift register will not be cleared.
     * |[26:24] |RXTH      |Receive FIFO Threshold
     * |        |          |If the valid data count of the receive FIFO buffer is larger than the RXTH setting, the RXTHIF bit will be set to 1, else the RXTHIF bit will be cleared to 0
     * |[30:28] |TXTH      |Transmit FIFO Threshold
     * |        |          |If the valid data count of the transmit FIFO buffer is less than or equal to the TXTH setting, the TXTHIF bit will be set to 1, else the TXTHIF bit will be cleared to 0
     * @var QSPI_T::STATUS
     * Offset: 0x14  QSPI Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |Busy Status (Read Only)
     * |        |          |0 = QSPI controller is in idle state.
     * |        |          |1 = QSPI controller is in busy state.
     * |        |          |The following listing are the bus busy conditions:
     * |        |          |a. QSPIx_CTL[0] = 1 and TXEMPTY = 0.
     * |        |          |b
     * |        |          |For QSPI Master mode, QSPIx_CTL[0] = 1 and TXEMPTY = 1 but the current transaction is not finished yet.
     * |        |          |c. For QSPI Master mode, QSPIx_CTL[0] = 1 and RXONLY = 1.
     * |        |          |d
     * |        |          |For QSPI Slave mode, the QSPIx_CTL[0] = 1 and there is serial clock input into the QSPI core logic when slave select is active.
     * |        |          |For QSPI Slave mode, the QSPIx_CTL[0] = 1 and the transmit buffer or transmit shift register is not empty even if the slave select is inactive.
     * |[1]     |UNITIF    |Unit Transfer Interrupt Flag
     * |        |          |0 = No transaction has been finished since this bit was cleared to 0.
     * |        |          |1 = QSPI controller has finished one unit transfer.
     * |        |          |Note: This bit will be cleared by writing 1 to it.
     * |[2]     |SSACTIF   |Slave Select Active Interrupt Flag
     * |        |          |0 = Slave select active interrupt was cleared or not occurred.
     * |        |          |1 = Slave select active interrupt event occurred.
     * |        |          |Note: Only available in Slave mode. This bit will be cleared by writing 1 to it.
     * |[3]     |SSINAIF   |Slave Select Inactive Interrupt Flag
     * |        |          |0 = Slave select inactive interrupt was cleared or not occurred.
     * |        |          |1 = Slave select inactive interrupt event occurred.
     * |        |          |Note: Only available in Slave mode. This bit will be cleared by writing 1 to it.
     * |[4]     |SSLINE    |Slave Select Line Bus Status (Read Only)
     * |        |          |0 = The slave select line status is 0.
     * |        |          |1 = The slave select line status is 1.
     * |        |          |Note: This bit is only available in Slave mode
     * |        |          |If SSACTPOL (QSPIx_SSCTL[2]) is set 0, and the SSLINE is 1, the QSPI slave select is in inactive status.
     * |[5]     |SLVTOIF   |Slave Time-out Interrupt Flag (Only Supported in QSPI0)
     * |        |          |When the slave select is active and the value of SLVTOCNT is not 0, as the bus clock is detected, the slave time-out counter in QSPI controller logic will be started
     * |        |          |When the value of time-out counter is greater than or equal to the value of SLVTOCNT (QSPI_SSCTL[31:16]) before one transaction is done, the slave time-out interrupt event will be asserted.
     * |        |          |0 = Slave time-out is not active.
     * |        |          |1 = Slave time-out is active.
     * |        |          |Note: This bit will be cleared by writing 1 to it.
     * |[6]     |SLVBEIF   |Slave Mode Bit Count Error Interrupt Flag
     * |        |          |In Slave mode, when the slave select line goes to inactive state, if bit counter is mismatch with DWIDTH, this interrupt flag will be set to 1.
     * |        |          |0 = No Slave mode bit count error event.
     * |        |          |1 = Slave mode bit count error event occurs.
     * |        |          |Note: If the slave select active but there is no any bus clock input, the SLVBEIF also active when the slave select goes to inactive state
     * |        |          |This bit will be cleared by writing 1 to it.
     * |[7]     |SLVURIF   |Slave Mode TX Under Run Interrupt Flag
     * |        |          |In Slave mode, if TX underflow event occurs and the slave select line goes to inactive state, this interrupt flag will be set to 1.
     * |        |          |0 = No Slave TX under run event.
     * |        |          |1 = Slave TX under run event occurs.
     * |        |          |Note: This bit will be cleared by writing 1 to it.
     * |[8]     |RXEMPTY   |Receive FIFO Buffer Empty Indicator (Read Only)
     * |        |          |0 = Receive FIFO buffer is not empty.
     * |        |          |1 = Receive FIFO buffer is empty.
     * |[9]     |RXFULL    |Receive FIFO Buffer Full Indicator (Read Only)
     * |        |          |0 = Receive FIFO buffer is not full.
     * |        |          |1 = Receive FIFO buffer is full.
     * |[10]    |RXTHIF    |Receive FIFO Threshold Interrupt Flag (Read Only)
     * |        |          |0 = The valid data count within the receive FIFO buffer is smaller than or equal to the setting value of RXTH.
     * |        |          |1 = The valid data count within the receive FIFO buffer is larger than the setting value of RXTH.
     * |[11]    |RXOVIF    |Receive FIFO Overrun Interrupt Flag
     * |        |          |When the receive FIFO buffer is full, the follow-up data will be dropped and this bit will be set to 1.
     * |        |          |0 = No FIFO is overrun.
     * |        |          |1 = Receive FIFO is overrun.
     * |        |          |Note: This bit will be cleared by writing 1 to it.
     * |[12]    |RXTOIF    |Receive Time-out Interrupt Flag
     * |        |          |0 = No receive FIFO time-out event.
     * |        |          |1 = Receive FIFO buffer is not empty and no read operation on receive FIFO buffer over 64 QSPI peripheral clock periods in Master mode or over 576 QSPI peripheral clock periods in Slave mode
     * |        |          |When the received FIFO buffer is read by software, the time-out status will be cleared automatically.
     * |        |          |Note: This bit will be cleared by writing 1 to it.
     * |[15]    |QSPIENSTS |QSPI Enable Status (Read Only)
     * |        |          |0 = The QSPI controller is disabled.
     * |        |          |1 = The QSPI controller is enabled.
     * |        |          |Note: The QSPI peripheral clock is asynchronous with the system clock
     * |        |          |In order to make sure the QSPI control logic is disabled, this bit indicates the real status of QSPI controller.
     * |[16]    |TXEMPTY   |Transmit FIFO Buffer Empty Indicator (Read Only)
     * |        |          |0 = Transmit FIFO buffer is not empty.
     * |        |          |1 = Transmit FIFO buffer is empty.
     * |[17]    |TXFULL    |Transmit FIFO Buffer Full Indicator (Read Only)
     * |        |          |0 = Transmit FIFO buffer is not full.
     * |        |          |1 = Transmit FIFO buffer is full.
     * |[18]    |TXTHIF    |Transmit FIFO Threshold Interrupt Flag (Read Only)
     * |        |          |0 = The valid data count within the transmit FIFO buffer is larger than the setting value of TXTH.
     * |        |          |1 = The valid data count within the transmit FIFO buffer is less than or equal to the setting value of TXTH.
     * |[19]    |TXUFIF    |TX Underflow Interrupt Flag
     * |        |          |When the TX underflow event occurs, this bit will be set to 1, the state of data output pin depends on the setting of TXUFPOL.
     * |        |          |0 = No effect.
     * |        |          |1 = No data in Transmit FIFO and TX shift register when the slave selection signal is active.
     * |        |          |Note 1: This bit will be cleared by writing 1 to it.
     * |        |          |Note 2: If reset slave's transmission circuit when slave selection signal is active, this flag will be set to 1 after 2 peripheral clock cycles + 3 system clock cycles since the reset operation is done.
     * |[23]    |TXRXRST   |TX or RX Reset Status (Read Only)
     * |        |          |0 = The reset function of TXRST or RXRST is done.
     * |        |          |1 = Doing the reset function of TXRST or RXRST.
     * |        |          |Note: Both the reset operations of TXRST and RXRST need 3 system clock cycles + 2 peripheral clock cycles
     * |        |          |User can check the status of this bit to monitor the reset function is doing or done.
     * |[27:24] |RXCNT     |Receive FIFO Data Count (Read Only)
     * |        |          |This bit field indicates the valid data count of receive FIFO buffer.
     * |[31:28] |TXCNT     |Transmit FIFO Data Count (Read Only)
     * |        |          |This bit field indicates the valid data count of transmit FIFO buffer.
     * @var QSPI_T::TX
     * Offset: 0x20  QSPI Data Transmit Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |TX        |Data Transmit Register
     * |        |          |The data transmit registers pass through the transmitted data into the 4-level transmit FIFO buffers
     * |        |          |The number of valid bits depends on the setting of DWIDTH (QSPIx_CTL[12:8]) in SPI mode.
     * |        |          |In SPI mode, if DWIDTH is set to 0x08, the bits TX[7:0] will be transmitted
     * |        |          |If DWIDTH is set to 0x00 , the QSPI controller will perform a 32-bit transfer.
     * |        |          |If WDWIDTH is set as 0x0, 0x1, or 0x3, all bits of this field are valid
     * |        |          |Note: In Master mode, QSPI controller will start to transfer the QSPI bus clock after 1 APB clock and 6 peripheral clock cycles after user writes to this register.
     * @var QSPI_T::RX
     * Offset: 0x30  QSPI Data Receive Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RX        |Data Receive Register
     * |        |          |There are 4-level FIFO buffers in this controller
     * |        |          |The data receive register holds the data received from QSPI data input pin
     * |        |          |This is a read only register.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] QSPI Control Register                                             */
    __IO uint32_t CLKDIV;                /*!< [0x0004] QSPI Clock Divider Register                                       */
    __IO uint32_t SSCTL;                 /*!< [0x0008] QSPI Slave Select Control Register                                */
    __IO uint32_t PDMACTL;               /*!< [0x000c] QSPI PDMA Control Register                                        */
    __IO uint32_t FIFOCTL;               /*!< [0x0010] QSPI FIFO Control Register                                        */
    __IO uint32_t STATUS;                /*!< [0x0014] QSPI Status Register                                              */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[2];
    /// @endcond //HIDDEN_SYMBOLS
    __O  uint32_t TX;                    /*!< [0x0020] QSPI Data Transmit Register                                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[3];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t RX;                    /*!< [0x0030] QSPI Data Receive Register                                        */

} QSPI_T;

/**
    @addtogroup QSPI_CONST QSPI Bit Field Definition
    Constant Definitions for QSPI Controller
@{ */

#define QSPI_CTL_QSPIEN_Pos               (0)                                                /*!< QSPI_T::CTL: QSPIEN Position             */
#define QSPI_CTL_QSPIEN_Msk               (0x1ul << QSPI_CTL_QSPIEN_Pos)                     /*!< QSPI_T::CTL: QSPIEN Mask                 */

#define QSPI_CTL_RXNEG_Pos                (1)                                                /*!< QSPI_T::CTL: RXNEG Position             */
#define QSPI_CTL_RXNEG_Msk                (0x1ul << QSPI_CTL_RXNEG_Pos)                      /*!< QSPI_T::CTL: RXNEG Mask                 */

#define QSPI_CTL_TXNEG_Pos                (2)                                                /*!< QSPI_T::CTL: TXNEG Position             */
#define QSPI_CTL_TXNEG_Msk                (0x1ul << QSPI_CTL_TXNEG_Pos)                      /*!< QSPI_T::CTL: TXNEG Mask                 */

#define QSPI_CTL_CLKPOL_Pos               (3)                                                /*!< QSPI_T::CTL: CLKPOL Position            */
#define QSPI_CTL_CLKPOL_Msk               (0x1ul << QSPI_CTL_CLKPOL_Pos)                     /*!< QSPI_T::CTL: CLKPOL Mask                */

#define QSPI_CTL_SUSPITV_Pos              (4)                                                /*!< QSPI_T::CTL: SUSPITV Position           */
#define QSPI_CTL_SUSPITV_Msk              (0xful << QSPI_CTL_SUSPITV_Pos)                    /*!< QSPI_T::CTL: SUSPITV Mask               */

#define QSPI_CTL_DWIDTH_Pos               (8)                                                /*!< QSPI_T::CTL: DWIDTH Position            */
#define QSPI_CTL_DWIDTH_Msk               (0x1ful << QSPI_CTL_DWIDTH_Pos)                    /*!< QSPI_T::CTL: DWIDTH Mask                */

#define QSPI_CTL_LSB_Pos                  (13)                                               /*!< QSPI_T::CTL: LSB Position               */
#define QSPI_CTL_LSB_Msk                  (0x1ul << QSPI_CTL_LSB_Pos)                        /*!< QSPI_T::CTL: LSB Mask                   */

#define QSPI_CTL_HALFDPX_Pos              (14)                                               /*!< QSPI_T::CTL: HALFDPX Position           */
#define QSPI_CTL_HALFDPX_Msk              (0x1ul << QSPI_CTL_HALFDPX_Pos)                    /*!< QSPI_T::CTL: HALFDPX Mask               */

#define QSPI_CTL_RXONLY_Pos               (15)                                               /*!< QSPI_T::CTL: RXONLY Position            */
#define QSPI_CTL_RXONLY_Msk               (0x1ul << QSPI_CTL_RXONLY_Pos)                     /*!< QSPI_T::CTL: RXONLY Mask                */

#define QSPI_CTL_TWOBIT_Pos               (16)                                               /*!< QSPI_T::CTL: TWOBIT Position            */
#define QSPI_CTL_TWOBIT_Msk               (0x1ul << QSPI_CTL_TWOBIT_Pos)                     /*!< QSPI_T::CTL: TWOBIT Mask                */

#define QSPI_CTL_UNITIEN_Pos              (17)                                               /*!< QSPI_T::CTL: UNITIEN Position           */
#define QSPI_CTL_UNITIEN_Msk              (0x1ul << QSPI_CTL_UNITIEN_Pos)                    /*!< QSPI_T::CTL: UNITIEN Mask               */

#define QSPI_CTL_SLAVE_Pos                (18)                                               /*!< QSPI_T::CTL: SLAVE Position             */
#define QSPI_CTL_SLAVE_Msk                (0x1ul << QSPI_CTL_SLAVE_Pos)                      /*!< QSPI_T::CTL: SLAVE Mask                 */

#define QSPI_CTL_REORDER_Pos              (19)                                               /*!< QSPI_T::CTL: REORDER Position           */
#define QSPI_CTL_REORDER_Msk              (0x1ul << QSPI_CTL_REORDER_Pos)                    /*!< QSPI_T::CTL: REORDER Mask               */

#define QSPI_CTL_DATDIR_Pos               (20)                                               /*!< QSPI_T::CTL: DATDIR Position            */
#define QSPI_CTL_DATDIR_Msk               (0x1ul << QSPI_CTL_DATDIR_Pos)                     /*!< QSPI_T::CTL: DATDIR Mask                */

#define QSPI_CTL_DUALIOEN_Pos             (21)                                               /*!< QSPI_T::CTL: DUALIOEN Position          */
#define QSPI_CTL_DUALIOEN_Msk             (0x1ul << QSPI_CTL_DUALIOEN_Pos)                   /*!< QSPI_T::CTL: DUALIOEN Mask              */

#define QSPI_CTL_QUADIOEN_Pos             (22)                                               /*!< QSPI_T::CTL: QUADIOEN Position          */
#define QSPI_CTL_QUADIOEN_Msk             (0x1ul << QSPI_CTL_QUADIOEN_Pos)                   /*!< QSPI_T::CTL: QUADIOEN Mask              */

#define QSPI_CLKDIV_DIVIDER_Pos           (0)                                                /*!< QSPI_T::CLKDIV: DIVIDER Position        */
#define QSPI_CLKDIV_DIVIDER_Msk           (0x1fful << QSPI_CLKDIV_DIVIDER_Pos)               /*!< QSPI_T::CLKDIV: DIVIDER Mask            */

#define QSPI_SSCTL_SS_Pos                 (0)                                                /*!< QSPI_T::SSCTL: SS Position              */
#define QSPI_SSCTL_SS_Msk                 (0x1ul << QSPI_SSCTL_SS_Pos)                       /*!< QSPI_T::SSCTL: SS Mask                  */

#define QSPI_SSCTL_SSACTPOL_Pos           (2)                                                /*!< QSPI_T::SSCTL: SSACTPOL Position        */
#define QSPI_SSCTL_SSACTPOL_Msk           (0x1ul << QSPI_SSCTL_SSACTPOL_Pos)                 /*!< QSPI_T::SSCTL: SSACTPOL Mask            */

#define QSPI_SSCTL_AUTOSS_Pos             (3)                                                /*!< QSPI_T::SSCTL: AUTOSS Position          */
#define QSPI_SSCTL_AUTOSS_Msk             (0x1ul << QSPI_SSCTL_AUTOSS_Pos)                   /*!< QSPI_T::SSCTL: AUTOSS Mask              */

#define QSPI_SSCTL_SLV3WIRE_Pos           (4)                                                /*!< QSPI_T::SSCTL: SLV3WIRE Position        */
#define QSPI_SSCTL_SLV3WIRE_Msk           (0x1ul << QSPI_SSCTL_SLV3WIRE_Pos)                 /*!< QSPI_T::SSCTL: SLV3WIRE Mask            */

#define QSPI_SSCTL_SLVTOIEN_Pos           (5)                                                /*!< QSPI_T::SSCTL: SLVTOIEN Position        */
#define QSPI_SSCTL_SLVTOIEN_Msk           (0x1ul << QSPI_SSCTL_SLVTOIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVTOIEN Mask            */

#define QSPI_SSCTL_SLVTORST_Pos           (6)                                                /*!< QSPI_T::SSCTL: SLVTORST Position        */
#define QSPI_SSCTL_SLVTORST_Msk           (0x1ul << QSPI_SSCTL_SLVTORST_Pos)                 /*!< QSPI_T::SSCTL: SLVTORST Mask            */

#define QSPI_SSCTL_SLVBEIEN_Pos           (8)                                                /*!< QSPI_T::SSCTL: SLVBEIEN Position        */
#define QSPI_SSCTL_SLVBEIEN_Msk           (0x1ul << QSPI_SSCTL_SLVBEIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVBEIEN Mask            */

#define QSPI_SSCTL_SLVURIEN_Pos           (9)                                                /*!< QSPI_T::SSCTL: SLVURIEN Position        */
#define QSPI_SSCTL_SLVURIEN_Msk           (0x1ul << QSPI_SSCTL_SLVURIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVURIEN Mask            */

#define QSPI_SSCTL_SSACTIEN_Pos           (12)                                               /*!< QSPI_T::SSCTL: SSACTIEN Position        */
#define QSPI_SSCTL_SSACTIEN_Msk           (0x1ul << QSPI_SSCTL_SSACTIEN_Pos)                 /*!< QSPI_T::SSCTL: SSACTIEN Mask            */

#define QSPI_SSCTL_SSINAIEN_Pos           (13)                                               /*!< QSPI_T::SSCTL: SSINAIEN Position        */
#define QSPI_SSCTL_SSINAIEN_Msk           (0x1ul << QSPI_SSCTL_SSINAIEN_Pos)                 /*!< QSPI_T::SSCTL: SSINAIEN Mask            */

#define QSPI_SSCTL_SLVTOCNT_Pos           (16)                                               /*!< QSPI_T::SSCTL: SLVTOCNT Position        */
#define QSPI_SSCTL_SLVTOCNT_Msk           (0xfffful << QSPI_SSCTL_SLVTOCNT_Pos)              /*!< QSPI_T::SSCTL: SLVTOCNT Mask            */

#define QSPI_PDMACTL_TXPDMAEN_Pos         (0)                                                /*!< QSPI_T::PDMACTL: TXPDMAEN Position      */
#define QSPI_PDMACTL_TXPDMAEN_Msk         (0x1ul << QSPI_PDMACTL_TXPDMAEN_Pos)               /*!< QSPI_T::PDMACTL: TXPDMAEN Mask          */

#define QSPI_PDMACTL_RXPDMAEN_Pos         (1)                                                /*!< QSPI_T::PDMACTL: RXPDMAEN Position      */
#define QSPI_PDMACTL_RXPDMAEN_Msk         (0x1ul << QSPI_PDMACTL_RXPDMAEN_Pos)               /*!< QSPI_T::PDMACTL: RXPDMAEN Mask          */

#define QSPI_PDMACTL_PDMARST_Pos          (2)                                                /*!< QSPI_T::PDMACTL: PDMARST Position       */
#define QSPI_PDMACTL_PDMARST_Msk          (0x1ul << QSPI_PDMACTL_PDMARST_Pos)                /*!< QSPI_T::PDMACTL: PDMARST Mask           */

#define QSPI_FIFOCTL_RXRST_Pos            (0)                                                /*!< QSPI_T::FIFOCTL: RXRST Position         */
#define QSPI_FIFOCTL_RXRST_Msk            (0x1ul << QSPI_FIFOCTL_RXRST_Pos)                  /*!< QSPI_T::FIFOCTL: RXRST Mask             */

#define QSPI_FIFOCTL_TXRST_Pos            (1)                                                /*!< QSPI_T::FIFOCTL: TXRST Position         */
#define QSPI_FIFOCTL_TXRST_Msk            (0x1ul << QSPI_FIFOCTL_TXRST_Pos)                  /*!< QSPI_T::FIFOCTL: TXRST Mask             */

#define QSPI_FIFOCTL_RXTHIEN_Pos          (2)                                                /*!< QSPI_T::FIFOCTL: RXTHIEN Position       */
#define QSPI_FIFOCTL_RXTHIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXTHIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXTHIEN Mask           */

#define QSPI_FIFOCTL_TXTHIEN_Pos          (3)                                                /*!< QSPI_T::FIFOCTL: TXTHIEN Position       */
#define QSPI_FIFOCTL_TXTHIEN_Msk          (0x1ul << QSPI_FIFOCTL_TXTHIEN_Pos)                /*!< QSPI_T::FIFOCTL: TXTHIEN Mask           */

#define QSPI_FIFOCTL_RXTOIEN_Pos          (4)                                                /*!< QSPI_T::FIFOCTL: RXTOIEN Position       */
#define QSPI_FIFOCTL_RXTOIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXTOIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXTOIEN Mask           */

#define QSPI_FIFOCTL_RXOVIEN_Pos          (5)                                                /*!< QSPI_T::FIFOCTL: RXOVIEN Position       */
#define QSPI_FIFOCTL_RXOVIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXOVIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXOVIEN Mask           */

#define QSPI_FIFOCTL_TXUFPOL_Pos          (6)                                                /*!< QSPI_T::FIFOCTL: TXUFPOL Position       */
#define QSPI_FIFOCTL_TXUFPOL_Msk          (0x1ul << QSPI_FIFOCTL_TXUFPOL_Pos)                /*!< QSPI_T::FIFOCTL: TXUFPOL Mask           */

#define QSPI_FIFOCTL_TXUFIEN_Pos          (7)                                                /*!< QSPI_T::FIFOCTL: TXUFIEN Position       */
#define QSPI_FIFOCTL_TXUFIEN_Msk          (0x1ul << QSPI_FIFOCTL_TXUFIEN_Pos)                /*!< QSPI_T::FIFOCTL: TXUFIEN Mask           */

#define QSPI_FIFOCTL_RXFBCLR_Pos          (8)                                                /*!< QSPI_T::FIFOCTL: RXFBCLR Position       */
#define QSPI_FIFOCTL_RXFBCLR_Msk          (0x1ul << QSPI_FIFOCTL_RXFBCLR_Pos)                /*!< QSPI_T::FIFOCTL: RXFBCLR Mask           */

#define QSPI_FIFOCTL_TXFBCLR_Pos          (9)                                                /*!< QSPI_T::FIFOCTL: TXFBCLR Position       */
#define QSPI_FIFOCTL_TXFBCLR_Msk          (0x1ul << QSPI_FIFOCTL_TXFBCLR_Pos)                /*!< QSPI_T::FIFOCTL: TXFBCLR Mask           */

#define QSPI_FIFOCTL_RXTH_Pos             (24)                                               /*!< QSPI_T::FIFOCTL: RXTH Position          */
#define QSPI_FIFOCTL_RXTH_Msk             (0x7ul << QSPI_FIFOCTL_RXTH_Pos)                   /*!< QSPI_T::FIFOCTL: RXTH Mask              */

#define QSPI_FIFOCTL_TXTH_Pos             (28)                                               /*!< QSPI_T::FIFOCTL: TXTH Position          */
#define QSPI_FIFOCTL_TXTH_Msk             (0x7ul << QSPI_FIFOCTL_TXTH_Pos)                   /*!< QSPI_T::FIFOCTL: TXTH Mask              */

#define QSPI_STATUS_BUSY_Pos              (0)                                                /*!< QSPI_T::STATUS: BUSY Position           */
#define QSPI_STATUS_BUSY_Msk              (0x1ul << QSPI_STATUS_BUSY_Pos)                    /*!< QSPI_T::STATUS: BUSY Mask               */

#define QSPI_STATUS_UNITIF_Pos            (1)                                                /*!< QSPI_T::STATUS: UNITIF Position         */
#define QSPI_STATUS_UNITIF_Msk            (0x1ul << QSPI_STATUS_UNITIF_Pos)                  /*!< QSPI_T::STATUS: UNITIF Mask             */

#define QSPI_STATUS_SSACTIF_Pos           (2)                                                /*!< QSPI_T::STATUS: SSACTIF Position        */
#define QSPI_STATUS_SSACTIF_Msk           (0x1ul << QSPI_STATUS_SSACTIF_Pos)                 /*!< QSPI_T::STATUS: SSACTIF Mask            */

#define QSPI_STATUS_SSINAIF_Pos           (3)                                                /*!< QSPI_T::STATUS: SSINAIF Position        */
#define QSPI_STATUS_SSINAIF_Msk           (0x1ul << QSPI_STATUS_SSINAIF_Pos)                 /*!< QSPI_T::STATUS: SSINAIF Mask            */

#define QSPI_STATUS_SSLINE_Pos            (4)                                                /*!< QSPI_T::STATUS: SSLINE Position         */
#define QSPI_STATUS_SSLINE_Msk            (0x1ul << QSPI_STATUS_SSLINE_Pos)                  /*!< QSPI_T::STATUS: SSLINE Mask             */

#define QSPI_STATUS_SLVTOIF_Pos           (5)                                                /*!< QSPI_T::STATUS: SLVTOIF Position        */
#define QSPI_STATUS_SLVTOIF_Msk           (0x1ul << QSPI_STATUS_SLVTOIF_Pos)                 /*!< QSPI_T::STATUS: SLVTOIF Mask            */

#define QSPI_STATUS_SLVBEIF_Pos           (6)                                                /*!< QSPI_T::STATUS: SLVBEIF Position        */
#define QSPI_STATUS_SLVBEIF_Msk           (0x1ul << QSPI_STATUS_SLVBEIF_Pos)                 /*!< QSPI_T::STATUS: SLVBEIF Mask            */

#define QSPI_STATUS_SLVURIF_Pos           (7)                                                /*!< QSPI_T::STATUS: SLVURIF Position        */
#define QSPI_STATUS_SLVURIF_Msk           (0x1ul << QSPI_STATUS_SLVURIF_Pos)                 /*!< QSPI_T::STATUS: SLVURIF Mask            */

#define QSPI_STATUS_RXEMPTY_Pos           (8)                                                /*!< QSPI_T::STATUS: RXEMPTY Position        */
#define QSPI_STATUS_RXEMPTY_Msk           (0x1ul << QSPI_STATUS_RXEMPTY_Pos)                 /*!< QSPI_T::STATUS: RXEMPTY Mask            */

#define QSPI_STATUS_RXFULL_Pos            (9)                                                /*!< QSPI_T::STATUS: RXFULL Position         */
#define QSPI_STATUS_RXFULL_Msk            (0x1ul << QSPI_STATUS_RXFULL_Pos)                  /*!< QSPI_T::STATUS: RXFULL Mask             */

#define QSPI_STATUS_RXTHIF_Pos            (10)                                               /*!< QSPI_T::STATUS: RXTHIF Position         */
#define QSPI_STATUS_RXTHIF_Msk            (0x1ul << QSPI_STATUS_RXTHIF_Pos)                  /*!< QSPI_T::STATUS: RXTHIF Mask             */

#define QSPI_STATUS_RXOVIF_Pos            (11)                                               /*!< QSPI_T::STATUS: RXOVIF Position         */
#define QSPI_STATUS_RXOVIF_Msk            (0x1ul << QSPI_STATUS_RXOVIF_Pos)                  /*!< QSPI_T::STATUS: RXOVIF Mask             */

#define QSPI_STATUS_RXTOIF_Pos            (12)                                               /*!< QSPI_T::STATUS: RXTOIF Position         */
#define QSPI_STATUS_RXTOIF_Msk            (0x1ul << QSPI_STATUS_RXTOIF_Pos)                  /*!< QSPI_T::STATUS: RXTOIF Mask             */

#define QSPI_STATUS_QSPIENSTS_Pos          (15)                                              /*!< QSPI_T::STATUS: QSPIENSTS Position       */
#define QSPI_STATUS_QSPIENSTS_Msk          (0x1ul << QSPI_STATUS_QSPIENSTS_Pos)              /*!< QSPI_T::STATUS: QSPIENSTS Mask           */

#define QSPI_STATUS_TXEMPTY_Pos           (16)                                               /*!< QSPI_T::STATUS: TXEMPTY Position        */
#define QSPI_STATUS_TXEMPTY_Msk           (0x1ul << QSPI_STATUS_TXEMPTY_Pos)                 /*!< QSPI_T::STATUS: TXEMPTY Mask            */

#define QSPI_STATUS_TXFULL_Pos            (17)                                               /*!< QSPI_T::STATUS: TXFULL Position         */
#define QSPI_STATUS_TXFULL_Msk            (0x1ul << QSPI_STATUS_TXFULL_Pos)                  /*!< QSPI_T::STATUS: TXFULL Mask             */

#define QSPI_STATUS_TXTHIF_Pos            (18)                                               /*!< QSPI_T::STATUS: TXTHIF Position         */
#define QSPI_STATUS_TXTHIF_Msk            (0x1ul << QSPI_STATUS_TXTHIF_Pos)                  /*!< QSPI_T::STATUS: TXTHIF Mask             */

#define QSPI_STATUS_TXUFIF_Pos            (19)                                               /*!< QSPI_T::STATUS: TXUFIF Position         */
#define QSPI_STATUS_TXUFIF_Msk            (0x1ul << QSPI_STATUS_TXUFIF_Pos)                  /*!< QSPI_T::STATUS: TXUFIF Mask             */

#define QSPI_STATUS_TXRXRST_Pos           (23)                                               /*!< QSPI_T::STATUS: TXRXRST Position        */
#define QSPI_STATUS_TXRXRST_Msk           (0x1ul << QSPI_STATUS_TXRXRST_Pos)                 /*!< QSPI_T::STATUS: TXRXRST Mask            */

#define QSPI_STATUS_RXCNT_Pos             (24)                                               /*!< QSPI_T::STATUS: RXCNT Position          */
#define QSPI_STATUS_RXCNT_Msk             (0xful << QSPI_STATUS_RXCNT_Pos)                   /*!< QSPI_T::STATUS: RXCNT Mask              */

#define QSPI_STATUS_TXCNT_Pos             (28)                                               /*!< QSPI_T::STATUS: TXCNT Position          */
#define QSPI_STATUS_TXCNT_Msk             (0xful << QSPI_STATUS_TXCNT_Pos)                   /*!< QSPI_T::STATUS: TXCNT Mask              */

#define QSPI_TX_TX_Pos                    (0)                                                /*!< QSPI_T::TX: TX Position                 */
#define QSPI_TX_TX_Msk                    (0xfffffffful << QSPI_TX_TX_Pos)                   /*!< QSPI_T::TX: TX Mask                     */

#define QSPI_RX_RX_Pos                    (0)                                                /*!< QSPI_T::RX: RX Position                 */
#define QSPI_RX_RX_Msk                    (0xfffffffful << QSPI_RX_RX_Pos)                   /*!< QSPI_T::RX: RX Mask                     */


/**@}*/ /* QSPI_CONST */
/**@}*/ /* end of QSPI register group */
/**@}*/ /* end of REGISTER group */

#define QSPI0                  ((QSPI_T *)   QSPI0_BA)

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup QSPI_Driver QSPI Driver
  @{
*/

/** @addtogroup QSPI_EXPORTED_CONSTANTS QSPI Exported Constants
  @{
*/

#define QSPI_MODE_0        (QSPI_CTL_TXNEG_Msk)                             /*!< CLKPOL=0; RXNEG=0; TXNEG=1 \hideinitializer */
#define QSPI_MODE_1        (QSPI_CTL_RXNEG_Msk)                             /*!< CLKPOL=0; RXNEG=1; TXNEG=0 \hideinitializer */
#define QSPI_MODE_2        (QSPI_CTL_CLKPOL_Msk | QSPI_CTL_RXNEG_Msk)       /*!< CLKPOL=1; RXNEG=1; TXNEG=0 \hideinitializer */
#define QSPI_MODE_3        (QSPI_CTL_CLKPOL_Msk | QSPI_CTL_TXNEG_Msk)       /*!< CLKPOL=1; RXNEG=0; TXNEG=1 \hideinitializer */

#define QSPI_SLAVE         (QSPI_CTL_SLAVE_Msk)                             /*!< Set as slave \hideinitializer */
#define QSPI_MASTER        (0x0U)                                           /*!< Set as master \hideinitializer */

#define QSPI_SS                (QSPI_SSCTL_SS_Msk)                          /*!< Set SS \hideinitializer */
#define QSPI_SS_ACTIVE_HIGH    (QSPI_SSCTL_SSACTPOL_Msk)                    /*!< SS active high \hideinitializer */
#define QSPI_SS_ACTIVE_LOW     (0x0U)                                       /*!< SS active low \hideinitializer */

/* QSPI Interrupt Mask */
#define QSPI_UNIT_INT_MASK                (0x001U)                          /*!< Unit transfer interrupt mask \hideinitializer */
#define QSPI_SSACT_INT_MASK               (0x002U)                          /*!< Slave selection signal active interrupt mask \hideinitializer */
#define QSPI_SSINACT_INT_MASK             (0x004U)                          /*!< Slave selection signal inactive interrupt mask \hideinitializer */
#define QSPI_SLVUR_INT_MASK               (0x008U)                          /*!< Slave under run interrupt mask \hideinitializer */
#define QSPI_SLVBE_INT_MASK               (0x010U)                          /*!< Slave bit count error interrupt mask \hideinitializer */
#define QSPI_TXUF_INT_MASK                (0x040U)                          /*!< Slave TX underflow interrupt mask \hideinitializer */
#define QSPI_FIFO_TXTH_INT_MASK           (0x080U)                          /*!< FIFO TX threshold interrupt mask \hideinitializer */
#define QSPI_FIFO_RXTH_INT_MASK           (0x100U)                          /*!< FIFO RX threshold interrupt mask \hideinitializer */
#define QSPI_FIFO_RXOV_INT_MASK           (0x200U)                          /*!< FIFO RX overrun interrupt mask \hideinitializer */
#define QSPI_FIFO_RXTO_INT_MASK           (0x400U)                          /*!< FIFO RX time-out interrupt mask \hideinitializer */

/* QSPI Status Mask */
#define QSPI_BUSY_MASK                    (0x01U)                           /*!< Busy status mask \hideinitializer */
#define QSPI_RX_EMPTY_MASK                (0x02U)                           /*!< RX empty status mask \hideinitializer */
#define QSPI_RX_FULL_MASK                 (0x04U)                           /*!< RX full status mask \hideinitializer */
#define QSPI_TX_EMPTY_MASK                (0x08U)                           /*!< TX empty status mask \hideinitializer */
#define QSPI_TX_FULL_MASK                 (0x10U)                           /*!< TX full status mask \hideinitializer */
#define QSPI_TXRX_RESET_MASK              (0x20U)                           /*!< TX or RX reset status mask \hideinitializer */
#define QSPI_QSPIEN_STS_MASK              (0x40U)                           /*!< QSPIEN status mask \hideinitializer */
#define QSPI_SSLINE_STS_MASK              (0x80U)                           /*!< QSPIx_SS line status mask \hideinitializer */

/*@}*/ /* end of group QSPI_EXPORTED_CONSTANTS */


/** @addtogroup QSPI_EXPORTED_FUNCTIONS QSPI Exported Functions
  @{
*/

/**
  * @brief      Clear the unit transfer interrupt flag.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Write 1 to UNITIF bit of QSPI_STATUS register to clear the unit transfer interrupt flag.
  * \hideinitializer
  */
#define QSPI_CLR_UNIT_TRANS_INT_FLAG(qspi)   ((qspi)->STATUS = QSPI_STATUS_UNITIF_Msk)

/**
  * @brief      Trigger RX PDMA function.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Set RXPDMAEN bit of QSPI_PDMACTL register to enable RX PDMA transfer function.
  * \hideinitializer
  */
#define QSPI_TRIGGER_RX_PDMA(qspi)   ((qspi)->PDMACTL |= QSPI_PDMACTL_RXPDMAEN_Msk)

/**
  * @brief      Trigger TX PDMA function.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Set TXPDMAEN bit of QSPI_PDMACTL register to enable TX PDMA transfer function.
  * \hideinitializer
  */
#define QSPI_TRIGGER_TX_PDMA(qspi)   ((qspi)->PDMACTL |= QSPI_PDMACTL_TXPDMAEN_Msk)

/**
  * @brief      Disable RX PDMA transfer.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Clear RXPDMAEN bit of QSPI_PDMACTL register to disable RX PDMA transfer function.
  * \hideinitializer
  */
#define QSPI_DISABLE_RX_PDMA(qspi) ( (qspi)->PDMACTL &= ~QSPI_PDMACTL_RXPDMAEN_Msk )

/**
  * @brief      Disable TX PDMA transfer.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Clear TXPDMAEN bit of QSPI_PDMACTL register to disable TX PDMA transfer function.
  * \hideinitializer
  */
#define QSPI_DISABLE_TX_PDMA(qspi) ( (qspi)->PDMACTL &= ~QSPI_PDMACTL_TXPDMAEN_Msk )

/**
  * @brief      Get the count of available data in RX FIFO.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     The count of available data in RX FIFO.
  * @details    Read RXCNT (QSPI_STATUS[27:24]) to get the count of available data in RX FIFO.
  * \hideinitializer
  */
#define QSPI_GET_RX_FIFO_COUNT(qspi)   (((qspi)->STATUS & QSPI_STATUS_RXCNT_Msk) >> QSPI_STATUS_RXCNT_Pos)

/**
  * @brief      Get the RX FIFO empty flag.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @retval     0 RX FIFO is not empty.
  * @retval     1 RX FIFO is empty.
  * @details    Read RXEMPTY bit of QSPI_STATUS register to get the RX FIFO empty flag.
  * \hideinitializer
  */
#define QSPI_GET_RX_FIFO_EMPTY_FLAG(qspi)   (((qspi)->STATUS & QSPI_STATUS_RXEMPTY_Msk)>>QSPI_STATUS_RXEMPTY_Pos)

/**
  * @brief      Get the TX FIFO empty flag.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @retval     0 TX FIFO is not empty.
  * @retval     1 TX FIFO is empty.
  * @details    Read TXEMPTY bit of QSPI_STATUS register to get the TX FIFO empty flag.
  * \hideinitializer
  */
#define QSPI_GET_TX_FIFO_EMPTY_FLAG(qspi)   (((qspi)->STATUS & QSPI_STATUS_TXEMPTY_Msk)>>QSPI_STATUS_TXEMPTY_Pos)

/**
  * @brief      Get the TX FIFO full flag.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @retval     0 TX FIFO is not full.
  * @retval     1 TX FIFO is full.
  * @details    Read TXFULL bit of QSPI_STATUS register to get the TX FIFO full flag.
  * \hideinitializer
  */
#define QSPI_GET_TX_FIFO_FULL_FLAG(qspi)   (((qspi)->STATUS & QSPI_STATUS_TXFULL_Msk)>>QSPI_STATUS_TXFULL_Pos)

/**
  * @brief      Get the datum read from RX register.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     Data in RX register.
  * @details    Read QSPI_RX register to get the received datum.
  * \hideinitializer
  */
#define QSPI_READ_RX(qspi)   ((qspi)->RX)

/**
  * @brief      Write datum to TX register.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @param[in]  u32TxData The datum which user attempt to transfer through QSPI bus.
  * @return     None.
  * @details    Write u32TxData to QSPI_TX register.
  * \hideinitializer
  */
#define QSPI_WRITE_TX(qspi, u32TxData)   ((qspi)->TX = (u32TxData))

/**
  * @brief      Set QSPIx_SS pin to high state.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set QSPIx_SS pin to high state.
  * \hideinitializer
  */
#define QSPI_SET_SS_HIGH(qspi)   ((qspi)->SSCTL = ((qspi)->SSCTL & (~QSPI_SSCTL_AUTOSS_Msk)) | (QSPI_SSCTL_SSACTPOL_Msk | QSPI_SSCTL_SS_Msk))

/**
  * @brief      Set QSPIx_SS pin to low state.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set QSPIx_SS pin to low state.
  * \hideinitializer
  */
#define QSPI_SET_SS_LOW(qspi)   ((qspi)->SSCTL = ((qspi)->SSCTL & (~(QSPI_SSCTL_AUTOSS_Msk | QSPI_SSCTL_SSACTPOL_Msk))) | QSPI_SSCTL_SS_Msk)

/**
  * @brief      Enable Byte Reorder function.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Enable Byte Reorder function. The suspend interval depends on the setting of SUSPITV (QSPI_CTL[7:4]).
  * \hideinitializer
  */
#define QSPI_ENABLE_BYTE_REORDER(qspi)   ((qspi)->CTL |=  QSPI_CTL_REORDER_Msk)

/**
  * @brief      Disable Byte Reorder function.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Clear REORDER bit field of QSPI_CTL register to disable Byte Reorder function.
  * \hideinitializer
  */
#define QSPI_DISABLE_BYTE_REORDER(qspi)   ((qspi)->CTL &= ~QSPI_CTL_REORDER_Msk)

/**
  * @brief      Set the length of suspend interval.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @param[in]  u32SuspCycle Decides the length of suspend interval. It could be 0 ~ 15.
  * @return     None.
  * @details    Set the length of suspend interval according to u32SuspCycle.
  *             The length of suspend interval is ((u32SuspCycle + 0.5) * the length of one QSPI bus clock cycle).
  * \hideinitializer
  */
#define QSPI_SET_SUSPEND_CYCLE(qspi, u32SuspCycle)   ((qspi)->CTL = ((qspi)->CTL & ~QSPI_CTL_SUSPITV_Msk) | ((u32SuspCycle) << QSPI_CTL_SUSPITV_Pos))

/**
  * @brief      Set the QSPI transfer sequence with LSB first.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Set LSB bit of QSPI_CTL register to set the QSPI transfer sequence with LSB first.
  * \hideinitializer
  */
#define QSPI_SET_LSB_FIRST(qspi)   ((qspi)->CTL |= QSPI_CTL_LSB_Msk)

/**
  * @brief      Set the QSPI transfer sequence with MSB first.
  * @param[in]  qspi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear LSB bit of QSPI_CTL register to set the QSPI transfer sequence with MSB first.
  * \hideinitializer
  */
#define QSPI_SET_MSB_FIRST(qspi)   ((qspi)->CTL &= ~QSPI_CTL_LSB_Msk)

/**
  * @brief      Set the data width of a QSPI transaction.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @param[in]  u32Width The bit width of one transaction.
  * @return     None.
  * @details    The data width can be 8 ~ 32 bits.
  * \hideinitializer
  */
#define QSPI_SET_DATA_WIDTH(qspi, u32Width)   ((qspi)->CTL = ((qspi)->CTL & ~QSPI_CTL_DWIDTH_Msk) | (((u32Width)&0x1F) << QSPI_CTL_DWIDTH_Pos))

/**
  * @brief      Get the QSPI busy state.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @retval     0 QSPI controller is not busy.
  * @retval     1 QSPI controller is busy.
  * @details    This macro will return the busy state of QSPI controller.
  * \hideinitializer
  */
#define QSPI_IS_BUSY(qspi)   ( ((qspi)->STATUS & QSPI_STATUS_BUSY_Msk)>>QSPI_STATUS_BUSY_Pos )

/**
  * @brief      Enable QSPI controller.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Set QSPIEN (QSPI_CTL[0]) to enable QSPI controller.
  * \hideinitializer
  */
#define QSPI_ENABLE(qspi)   ((qspi)->CTL |= QSPI_CTL_QSPIEN_Msk)

/**
  * @brief      Disable QSPI controller.
  * @param[in]  qspi The pointer of the specified QSPI module.
  * @return     None.
  * @details    Clear QSPIEN (QSPI_CTL[0]) to disable QSPI controller.
  * \hideinitializer
  */
#define QSPI_DISABLE(qspi)   ((qspi)->CTL &= ~QSPI_CTL_QSPIEN_Msk)

/**
  * @brief  Disable QSPI Dual IO function.
  * @param[in]  qspi is the base address of QSPI module.
  * @return none
  * \hideinitializer
  */
#define QSPI_DISABLE_DUAL_MODE(qspi) ( (qspi)->CTL &= ~QSPI_CTL_DUALIOEN_Msk )

/**
  * @brief  Enable Dual IO function and set QSPI Dual IO direction to input.
  * @param[in]  qspi is the base address of QSPI module.
  * @return none
  * \hideinitializer
  */
#define QSPI_ENABLE_DUAL_INPUT_MODE(qspi) ( (qspi)->CTL = ((qspi)->CTL & ~QSPI_CTL_DATDIR_Msk) | QSPI_CTL_DUALIOEN_Msk )

/**
  * @brief  Enable Dual IO function and set QSPI Dual IO direction to output.
  * @param[in]  qspi is the base address of QSPI module.
  * @return none
  * \hideinitializer
  */
#define QSPI_ENABLE_DUAL_OUTPUT_MODE(qspi) ( (qspi)->CTL |= QSPI_CTL_DATDIR_Msk | QSPI_CTL_DUALIOEN_Msk )

/**
  * @brief  Disable QSPI Dual IO function.
  * @param[in]  qspi is the base address of QSPI module.
  * @return none
  * \hideinitializer
  */
#define QSPI_DISABLE_QUAD_MODE(qspi) ( (qspi)->CTL &= ~QSPI_CTL_QUADIOEN_Msk )

/**
  * @brief  Set QSPI Quad IO direction to input.
  * @param[in]  qspi is the base address of QSPI module.
  * @return none
  * \hideinitializer
  */
#define QSPI_ENABLE_QUAD_INPUT_MODE(qspi) ( (qspi)->CTL = ((qspi)->CTL & ~QSPI_CTL_DATDIR_Msk) | QSPI_CTL_QUADIOEN_Msk )

/**
  * @brief  Set QSPI Quad IO direction to output.
  * @param[in]  qspi is the base address of QSPI module.
  * @return none
  * \hideinitializer
  */
#define QSPI_ENABLE_QUAD_OUTPUT_MODE(qspi) ( (qspi)->CTL |= QSPI_CTL_DATDIR_Msk | QSPI_CTL_QUADIOEN_Msk )




/* Function prototype declaration */
uint32_t QSPI_Open(QSPI_T *qspi, uint32_t u32MasterSlave, uint32_t u32QSPIMode, uint32_t u32DataWidth, uint32_t u32BusClock);
void QSPI_Close(QSPI_T *qspi);
void QSPI_ClearRxFIFO(QSPI_T *qspi);
void QSPI_ClearTxFIFO(QSPI_T *qspi);
void QSPI_DisableAutoSS(QSPI_T *qspi);
void QSPI_EnableAutoSS(QSPI_T *qspi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t QSPI_SetBusClock(QSPI_T *qspi, uint32_t u32BusClock);
void QSPI_SetFIFO(QSPI_T *qspi, uint32_t u32TxThreshold, uint32_t u32RxThreshold);
uint32_t QSPI_GetBusClock(QSPI_T *qspi);
void QSPI_EnableInt(QSPI_T *qspi, uint32_t u32Mask);
void QSPI_DisableInt(QSPI_T *qspi, uint32_t u32Mask);
uint32_t QSPI_GetIntFlag(QSPI_T *qspi, uint32_t u32Mask);
void QSPI_ClearIntFlag(QSPI_T *qspi, uint32_t u32Mask);
uint32_t QSPI_GetStatus(QSPI_T *qspi, uint32_t u32Mask);


/*@}*/ /* end of group QSPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group QSPI_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
