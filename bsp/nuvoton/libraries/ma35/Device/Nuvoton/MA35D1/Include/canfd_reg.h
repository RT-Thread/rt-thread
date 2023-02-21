/**************************************************************************//**
 * @file     canfd_reg.h
 * @brief    CANFD register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef __CANFD_REG_H__
#define __CANFD_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup Controller Area Network with Feasibility Data Rate (CAN FD)
    Memory Mapped Structure for CAN FD Controller
@{ */

typedef struct
{


    /**
     * @var CANFD_T::DBTP
     * Offset: 0x0C  Data Bit Timing & Prescaler Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DSJW      |Data Re-Synchronization Jump Width
     * |        |          |Valid values are 0 to 15
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the programmed value is used
     * |        |          |tSJW = (DSJW + 1) x tq.
     * |[7:4]   |DTSEG2    |Data time segment after sample point
     * |        |          |Valid values are 0 to 15
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the programmed value is used
     * |        |          |tBS2 = (DTSEG2 + 1) x tq.
     * |[12:8]  |DTSEG1    |Data time segment before sample point
     * |        |          |Valid values are 0 to 31
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the programmed value is used
     * |        |          |tBS1 = (DTSEG1 + 1) x tq.
     * |[20:16] |DBRP      |Data Bit Rate Prescaler
     * |        |          |The value by which the oscillator frequency is divided for generating the bit time quanta
     * |        |          |The bit time is built up from a multiple of this quanta
     * |        |          |Valid values for the Bit Rate Prescaler are 0 to 31
     * |        |          |When TDC = '1', the range is limited to 0,1
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
     * |[23]    |TDC       |Transmitter Delay Compensation
     * |        |          |0 =Transmitter Delay Compensation Disabled.
     * |        |          |1 =Transmitter Delay Compensation Enabled.
     * @var CANFD_T::TEST
     * Offset: 0x10  Test Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4]     |LBCK      |Loop Back Mode
     * |        |          |0 = Reset value, Loop Back Mode Disabled.
     * |        |          |1 = Loop Back Mode Enabled (refer to section 6.33.5.1 TEST Mode).
     * |[6:5]   |TX        |Control of Transmit Pin
     * |        |          |00 = Reset value, CANx_TXD controlled by the CAN Core, updated at the end of the CAN bit time.
     * |        |          |01 = Sample Point can be monitored at pin CANx_TXD.
     * |        |          |10 = Dominant ('0') level at pin CANx_TXD.
     * |        |          |11 = Recessive ('1') level at pin CANx_TXD.
     * |[7]     |RX        |Receive Pin
     * |        |          |Monitors the actual value of pin CANx_RXD
     * |        |          |0 = The CAN bus is dominant (CANx_RXD = 0).
     * |        |          |1 = The CAN bus is recessive (CANx_RXD = 1).
     * @var CANFD_T::RWD
     * Offset: 0x14  RAM Watchdog
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |WDC       |Watchdog Configuration
     * |        |          |Start value of the Message RAM Watchdog Counter. With the reset value of 00 the counter is disabled.
     * |[15:8]  |WDV       |Watchdog Value
     * |        |          |Actual Message RAM Watchdog Counter Value.
     * @var CANFD_T::CCCR
     * Offset: 0x18  CC Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INIT      |Initialization
     * |        |          |0 = Normal Operation.
     * |        |          |1 = Initialization is started.
     * |        |          |Note: Due to the synchronization mechanism between the two clock domains, there may be a delay until the value written to INIT can be read back
     * |        |          |Therefore the programmer has to assure that the previous value written to INIT has been accepted by reading INIT before setting INIT to a new value.
     * |[1]     |CCE       |Configuration Change Enable
     * |        |          |0 = The CPU has no write access to the protected configuration registers.
     * |        |          |1 = The CPU has write access to the protected configuration registers (while CANFD_INIT (CANFD_CCCR[0]) = 1).
     * |[2]     |ASM       |Restricted Operation Mode
     * |        |          |Bit ASM can only be set by the Host when both CCE and INIT are set to 1
     * |        |          |The bit can be reset by the software at any time
     * |        |          |This bit will be set automatically set to 1 when the Tx handler was not able to read data from the message RAM in time
     * |        |          |For a description of the Restricted Operation Mode refer to Restricted Operation Mode.
     * |        |          |0 = Normal CAN operation.
     * |        |          |1 = Restricted Operation Mode active.
     * |[3]     |CSA       |Clock Stop Acknowledge
     * |        |          |0 = No clock stop acknowledged.
     * |        |          |1 = The Controller may be set in power down by stopping AHB clock and CAN Core clock.
     * |[4]     |CSR       |Clock Stop Request
     * |        |          |0 = No clock stop is requested.
     * |        |          |1 = Clock stop requested
     * |        |          |When clock stop is requested, first INIT and then CSA will be set after all pending transfer requests have been completed and the CAN bus reached idle.
     * |[5]     |MON       |Bus Monitoring Mode
     * |        |          |Bit MON can only be set by the Host when both CCE and INIT are set to 1
     * |        |          |The bit can be reset by the Host at any time.
     * |        |          |0 = Bus Monitoring Mode Disabled.
     * |        |          |1 = Bus Monitoring Mode Enabled.
     * |[6]     |DAR       |Disable Automatic Retransmission
     * |        |          |0 = Automatic retransmission of messages not transmitted successfully Enabled.
     * |        |          |1 = Automatic retransmission Disabled.
     * |[7]     |TEST      |Test Mode Enable
     * |        |          |0 = Normal operation, register TEST holds reset values.
     * |        |          |1 = Test Mode, write access to register TEST enabled.
     * |[8]     |FDOE      |FD Operation Enable
     * |        |          |0 = FD operation Disabled.
     * |        |          |1 = FD operation Enabled.
     * |[9]     |BRSE      |Bit Rate Switch Enable
     * |        |          |0 = Bit rate switching for transmissions Disabled.
     * |        |          |1 = Bit rate switching for transmissions Enabled.
     * |        |          |Note: When CAN FD operation is disabled FDOE = 0, BRSE is not evaluated.
     * |[12]    |PXHD      |Protocol Exception Handling Disable
     * |        |          |0 = Protocol exception handling Enabled.
     * |        |          |1 = Protocol exception handling Disabled.
     * |        |          |Note: When protocol exception handling is disabled, the controller will transmit an error frame when it detects a protocol exception condition.
     * |[13]    |EFBI      |Edge Filtering during Bus Integration
     * |        |          |0 = Edge filtering Disabled.
     * |        |          |1 = Two consecutive dominant tq required to detect an edge f or hard synchronization.
     * |[14]    |TXP       |Transmit Pause
     * |        |          |If this bit is set, the CAN FD controller pauses for two CAN bit times before starting the next transmission after itself has successfully transmitted a frame (refer to section 6.33.5.5).
     * |        |          |0 = Transmit pause Disabled.
     * |        |          |1 = Transmit pause Enabled.
     * |[15]    |NISO      |Non ISO Operation
     * |        |          |If this bit is set, the CAN FD controller uses the CAN FD frame format as speci&#64257;ed by the Bosch CAN FD Speci&#64257;cation V1.0.
     * |        |          |0 = CAN FD frame format according to ISO 11898-1:2015.
     * |        |          |1 = CAN FD frame format according to Bosch CAN FD Speci&#64257;cation V1.0.
     * @var CANFD_T::NBTP
     * Offset: 0x1C  Nominal Bit Timing & Prescaler Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |NTSEG2    |Nominal Time Segment after Sample Point
     * |        |          |0x01-0x7F Valid values are 1 to 127
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the programmed value is used
     * |        |          |tBS2 = (NTSEG2 + 1) x tq.
     * |        |          |Note: With a CAN Core clock (cclk) of 8 MHz, the reset value of 0x06000A03 configures the controller for a bit rate of 500 kBit/s.
     * |[15:8]  |NTSEG1    |Nominal Time Segment before Sample Point
     * |        |          |Valid values are 1 to 255
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the programmed value is used
     * |        |          |tBS1 = (NTSEG1 + 1) x tq.
     * |[24:16] |NBRP      |Nominal Bit Rate Prescaler
     * |        |          |The value by which the oscillator frequency is divided for generating the bit time quanta
     * |        |          |The bit time is built up from a multiple of this quanta
     * |        |          |Valid values for the Bit Rate Prescaler are 0 to 511
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed here is used
     * |[31:25] |NSJW      |Nominal Re-Synchronization Jump Width
     * |        |          |Valid values are 0 to 127, which should be smaller than NTSEG2
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed here is used
     * |        |          |tSJW = (NSJW + 1) x tq.
     * @var CANFD_T::TSCC
     * Offset: 0x20  Timestamp Counter Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |TSS       |Timestamp Select
     * |        |          |00 = Timestamp counter value always 0x0000.
     * |        |          |01 = Timestamp counter value incremented according to TCP.
     * |        |          |10 = Reserved.
     * |        |          |11 = Same as '00'.
     * |[19:16] |TCP       |Timestamp Counter Prescaler
     * |        |          |Configures the timestamp and timeout counters time unit in multiples of CAN bit times [ 1u202616 ]
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
     * @var CANFD_T::TSCV
     * Offset: 0x24  Timestamp Counter Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TSC       |Timestamp Counter
     * |        |          |The internal Timestamp Counter value is captured on start of frame (both Rx and Tx)
     * |        |          |When CANFD_TSS (TSCC[[1:0]) = 2'b01, the Timestamp Counter is incremented in multiples of CAN bit times [ 1...16 ] depending on the configuration of CANFD_TCP (CANFD_TSCC[19:16])
     * |        |          |A wrap around sets interrupt flag CANFD_IR (CANFD_IR[16])
     * |        |          |Write access resets the counter to 0.
     * |        |          |Note: A "around" is a change of the Timestamp Counter value from non-zero to 0 not caused by write access to CANFD_TSCV.
     * @var CANFD_T::TOCC
     * Offset: 0x28  Timeout Counter Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ETOC      |Enable Timeout Counter
     * |        |          |0 = Timeout Counter Disabled.
     * |        |          |1 = Timeout Counter Enabled.
     * |        |          |Note: For use of timeout function with CAN FD refer to section 6.33.5.3.
     * |[2:1]   |TOS       |Timeout Select
     * |        |          |When operating in Continuous mode, a write to CANFD_TOCV presets the counter to the value con&#64257;gured by CANFD_TOP (TOCC[31:16]) and continues down-counting
     * |        |          |When the Timeout Counter is controlled by one of the FIFOs, an empty FIFO presets the counter to the value con&#64257;gured by CANFD_TOP (TOCC[31:16])
     * |        |          |Down-counting is started when the first FIFO element is stored.
     * |        |          |00 = Continuous operation.
     * |        |          |01 = Timeout controlled by Tx Event FIFO.
     * |        |          |10 = Timeout controlled by Rx FIFO 0.
     * |        |          |11 = Timeout controlled by Rx FIFO 1.
     * |[31:16] |TOP       |Timeout Period
     * |        |          |Start value of the Timeout Counter (down-counter). Configures the Timeout Period.
     * @var CANFD_T::TOCV
     * Offset: 0x2C  Timeout Counter Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC       |Timeout Counter
     * |        |          |The filed is decremented in multiples of CAN bit times [ 1...16 ] depending on the configuration of TCP (CANFD_TSCC[19:16])
     * |        |          |When decremented to 0, interrupt flag TOO (CANFD_IR[18]) is set and the timeout counter is stopped
     * |        |          |Start and reset/restart conditions are configured via TOS (CANFD_TOCC[1:0]).
     * @var CANFD_T::ECR
     * Offset: 0x40  Error Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |TEC       |Transmit Error Counter
     * |        |          |Actual state of the Transmit Error Counter, values between 0 and 255.
     * |        |          |Note: When ASM (CANFD_CCCR[2]) is set, the CAN protocol controller does not increment TEC and REC when a CAN protocol error is detected, but CEL is still incremented.
     * |[14:8]  |REC       |Receive Error Counter
     * |        |          |Actual state of the Receive Error Counter, values between 0 and 127.
     * |[15]    |RP        |Receive Error Passive
     * |        |          |0 = The Receive Error Counter is below the error passive level of 128.
     * |        |          |1 = The Receive Error Counter has reached the error passive level of 128.
     * |[23:16] |CEL       |CAN Error Logging
     * |        |          |The counter is incremented each time when a CAN protocol error causes the 8-bit Transmit Error Counter TEC or the 7-bit Receive Error Counter REC to be incremented
     * |        |          |The counter is also incremented when the Bus_Off limit is reached
     * |        |          |It is not incremented when only RP is set without changing REC
     * |        |          |The increment of CEL follows after the increment of REC or TEC.
     * |        |          |The counter is reset by read access to CEL
     * |        |          |The counter stops at 0xFF; the next increment of TEC or REC sets interrupt flag ELO (CANFD_IR[22]).
     * @var CANFD_T::PSR
     * Offset: 0x44  Protocol Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |LEC       |Last Error Code
     * |        |          |The LEC indicates the type of the last error to occur on the CAN bus
     * |        |          |This field will be cleared to 0 when a message has been transferred (reception or transmission) without error.
     * |        |          |000 = No Error: No error occurred since LEC has been reset by successful reception or transmission.
     * |        |          |001 = Stuff Error: More than 5 equal bits in a sequence have occurred in a part of a received message where this is not allowed.
     * |        |          |010 = Form Error: A fixed format part of a received frame has the wrong format.
     * |        |          |011 = AckError: The message transmitted by the CANFD CONTROLLER was not acknowledged by another node.
     * |        |          |100 = Bit1Error: During the transmission of a message (with the exception of the arbitration field), the device wanted to send a recessive level (bit of logical value 1), but the monitored bus value was dominant.
     * |        |          |101 = Bit0Error : During the transmission of a message (or acknowledge bit, or active error flag, or overload flag), the device wanted to send a dominant level (data or identifier bit logical value 0), but the monitored bus value was recessive
     * |        |          |During Bus_Off recovery this status is set each time a sequence of 11 recessive bits has been monitored
     * |        |          |This enables the CPU to monitor the proceeding of the Bus_Off recovery sequence (indicating the bus is not stuck at dominant or continuously disturbed).
     * |        |          |110 = CRCError: The CRC check sum of a received message was incorrect
     * |        |          |The CRC of an incoming message does not match with the CRC calculated from the received data.
     * |        |          |111 = NoChange: Any read access to the Protocol Status Register re-initializes the LEC to 7.When the LEC shows the value 7, no CAN bus event was detected since the last CPU read access to the Protocol Status Register.
     * |[4:3]   |ACT       |Activity
     * |        |          |Monitors the module's CAN communication state.
     * |        |          |00 = Synchronizing - node is synchronizing on CAN communication.
     * |        |          |01 = Idle - node is neither receiver nor transmitter.
     * |        |          |10 = Receiver - node is operating as receiver.
     * |        |          |11 = Transmitter - node is operating as transmitter.
     * |[5]     |EP        |Error Passive
     * |        |          |0 = The CAN FD controller is in the Error_Active state
     * |        |          |It normally takes part in bus communication and sends an active error flag when an error has been detected.
     * |        |          |1 = The CAN FD controller is in the Error_Passive state.
     * |[6]     |EW        |Warning Status
     * |        |          |0 = Both error counters are below the Error_Warning limit of 96.
     * |        |          |1 = At least one of error counter has reached the Error_Warning limit of 96.
     * |[7]     |BO        |Bus_Off Status
     * |        |          |0 = The CAN FD controller is not Bus_Off.
     * |        |          |1 = The CAN FD controller is in Bus_Off state.
     * |[10:8]  |DLEC      |Data Phase Last Error Code
     * |        |          |Type of last error that occurred in the data phase of a CAN FD format frame with its BRS flag set
     * |        |          |Coding is the same as for LEC
     * |        |          |This field will be cleared to 0 when a CAN FD format frame with its BRS flag set has been transferred (reception or transmission) without error.
     * |[11]    |RESI      |ESI flag of last received CAN FD Message
     * |        |          |This bit is set together with RFDF, independent of acceptance filtering.
     * |        |          |0 = Last received CAN FD message did not have its ESI flag set.
     * |        |          |1 = Last received CAN FD message had its ESI flag set.
     * |[12]    |RBRS      |BRS flag of last received CAN FD Message
     * |        |          |This bit is set together with RFDF, independent of acceptance filtering.
     * |        |          |0 = Last received CAN FD message did not have its BRS flag set.
     * |        |          |1 = Last received CAN FD message had its BRS flag set.
     * |        |          |Note: Byte access: Reading byte 0 will reset RBRS, reading bytes 3/2/1 has no impact.
     * |[13]    |RFDF      |Received a CAN FD Message
     * |        |          |This bit is set independent of acceptance filtering.
     * |        |          |0 = Since this bit was reset by the CPU, no CAN FD message has been received.
     * |        |          |1 = Message in CAN FD format with FDF flag set has been received.
     * |        |          |Note: Byte access: Reading byte 0 will reset RFDF, reading bytes 3/2/1 has no impact.
     * |[14]    |PXE       |Protocol Exception Event
     * |        |          |0 = No protocol exception event occurred since last read access.
     * |        |          |1 = Protocol exception event occurred.
     * |[22:16] |TDCV      |Transmitter Delay Compensation Value
     * |        |          |Position of the secondary sample point, defined by the sum of the measured delay from CANx_TXD to CANx_RXD and TDCO (TDCR[[14:8])
     * |        |          |The SSP position is, in the data phase, the number of minimum time quata (mtq) between the start of the transmitted bit and the secondary sample point
     * |        |          |Valid values are 0 to 127 mtq.
     * @var CANFD_T::TDCR
     * Offset: 0x48  Transmitter Delay Compensation Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |TDCF      |Transmitter Delay Compensation Filter Window Length
     * |        |          |Defines the minimum value for the SSP position, dominant edges on CANx_RXD that would result in an earlier SSP position are ignored for transmitter delay measurement
     * |        |          |The feature is enabled when TDCF is configured to a value greater than TDCO
     * |        |          |Valid values are 0 to 127 mtq.
     * |[14:8]  |TDCO      |Transmitter Delay Compensation SSP Offset
     * |        |          |Offset value defining the distance between the measured delay from CANx_TXD to CANx_RXD and the secondary sample point
     * |        |          |Valid values are 0 to 127 mtq.
     * @var CANFD_T::IR
     * Offset: 0x50  Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RF0N      |Rx FIFO 0 New Message
     * |        |          |0 = No new message written to Rx FIFO 0.
     * |        |          |1 = New message written to Rx FIFO 0.
     * |[1]     |RF0W      |Rx FIFO 0 Watermark Reached
     * |        |          |0 = Rx FIFO 0 fill level below watermark.
     * |        |          |1 = Rx FIFO 0 fill level reached watermark.
     * |[2]     |RF0F      |Rx FIFO 0 Full
     * |        |          |0 = Rx FIFO 0 not full.
     * |        |          |1 = Rx FIFO 0 full.
     * |[3]     |RF0L      |Rx FIFO 0 Message Lost
     * |        |          |0 = No Rx FIFO 0 message lost.
     * |        |          |1 = Rx FIFO 0 message lost, also set after write attempt to Rx FIFO 0 of size zero.
     * |[4]     |RF1N      |Rx FIFO 1 New Message
     * |        |          |0 = No new message written to Rx FIFO 1.
     * |        |          |1 = New message written to Rx FIFO 1.
     * |[5]     |RF1W      |Rx FIFO 1 Watermark Reached
     * |        |          |0 = Rx FIFO 1 fill level below watermark.
     * |        |          |1 = Rx FIFO 1 fill level reached watermark.
     * |[6]     |RF1F      |Rx FIFO 1 Full
     * |        |          |0 = Rx FIFO 1 not full.
     * |        |          |1 = Rx FIFO 1 full.
     * |[7]     |RF1L      |Rx FIFO 1 Message Lost
     * |        |          |0 = No Rx FIFO 1 message lost.
     * |        |          |1 = Rx FIFO 1 message lost, also set after write attempt to Rx FIFO 1 of size zero.
     * |[8]     |HPM       |High Priority Message
     * |        |          |0 = No high priority message received.
     * |        |          |1 = High priority message received.
     * |[9]     |TC        |Transmission Completed
     * |        |          |0 = No transmission completed.
     * |        |          |1 = Transmission completed.
     * |[10]    |TCF       |Transmission Cancellation Finished
     * |        |          |0 = No transmission cancellation finished.
     * |        |          |1 = Transmission cancellation finished.
     * |[11]    |TFE       |Tx FIFO Empty
     * |        |          |0 = Tx FIFO non-empty.
     * |        |          |1 = Tx FIFO empty.
     * |[12]    |TEFN      |Tx Event FIFO New Entry
     * |        |          |0 = Tx Event FIFO unchanged.
     * |        |          |1 = Tx Handler wrote Tx Event FIFO element.
     * |[13]    |TEFW      |Tx Event FIFO Watermark Reached
     * |        |          |0 = Tx Event FIFO fill level below watermark.
     * |        |          |1 = Tx Event FIFO fill level reached watermark.
     * |[14]    |TEFF      |Tx Event FIFO Full
     * |        |          |0 = Tx Event FIFO not full.
     * |        |          |1 = Tx Event FIFO full.
     * |[15]    |TEFL      |Tx Event FIFO Element Lost
     * |        |          |0 = No Tx Event FIFO element lost.
     * |        |          |1 = Tx Event FIFO element lost, also set after write attempt to Tx Event FIFO of size zero.
     * |[16]    |TSW       |Timestamp Wraparound
     * |        |          |0 = No timestamp counter wrap-around.
     * |        |          |1 = Timestamp counter wrapped around.
     * |[17]    |MRAF      |Message RAM Access Failure
     * |        |          |The flag is set, when the Rx Handler
     * |        |          |Has not completed acceptance filtering or storage of an accepted message until the arbitration field of the following message has been received
     * |        |          |In this case acceptance filtering or message storage is aborted and the Rx Handler starts processing of the following message.
     * |        |          |Was not able to write a message to the Message RAM. In this case message storage is aborted.
     * |        |          |In both cases the FIFO put index is not updated resp
     * |        |          |The New Data flag for a dedicated Rx Buffer is not set, a partly stored message is overwritten when the next message is stored to this location.
     * |        |          |The flag is also set when the Tx Handler was not able to read a message from the Message RAM in time
     * |        |          |In this case message transmission is aborted
     * |        |          |In case of a Tx Handler access failure the CAN FD controller is switched into Restricted Operation Mode (refer to Restricted Operation Mode)
     * |        |          |To leave Restricted Operation Mode, the Host CPU has to reset CANFD_ASM (CANFD_CCCR[2]).
     * |        |          |0 = No Message RAM access failure occurred.
     * |        |          |1 = Message RAM access failure occurred.
     * |[18]    |TOO       |Timeout Occurred
     * |        |          |0 = No timeout.
     * |        |          |1 = Timeout reached.
     * |[19]    |DRX       |Message stored to Dedicated Rx Buffer
     * |        |          |The flag is set whenever a received message has been stored into a dedicated Rx Buffer.
     * |        |          |0 = No Rx Buffer updated.
     * |        |          |1 = At least one received message stored into an Rx Buffer.
     * |[22]    |ELO       |Error Logging Overflow
     * |        |          |0 = CAN Error Logging Counter did not overflow.
     * |        |          |1 = Overflow of CAN Error Logging Counter occurred.
     * |[23]    |EP        |Error Passive
     * |        |          |0 = Error_Passive status unchanged.
     * |        |          |1 = Error_Passive status changed.
     * |[24]    |EW        |Warning Status
     * |        |          |0 = Error_Warning status unchanged.
     * |        |          |1 = Error_Warning status changed.
     * |[25]    |BO        |Bus_Off Status
     * |        |          |0 = Bus_Off status unchanged.
     * |        |          |1 = Bus_Off status changed.
     * |[26]    |WDI       |Watchdog Interrupt
     * |        |          |0 = No Message RAM Watchdog event occurred.
     * |        |          |1 = Message RAM Watchdog event due to missing READY.
     * |[27]    |PEA       |Protocol Error in Arbitration Phase
     * |        |          |0 = No protocol error in arbitration phase.
     * |        |          |1 = Protocol error in arbitration phase detected (CANFD_LEC (CANFD_PSR[2:0]) no equal 0 or 7).
     * |        |          |Note: Nominal bit time is used.
     * |[28]    |PED       |Protocol Error in Data Phase
     * |        |          |0 = No protocol error in data phase.
     * |        |          |1 = Protocol error in data phase detected (DLEC (CANFD_PSR[10:8]) no equal 0 or 7).
     * |        |          |Note: Data bit time is used.
     * |[29]    |ARA       |Access to Reserved Address
     * |        |          |0 = No access to reserved address occurred.
     * |        |          |1 = Access to reserved address occurred.
     * @var CANFD_T::IE
     * Offset: 0x54  Interrupt Enable
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RF0NE     |Rx FIFO 0 New Message Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[1]     |RF0WE     |Rx FIFO 0 Watermark Reached Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[2]     |RF0FE     |Rx FIFO 0 Full Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[3]     |RF0LE     |Rx FIFO 0 Message Lost Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[4]     |RF1NE     |Rx FIFO 1 New Message Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[5]     |RF1WE     |Rx FIFO 1 Watermark Reached Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[6]     |RF1FE     |Rx FIFO 1 Full Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[7]     |RF1LE     |Rx FIFO 1 Message Lost Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[8]     |HPME      |High Priority Message Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[9]     |TCE       |Transmission Completed Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[10]    |TCFE      |Transmission Cancellation Finished Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[11]    |TFEE      |Tx FIFO Empty Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[12]    |TEFNE     |Tx Event FIFO New Entry Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[13]    |TEFWE     |Tx Event FIFO Watermark Reached Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[14]    |TEFFE     |Tx Event FIFO Full Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[15]    |TEFLE     |Tx Event FIFO Event Lost Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[16]    |TSWE      |Timestamp Wraparound Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[17]    |MRAFE     |Message RAM Access Failure Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[18]    |TOOE      |Timeout Occurred Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[19]    |DRXE      |Message stored to Dedicated Rx Buffer Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[20]    |BECE      |Bit Error Corrected Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[21]    |BEUE      |Bit Error Uncorrected Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[22]    |ELOE      |Error Logging Overflow Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[23]    |EPE       |Error Passive Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[24]    |EWE       |Warning Status Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[25]    |BOE       |Bus_Off Status Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[26]    |WDIE      |Watchdog Interrupt Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[27]    |PEAE      |Protocol Error in Arbitration Phase Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[28]    |PEDE      |Protocol Error in Data Phase Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * |[29]    |ARAE      |Access to Reserved Address Enable
     * |        |          |0 = Interrupt Disabled.
     * |        |          |1 = Interrupt Enabled.
     * @var CANFD_T::ILS
     * Offset: 0x58  Interrupt Line Select
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RF0NL     |Rx FIFO 0 New Message Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[1]     |RF0WL     |Rx FIFO 0 Watermark Reached Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[2]     |RF0FL     |Rx FIFO 0 Full Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[3]     |RF0LL     |Rx FIFO 0 Message Lost Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[4]     |RF1NL     |Rx FIFO 1 New Message Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[5]     |RF1WL     |Rx FIFO 1 Watermark Reached Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[6]     |RF1FL     |Rx FIFO 1 Full Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[7]     |RF1LL     |Rx FIFO 1 Message Lost Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[8]     |HPML      |High Priority Message Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[9]     |TCL       |Transmission Completed Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[10]    |TCFL      |Transmission Cancellation Finished Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[11]    |TFEL      |Tx FIFO Empty Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[12]    |TEFNL     |Tx Event FIFO New Entry Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[13]    |TEFWL     |Tx Event FIFO Watermark Reached Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[14]    |TEFFL     |Tx Event FIFO Full Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[15]    |TEFLL     |Tx Event FIFO Event Lost Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[16]    |TSWL      |Timestamp Wraparound Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[17]    |MRAFL     |Message RAM Access Failure Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[18]    |TOOL      |Timeout Occurred Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[19]    |DRXL      |Message stored to Dedicated Rx Buffer Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[22]    |ELOL      |Error Logging Overflow Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[23]    |EPL       |Error Passive Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[24]    |EWL       |Warning Status Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[25]    |BOL       |Bus_Off Status Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[26]    |WDIL      |Watchdog Interrupt Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[27]    |PEAL      |Protocol Error in Arbitration Phase Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[28]    |PEDL      |Protocol Error in Data Phase Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * |[29]    |ARAL      |Access to Reserved Address Line
     * |        |          |0 = Interrupt assigned to CAN interrupt line 0.
     * |        |          |1 = Interrupt assigned to CAN interrupt line 1.
     * @var CANFD_T::ILE
     * Offset: 0x5C  Interrupt Line Enable
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ENT0      |Enable Interrupt Line 0
     * |        |          |0 = Interrupt line canfd_int0 Disabled.
     * |        |          |1 = Interrupt line canfd_int0 Enabled.
     * |[1]     |ENT1      |Enable Interrupt Line 1
     * |        |          |0 = Interrupt line canfd_int1 Disabled.
     * |        |          |1 = Interrupt line canfd_int1 Enabled.
     * @var CANFD_T::GFC
     * Offset: 0x80  Global Filter Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RRFE      |Reject Remote Frames Extended
     * |        |          |0 = Filter remote frames with 29-bit extended IDs.
     * |        |          |1 = Reject all remote frames with 29-bit extended IDs.
     * |[1]     |RRFS      |Reject Remote Frames Standard
     * |        |          |0 = Filter remote frames with 11-bit standard IDs.
     * |        |          |1 = Reject all remote frames with 11-bit standard IDs.
     * |[3:2]   |ANFE      |Accept Non-matching Frames Extended
     * |        |          |Defines how received messages with 29-bit IDs that do not match any element of the filter list are treated.
     * |        |          |00 = Accept in Rx FIFO 0.
     * |        |          |01 = Accept in Rx FIFO 1.
     * |        |          |10 = Reject.
     * |        |          |11 = Reject.
     * |[5:4]   |ANFS      |Accept Non-matching Frames Standard
     * |        |          |Defines how received messages with 11-bit IDs that do not match any element of the filter list are treated.
     * |        |          |00 = Accept in Rx FIFO 0.
     * |        |          |01 = Accept in Rx FIFO 1.
     * |        |          |10 = Reject.
     * |        |          |11 = Reject.
     * @var CANFD_T::SIDFC
     * Offset: 0x84  Standard ID Filter Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:2]  |FLSSA     |Filter List Standard Start Address
     * |        |          |Start address of standard Message ID filter list (32-bit word address, refer to Figure 6.33-11).
     * |[23:16] |LSS       |List Size Standard
     * |        |          |0 = No standard Message ID filter.
     * |        |          |1-128 = Number of standard Message ID filter elements.
     * |        |          |>128 = Values greater than 128 are interpreted as 128.
     * @var CANFD_T::XIDFC
     * Offset: 0x88  Extended ID Filter Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:2]  |FLESA     |Filter List Extended Start Address
     * |        |          |Start address of extended Message ID filter list (32-bit word address, refer to Figure 6.33-11).
     * |[22:16] |LSE       |List Size Extended
     * |        |          |0 = No extended Message ID filter.
     * |        |          |1-64 = Number of extended Message ID filter elements.
     * |        |          |>64 = Values greater than 64 are interpreted as 64.
     * @var CANFD_T::XIDAM
     * Offset: 0x90  Extended ID AND Mask
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[28:0]  |EIDM      |Extended ID Mask
     * |        |          |For acceptance filtering of extended frames the Extended ID AND Mask is ANDed with the Message ID of a received frame
     * |        |          |Intended for masking of 29-bit IDs in SAE J1939
     * |        |          |With the reset value of all bits set to one the mask is not active.
     * @var CANFD_T::HPMS
     * Offset: 0x94  High Priority Message Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |BIDX      |Buffer Index
     * |        |          |Index of Rx FIFO element to which the message was stored. Only valid when MSI[1] = 1.
     * |[7:6]   |MSI       |Message Storage Indicator
     * |        |          |00 = No FIFO selected.
     * |        |          |01 = FIFO message lost.
     * |        |          |10 = Message stored in FIFO 0.
     * |        |          |11 = Message stored in FIFO 1.
     * |[14:8]  |FIDX      |Filter Index
     * |        |          |Index of matching filter element. Range is 0 to CANFD_SIDFC.LSS - 1 or CANFD_XIDFC.LSE - 1
     * |[15]    |FLST      |Filter List
     * |        |          |Indicates the filter list of the matching filter element.
     * |        |          |0 = Standard Filter List.
     * |        |          |1 = Extended Filter List.
     * @var CANFD_T::NDAT1
     * Offset: 0x98  New Data 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NDn       |New Data
     * |        |          |The register holds the New Data flags of Rx Buffers 0 to 31
     * |        |          |The flags are set when the respective Rx Buffer has been updated from a received frame
     * |        |          |The flags remain set until the Host clears them
     * |        |          |A flag is cleared by writing a 1 to the corresponding bit position
     * |        |          |Writing a 0 has no effect
     * |        |          |A hard reset will clear the register.
     * |        |          |0 = Rx Buffer not updated.
     * |        |          |1 = Rx Buffer updated from new message.
     * @var CANFD_T::NDAT2
     * Offset: 0x9C  New Data 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NDn       |New Data
     * |        |          |The register holds the New Data flags of Rx Buffers 32 to 63
     * |        |          |The flags are set when the respective Rx Buffer has been updated from a received frame
     * |        |          |The flags remain set until the Host clears them
     * |        |          |A flag is cleared by writing a 1 to the corresponding bit position
     * |        |          |Writing a 0 has no effect
     * |        |          |A hard reset will clear the register.
     * |        |          |0 = Rx Buffer not updated.
     * |        |          |1 = Rx Buffer updated from new message.
     * @var CANFD_T::RXF0C
     * Offset: 0xA0  Rx FIFO 0 Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:2]  |F0SA      |Rx FIFO 0 Start Address
     * |        |          |Start address of Rx FIFO 0 in Message RAM (32-bit word address).
     * |[22:16] |F0S       |Rx FIFO 0 Size
     * |        |          |0 = No Rx FIFO 0.
     * |        |          |1-64 = Number of Rx FIFO 0 elements.
     * |        |          |>64 = Values greater than 64 are interpreted as 64.
     * |        |          |The Rx FIFO 0 elements are indexed from 0 to F0S-1
     * |[30:24] |F0WM      |Rx FIFO 0 Watermark
     * |        |          |0 = Watermark interrupt Disabled.
     * |        |          |1-64 = Level for Rx FIFO 0 watermark interrupt (CANFD_IR.RF0W).
     * |        |          |>64 = Watermark interrupt Disabled.
     * |[31]    |F0OM      |FIFO 0 Operation Mode
     * |        |          |FIFO 0 can be operated in blocking or in overwrite mode (refer to Rx FIFOs).
     * |        |          |0 = FIFO 0 blocking mode.
     * |        |          |1 = FIFO 0 overwrite mode.
     * @var CANFD_T::RXF0S
     * Offset: 0xA4  Rx FIFO 0 Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |F0FL      |Rx FIFO 0 Fill Level
     * |        |          |Number of elements stored in Rx FIFO 0, range 0 to 64
     * |[13:8]  |F0GI      |Rx FIFO 0 Get Index
     * |        |          |Rx FIFO 0 read index pointer, range 0 to 63.
     * |[21:16] |F0PI      |Rx FIFO 0 Put Index
     * |        |          |Rx FIFO 0 write index pointer, range 0 to 63.
     * |[24]    |F0F       |Rx FIFO 0 Full
     * |        |          |0 = Rx FIFO 0 not full.
     * |        |          |1 = Rx FIFO 0 full.
     * |[25]    |RF0L      |Rx FIFO 0 Message Lost
     * |        |          |This bit is a copy of interrupt flag CANFD_IR.RF0L
     * |        |          |When CANFD_IR.RF0L is reset, this bit is also reset
     * |        |          |0 = No Rx FIFO 0 message lost.
     * |        |          |1 = Rx FIFO 0 message lost, also set after write attempt to Rx FIFO 0 of size zero.
     * |        |          |Note: Overwriting the oldest message when F0OM (CANFD_RXF0C[31]) = 1 will not set this flag.
     * @var CANFD_T::RXF0A
     * Offset: 0xA8  Rx FIFO 0 Acknowledge
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |F0A       |Rx FIFO 0 Acknowledge Index
     * |        |          |After the Host has read a message or a sequence of messages from Rx FIFO 0 it has to write the buffer index of the last element read from Rx FIFO 0 to F0AI
     * |        |          |This will set the Rx FIFO 0 Get Index F0GI (CANFD_RXF0S[13:8]) to F0AI (CANFD_RXF0A[5:0]) + 1 and update the FIFO 0 Fill Level CANFD_RXF0S.F0FL.
     * @var CANFD_T::RXBC
     * Offset: 0xAC  Rx Buffer Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:2]  |RBSA      |Rx Buffer Start Address
     * |        |          |Configures the start address of the Rx Buffers section in the Message RAM (32-bit word address).
     * @var CANFD_T::RXF1C
     * Offset: 0xB0  Rx FIFO 1 Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:2]  |F1SA      |Rx FIFO 1 Start Address
     * |        |          |Start address of Rx FIFO 1 in Message RAM (32-bit word address, refer to Figure 6.33-11).
     * |[22:16] |F1S       |Rx FIFO 1 Size
     * |        |          |0 = No Rx FIFO 1.
     * |        |          |1-64 = Number of Rx FIFO 1 elements.
     * |        |          |>64 = Values greater than 64 are interpreted as 64.
     * |        |          |The Rx FIFO 1 elements are indexed from 0 to F1S - 1
     * |[30:24] |F1WM      |Rx FIFO 1 Watermark
     * |        |          |0 = Watermark interrupt Disabled.
     * |        |          |1-64 = Level for Rx FIFO 1 watermark interrupt (CANFD_IR.RF1W).
     * |        |          |>64 = Watermark interrupt Disabled.
     * |[31]    |F1OM      |FIFO 1 Operation Mode
     * |        |          |FIFO 1 can be operated in blocking or in overwrite mode (refer to Rx FIFOs).
     * |        |          |0 = FIFO 1 blocking mode.
     * |        |          |1 = FIFO 1 overwrite mode.
     * @var CANFD_T::RXF1S
     * Offset: 0xB4  Rx FIFO 1 Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |F1FL      |Rx FIFO 1 Fill Level
     * |        |          |Number of elements stored in Rx FIFO 1, range 0 to 64
     * |[13:8]  |F1G       |Rx FIFO 1 Get Index
     * |        |          |Rx FIFO 1 read index pointer, range 0 to 63.
     * |[21:16] |F1P       |Rx FIFO 1 Fill Level
     * |        |          |Number of elements stored in Rx FIFO 1, range 0 to 64.
     * |[24]    |F1F       |Rx FIFO 1 Full
     * |        |          |0 = Rx FIFO 1 not full.
     * |        |          |1 = Rx FIFO 1 full.
     * |[25]    |RF1L      |Rx FIFO 1 Message Lost
     * |        |          |This bit is a copy of interrupt flag CANFD_IR.RF1L
     * |        |          |When CANFD_IR.RF1L is reset, this bit is also reset
     * |        |          |0 = No Rx FIFO 1 message lost.
     * |        |          |1 = Rx FIFO 1 message lost, also set after write attempt to Rx FIFO 1 of size zero.
     * |        |          |Note: Overwriting the oldest message when F1OM (CANFD_RXF1C[31]) = 1 will not set this flag.
     * @var CANFD_T::RXF1A
     * Offset: 0xB8  Rx FIFO 1 Acknowledge
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |F1A       |Rx FIFO 1 Acknowledge Index
     * |        |          |After the Host has read a message or a sequence of messages from Rx FIFO 1 it has to write the buffer index of the last element read from Rx FIFO 1 to F1AI
     * |        |          |This will set the Rx FIFO 1 Get Index F1GI (CANFD_RXF1S[13:8]) to F1AI (CANFD_RXF1A[5:0]) + 1 and update the FIFO 1 Fill Level F1FL (CANFD_RXF1S[6:0]).
     * @var CANFD_T::RXESC
     * Offset: 0xBC  Rx Buffer / FIFO Element Size Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |F0DS      |Rx FIFO 0 Data Field Size
     * |        |          |000 = 8 byte data field.
     * |        |          |001 = 12 byte data field.
     * |        |          |010 = 16 byte data field.
     * |        |          |011 = 20 byte data field.
     * |        |          |100 = 24 byte data field.
     * |        |          |101 = 32 byte data field.
     * |        |          |110 = 48 byte data field.
     * |        |          |111 = 64 byte data field.
     * |        |          |Note: In case the data field size of an accepted CAN frame exceeds the data field size configured for the matching Rx Buffer or Rx FIFO, only the number of bytes as configured by CANFD_RXESC are stored to the Rx Buffer resp
     * |        |          |Rx FIFO element
     * |        |          |The rest of the frame data field is ignored.
     * |[6:4]   |F1DS      |Rx FIFO 1 Data Field Size
     * |        |          |000 = 8 byte data field.
     * |        |          |001 = 12 byte data field.
     * |        |          |010 = 16 byte data field.
     * |        |          |011 = 20 byte data field.
     * |        |          |100 = 24 byte data field.
     * |        |          |101 = 32 byte data field.
     * |        |          |110 = 48 byte data field.
     * |        |          |111 = 64 byte data field.
     * |[10:8]  |RBDS      |Rx Buffer Data Field Size
     * |        |          |000 = 8 byte data field.
     * |        |          |001 = 12 byte data field.
     * |        |          |010 = 16 byte data field.
     * |        |          |011 = 20 byte data field.
     * |        |          |100 = 24 byte data field.
     * |        |          |101 = 32 byte data field.
     * |        |          |110 = 48 byte data field.
     * |        |          |111 = 64 byte data field.
     * @var CANFD_T::TXBC
     * Offset: 0xC0  Tx Buffer Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:2]  |TBSA      |Tx Buffers Start Address
     * |        |          |Start address of Tx Buffers section in Message RAM (32-bit word address, refer to Figure 6.33-11).
     * |        |          |Note: The sum of TFQS and NDTB may be not greater than 32
     * |        |          |There is no check for erroneous configurations
     * |        |          |The Tx Buffers section in the Message RAM starts with the dedicated Tx Buffers.
     * |[21:16] |NDTB      |Number of Dedicated Transmit Buffers
     * |        |          |0 = No Dedicated Tx Buffers.
     * |        |          |1-32 = Number of Dedicated Tx Buffers.
     * |        |          |>32 = Values greater than 32 are interpreted as 32.
     * |[29:24] |TFQS      |Transmit FIFO/Queue Size
     * |        |          |0 = No Tx FIFO/Queue.
     * |        |          |1-32 = Number of Tx Buffers used for Tx FIFO/Queue.
     * |        |          |>32 = Values greater than 32 are interpreted as 32.
     * |[30]    |TFQM      |Tx FIFO/Queue Mode
     * |        |          |0 = Tx FIFO operation.
     * |        |          |1 = Tx Queue operation.
     * @var CANFD_T::TXFQS
     * Offset: 0xC4  Tx FIFO/Queue Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |TFFL      |Tx FIFO Free Level
     * |        |          |Number of consecutive free Tx FIFO elements starting from TFGI, range 0 to 32
     * |        |          |Read as 0 when Tx Queue operation is configured (TFQM (CANFD_TXBC[3]) = 1).
     * |        |          |Note: In case of mixed configurations where dedicated Tx Buffers are combined with a Tx FIFO or a Tx Queue, the Put and Get Indices indicate the number of the Tx Buffer starting with the first dedicated Tx Buffers.
     * |        |          |Example: For a configuration of 12 dedicated Tx Buffers and a Tx FIFO of 20 Buffers a Put Index of 15 points to the fourth buffer of the Tx FIFO.
     * |[12:8]  |TFG       |Tx FIFO Get Index
     * |        |          |Tx FIFO read index pointer, range 0 to 31
     * |        |          |Read as 0 when Tx Queue operation is configured (TFQM (CANFD_TXBC[30]) = 1).
     * |[20:16] |TFQP      |Tx FIFO/Queue Put Index
     * |        |          |Tx FIFO/Queue write index pointer, range 0 to 31.
     * |[21]    |TFQF      |Tx FIFO/Queue Full
     * |        |          |0 = Tx FIFO/Queue not full.
     * |        |          |1 = Tx FIFO/Queue full.
     * @var CANFD_T::TXESC
     * Offset: 0xC8  Tx Buffer Element Size Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TBDS      |Tx Buffer Data Field Size
     * |        |          |000 = 8 byte data field.
     * |        |          |001 = 12 byte data field.
     * |        |          |010 = 16 byte data field.
     * |        |          |011 = 20 byte data field.
     * |        |          |100 = 24 byte data field.
     * |        |          |101 = 32 byte data field.
     * |        |          |110 = 48 byte data field.
     * |        |          |111 = 64 byte data field.
     * |        |          |Note: In case the data length code DLC of a Tx Buffer element is configured to a value higher than the Tx Buffer data field size CANFD_TXESC.TBDS, the bytes not defined by the Tx Buffer are transmitted as 0xCC (padding bytes).
     * @var CANFD_T::TXBRP
     * Offset: 0xCC  Tx Buffer Request Pending
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |TRPn      |Transmission Request Pending Each Tx Buffer has its own Transmission Request Pending bit The bits are set via register CANFD_TXBAR The bits are reset after a requested transmission has completed or has been cancelled via register CANFD_TXBCR
     * |        |          |CANFD_TXBRP bits are set only for those Tx Buffers configured via CANFD_TXBC
     * |        |          |After a CANFD_TXBRP bit has been set, a Tx scan (refer to section 6.33.5.5, Tx Handling) is started to check for the pending Tx request with the highest priority (Tx Buffer with lowest Message ID).
     * |        |          |A cancellation request resets the corresponding transmission request pending bit of register CANFD_TXBRP
     * |        |          |In case a transmission has already been started when a cancellation is requested, this is done at the end of the transmission, regardless whether the transmission was successful or not
     * |        |          |The cancellation request bits are reset directly after the corresponding CANFD_TXBRP bit has been reset.
     * |        |          |After a cancellation has been requested, a finished cancellation is signaled via CANFD_TXBCF
     * |        |          |- after successful transmission together with the corresponding CANFD_TXBTO bit
     * |        |          |- when the transmission has not yet been started at the point of cancellation
     * |        |          |- when the transmission has been aborted due to lost arbitration
     * |        |          |- when an error occurred during frame transmission
     * |        |          |In DAR mode all transmissions are automatically cancelled if they are not successful
     * |        |          |The corresponding CANFD_TXBCF bit is set for all unsuccessful transmissions.
     * |        |          |0 = No transmission request pending.
     * |        |          |1 = Transmission request pending.
     * |        |          |Note: CANFD_TXBRP bits which are set while a Tx scan is in progress are not considered during this particular Tx scan
     * |        |          |In case a cancellation is requested for such a Tx Buffer, this Add Request is cancelled immediately, the corresponding CANFD_TXBRP bit is reset.
     * @var CANFD_T::TXBAR
     * Offset: 0xD0  Tx Buffer Add Request
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ARn       |Add Request Each Tx Buffer has its own Add Request bit Writing a 1 will set the corresponding Add Request bit; writing a 0 has no impact This enables the Host to set transmission requests for multiple Tx Buffers with one write to CANFD_TXBAR CANFD_TXBAR bits are set only for those Tx Buffers configured via CANFD_TXBC
     * |        |          |When no Tx scan is running, the bits are reset immediately, else the bits remain set until the Tx scan process has completed
     * |        |          |0 = No transmission request added.
     * |        |          |1 = Transmission requested added.
     * |        |          |Note: If an add request is applied for a Tx Buffer with pending transmission request (corresponding CANFD_TXBRP bit already set), this add request is ignored.
     * @var CANFD_T::TXBCR
     * Offset: 0xD4  Tx Buffer Cancellation Request
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CRn       |Cancellation Request
     * |        |          |Each Tx Buffer has its own Cancellation Request bit
     * |        |          |Writing a 1 will set the corresponding Cancellation Request bit; writing a 0 has no impact
     * |        |          |This enables the Host to set cancellation requests for multiple Tx Buffers with one write to CANFD_TXBCR
     * |        |          |CANFD_TXBCR bits are set only for those Tx Buffers configured via CANFD_TXBC
     * |        |          |The bits remain set until the corresponding bit of CANFD_TXBRP is reset.
     * |        |          |0 = No cancellation pending.
     * |        |          |1 = Cancellation pending.
     * @var CANFD_T::TXBTO
     * Offset: 0xD8  Tx Buffer Transmission Occurred
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |TOn       |Transmission Occurred
     * |        |          |Each Tx Buffer has its own Transmission Occurred bit
     * |        |          |The bits are set when the corresponding CANFD_TXBRP bit is cleared after a successful transmission
     * |        |          |The bits are reset when a new transmission is requested by writing a 1 to the corresponding bit of register CANFD_TXBAR.
     * |        |          |0 = No transmission occurred.
     * |        |          |1 = Transmission occurred.
     * @var CANFD_T::TXBCF
     * Offset: 0xDC  Tx Buffer Cancellation Finished
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CFn       |Cancellation Finished
     * |        |          |Each Tx Buffer has its own Cancellation Finished bit
     * |        |          |The bits are set when the corresponding CANFD_TXBRP bit is cleared after a cancellation was requested via CANFD_TXBCR
     * |        |          |In case the corresponding CANFD_TXBRP bit was not set at the point of cancellation, CF is set immediately
     * |        |          |The bits are reset when a new transmission is requested by writing a 1 to the corresponding bit of register CANFD_TXBAR.
     * |        |          |0 = No transmit buffer cancellation.
     * |        |          |1 = Transmit buffer cancellation finished.
     * @var CANFD_T::TXBTIE
     * Offset: 0xE0  Tx Buffer Transmission Interrupt Enable
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |TIEn      |Transmission Interrupt Enable
     * |        |          |Each Tx Buffer has its own Transmission Interrupt Enable bit.
     * |        |          |0 = Transmission interrupt Disabled.
     * |        |          |1 = Transmission interrupt Enabled.
     * @var CANFD_T::TXBCIE
     * Offset: 0xE4  Tx Buffer Cancellation Finished Interrupt Enable
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CFIEn     |Cancellation Finished Interrupt Enable
     * |        |          |Each Tx Buffer has its own Cancellation Finished Interrupt Enable bit.
     * |        |          |0 = Cancellation finished interrupt Disabled.
     * |        |          |1 = Cancellation finished interrupt Enabled.
     * @var CANFD_T::TXEFC
     * Offset: 0xF0  Tx Event FIFO Configuration
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:2]  |EFSA      |Event FIFO Start Address
     * |        |          |Start address of Tx Event FIFO in Message RAM (32-bit word address, refer to Figure 6.33-11).
     * |[21:16] |EFS       |Event FIFO Size
     * |        |          |0 = Tx Event FIFO Disabled.
     * |        |          |1-32 = Number of Tx Event FIFO elements.
     * |        |          |>32 = Values greater than 32 are interpreted as 32.
     * |        |          |The Tx Event FIFO elements are indexed from 0 to EFS - 1
     * |[29:24] |EFWN      |Event FIFO Watermark
     * |        |          |0 = Watermark interrupt Disabled.
     * |        |          |1-32 = Level for Tx Event FIFO watermark interrupt (TEFW (CANFD_IR[13])).
     * |        |          |>32 = Watermark interrupt Disabled.
     * @var CANFD_T::TXEFS
     * Offset: 0xF4  Tx Event FIFO Status
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |EFFL      |Event FIFO Fill Level
     * |        |          |Number of elements stored in Tx Event FIFO, range 0 to 32
     * |[12:8]  |EFG       |Event FIFO Get Index
     * |        |          |Tx Event FIFO read index pointer, range 0 to 31
     * |[20:16] |EFP       |Event FIFO Put Index
     * |        |          |Tx Event FIFO write index pointer, range 0 to 31
     * |[24]    |EFF       |Event FIFO Full
     * |        |          |0 = Tx Event FIFO not full.
     * |        |          |1 = Tx Event FIFO full.
     * |[25]    |TEFL      |Tx Event FIFO Element Lost
     * |        |          |This bit is a copy of interrupt flag TEFL (CANFD_IR[15]). When TEFL is reset, this bit is also reset.
     * |        |          |0 = No Tx Event FIFO element lost.
     * |        |          |1 = Tx Event FIFO element lost, also set after write attempt to Tx Event FIFO of size zero.
     * @var CANFD_T::TXEFA
     * Offset: 0xF8  Tx Event FIFO Acknowledge
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |EFA       |Event FIFO Acknowledge Index
     * |        |          |After the Host has read an element or a sequence of elements from the Tx Event FIFO it has to write the index of the last element read from Tx Event FIFO to EFAI
     * |        |          |This will set the Tx Event FIFO Get Index EFGI (CANFD_TXEFS[12:8]) to EFAI + 1 and update the Event FIFO Fill Level EFFL (CANFD_TXEFS[5:0])
     */
    __I  uint32_t RESERVE0[3];
    __IO uint32_t DBTP;                  /*!< [0x000c] Data Bit Timing & Prescaler Register                             */
    __IO uint32_t TEST;                  /*!< [0x0010] Test Register                                                    */
    __IO uint32_t RWD;                   /*!< [0x0014] RAM Watchdog                                                     */
    __IO uint32_t CCCR;                  /*!< [0x0018] CC Control Register                                              */
    __IO uint32_t NBTP;                  /*!< [0x001c] Nominal Bit Timing & Prescaler Register                          */
    __IO uint32_t TSCC;                  /*!< [0x0020] Timestamp Counter Configuration                                  */
    __IO uint32_t TSCV;                  /*!< [0x0024] Timestamp Counter Value                                          */
    __IO uint32_t TOCC;                  /*!< [0x0028] Timeout Counter Configuration                                    */
    __IO uint32_t TOCV;                  /*!< [0x002c] Timeout Counter Value                                            */
    __I  uint32_t RESERVE1[4];
    __IO uint32_t ECR;                   /*!< [0x0040] Error Counter Register                                           */
    __IO uint32_t PSR;                   /*!< [0x0044] Protocol Status Register                                         */
    __IO uint32_t TDCR;                  /*!< [0x0048] Transmitter Delay Compensation Register                          */
    __I  uint32_t RESERVE2[1];
    __IO uint32_t IR;                    /*!< [0x0050] Interrupt Register                                               */
    __IO uint32_t IE;                    /*!< [0x0054] Interrupt Enable                                                 */
    __IO uint32_t ILS;                   /*!< [0x0058] Interrupt Line Select                                            */
    __IO uint32_t ILE;                   /*!< [0x005c] Interrupt Line Enable                                            */
    __I  uint32_t RESERVE3[8];
    __IO uint32_t GFC;                   /*!< [0x0080] Global Filter Configuration                                      */
    __IO uint32_t SIDFC;                 /*!< [0x0084] Standard ID Filter Configuration                                 */
    __IO uint32_t XIDFC;                 /*!< [0x0088] Extended ID Filter Configuration                                 */
    __I  uint32_t RESERVE4[1];
    __IO uint32_t XIDAM;                 /*!< [0x0090] Extended ID AND Mask                                             */
    __I  uint32_t HPMS;                  /*!< [0x0094] High Priority Message Status                                     */
    __IO uint32_t NDAT1;                 /*!< [0x0098] New Data 1                                                       */
    __IO uint32_t NDAT2;                 /*!< [0x009c] New Data 2                                                       */
    __IO uint32_t RXF0C;                 /*!< [0x00a0] Rx FIFO 0 Configuration                                          */
    __I  uint32_t RXF0S;                 /*!< [0x00a4] Rx FIFO 0 Status                                                 */
    __IO uint32_t RXF0A;                 /*!< [0x00a8] Rx FIFO 0 Acknowledge                                            */
    __IO uint32_t RXBC;                  /*!< [0x00ac] Rx Buffer Configuration                                          */
    __IO uint32_t RXF1C;                 /*!< [0x00b0] Rx FIFO 1 Configuration                                          */
    __I  uint32_t RXF1S;                 /*!< [0x00b4] Rx FIFO 1 Status                                                 */
    __IO uint32_t RXF1A;                 /*!< [0x00b8] Rx FIFO 1 Acknowledge                                            */
    __IO uint32_t RXESC;                 /*!< [0x00bc] Rx Buffer / FIFO Element Size Configuration                      */
    __IO uint32_t TXBC;                  /*!< [0x00c0] Tx Buffer Configuration                                          */
    __I  uint32_t TXFQS;                 /*!< [0x00c4] Tx FIFO/Queue Status                                             */
    __IO uint32_t TXESC;                 /*!< [0x00c8] Tx Buffer Element Size Configuration                             */
    __I  uint32_t TXBRP;                 /*!< [0x00cc] Tx Buffer Request Pending                                        */
    __IO uint32_t TXBAR;                 /*!< [0x00d0] Tx Buffer Add Request                                            */
    __IO uint32_t TXBCR;                 /*!< [0x00d4] Tx Buffer Cancellation Request                                   */
    __I  uint32_t TXBTO;                 /*!< [0x00d8] Tx Buffer Transmission Occurred                                  */
    __I  uint32_t TXBCF;                 /*!< [0x00dc] Tx Buffer Cancellation Finished                                  */
    __IO uint32_t TXBTIE;                /*!< [0x00e0] Tx Buffer Transmission Interrupt Enable                          */
    __IO uint32_t TXBCIE;                /*!< [0x00e4] Tx Buffer Cancellation Finished Interrupt Enable                 */
    __I  uint32_t RESERVE5[2];
    __IO uint32_t TXEFC;                 /*!< [0x00f0] Tx Event FIFO Configuration                                      */
    __I  uint32_t TXEFS;                 /*!< [0x00f4] Tx Event FIFO Status                                             */
    __IO uint32_t TXEFA;                 /*!< [0x00f8] Tx Event FIFO Acknowledge                                        */

} CANFD_T;

/**
    @addtogroup CANFD_CONST CANFD Bit Field Definition
    Constant Definitions for CANFD Controller
@{ */

#define CANFD_DBTP_DSJW_Pos              (0)                                               /*!< CANFD_T::DBTP: DSJW Position           */
#define CANFD_DBTP_DSJW_Msk              (0xful << CANFD_DBTP_DSJW_Pos)                    /*!< CANFD_T::DBTP: DSJW Mask               */

#define CANFD_DBTP_DTSEG2_Pos            (4)                                               /*!< CANFD_T::DBTP: DTSEG2 Position         */
#define CANFD_DBTP_DTSEG2_Msk            (0xful << CANFD_DBTP_DTSEG2_Pos)                  /*!< CANFD_T::DBTP: DTSEG2 Mask             */

#define CANFD_DBTP_DTSEG1_Pos            (8)                                               /*!< CANFD_T::DBTP: DTSEG1 Position         */
#define CANFD_DBTP_DTSEG1_Msk            (0x1ful << CANFD_DBTP_DTSEG1_Pos)                 /*!< CANFD_T::DBTP: DTSEG1 Mask             */

#define CANFD_DBTP_DBRP_Pos              (16)                                              /*!< CANFD_T::DBTP: DBRP Position           */
#define CANFD_DBTP_DBRP_Msk              (0x1ful << CANFD_DBTP_DBRP_Pos)                   /*!< CANFD_T::DBTP: DBRP Mask               */

#define CANFD_DBTP_TDC_Pos               (23)                                              /*!< CANFD_T::DBTP: TDC Position            */
#define CANFD_DBTP_TDC_Msk               (0x1ul << CANFD_DBTP_TDC_Pos)                     /*!< CANFD_T::DBTP: TDC Mask                */

#define CANFD_TEST_LBCK_Pos              (4)                                               /*!< CANFD_T::TEST: LBCK Position           */
#define CANFD_TEST_LBCK_Msk              (0x1ul << CANFD_TEST_LBCK_Pos)                    /*!< CANFD_T::TEST: LBCK Mask               */

#define CANFD_TEST_TX_Pos                (5)                                               /*!< CANFD_T::TEST: TX Position             */
#define CANFD_TEST_TX_Msk                (0x3ul << CANFD_TEST_TX_Pos)                      /*!< CANFD_T::TEST: TX Mask                 */

#define CANFD_TEST_RX_Pos                (7)                                               /*!< CANFD_T::TEST: RX Position             */
#define CANFD_TEST_RX_Msk                (0x1ul << CANFD_TEST_RX_Pos)                      /*!< CANFD_T::TEST: RX Mask                 */

#define CANFD_RWD_WDC_Pos                (0)                                               /*!< CANFD_T::RWD: WDC Position             */
#define CANFD_RWD_WDC_Msk                (0xfful << CANFD_RWD_WDC_Pos)                     /*!< CANFD_T::RWD: WDC Mask                 */

#define CANFD_RWD_WDV_Pos                (8)                                               /*!< CANFD_T::RWD: WDV Position             */
#define CANFD_RWD_WDV_Msk                (0xfful << CANFD_RWD_WDV_Pos)                     /*!< CANFD_T::RWD: WDV Mask                 */

#define CANFD_CCCR_INIT_Pos              (0)                                               /*!< CANFD_T::CCCR: INIT Position           */
#define CANFD_CCCR_INIT_Msk              (0x1ul << CANFD_CCCR_INIT_Pos)                    /*!< CANFD_T::CCCR: INIT Mask               */

#define CANFD_CCCR_CCE_Pos               (1)                                               /*!< CANFD_T::CCCR: CCE Position            */
#define CANFD_CCCR_CCE_Msk               (0x1ul << CANFD_CCCR_CCE_Pos)                     /*!< CANFD_T::CCCR: CCE Mask                */

#define CANFD_CCCR_ASM_Pos               (2)                                               /*!< CANFD_T::CCCR: ASM Position            */
#define CANFD_CCCR_ASM_Msk               (0x1ul << CANFD_CCCR_ASM_Pos)                     /*!< CANFD_T::CCCR: ASM Mask                */

#define CANFD_CCCR_CSA_Pos               (3)                                               /*!< CANFD_T::CCCR: CSA Position            */
#define CANFD_CCCR_CSA_Msk               (0x1ul << CANFD_CCCR_CSA_Pos)                     /*!< CANFD_T::CCCR: CSA Mask                */

#define CANFD_CCCR_CSR_Pos               (4)                                               /*!< CANFD_T::CCCR: CSR Position            */
#define CANFD_CCCR_CSR_Msk               (0x1ul << CANFD_CCCR_CSR_Pos)                     /*!< CANFD_T::CCCR: CSR Mask                */

#define CANFD_CCCR_MON_Pos               (5)                                               /*!< CANFD_T::CCCR: MON Position            */
#define CANFD_CCCR_MON_Msk               (0x1ul << CANFD_CCCR_MON_Pos)                     /*!< CANFD_T::CCCR: MON Mask                */

#define CANFD_CCCR_DAR_Pos               (6)                                               /*!< CANFD_T::CCCR: DAR Position            */
#define CANFD_CCCR_DAR_Msk               (0x1ul << CANFD_CCCR_DAR_Pos)                     /*!< CANFD_T::CCCR: DAR Mask                */

#define CANFD_CCCR_TEST_Pos              (7)                                               /*!< CANFD_T::CCCR: TEST Position           */
#define CANFD_CCCR_TEST_Msk              (0x1ul << CANFD_CCCR_TEST_Pos)                    /*!< CANFD_T::CCCR: TEST Mask               */

#define CANFD_CCCR_FDOE_Pos              (8)                                               /*!< CANFD_T::CCCR: FDOE Position           */
#define CANFD_CCCR_FDOE_Msk              (0x1ul << CANFD_CCCR_FDOE_Pos)                    /*!< CANFD_T::CCCR: FDOE Mask               */

#define CANFD_CCCR_BRSE_Pos              (9)                                               /*!< CANFD_T::CCCR: BRSE Position           */
#define CANFD_CCCR_BRSE_Msk              (0x1ul << CANFD_CCCR_BRSE_Pos)                    /*!< CANFD_T::CCCR: BRSE Mask               */

#define CANFD_CCCR_PXHD_Pos              (12)                                              /*!< CANFD_T::CCCR: PXHD Position           */
#define CANFD_CCCR_PXHD_Msk              (0x1ul << CANFD_CCCR_PXHD_Pos)                    /*!< CANFD_T::CCCR: PXHD Mask               */

#define CANFD_CCCR_EFBI_Pos              (13)                                              /*!< CANFD_T::CCCR: EFBI Position           */
#define CANFD_CCCR_EFBI_Msk              (0x1ul << CANFD_CCCR_EFBI_Pos)                    /*!< CANFD_T::CCCR: EFBI Mask               */

#define CANFD_CCCR_TXP_Pos               (14)                                              /*!< CANFD_T::CCCR: TXP Position            */
#define CANFD_CCCR_TXP_Msk               (0x1ul << CANFD_CCCR_TXP_Pos)                     /*!< CANFD_T::CCCR: TXP Mask                */

#define CANFD_CCCR_NISO_Pos              (15)                                              /*!< CANFD_T::CCCR: NISO Position           */
#define CANFD_CCCR_NISO_Msk              (0x1ul << CANFD_CCCR_NISO_Pos)                    /*!< CANFD_T::CCCR: NISO Mask               */

#define CANFD_NBTP_NTSEG2_Pos            (0)                                               /*!< CANFD_T::NBTP: NTSEG2 Position         */
#define CANFD_NBTP_NTSEG2_Msk            (0x7ful << CANFD_NBTP_NTSEG2_Pos)                 /*!< CANFD_T::NBTP: NTSEG2 Mask             */

#define CANFD_NBTP_NTSEG1_Pos            (8)                                               /*!< CANFD_T::NBTP: NTSEG1 Position         */
#define CANFD_NBTP_NTSEG1_Msk            (0xfful << CANFD_NBTP_NTSEG1_Pos)                 /*!< CANFD_T::NBTP: NTSEG1 Mask             */

#define CANFD_NBTP_NBRP_Pos              (16)                                              /*!< CANFD_T::NBTP: NBRP Position           */
#define CANFD_NBTP_NBRP_Msk              (0x1fful << CANFD_NBTP_NBRP_Pos)                  /*!< CANFD_T::NBTP: NBRP Mask               */

#define CANFD_NBTP_NSJW_Pos              (25)                                              /*!< CANFD_T::NBTP: NSJW Position           */
#define CANFD_NBTP_NSJW_Msk              (0x7ful << CANFD_NBTP_NSJW_Pos)                   /*!< CANFD_T::NBTP: NSJW Mask               */

#define CANFD_TSCC_TSS_Pos               (0)                                               /*!< CANFD_T::TSCC: TSS Position            */
#define CANFD_TSCC_TSS_Msk               (0x3ul << CANFD_TSCC_TSS_Pos)                     /*!< CANFD_T::TSCC: TSS Mask                */

#define CANFD_TSCC_TCP_Pos               (16)                                              /*!< CANFD_T::TSCC: TCP Position            */
#define CANFD_TSCC_TCP_Msk               (0xful << CANFD_TSCC_TCP_Pos)                     /*!< CANFD_T::TSCC: TCP Mask                */

#define CANFD_TSCV_TSC_Pos               (0)                                               /*!< CANFD_T::TSCV: TSC Position            */
#define CANFD_TSCV_TSC_Msk               (0xfffful << CANFD_TSCV_TSC_Pos)                  /*!< CANFD_T::TSCV: TSC Mask                */

#define CANFD_TOCC_ETOC_Pos              (0)                                               /*!< CANFD_T::TOCC: ETOC Position           */
#define CANFD_TOCC_ETOC_Msk              (0x1ul << CANFD_TOCC_ETOC_Pos)                    /*!< CANFD_T::TOCC: ETOC Mask               */

#define CANFD_TOCC_TOS_Pos               (1)                                               /*!< CANFD_T::TOCC: TOS Position            */
#define CANFD_TOCC_TOS_Msk               (0x3ul << CANFD_TOCC_TOS_Pos)                     /*!< CANFD_T::TOCC: TOS Mask                */

#define CANFD_TOCC_TOP_Pos               (16)                                              /*!< CANFD_T::TOCC: TOP Position            */
#define CANFD_TOCC_TOP_Msk               (0xfffful << CANFD_TOCC_TOP_Pos)                  /*!< CANFD_T::TOCC: TOP Mask                */

#define CANFD_TOCV_TOC_Pos               (0)                                               /*!< CANFD_T::TOCV: TOC Position            */
#define CANFD_TOCV_TOC_Msk               (0xfffful << CANFD_TOCV_TOC_Pos)                  /*!< CANFD_T::TOCV: TOC Mask                */

#define CANFD_ECR_TEC_Pos                (0)                                               /*!< CANFD_T::ECR: TEC Position             */
#define CANFD_ECR_TEC_Msk                (0xfful << CANFD_ECR_TEC_Pos)                     /*!< CANFD_T::ECR: TEC Mask                 */

#define CANFD_ECR_REC_Pos                (8)                                               /*!< CANFD_T::ECR: REC Position             */
#define CANFD_ECR_REC_Msk                (0x7ful << CANFD_ECR_REC_Pos)                     /*!< CANFD_T::ECR: REC Mask                 */

#define CANFD_ECR_RP_Pos                 (15)                                              /*!< CANFD_T::ECR: RP Position              */
#define CANFD_ECR_RP_Msk                 (0x1ul << CANFD_ECR_RP_Pos)                       /*!< CANFD_T::ECR: RP Mask                  */

#define CANFD_ECR_CEL_Pos                (16)                                              /*!< CANFD_T::ECR: CEL Position             */
#define CANFD_ECR_CEL_Msk                (0xfful << CANFD_ECR_CEL_Pos)                     /*!< CANFD_T::ECR: CEL Mask                 */

#define CANFD_PSR_LEC_Pos                (0)                                               /*!< CANFD_T::PSR: LEC Position             */
#define CANFD_PSR_LEC_Msk                (0x7ul << CANFD_PSR_LEC_Pos)                      /*!< CANFD_T::PSR: LEC Mask                 */

#define CANFD_PSR_ACT_Pos                (3)                                               /*!< CANFD_T::PSR: ACT Position             */
#define CANFD_PSR_ACT_Msk                (0x3ul << CANFD_PSR_ACT_Pos)                      /*!< CANFD_T::PSR: ACT Mask                 */

#define CANFD_PSR_EP_Pos                 (5)                                               /*!< CANFD_T::PSR: EP Position              */
#define CANFD_PSR_EP_Msk                 (0x1ul << CANFD_PSR_EP_Pos)                       /*!< CANFD_T::PSR: EP Mask                  */

#define CANFD_PSR_EW_Pos                 (6)                                               /*!< CANFD_T::PSR: EW Position              */
#define CANFD_PSR_EW_Msk                 (0x1ul << CANFD_PSR_EW_Pos)                       /*!< CANFD_T::PSR: EW Mask                  */

#define CANFD_PSR_BO_Pos                 (7)                                               /*!< CANFD_T::PSR: BO Position              */
#define CANFD_PSR_BO_Msk                 (0x1ul << CANFD_PSR_BO_Pos)                       /*!< CANFD_T::PSR: BO Mask                  */

#define CANFD_PSR_DLEC_Pos               (8)                                               /*!< CANFD_T::PSR: DLEC Position            */
#define CANFD_PSR_DLEC_Msk               (0x7ul << CANFD_PSR_DLEC_Pos)                     /*!< CANFD_T::PSR: DLEC Mask                */

#define CANFD_PSR_RESI_Pos               (11)                                              /*!< CANFD_T::PSR: RESI Position            */
#define CANFD_PSR_RESI_Msk               (0x1ul << CANFD_PSR_RESI_Pos)                     /*!< CANFD_T::PSR: RESI Mask                */

#define CANFD_PSR_RBRS_Pos               (12)                                              /*!< CANFD_T::PSR: RBRS Position            */
#define CANFD_PSR_RBRS_Msk               (0x1ul << CANFD_PSR_RBRS_Pos)                     /*!< CANFD_T::PSR: RBRS Mask                */

#define CANFD_PSR_RFDF_Pos               (13)                                              /*!< CANFD_T::PSR: RFDF Position            */
#define CANFD_PSR_RFDF_Msk               (0x1ul << CANFD_PSR_RFDF_Pos)                     /*!< CANFD_T::PSR: RFDF Mask                */

#define CANFD_PSR_PXE_Pos                (14)                                              /*!< CANFD_T::PSR: PXE Position             */
#define CANFD_PSR_PXE_Msk                (0x1ul << CANFD_PSR_PXE_Pos)                      /*!< CANFD_T::PSR: PXE Mask                 */

#define CANFD_PSR_TDCV_Pos               (16)                                              /*!< CANFD_T::PSR: TDCV Position            */
#define CANFD_PSR_TDCV_Msk               (0x7ful << CANFD_PSR_TDCV_Pos)                    /*!< CANFD_T::PSR: TDCV Mask                */

#define CANFD_TDCR_TDCF_Pos              (0)                                               /*!< CANFD_T::TDCR: TDCF Position           */
#define CANFD_TDCR_TDCF_Msk              (0x7ful << CANFD_TDCR_TDCF_Pos)                   /*!< CANFD_T::TDCR: TDCF Mask               */

#define CANFD_TDCR_TDCO_Pos              (8)                                               /*!< CANFD_T::TDCR: TDCO Position           */
#define CANFD_TDCR_TDCO_Msk              (0x7ful << CANFD_TDCR_TDCO_Pos)                   /*!< CANFD_T::TDCR: TDCO Mask               */

#define CANFD_IR_RF0N_Pos                (0)                                               /*!< CANFD_T::IR: RF0N Position             */
#define CANFD_IR_RF0N_Msk                (0x1ul << CANFD_IR_RF0N_Pos)                      /*!< CANFD_T::IR: RF0N Mask                 */

#define CANFD_IR_RF0W_Pos                (1)                                               /*!< CANFD_T::IR: RF0W Position             */
#define CANFD_IR_RF0W_Msk                (0x1ul << CANFD_IR_RF0W_Pos)                      /*!< CANFD_T::IR: RF0W Mask                 */

#define CANFD_IR_RF0F_Pos                (2)                                               /*!< CANFD_T::IR: RF0F Position             */
#define CANFD_IR_RF0F_Msk                (0x1ul << CANFD_IR_RF0F_Pos)                      /*!< CANFD_T::IR: RF0F Mask                 */

#define CANFD_IR_RF0L_Pos                (3)                                               /*!< CANFD_T::IR: RF0L Position             */
#define CANFD_IR_RF0L_Msk                (0x1ul << CANFD_IR_RF0L_Pos)                      /*!< CANFD_T::IR: RF0L Mask                 */

#define CANFD_IR_RF1N_Pos                (4)                                               /*!< CANFD_T::IR: RF1N Position             */
#define CANFD_IR_RF1N_Msk                (0x1ul << CANFD_IR_RF1N_Pos)                      /*!< CANFD_T::IR: RF1N Mask                 */

#define CANFD_IR_RF1W_Pos                (5)                                               /*!< CANFD_T::IR: RF1W Position             */
#define CANFD_IR_RF1W_Msk                (0x1ul << CANFD_IR_RF1W_Pos)                      /*!< CANFD_T::IR: RF1W Mask                 */

#define CANFD_IR_RF1F_Pos                (6)                                               /*!< CANFD_T::IR: RF1F Position             */
#define CANFD_IR_RF1F_Msk                (0x1ul << CANFD_IR_RF1F_Pos)                      /*!< CANFD_T::IR: RF1F Mask                 */

#define CANFD_IR_RF1L_Pos                (7)                                               /*!< CANFD_T::IR: RF1L Position             */
#define CANFD_IR_RF1L_Msk                (0x1ul << CANFD_IR_RF1L_Pos)                      /*!< CANFD_T::IR: RF1L Mask                 */

#define CANFD_IR_HPM_Pos                 (8)                                               /*!< CANFD_T::IR: HPM Position              */
#define CANFD_IR_HPM_Msk                 (0x1ul << CANFD_IR_HPM_Pos)                       /*!< CANFD_T::IR: HPM Mask                  */

#define CANFD_IR_TC_Pos                  (9)                                               /*!< CANFD_T::IR: TC Position               */
#define CANFD_IR_TC_Msk                  (0x1ul << CANFD_IR_TC_Pos)                        /*!< CANFD_T::IR: TC Mask                   */

#define CANFD_IR_TCF_Pos                 (10)                                              /*!< CANFD_T::IR: TCF Position              */
#define CANFD_IR_TCF_Msk                 (0x1ul << CANFD_IR_TCF_Pos)                       /*!< CANFD_T::IR: TCF Mask                  */

#define CANFD_IR_TFE_Pos                 (11)                                              /*!< CANFD_T::IR: TFE Position              */
#define CANFD_IR_TFE_Msk                 (0x1ul << CANFD_IR_TFE_Pos)                       /*!< CANFD_T::IR: TFE Mask                  */

#define CANFD_IR_TEFN_Pos                (12)                                              /*!< CANFD_T::IR: TEFN Position             */
#define CANFD_IR_TEFN_Msk                (0x1ul << CANFD_IR_TEFN_Pos)                      /*!< CANFD_T::IR: TEFN Mask                 */

#define CANFD_IR_TEFW_Pos                (13)                                              /*!< CANFD_T::IR: TEFW Position             */
#define CANFD_IR_TEFW_Msk                (0x1ul << CANFD_IR_TEFW_Pos)                      /*!< CANFD_T::IR: TEFW Mask                 */

#define CANFD_IR_TEFF_Pos                (14)                                              /*!< CANFD_T::IR: TEFF Position             */
#define CANFD_IR_TEFF_Msk                (0x1ul << CANFD_IR_TEFF_Pos)                      /*!< CANFD_T::IR: TEFF Mask                 */

#define CANFD_IR_TEFL_Pos                (15)                                              /*!< CANFD_T::IR: TEFL Position             */
#define CANFD_IR_TEFL_Msk                (0x1ul << CANFD_IR_TEFL_Pos)                      /*!< CANFD_T::IR: TEFL Mask                 */

#define CANFD_IR_TSW_Pos                 (16)                                              /*!< CANFD_T::IR: TSW Position              */
#define CANFD_IR_TSW_Msk                 (0x1ul << CANFD_IR_TSW_Pos)                       /*!< CANFD_T::IR: TSW Mask                  */

#define CANFD_IR_MRAF_Pos                (17)                                              /*!< CANFD_T::IR: MRAF Position             */
#define CANFD_IR_MRAF_Msk                (0x1ul << CANFD_IR_MRAF_Pos)                      /*!< CANFD_T::IR: MRAF Mask                 */

#define CANFD_IR_TOO_Pos                 (18)                                              /*!< CANFD_T::IR: TOO Position              */
#define CANFD_IR_TOO_Msk                 (0x1ul << CANFD_IR_TOO_Pos)                       /*!< CANFD_T::IR: TOO Mask                  */

#define CANFD_IR_DRX_Pos                 (19)                                              /*!< CANFD_T::IR: DRX Position              */
#define CANFD_IR_DRX_Msk                 (0x1ul << CANFD_IR_DRX_Pos)                       /*!< CANFD_T::IR: DRX Mask                  */

#define CANFD_IR_ELO_Pos                 (22)                                              /*!< CANFD_T::IR: ELO Position              */
#define CANFD_IR_ELO_Msk                 (0x1ul << CANFD_IR_ELO_Pos)                       /*!< CANFD_T::IR: ELO Mask                  */

#define CANFD_IR_EP_Pos                  (23)                                              /*!< CANFD_T::IR: EP Position               */
#define CANFD_IR_EP_Msk                  (0x1ul << CANFD_IR_EP_Pos)                        /*!< CANFD_T::IR: EP Mask                   */

#define CANFD_IR_EW_Pos                  (24)                                              /*!< CANFD_T::IR: EW Position               */
#define CANFD_IR_EW_Msk                  (0x1ul << CANFD_IR_EW_Pos)                        /*!< CANFD_T::IR: EW Mask                   */

#define CANFD_IR_BO_Pos                  (25)                                              /*!< CANFD_T::IR: BO Position               */
#define CANFD_IR_BO_Msk                  (0x1ul << CANFD_IR_BO_Pos)                        /*!< CANFD_T::IR: BO Mask                   */

#define CANFD_IR_WDI_Pos                 (26)                                              /*!< CANFD_T::IR: WDI Position              */
#define CANFD_IR_WDI_Msk                 (0x1ul << CANFD_IR_WDI_Pos)                       /*!< CANFD_T::IR: WDI Mask                  */

#define CANFD_IR_PEA_Pos                 (27)                                              /*!< CANFD_T::IR: PEA Position              */
#define CANFD_IR_PEA_Msk                 (0x1ul << CANFD_IR_PEA_Pos)                       /*!< CANFD_T::IR: PEA Mask                  */

#define CANFD_IR_PED_Pos                 (28)                                              /*!< CANFD_T::IR: PED Position              */
#define CANFD_IR_PED_Msk                 (0x1ul << CANFD_IR_PED_Pos)                       /*!< CANFD_T::IR: PED Mask                  */

#define CANFD_IR_ARA_Pos                 (29)                                              /*!< CANFD_T::IR: ARA Position              */
#define CANFD_IR_ARA_Msk                 (0x1ul << CANFD_IR_ARA_Pos)                       /*!< CANFD_T::IR: ARA Mask                  */

#define CANFD_IE_RF0NE_Pos               (0)                                               /*!< CANFD_T::IE: RF0NE Position            */
#define CANFD_IE_RF0NE_Msk               (0x1ul << CANFD_IE_RF0NE_Pos)                     /*!< CANFD_T::IE: RF0NE Mask                */

#define CANFD_IE_RF0WE_Pos               (1)                                               /*!< CANFD_T::IE: RF0WE Position            */
#define CANFD_IE_RF0WE_Msk               (0x1ul << CANFD_IE_RF0WE_Pos)                     /*!< CANFD_T::IE: RF0WE Mask                */

#define CANFD_IE_RF0FE_Pos               (2)                                               /*!< CANFD_T::IE: RF0FE Position            */
#define CANFD_IE_RF0FE_Msk               (0x1ul << CANFD_IE_RF0FE_Pos)                     /*!< CANFD_T::IE: RF0FE Mask                */

#define CANFD_IE_RF0LE_Pos               (3)                                               /*!< CANFD_T::IE: RF0LE Position            */
#define CANFD_IE_RF0LE_Msk               (0x1ul << CANFD_IE_RF0LE_Pos)                     /*!< CANFD_T::IE: RF0LE Mask                */

#define CANFD_IE_RF1NE_Pos               (4)                                               /*!< CANFD_T::IE: RF1NE Position            */
#define CANFD_IE_RF1NE_Msk               (0x1ul << CANFD_IE_RF1NE_Pos)                     /*!< CANFD_T::IE: RF1NE Mask                */

#define CANFD_IE_RF1WE_Pos               (5)                                               /*!< CANFD_T::IE: RF1WE Position            */
#define CANFD_IE_RF1WE_Msk               (0x1ul << CANFD_IE_RF1WE_Pos)                     /*!< CANFD_T::IE: RF1WE Mask                */

#define CANFD_IE_RF1FE_Pos               (6)                                               /*!< CANFD_T::IE: RF1FE Position            */
#define CANFD_IE_RF1FE_Msk               (0x1ul << CANFD_IE_RF1FE_Pos)                     /*!< CANFD_T::IE: RF1FE Mask                */

#define CANFD_IE_RF1LE_Pos               (7)                                               /*!< CANFD_T::IE: RF1LE Position            */
#define CANFD_IE_RF1LE_Msk               (0x1ul << CANFD_IE_RF1LE_Pos)                     /*!< CANFD_T::IE: RF1LE Mask                */

#define CANFD_IE_HPME_Pos                (8)                                               /*!< CANFD_T::IE: HPME Position             */
#define CANFD_IE_HPME_Msk                (0x1ul << CANFD_IE_HPME_Pos)                      /*!< CANFD_T::IE: HPME Mask                 */

#define CANFD_IE_TCE_Pos                 (9)                                               /*!< CANFD_T::IE: TCE Position              */
#define CANFD_IE_TCE_Msk                 (0x1ul << CANFD_IE_TCE_Pos)                       /*!< CANFD_T::IE: TCE Mask                  */

#define CANFD_IE_TCFE_Pos                (10)                                              /*!< CANFD_T::IE: TCFE Position             */
#define CANFD_IE_TCFE_Msk                (0x1ul << CANFD_IE_TCFE_Pos)                      /*!< CANFD_T::IE: TCFE Mask                 */

#define CANFD_IE_TFEE_Pos                (11)                                              /*!< CANFD_T::IE: TFEE Position             */
#define CANFD_IE_TFEE_Msk                (0x1ul << CANFD_IE_TFEE_Pos)                      /*!< CANFD_T::IE: TFEE Mask                 */

#define CANFD_IE_TEFNE_Pos               (12)                                              /*!< CANFD_T::IE: TEFNE Position            */
#define CANFD_IE_TEFNE_Msk               (0x1ul << CANFD_IE_TEFNE_Pos)                     /*!< CANFD_T::IE: TEFNE Mask                */

#define CANFD_IE_TEFWE_Pos               (13)                                              /*!< CANFD_T::IE: TEFWE Position            */
#define CANFD_IE_TEFWE_Msk               (0x1ul << CANFD_IE_TEFWE_Pos)                     /*!< CANFD_T::IE: TEFWE Mask                */

#define CANFD_IE_TEFFE_Pos               (14)                                              /*!< CANFD_T::IE: TEFFE Position            */
#define CANFD_IE_TEFFE_Msk               (0x1ul << CANFD_IE_TEFFE_Pos)                     /*!< CANFD_T::IE: TEFFE Mask                */

#define CANFD_IE_TEFLE_Pos               (15)                                              /*!< CANFD_T::IE: TEFLE Position            */
#define CANFD_IE_TEFLE_Msk               (0x1ul << CANFD_IE_TEFLE_Pos)                     /*!< CANFD_T::IE: TEFLE Mask                */

#define CANFD_IE_TSWE_Pos                (16)                                              /*!< CANFD_T::IE: TSWE Position             */
#define CANFD_IE_TSWE_Msk                (0x1ul << CANFD_IE_TSWE_Pos)                      /*!< CANFD_T::IE: TSWE Mask                 */

#define CANFD_IE_MRAFE_Pos               (17)                                              /*!< CANFD_T::IE: MRAFE Position            */
#define CANFD_IE_MRAFE_Msk               (0x1ul << CANFD_IE_MRAFE_Pos)                     /*!< CANFD_T::IE: MRAFE Mask                */

#define CANFD_IE_TOOE_Pos                (18)                                              /*!< CANFD_T::IE: TOOE Position             */
#define CANFD_IE_TOOE_Msk                (0x1ul << CANFD_IE_TOOE_Pos)                      /*!< CANFD_T::IE: TOOE Mask                 */

#define CANFD_IE_DRXE_Pos                (19)                                              /*!< CANFD_T::IE: DRXE Position             */
#define CANFD_IE_DRXE_Msk                (0x1ul << CANFD_IE_DRXE_Pos)                      /*!< CANFD_T::IE: DRXE Mask                 */

#define CANFD_IE_BECE_Pos                (20)                                              /*!< CANFD_T::IE: BECE Position             */
#define CANFD_IE_BECE_Msk                (0x1ul << CANFD_IE_BECE_Pos)                      /*!< CANFD_T::IE: BECE Mask                 */

#define CANFD_IE_BEUE_Pos                (21)                                              /*!< CANFD_T::IE: BEUE Position             */
#define CANFD_IE_BEUE_Msk                (0x1ul << CANFD_IE_BEUE_Pos)                      /*!< CANFD_T::IE: BEUE Mask                 */

#define CANFD_IE_ELOE_Pos                (22)                                              /*!< CANFD_T::IE: ELOE Position             */
#define CANFD_IE_ELOE_Msk                (0x1ul << CANFD_IE_ELOE_Pos)                      /*!< CANFD_T::IE: ELOE Mask                 */

#define CANFD_IE_EPE_Pos                 (23)                                              /*!< CANFD_T::IE: EPE Position              */
#define CANFD_IE_EPE_Msk                 (0x1ul << CANFD_IE_EPE_Pos)                       /*!< CANFD_T::IE: EPE Mask                  */

#define CANFD_IE_EWE_Pos                 (24)                                              /*!< CANFD_T::IE: EWE Position              */
#define CANFD_IE_EWE_Msk                 (0x1ul << CANFD_IE_EWE_Pos)                       /*!< CANFD_T::IE: EWE Mask                  */

#define CANFD_IE_BOE_Pos                 (25)                                              /*!< CANFD_T::IE: BOE Position              */
#define CANFD_IE_BOE_Msk                 (0x1ul << CANFD_IE_BOE_Pos)                       /*!< CANFD_T::IE: BOE Mask                  */

#define CANFD_IE_WDIE_Pos                (26)                                              /*!< CANFD_T::IE: WDIE Position             */
#define CANFD_IE_WDIE_Msk                (0x1ul << CANFD_IE_WDIE_Pos)                      /*!< CANFD_T::IE: WDIE Mask                 */

#define CANFD_IE_PEAE_Pos                (27)                                              /*!< CANFD_T::IE: PEAE Position             */
#define CANFD_IE_PEAE_Msk                (0x1ul << CANFD_IE_PEAE_Pos)                      /*!< CANFD_T::IE: PEAE Mask                 */

#define CANFD_IE_PEDE_Pos                (28)                                              /*!< CANFD_T::IE: PEDE Position             */
#define CANFD_IE_PEDE_Msk                (0x1ul << CANFD_IE_PEDE_Pos)                      /*!< CANFD_T::IE: PEDE Mask                 */

#define CANFD_IE_ARAE_Pos                (29)                                              /*!< CANFD_T::IE: ARAE Position             */
#define CANFD_IE_ARAE_Msk                (0x1ul << CANFD_IE_ARAE_Pos)                      /*!< CANFD_T::IE: ARAE Mask                 */

#define CANFD_ILS_RF0NL_Pos              (0)                                               /*!< CANFD_T::ILS: RF0NL Position           */
#define CANFD_ILS_RF0NL_Msk              (0x1ul << CANFD_ILS_RF0NL_Pos)                    /*!< CANFD_T::ILS: RF0NL Mask               */

#define CANFD_ILS_RF0WL_Pos              (1)                                               /*!< CANFD_T::ILS: RF0WL Position           */
#define CANFD_ILS_RF0WL_Msk              (0x1ul << CANFD_ILS_RF0WL_Pos)                    /*!< CANFD_T::ILS: RF0WL Mask               */

#define CANFD_ILS_RF0FL_Pos              (2)                                               /*!< CANFD_T::ILS: RF0FL Position           */
#define CANFD_ILS_RF0FL_Msk              (0x1ul << CANFD_ILS_RF0FL_Pos)                    /*!< CANFD_T::ILS: RF0FL Mask               */

#define CANFD_ILS_RF0LL_Pos              (3)                                               /*!< CANFD_T::ILS: RF0LL Position           */
#define CANFD_ILS_RF0LL_Msk              (0x1ul << CANFD_ILS_RF0LL_Pos)                    /*!< CANFD_T::ILS: RF0LL Mask               */

#define CANFD_ILS_RF1NL_Pos              (4)                                               /*!< CANFD_T::ILS: RF1NL Position           */
#define CANFD_ILS_RF1NL_Msk              (0x1ul << CANFD_ILS_RF1NL_Pos)                    /*!< CANFD_T::ILS: RF1NL Mask               */

#define CANFD_ILS_RF1WL_Pos              (5)                                               /*!< CANFD_T::ILS: RF1WL Position           */
#define CANFD_ILS_RF1WL_Msk              (0x1ul << CANFD_ILS_RF1WL_Pos)                    /*!< CANFD_T::ILS: RF1WL Mask               */

#define CANFD_ILS_RF1FL_Pos              (6)                                               /*!< CANFD_T::ILS: RF1FL Position           */
#define CANFD_ILS_RF1FL_Msk              (0x1ul << CANFD_ILS_RF1FL_Pos)                    /*!< CANFD_T::ILS: RF1FL Mask               */

#define CANFD_ILS_RF1LL_Pos              (7)                                               /*!< CANFD_T::ILS: RF1LL Position           */
#define CANFD_ILS_RF1LL_Msk              (0x1ul << CANFD_ILS_RF1LL_Pos)                    /*!< CANFD_T::ILS: RF1LL Mask               */

#define CANFD_ILS_HPML_Pos               (8)                                               /*!< CANFD_T::ILS: HPML Position            */
#define CANFD_ILS_HPML_Msk               (0x1ul << CANFD_ILS_HPML_Pos)                     /*!< CANFD_T::ILS: HPML Mask                */

#define CANFD_ILS_TCL_Pos                (9)                                               /*!< CANFD_T::ILS: TCL Position             */
#define CANFD_ILS_TCL_Msk                (0x1ul << CANFD_ILS_TCL_Pos)                      /*!< CANFD_T::ILS: TCL Mask                 */

#define CANFD_ILS_TCFL_Pos               (10)                                              /*!< CANFD_T::ILS: TCFL Position            */
#define CANFD_ILS_TCFL_Msk               (0x1ul << CANFD_ILS_TCFL_Pos)                     /*!< CANFD_T::ILS: TCFL Mask                */

#define CANFD_ILS_TFEL_Pos               (11)                                              /*!< CANFD_T::ILS: TFEL Position            */
#define CANFD_ILS_TFEL_Msk               (0x1ul << CANFD_ILS_TFEL_Pos)                     /*!< CANFD_T::ILS: TFEL Mask                */

#define CANFD_ILS_TEFNL_Pos              (12)                                              /*!< CANFD_T::ILS: TEFNL Position           */
#define CANFD_ILS_TEFNL_Msk              (0x1ul << CANFD_ILS_TEFNL_Pos)                    /*!< CANFD_T::ILS: TEFNL Mask               */

#define CANFD_ILS_TEFWL_Pos              (13)                                              /*!< CANFD_T::ILS: TEFWL Position           */
#define CANFD_ILS_TEFWL_Msk              (0x1ul << CANFD_ILS_TEFWL_Pos)                    /*!< CANFD_T::ILS: TEFWL Mask               */

#define CANFD_ILS_TEFFL_Pos              (14)                                              /*!< CANFD_T::ILS: TEFFL Position           */
#define CANFD_ILS_TEFFL_Msk              (0x1ul << CANFD_ILS_TEFFL_Pos)                    /*!< CANFD_T::ILS: TEFFL Mask               */

#define CANFD_ILS_TEFLL_Pos              (15)                                              /*!< CANFD_T::ILS: TEFLL Position           */
#define CANFD_ILS_TEFLL_Msk              (0x1ul << CANFD_ILS_TEFLL_Pos)                    /*!< CANFD_T::ILS: TEFLL Mask               */

#define CANFD_ILS_TSWL_Pos               (16)                                              /*!< CANFD_T::ILS: TSWL Position            */
#define CANFD_ILS_TSWL_Msk               (0x1ul << CANFD_ILS_TSWL_Pos)                     /*!< CANFD_T::ILS: TSWL Mask                */

#define CANFD_ILS_MRAFL_Pos              (17)                                              /*!< CANFD_T::ILS: MRAFL Position           */
#define CANFD_ILS_MRAFL_Msk              (0x1ul << CANFD_ILS_MRAFL_Pos)                    /*!< CANFD_T::ILS: MRAFL Mask               */

#define CANFD_ILS_TOOL_Pos               (18)                                              /*!< CANFD_T::ILS: TOOL Position            */
#define CANFD_ILS_TOOL_Msk               (0x1ul << CANFD_ILS_TOOL_Pos)                     /*!< CANFD_T::ILS: TOOL Mask                */

#define CANFD_ILS_DRXL_Pos               (19)                                              /*!< CANFD_T::ILS: DRXL Position            */
#define CANFD_ILS_DRXL_Msk               (0x1ul << CANFD_ILS_DRXL_Pos)                     /*!< CANFD_T::ILS: DRXL Mask                */

#define CANFD_ILS_ELOL_Pos               (22)                                              /*!< CANFD_T::ILS: ELOL Position            */
#define CANFD_ILS_ELOL_Msk               (0x1ul << CANFD_ILS_ELOL_Pos)                     /*!< CANFD_T::ILS: ELOL Mask                */

#define CANFD_ILS_EPL_Pos                (23)                                              /*!< CANFD_T::ILS: EPL Position             */
#define CANFD_ILS_EPL_Msk                (0x1ul << CANFD_ILS_EPL_Pos)                      /*!< CANFD_T::ILS: EPL Mask                 */

#define CANFD_ILS_EWL_Pos                (24)                                              /*!< CANFD_T::ILS: EWL Position             */
#define CANFD_ILS_EWL_Msk                (0x1ul << CANFD_ILS_EWL_Pos)                      /*!< CANFD_T::ILS: EWL Mask                 */

#define CANFD_ILS_BOL_Pos                (25)                                              /*!< CANFD_T::ILS: BOL Position             */
#define CANFD_ILS_BOL_Msk                (0x1ul << CANFD_ILS_BOL_Pos)                      /*!< CANFD_T::ILS: BOL Mask                 */

#define CANFD_ILS_WDIL_Pos               (26)                                              /*!< CANFD_T::ILS: WDIL Position            */
#define CANFD_ILS_WDIL_Msk               (0x1ul << CANFD_ILS_WDIL_Pos)                     /*!< CANFD_T::ILS: WDIL Mask                */

#define CANFD_ILS_PEAL_Pos               (27)                                              /*!< CANFD_T::ILS: PEAL Position            */
#define CANFD_ILS_PEAL_Msk               (0x1ul << CANFD_ILS_PEAL_Pos)                     /*!< CANFD_T::ILS: PEAL Mask                */

#define CANFD_ILS_PEDL_Pos               (28)                                              /*!< CANFD_T::ILS: PEDL Position            */
#define CANFD_ILS_PEDL_Msk               (0x1ul << CANFD_ILS_PEDL_Pos)                     /*!< CANFD_T::ILS: PEDL Mask                */

#define CANFD_ILS_ARAL_Pos               (29)                                              /*!< CANFD_T::ILS: ARAL Position            */
#define CANFD_ILS_ARAL_Msk               (0x1ul << CANFD_ILS_ARAL_Pos)                     /*!< CANFD_T::ILS: ARAL Mask                */

#define CANFD_ILE_ENT0_Pos               (0)                                               /*!< CANFD_T::ILE: ENT0 Position            */
#define CANFD_ILE_ENT0_Msk               (0x1ul << CANFD_ILE_ENT0_Pos)                     /*!< CANFD_T::ILE: ENT0 Mask                */

#define CANFD_ILE_ENT1_Pos               (1)                                               /*!< CANFD_T::ILE: ENT1 Position            */
#define CANFD_ILE_ENT1_Msk               (0x1ul << CANFD_ILE_ENT1_Pos)                     /*!< CANFD_T::ILE: ENT1 Mask                */

#define CANFD_GFC_RRFE_Pos               (0)                                               /*!< CANFD_T::GFC: RRFE Position            */
#define CANFD_GFC_RRFE_Msk               (0x1ul << CANFD_GFC_RRFE_Pos)                     /*!< CANFD_T::GFC: RRFE Mask                */

#define CANFD_GFC_RRFS_Pos               (1)                                               /*!< CANFD_T::GFC: RRFS Position            */
#define CANFD_GFC_RRFS_Msk               (0x1ul << CANFD_GFC_RRFS_Pos)                     /*!< CANFD_T::GFC: RRFS Mask                */

#define CANFD_GFC_ANFE_Pos               (2)                                               /*!< CANFD_T::GFC: ANFE Position            */
#define CANFD_GFC_ANFE_Msk               (0x3ul << CANFD_GFC_ANFE_Pos)                     /*!< CANFD_T::GFC: ANFE Mask                */

#define CANFD_GFC_ANFS_Pos               (4)                                               /*!< CANFD_T::GFC: ANFS Position            */
#define CANFD_GFC_ANFS_Msk               (0x3ul << CANFD_GFC_ANFS_Pos)                     /*!< CANFD_T::GFC: ANFS Mask                */

#define CANFD_SIDFC_FLSSA_Pos            (2)                                               /*!< CANFD_T::SIDFC: FLSSA Position         */
#define CANFD_SIDFC_FLSSA_Msk            (0x3ffful << CANFD_SIDFC_FLSSA_Pos)               /*!< CANFD_T::SIDFC: FLSSA Mask             */

#define CANFD_SIDFC_LSS_Pos              (16)                                              /*!< CANFD_T::SIDFC: LSS Position           */
#define CANFD_SIDFC_LSS_Msk              (0xfful << CANFD_SIDFC_LSS_Pos)                   /*!< CANFD_T::SIDFC: LSS Mask               */

#define CANFD_XIDFC_FLESA_Pos            (2)                                               /*!< CANFD_T::XIDFC: FLESA Position         */
#define CANFD_XIDFC_FLESA_Msk            (0x3ffful << CANFD_XIDFC_FLESA_Pos)               /*!< CANFD_T::XIDFC: FLESA Mask             */

#define CANFD_XIDFC_LSE_Pos              (16)                                              /*!< CANFD_T::XIDFC: LSE Position           */
#define CANFD_XIDFC_LSE_Msk              (0x7ful << CANFD_XIDFC_LSE_Pos)                   /*!< CANFD_T::XIDFC: LSE Mask               */

#define CANFD_XIDAM_EIDM_Pos             (0)                                               /*!< CANFD_T::XIDAM: EIDM Position          */
#define CANFD_XIDAM_EIDM_Msk             (0x1ffffffful << CANFD_XIDAM_EIDM_Pos)            /*!< CANFD_T::XIDAM: EIDM Mask              */

#define CANFD_HPMS_BIDX_Pos              (0)                                               /*!< CANFD_T::HPMS: BIDX Position           */
#define CANFD_HPMS_BIDX_Msk              (0x3ful << CANFD_HPMS_BIDX_Pos)                   /*!< CANFD_T::HPMS: BIDX Mask               */

#define CANFD_HPMS_MSI_Pos               (6)                                               /*!< CANFD_T::HPMS: MSI Position            */
#define CANFD_HPMS_MSI_Msk               (0x3ul << CANFD_HPMS_MSI_Pos)                     /*!< CANFD_T::HPMS: MSI Mask                */

#define CANFD_HPMS_FIDX_Pos              (8)                                               /*!< CANFD_T::HPMS: FIDX Position           */
#define CANFD_HPMS_FIDX_Msk              (0x7ful << CANFD_HPMS_FIDX_Pos)                   /*!< CANFD_T::HPMS: FIDX Mask               */

#define CANFD_HPMS_FLST_Pos              (15)                                              /*!< CANFD_T::HPMS: FLST Position           */
#define CANFD_HPMS_FLST_Msk              (0x1ul << CANFD_HPMS_FLST_Pos)                    /*!< CANFD_T::HPMS: FLST Mask               */

#define CANFD_NDAT1_NDn_Pos              (0)                                               /*!< CANFD_T::NDAT1: NDn Position           */
#define CANFD_NDAT1_NDn_Msk              (0xfffffffful << CANFD_NDAT1_NDn_Pos)             /*!< CANFD_T::NDAT1: NDn Mask               */

#define CANFD_NDAT2_NDn_Pos              (0)                                               /*!< CANFD_T::NDAT2: NDn Position           */
#define CANFD_NDAT2_NDn_Msk              (0xfffffffful << CANFD_NDAT2_NDn_Pos)             /*!< CANFD_T::NDAT2: NDn Mask               */

#define CANFD_RXF0C_F0SA_Pos             (2)                                               /*!< CANFD_T::RXF0C: F0SA Position          */
#define CANFD_RXF0C_F0SA_Msk             (0x3ffful << CANFD_RXF0C_F0SA_Pos)                /*!< CANFD_T::RXF0C: F0SA Mask              */

#define CANFD_RXF0C_F0S_Pos              (16)                                              /*!< CANFD_T::RXF0C: F0S Position           */
#define CANFD_RXF0C_F0S_Msk              (0x7ful << CANFD_RXF0C_F0S_Pos)                   /*!< CANFD_T::RXF0C: F0S Mask               */

#define CANFD_RXF0C_F0WM_Pos             (24)                                              /*!< CANFD_T::RXF0C: F0WM Position          */
#define CANFD_RXF0C_F0WM_Msk             (0x7ful << CANFD_RXF0C_F0WM_Pos)                  /*!< CANFD_T::RXF0C: F0WM Mask              */

#define CANFD_RXF0C_F0OM_Pos             (31)                                              /*!< CANFD_T::RXF0C: F0OM Position          */
#define CANFD_RXF0C_F0OM_Msk             (0x1ul << CANFD_RXF0C_F0OM_Pos)                   /*!< CANFD_T::RXF0C: F0OM Mask              */

#define CANFD_RXF0S_F0FL_Pos             (0)                                               /*!< CANFD_T::RXF0S: F0FL Position          */
#define CANFD_RXF0S_F0FL_Msk             (0x7ful << CANFD_RXF0S_F0FL_Pos)                  /*!< CANFD_T::RXF0S: F0FL Mask              */

#define CANFD_RXF0S_F0GI_Pos             (8)                                               /*!< CANFD_T::RXF0S: F0GI Position          */
#define CANFD_RXF0S_F0GI_Msk             (0x3ful << CANFD_RXF0S_F0GI_Pos)                  /*!< CANFD_T::RXF0S: F0GI Mask              */

#define CANFD_RXF0S_F0PI_Pos             (16)                                              /*!< CANFD_T::RXF0S: F0PI Position          */
#define CANFD_RXF0S_F0PI_Msk             (0x3ful << CANFD_RXF0S_F0PI_Pos)                  /*!< CANFD_T::RXF0S: F0PI Mask              */

#define CANFD_RXF0S_F0F_Pos              (24)                                              /*!< CANFD_T::RXF0S: F0F Position           */
#define CANFD_RXF0S_F0F_Msk              (0x1ul << CANFD_RXF0S_F0F_Pos)                    /*!< CANFD_T::RXF0S: F0F Mask               */

#define CANFD_RXF0S_RF0L_Pos             (25)                                              /*!< CANFD_T::RXF0S: RF0L Position          */
#define CANFD_RXF0S_RF0L_Msk             (0x1ul << CANFD_RXF0S_RF0L_Pos)                   /*!< CANFD_T::RXF0S: RF0L Mask              */

#define CANFD_RXF0A_F0A_Pos              (0)                                               /*!< CANFD_T::RXF0A: F0A Position           */
#define CANFD_RXF0A_F0A_Msk              (0x3ful << CANFD_RXF0A_F0A_Pos)                   /*!< CANFD_T::RXF0A: F0A Mask               */

#define CANFD_RXBC_RBSA_Pos              (2)                                               /*!< CANFD_T::RXBC: RBSA Position           */
#define CANFD_RXBC_RBSA_Msk              (0x3ffful << CANFD_RXBC_RBSA_Pos)                 /*!< CANFD_T::RXBC: RBSA Mask               */

#define CANFD_RXF1C_F1SA_Pos             (2)                                               /*!< CANFD_T::RXF1C: F1SA Position          */
#define CANFD_RXF1C_F1SA_Msk             (0x3ffful << CANFD_RXF1C_F1SA_Pos)                /*!< CANFD_T::RXF1C: F1SA Mask              */

#define CANFD_RXF1C_F1S_Pos              (16)                                              /*!< CANFD_T::RXF1C: F1S Position           */
#define CANFD_RXF1C_F1S_Msk              (0x7ful << CANFD_RXF1C_F1S_Pos)                   /*!< CANFD_T::RXF1C: F1S Mask               */

#define CANFD_RXF1C_F1WM_Pos             (24)                                              /*!< CANFD_T::RXF1C: F1WM Position          */
#define CANFD_RXF1C_F1WM_Msk             (0x7ful << CANFD_RXF1C_F1WM_Pos)                  /*!< CANFD_T::RXF1C: F1WM Mask              */

#define CANFD_RXF1C_F1OM_Pos             (31)                                              /*!< CANFD_T::RXF1C: F1OM Position          */
#define CANFD_RXF1C_F1OM_Msk             (0x1ul << CANFD_RXF1C_F1OM_Pos)                   /*!< CANFD_T::RXF1C: F1OM Mask              */

#define CANFD_RXF1S_F1FL_Pos             (0)                                               /*!< CANFD_T::RXF1S: F1FL Position          */
#define CANFD_RXF1S_F1FL_Msk             (0x7ful << CANFD_RXF1S_F1FL_Pos)                  /*!< CANFD_T::RXF1S: F1FL Mask              */

#define CANFD_RXF1S_F1G_Pos              (8)                                               /*!< CANFD_T::RXF1S: F1G Position           */
#define CANFD_RXF1S_F1G_Msk              (0x3ful << CANFD_RXF1S_F1G_Pos)                   /*!< CANFD_T::RXF1S: F1G Mask               */

#define CANFD_RXF1S_F1P_Pos              (16)                                              /*!< CANFD_T::RXF1S: F1P Position           */
#define CANFD_RXF1S_F1P_Msk              (0x3ful << CANFD_RXF1S_F1P_Pos)                   /*!< CANFD_T::RXF1S: F1P Mask               */

#define CANFD_RXF1S_F1F_Pos              (24)                                              /*!< CANFD_T::RXF1S: F1F Position           */
#define CANFD_RXF1S_F1F_Msk              (0x1ul << CANFD_RXF1S_F1F_Pos)                    /*!< CANFD_T::RXF1S: F1F Mask               */

#define CANFD_RXF1S_RF1L_Pos             (25)                                              /*!< CANFD_T::RXF1S: RF1L Position          */
#define CANFD_RXF1S_RF1L_Msk             (0x1ul << CANFD_RXF1S_RF1L_Pos)                   /*!< CANFD_T::RXF1S: RF1L Mask              */

#define CANFD_RXF1S_DMS_Pos              (30)                                              /*!< CANFD_T::RXF1S: DMS Position           */
#define CANFD_RXF1S_DMS_Msk              (0x3ul << CANFD_RXF1S_DMS_Pos)                    /*!< CANFD_T::RXF1S: DMS Mask               */

#define CANFD_RXF1A_F1A_Pos              (0)                                               /*!< CANFD_T::RXF1A: F1A Position           */
#define CANFD_RXF1A_F1A_Msk              (0x3ful << CANFD_RXF1A_F1A_Pos)                   /*!< CANFD_T::RXF1A: F1A Mask               */

#define CANFD_RXESC_F0DS_Pos             (0)                                               /*!< CANFD_T::RXESC: F0DS Position          */
#define CANFD_RXESC_F0DS_Msk             (0x7ul << CANFD_RXESC_F0DS_Pos)                   /*!< CANFD_T::RXESC: F0DS Mask              */

#define CANFD_RXESC_F1DS_Pos             (4)                                               /*!< CANFD_T::RXESC: F1DS Position          */
#define CANFD_RXESC_F1DS_Msk             (0x7ul << CANFD_RXESC_F1DS_Pos)                   /*!< CANFD_T::RXESC: F1DS Mask              */

#define CANFD_RXESC_RBDS_Pos             (8)                                               /*!< CANFD_T::RXESC: RBDS Position          */
#define CANFD_RXESC_RBDS_Msk             (0x7ul << CANFD_RXESC_RBDS_Pos)                   /*!< CANFD_T::RXESC: RBDS Mask              */

#define CANFD_TXBC_TBSA_Pos              (2)                                               /*!< CANFD_T::TXBC: TBSA Position           */
#define CANFD_TXBC_TBSA_Msk              (0x3ffful << CANFD_TXBC_TBSA_Pos)                 /*!< CANFD_T::TXBC: TBSA Mask               */

#define CANFD_TXBC_NDTB_Pos              (16)                                              /*!< CANFD_T::TXBC: NDTB Position           */
#define CANFD_TXBC_NDTB_Msk              (0x3ful << CANFD_TXBC_NDTB_Pos)                   /*!< CANFD_T::TXBC: NDTB Mask               */

#define CANFD_TXBC_TFQS_Pos              (24)                                              /*!< CANFD_T::TXBC: TFQS Position           */
#define CANFD_TXBC_TFQS_Msk              (0x3ful << CANFD_TXBC_TFQS_Pos)                   /*!< CANFD_T::TXBC: TFQS Mask               */

#define CANFD_TXBC_TFQM_Pos              (30)                                              /*!< CANFD_T::TXBC: TFQM Position           */
#define CANFD_TXBC_TFQM_Msk              (0x1ul << CANFD_TXBC_TFQM_Pos)                    /*!< CANFD_T::TXBC: TFQM Mask               */

#define CANFD_TXFQS_TFFL_Pos             (0)                                               /*!< CANFD_T::TXFQS: TFFL Position          */
#define CANFD_TXFQS_TFFL_Msk             (0x3ful << CANFD_TXFQS_TFFL_Pos)                  /*!< CANFD_T::TXFQS: TFFL Mask              */

#define CANFD_TXFQS_TFG_Pos              (8)                                               /*!< CANFD_T::TXFQS: TFG Position           */
#define CANFD_TXFQS_TFG_Msk              (0x1ful << CANFD_TXFQS_TFG_Pos)                   /*!< CANFD_T::TXFQS: TFG Mask               */

#define CANFD_TXFQS_TFQP_Pos             (16)                                              /*!< CANFD_T::TXFQS: TFQP Position          */
#define CANFD_TXFQS_TFQP_Msk             (0x1ful << CANFD_TXFQS_TFQP_Pos)                  /*!< CANFD_T::TXFQS: TFQP Mask              */

#define CANFD_TXFQS_TFQF_Pos             (21)                                              /*!< CANFD_T::TXFQS: TFQF Position          */
#define CANFD_TXFQS_TFQF_Msk             (0x1ul << CANFD_TXFQS_TFQF_Pos)                   /*!< CANFD_T::TXFQS: TFQF Mask              */

#define CANFD_TXESC_TBDS_Pos             (0)                                               /*!< CANFD_T::TXESC: TBDS Position          */
#define CANFD_TXESC_TBDS_Msk             (0x7ul << CANFD_TXESC_TBDS_Pos)                   /*!< CANFD_T::TXESC: TBDS Mask              */

#define CANFD_TXBRP_TRPn_Pos             (0)                                               /*!< CANFD_T::TXBRP: TRPn Position          */
#define CANFD_TXBRP_TRPn_Msk             (0xfffffffful << CANFD_TXBRP_TRPn_Pos)            /*!< CANFD_T::TXBRP: TRPn Mask              */

#define CANFD_TXBAR_ARn_Pos              (0)                                               /*!< CANFD_T::TXBAR: ARn Position           */
#define CANFD_TXBAR_ARn_Msk              (0xfffffffful << CANFD_TXBAR_ARn_Pos)             /*!< CANFD_T::TXBAR: ARn Mask               */

#define CANFD_TXBCR_CRn_Pos              (0)                                               /*!< CANFD_T::TXBCR: CRn Position           */
#define CANFD_TXBCR_CRn_Msk              (0xfffffffful << CANFD_TXBCR_CRn_Pos)             /*!< CANFD_T::TXBCR: CRn Mask               */

#define CANFD_TXBTO_TOn_Pos              (0)                                               /*!< CANFD_T::TXBTO: TOn Position           */
#define CANFD_TXBTO_TOn_Msk              (0xfffffffful << CANFD_TXBTO_TOn_Pos)             /*!< CANFD_T::TXBTO: TOn Mask               */

#define CANFD_TXBCF_CFn_Pos              (0)                                               /*!< CANFD_T::TXBCF: CFn Position           */
#define CANFD_TXBCF_CFn_Msk              (0xfffffffful << CANFD_TXBCF_CFn_Pos)             /*!< CANFD_T::TXBCF: CFn Mask               */

#define CANFD_TXBTIE_TIEn_Pos            (0)                                               /*!< CANFD_T::TXBTIE: TIEn Position         */
#define CANFD_TXBTIE_TIEn_Msk            (0xfffffffful << CANFD_TXBTIE_TIEn_Pos)           /*!< CANFD_T::TXBTIE: TIEn Mask             */

#define CANFD_TXBCIE_CFIEn_Pos           (0)                                               /*!< CANFD_T::TXBCIE: CFIEn Position        */
#define CANFD_TXBCIE_CFIEn_Msk           (0xfffffffful << CANFD_TXBCIE_CFIEn_Pos)          /*!< CANFD_T::TXBCIE: CFIEn Mask            */

#define CANFD_TXEFC_EFSA_Pos             (2)                                               /*!< CANFD_T::TXEFC: EFSA Position          */
#define CANFD_TXEFC_EFSA_Msk             (0x3ffful << CANFD_TXEFC_EFSA_Pos)                /*!< CANFD_T::TXEFC: EFSA Mask              */

#define CANFD_TXEFC_EFS_Pos              (16)                                              /*!< CANFD_T::TXEFC: EFS Position           */
#define CANFD_TXEFC_EFS_Msk              (0x3ful << CANFD_TXEFC_EFS_Pos)                   /*!< CANFD_T::TXEFC: EFS Mask               */

#define CANFD_TXEFC_EFWN_Pos             (24)                                              /*!< CANFD_T::TXEFC: EFWN Position          */
#define CANFD_TXEFC_EFWN_Msk             (0x3ful << CANFD_TXEFC_EFWN_Pos)                  /*!< CANFD_T::TXEFC: EFWN Mask              */

#define CANFD_TXEFS_EFFL_Pos             (0)                                               /*!< CANFD_T::TXEFS: EFFL Position          */
#define CANFD_TXEFS_EFFL_Msk             (0x3ful << CANFD_TXEFS_EFFL_Pos)                  /*!< CANFD_T::TXEFS: EFFL Mask              */

#define CANFD_TXEFS_EFG_Pos              (8)                                               /*!< CANFD_T::TXEFS: EFG Position           */
#define CANFD_TXEFS_EFG_Msk              (0x1ful << CANFD_TXEFS_EFG_Pos)                   /*!< CANFD_T::TXEFS: EFG Mask               */

#define CANFD_TXEFS_EFP_Pos              (16)                                              /*!< CANFD_T::TXEFS: EFP Position           */
#define CANFD_TXEFS_EFP_Msk              (0x1ful << CANFD_TXEFS_EFP_Pos)                   /*!< CANFD_T::TXEFS: EFP Mask               */

#define CANFD_TXEFS_EFF_Pos              (24)                                              /*!< CANFD_T::TXEFS: EFF Position           */
#define CANFD_TXEFS_EFF_Msk              (0x1ul << CANFD_TXEFS_EFF_Pos)                    /*!< CANFD_T::TXEFS: EFF Mask               */

#define CANFD_TXEFS_TEFL_Pos             (25)                                              /*!< CANFD_T::TXEFS: TEFL Position          */
#define CANFD_TXEFS_TEFL_Msk             (0x1ul << CANFD_TXEFS_TEFL_Pos)                   /*!< CANFD_T::TXEFS: TEFL Mask              */

#define CANFD_TXEFA_EFA_Pos              (0)                                               /*!< CANFD_T::TXEFA: EFA Position           */
#define CANFD_TXEFA_EFA_Msk              (0x1ful << CANFD_TXEFA_EFA_Pos)                   /*!< CANFD_T::TXEFA: EFA Mask               */

/**@}*/ /* CANFD_CONST */
/**@}*/ /* end of CANFD register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __CANFD_REG_H__ */
