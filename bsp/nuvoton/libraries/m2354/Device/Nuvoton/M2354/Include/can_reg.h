/**************************************************************************//**
 * @file     can_reg.h
 * @version  V1.00
 * @brief    CAN register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CAN_REG_H__
#define __CAN_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Controller Area Network Controller -------------------------*/
/**
    @addtogroup CAN Controller Area Network Controller(CAN)
    Memory Mapped Structure for CAN Controller
  @{
*/


typedef struct
{



    /**
     * @var CAN_IF_T::CREQ
     * Offset: 0x20, 0x80  IFn (Register Map Note 2) Command Request Registers
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |MessageNumber|Message Number
     * |        |          |0x01-0x20: Valid Message Number, the Message Object in the Message
     * |        |          |RAM is selected for data transfer.
     * |        |          |0x00: Not a valid Message Number, interpreted as 0x20.
     * |        |          |0x21-0x3F: Not a valid Message Number, interpreted as 0x01-0x1F.
     * |[15]    |Busy      |Busy Flag
     * |        |          |0 = Read/write action has finished.
     * |        |          |1 = Writing to the IFn Command Request Register is in progress.
     * |        |          |This bit can only be read by the software.
     * @var CAN_IF_T::CMASK
     * Offset: 0x24, 0x84  IFn Command Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DAT_B     |Access Data Bytes [7:4]
     * |        |          |Write Operation:
     * |        |          |0 = Data Bytes [7:4] unchanged.
     * |        |          |1 = Transfer Data Bytes [7:4] to Message Object.
     * |        |          |Read Operation:
     * |        |          |0 = Data Bytes [7:4] unchanged.
     * |        |          |1 = Transfer Data Bytes [7:4] to IFn Message Buffer Register.
     * |[1]     |DAT_A     |Access Data Bytes [3:0]
     * |        |          |Write Operation:
     * |        |          |0 = Data Bytes [3:0] unchanged.
     * |        |          |1 = Transfer Data Bytes [3:0] to Message Object.
     * |        |          |Read Operation:
     * |        |          |0 = Data Bytes [3:0] unchanged.
     * |        |          |1 = Transfer Data Bytes [3:0] to IFn Message Buffer Register.
     * |[2]     |TxRqst_NewDat|Access Transmission Request Bit When Write Operation
     * |        |          |0 = TxRqst bit unchanged.
     * |        |          |1 = Set TxRqst bit.
     * |        |          |Note: If a transmission is requested by programming bit TxRqst/NewDat in the IFn Command Mask Register, bit TxRqst in the IFn Message Control Register will be ignored.
     * |        |          |Access New Data Bit when Read Operation.
     * |        |          |0 = NewDat bit remains unchanged.
     * |        |          |1 = Clear NewDat bit in the Message Object.
     * |        |          |Note: A read access to a Message Object can be combined with the reset of the control bits IntPnd and NewDat.
     * |        |          |The values of these bits transferred to the IFn Message Control Register always reflect the status before resetting these bits.
     * |[3]     |ClrIntPnd |Clear Interrupt Pending Bit
     * |        |          |Write Operation:
     * |        |          |When writing to a Message Object, this bit is ignored.
     * |        |          |Read Operation:
     * |        |          |0 = IntPnd bit (CAN_IFn_MCON[13]) remains unchanged.
     * |        |          |1 = Clear IntPnd bit in the Message Object.
     * |[4]     |Control   |Control Access Control Bits
     * |        |          |Write Operation:
     * |        |          |0 = Control Bits unchanged.
     * |        |          |1 = Transfer Control Bits to Message Object.
     * |        |          |Read Operation:
     * |        |          |0 = Control Bits unchanged.
     * |        |          |1 = Transfer Control Bits to IFn Message Buffer Register.
     * |[5]     |Arb       |Access Arbitration Bits
     * |        |          |Write Operation:
     * |        |          |0 = Arbitration bits unchanged.
     * |        |          |1 = Transfer Identifier + Dir (CAN_IFn_ARB2[13]) + Xtd (CAN_IFn_ARB2[14]) + MsgVal (CAN_IFn_APB2[15]) to Message Object.
     * |        |          |Read Operation:
     * |        |          |0 = Arbitration bits unchanged.
     * |        |          |1 = Transfer Identifier + Dir + Xtd + MsgVal to IFn Message Buffer Register.
     * |[6]     |Mask      |Access Mask Bits
     * |        |          |Write Operation:
     * |        |          |0 = Mask bits unchanged.
     * |        |          |1 = Transfer Identifier Mask + MDir + MXtd to Message Object.
     * |        |          |Read Operation:
     * |        |          |0 = Mask bits unchanged.
     * |        |          |1 = Transfer Identifier Mask + MDir + MXtd to IFn Message Buffer Register.
     * |[7]     |WR_RD     |Write / Read Mode
     * |        |          |0 = Read: Transfer data from the Message Object addressed by the Command Request Register into the selected Message Buffer Registers.
     * |        |          |1 = Write: Transfer data from the selected Message Buffer Registers to the Message Object addressed by the Command Request Register.
     * @var CAN_IF_T::MASK1
     * Offset: 0x28, 0x88  IFn Mask 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |Msk[15:0] |Identifier Mask 15-0
     * |        |          |0 = The corresponding bit in the identifier of the message object cannot inhibit the match in the acceptance filtering.
     * |        |          |1 = The corresponding identifier bit is used for acceptance filtering.
     * @var CAN_IF_T::MASK2
     * Offset: 0x2C, 0x8C  IFn Mask 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[12:0]  |Msk[28:16]|Identifier Mask 28-16
     * |        |          |0 = The corresponding bit in the identifier of the message object cannot inhibit the match in the acceptance filtering.
     * |        |          |1 = The corresponding identifier bit is used for acceptance filtering.
     * |[14]    |MDir      |Mask Message Direction
     * |        |          |0 = The message direction bit (Dir (CAN_IFn_ARB2[13])) has no effect on the acceptance filtering.
     * |        |          |1 = The message direction bit (Dir) is used for acceptance filtering.
     * |[15]    |MXtd      |Mask Extended Identifier
     * |        |          |0 = The extended identifier bit (IDE) has no effect on the acceptance filtering.
     * |        |          |1 = The extended identifier bit (IDE) is used for acceptance filtering.
     * |        |          |Note: When 11-bit ("standard") Identifiers are used for a Message Object, the identifiers of received Data Frames are written into bits ID28 to ID18 (CAN_IFn_ARB2[12:2]).
     * |        |          |For acceptance filtering, only these bits together with mask bits Msk28 to Msk18 (CAN_IFn_MASK2[12:2]) are considered.
     * @var CAN_IF_T::ARB1
     * Offset: 0x30, 0x90  IFn Arbitration 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |ID[15:0]  |Message Identifier 15-0
     * |        |          |ID28 - ID0, 29-bit Identifier ("Extended Frame").
     * |        |          |ID28 - ID18, 11-bit Identifier ("Standard Frame")
     * @var CAN_IF_T::ARB2
     * Offset: 0x34, 0x94  IFn Arbitration 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[12:0]  |ID[28:16] |Message Identifier 28-16
     * |        |          |ID28 - ID0, 29-bit Identifier ("Extended Frame").
     * |        |          |ID28 - ID18, 11-bit Identifier ("Standard Frame")
     * |[13]    |Dir       |Message Direction
     * |        |          |0 = Direction is receive.
     * |        |          |On TxRqst, a Remote Frame with the identifier of this Message Object is transmitted.
     * |        |          |On reception of a Data Frame with matching identifier, that message is stored in this Message Object.
     * |        |          |1 = Direction is transmit.
     * |        |          |On TxRqst, the respective Message Object is transmitted as a Data Frame.
     * |        |          |On reception of a Remote Frame with matching identifier, the TxRqst bit (CAN_IFn_CMASK[2]) of this Message Object is set (if RmtEn (CAN_IFn_MCON[9]) = one).
     * |[14]    |Xtd       |Extended Identifier
     * |        |          |0 = The 11-bit ("standard") Identifier will be used for this Message Object.
     * |        |          |1 = The 29-bit ("extended") Identifier will be used for this Message Object.
     * |[15]    |MsgVal    |Message Valid
     * |        |          |0 = The Message Object is ignored by the Message Handler.
     * |        |          |1 = The Message Object is configured and should be considered by the Message Handler.
     * |        |          |Note: The application software must reset the MsgVal bit of all unused Messages Objects during the initialization before it resets bit Init (CAN_CON[0]).
     * |        |          |This bit must also be reset before the identifier Id28-0 (CAN_IFn_ARB1/2), the control bits Xtd (CAN_IFn_ARB2[14]), Dir (CAN_IFn_APB2[13]), or the Data Length Code DLC3-0 (CAN_IFn_MCON[3:0]) are modified, or if the Messages Object is no longer required.
     * @var CAN_IF_T::MCON
     * Offset: 0x38, 0x98  IFn Message Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DLC       |Data Length Code
     * |        |          |0-8: Data Frame has 0-8 data bytes.
     * |        |          |9-15: Data Frame has 8 data bytes
     * |        |          |Note: The Data Length Code of a Message Object must be defined the same as in all the corresponding objects with the same identifier at other nodes.
     * |        |          |When the Message Handler stores a data frame, it will write the DLC to the value given by the received message.
     * |        |          |Data 0: 1st data byte of a CAN Data Frame
     * |        |          |Data 1: 2nd data byte of a CAN Data Frame
     * |        |          |Data 2: 3rd data byte of a CAN Data Frame
     * |        |          |Data 3: 4th data byte of a CAN Data Frame
     * |        |          |Data 4: 5th data byte of a CAN Data Frame
     * |        |          |Data 5: 6th data byte of a CAN Data Frame
     * |        |          |Data 6: 7th data byte of a CAN Data Frame
     * |        |          |Data 7 : 8th data byte of a CAN Data Frame
     * |        |          |Note: The Data 0 Byte is the first data byte shifted into the shift register of the CAN Core during a reception while the Data 7 byte is the last.
     * |        |          |When the Message Handler stores a Data Frame, it will write all the eight data bytes into a Message Object.
     * |        |          |If the Data Length Code is less than 8, the remaining bytes of the Message Object will be overwritten by unspecified values.
     * |[7]     |EoB       |End Of Buffer
     * |        |          |0 = Message Object belongs to a FIFO Buffer and is not the last Message Object of that FIFO Buffer.
     * |        |          |1 = Single Message Object or last Message Object of a FIFO Buffer.
     * |        |          |Note: This bit is used to concatenate two or more Message Objects (up to 32) to build a FIFO Buffer.
     * |        |          |For single Message Objects (not belonging to a FIFO Buffer), this bit must always be set to one.
     * |[8]     |TxRqst    |Transmit Request
     * |        |          |0 = This Message Object is not waiting for transmission.
     * |        |          |1 = The transmission of this Message Object is requested and is not yet done.
     * |[9]     |RmtEn     |Remote Enable Control
     * |        |          |0 = At the reception of a Remote Frame, TxRqst (CAN_IFn_MCON[8]) is left unchanged.
     * |        |          |1 = At the reception of a Remote Frame, TxRqst is set.
     * |[10]    |RxIE      |Receive Interrupt Enable Control
     * |        |          |0 = IntPnd (CAN_IFn_MCON[13]) will be left unchanged after a successful reception of a frame.
     * |        |          |1 = IntPnd will be set after a successful reception of a frame.
     * |[11]    |TxIE      |Transmit Interrupt Enable Control
     * |        |          |0 = IntPnd (CAN_IFn_MCON[13]) will be left unchanged after the successful transmission of a frame.
     * |        |          |1 = IntPnd will be set after a successful transmission of a frame.
     * |[12]    |UMask     |Use Acceptance Mask
     * |        |          |0 = Mask ignored.
     * |        |          |1 = Use Mask (Msk28-0, MXtd, and MDir) for acceptance filtering.
     * |        |          |Note: If the UMask bit is set to one, the Message Object's mask bits have to be programmed during initialization of the Message Object before MsgVal bit (CAN_IFn_APB2[15]) is set to one.
     * |[13]    |IntPnd    |Interrupt Pending
     * |        |          |0 = This message object is not the source of an interrupt.
     * |        |          |1 = This message object is the source of an interrupt.
     * |        |          |The Interrupt Identifier in the Interrupt Register will point to this message object if there is no other interrupt source with higher priority.
     * |[14]    |MsgLst    |Message Lost (only valid for Message Objects with direction = receive).
     * |        |          |0 = No message lost since last time this bit was reset by the CPU.
     * |        |          |1 = The Message Handler stored a new message into this object when NewDat was still set, the CPU has lost a message.
     * |[15]    |NewDat    |New Data
     * |        |          |0 = No new data has been written into the data portion of this Message Object by the Message Handler since last time this flag was cleared by the application software.
     * |        |          |1 = The Message Handler or the application software has written new data into the data portion of this Message Object.
     * @var CAN_IF_T::DAT_A1
     * Offset: 0x3C, 0x9C  IFn Data A1 Register (Register Map Note 3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |Data0     |Data Byte 0
     * |        |          |1st data byte of a CAN Data Frame
     * |[15:8]  |Data1     |Data Byte 1
     * |        |          |2nd data byte of a CAN Data Frame
     * @var CAN_IF_T::DAT_A2
     * Offset: 0x40, 0xA0  IFn Data A2 Register (Register Map Note 3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |Data2     |Data Byte 2
     * |        |          |3rd data byte of CAN Data Frame
     * |[15:8]  |Data3     |Data Byte 3
     * |        |          |4th data byte of CAN Data Frame
     * @var CAN_IF_T::DAT_B1
     * Offset: 0x44, 0xA4  IFn Data B1 Register (Register Map Note 3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |Data4     |Data Byte 4
     * |        |          |5th data byte of CAN Data Frame
     * |[15:8]  |Data5     |Data Byte 5
     * |        |          |6th data byte of CAN Data Frame
     * @var CAN_IF_T::DAT_B2
     * Offset: 0x48, 0xA8  IFn Data B2 Register (Register Map Note 3)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |Data6     |Data Byte 6
     * |        |          |7th data byte of CAN Data Frame.
     * |[15:8]  |Data7     |Data Byte 7
     * |        |          |8th data byte of CAN Data Frame.
     */

    __IO uint32_t CREQ;          /* Offset: 0x20, 0x80  IFn (Register Map Note 2) Command Request Registers          */
    __IO uint32_t CMASK;         /* Offset: 0x24, 0x84  IFn Command Mask Register                                    */
    __IO uint32_t MASK1;         /* Offset: 0x28, 0x88  IFn Mask 1 Register                                          */
    __IO uint32_t MASK2;         /* Offset: 0x2C, 0x8C  IFn Mask 2 Register                                          */
    __IO uint32_t ARB1;          /* Offset: 0x30, 0x90  IFn Arbitration 1 Register                                   */
    __IO uint32_t ARB2;          /* Offset: 0x34, 0x94  IFn Arbitration 2 Register                                   */
    __IO uint32_t MCON;          /* Offset: 0x38, 0x98  IFn Message Control Register                                 */
    __IO uint32_t DAT_A1;        /* Offset: 0x3C, 0x9C  IFn Data A1 Register (Register Map Note 3)                   */
    __IO uint32_t DAT_A2;        /* Offset: 0x40, 0xA0  IFn Data A2 Register (Register Map Note 3)                   */
    __IO uint32_t DAT_B1;        /* Offset: 0x44, 0xA4  IFn Data B1 Register (Register Map Note 3)                   */
    __IO uint32_t DAT_B2;        /* Offset: 0x48, 0xA8  IFn Data B2 Register (Register Map Note 3)                   */
    __I  uint32_t RESERVE0[13];

} CAN_IF_T;




typedef struct
{



    /**
     * @var CAN_T::CON
     * Offset: 0x00  Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |Init      |Init Initialization
     * |        |          |0 = Normal Operation.
     * |        |          |1 = Initialization is started.
     * |[1]     |IE        |Module Interrupt Enable Control
     * |        |          |0 = Disabled.
     * |        |          |1 = Enabled.
     * |[2]     |SIE       |Status Change Interrupt Enable Control
     * |        |          |0 = Disabled - No Status Change Interrupt will be generated.
     * |        |          |1 = Enabled - An interrupt will be generated when a message transfer is successfully completed or a CAN bus error is detected.
     * |[3]     |EIE       |Error Interrupt Enable Control
     * |        |          |0 = Disabled - No Error Status Interrupt will be generated.
     * |        |          |1 = Enabled - A change in the bits BOff (CAN_STATUS[7]) or EWarn (CAN_STATUS[6]) in the Status Register will generate an interrupt.
     * |[5]     |DAR       |Automatic Re-Transmission Disable Control
     * |        |          |0 = Automatic Retransmission of disturbed messages enabled.
     * |        |          |1 = Automatic Retransmission disabled.
     * |[6]     |CCE       |Configuration Change Enable Control
     * |        |          |0 = No write access to the Bit Timing Register.
     * |        |          |1 = Write access to the Bit Timing Register (CAN_BTIME) allowed. (while Init bit (CAN_CON[0]) = 1).
     * |[7]     |Test      |Test Mode Enable Control
     * |        |          |0 = Normal Operation.
     * |        |          |1 = Test Mode.
     * @var CAN_T::STATUS
     * Offset: 0x04  Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |LEC       |Last Error Code (Type Of The Last Error To Occur On The CAN Bus)
     * |        |          |The LEC field holds a code, which indicates the type of the last error to occur on the CAN bus.
     * |        |          |This field will be cleared to '0' when a message has been transferred (reception or transmission) without error.
     * |        |          |The unused code '7' may be written by the CPU to check for updates.
     * |        |          |The following table describes the error code.
     * |[3]     |TxOK      |Transmitted A Message Successfully
     * |        |          |0 = Since this bit was reset by the CPU, no message has been successfully transmitted.
     * |        |          |This bit is never reset by the CAN Core.
     * |        |          |1 = Since this bit was last reset by the CPU, a message has been successfully (error free and acknowledged by at least one other node) transmitted.
     * |[4]     |RxOK      |Received A Message Successfully
     * |        |          |0 = No message has been successfully received since this bit was last reset by the CPU.
     * |        |          |This bit is never reset by the CAN Core.
     * |        |          |1 = A message has been successfully received since this bit was last reset by the CPU (independent of the result of acceptance filtering).
     * |[5]     |EPass     |Error Passive (Read Only)
     * |        |          |0 = The CAN Core is error active.
     * |        |          |1 = The CAN Core is in the error passive state as defined in the CAN Specification.
     * |[6]     |EWarn     |Error Warning Status (Read Only)
     * |        |          |0 = Both error counters are below the error warning limit of 96.
     * |        |          |1 = At least one of the error counters in the EML has reached the error warning limit of 96.
     * |[7]     |BOff      |Bus-Off Status (Read Only)
     * |        |          |0 = The CAN module is not in bus-off state.
     * |        |          |1 = The CAN module is in bus-off state.
     * @var CAN_T::ERR
     * Offset: 0x08  Error Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |TEC       |Transmit Error Counter
     * |        |          |Actual state of the Transmit Error Counter. Values between 0 and 255.
     * |[14:8]  |REC       |Receive Error Counter
     * |        |          |Actual state of the Receive Error Counter. Values between 0 and 127.
     * |[15]    |RP        |Receive Error Passive
     * |        |          |0 = The Receive Error Counter is below the error passive level.
     * |        |          |1 = The Receive Error Counter has reached the error passive level as defined in the CAN Specification.
     * @var CAN_T::BTIME
     * Offset: 0x0C  Bit Timing Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |BRP       |Baud Rate Prescaler
     * |        |          |0x01-0x3F: The value by which the oscillator frequency is divided for generating the bit time quanta.
     * |        |          |The bit time is built up from a multiple of this quanta.
     * |        |          |Valid values for the Baud Rate Prescaler are [ 0 ... 63 ].
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
     * |[7:6]   |SJW       |(Re)Synchronization Jump Width
     * |        |          |0x0-0x3: Valid programmed values are [0 ... 3].
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
     * |[11:8]  |TSeg1     |Time Segment Before The Sample Point Minus Sync_Seg
     * |        |          |0x01-0x0F: valid values for TSeg1 are [1 ... 15].
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed is used.
     * |[14:12] |TSeg2     |Time Segment After Sample Point
     * |        |          |0x0-0x7: Valid values for TSeg2 are [0 ... 7].
     * |        |          |The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
     * @var CAN_T::IIDR
     * Offset: 0x10  Interrupt Identifier Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |IntId     |Interrupt Identifier (Indicates The Source Of The Interrupt)
     * |        |          |If several interrupts are pending, the CAN Interrupt Register will point to the pending interrupt with the highest priority, disregarding their chronological order.
     * |        |          |An interrupt remains pending until the application software has cleared it.
     * |        |          |If IntId is different from 0x0000 and IE (CAN_IFn_MCON[1]) is set, the IRQ interrupt signal to the EIC is active.
     * |        |          |The interrupt remains active until IntId is back to value 0x0000 (the cause of the interrupt is reset) or until IE is reset.
     * |        |          |The Status Interrupt has the highest priority.
     * |        |          |Among the message interrupts, the Message Object' s interrupt priority decreases with increasing message number.
     * |        |          |A message interrupt is cleared by clearing the Message Object's IntPnd bit (CAN_IFn_MCON[13]).
     * |        |          |The Status Interrupt is cleared by reading the Status Register.
     * @var CAN_T::TEST
     * Offset: 0x14  Test Register (Register Map Note 1)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |Res       |Reserved
     * |        |          |There are reserved bits.
     * |        |          |These bits are always read as '0' and must always be written with '0'.
     * |[2]     |Basic     |Basic Mode
     * |        |          |0 = Basic Mode disabled.
     * |        |          |1= IF1 Registers used as Tx Buffer, IF2 Registers used as Rx Buffer.
     * |[3]     |Silent    |Silent Mode
     * |        |          |0 = Normal operation.
     * |        |          |1 = The module is in Silent Mode.
     * |[4]     |LBack     |Loop Back Mode Enable Control
     * |        |          |0 = Loop Back Mode is disabled.
     * |        |          |1 = Loop Back Mode is enabled.
     * |[6:5]   |Tx10      |Tx[1:0]: Control Of CAN_TX Pin
     * |        |          |00 = Reset value, CAN_TX pin is controlled by the CAN Core.
     * |        |          |01 = Sample Point can be monitored at CAN_TX pin.
     * |        |          |10 = CAN_TX pin drives a dominant ('0') value.
     * |        |          |11 = CAN_TX pin drives a recessive ('1') value.
     * |[7]     |Rx        |Monitors The Actual Value Of CAN_RX Pin (Read Only)
     * |        |          |0 = The CAN bus is dominant (CAN_RX = '0').
     * |        |          |1 = The CAN bus is recessive (CAN_RX = '1').
     * @var CAN_T::BRPE
     * Offset: 0x18  Baud Rate Prescaler Extension Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |BRPE      |BRPE: Baud Rate Prescaler Extension
     * |        |          |0x00-0x0F: By programming BRPE, the Baud Rate Prescaler can be extended to values up to 1023.
     * |        |          |The actual interpretation by the hardware is that one more than the value programmed by BRPE (MSBs) and BTIME (LSBs) is used.
     * @var CAN_T::IF
     * Offset: 0x20~0xFC  CAN Interface Registers
     * ---------------------------------------------------------------------------------------------------
     * CAN interface structure. Refer to \ref CAN_IF_T for detail information.
         *
     * @var CAN_T::TXREQ1
     * Offset: 0x100  Transmission Request Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TxRqst[16:1]|Transmission Request Bits 16-1 (Of All Message Objects)
     * |        |          |0 = This Message Object is not waiting for transmission.
     * |        |          |1 = The transmission of this Message Object is requested and is not yet done.
     * |        |          |These bits are read only.
     * @var CAN_T::TXREQ2
     * Offset: 0x104  Transmission Request Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TxRqst[32:17]|Transmission Request Bits 32-17 (Of All Message Objects)
     * |        |          |0 = This Message Object is not waiting for transmission.
     * |        |          |1 = The transmission of this Message Object is requested and is not yet done.
     * |        |          |These bits are read only.
     * @var CAN_T::NDAT1
     * Offset: 0x120  New Data Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |NewData[16:1]|New Data Bits 16-1 (Of All Message Objects)
     * |        |          |0 = No new data has been written into the data portion of this Message Object by the Message Handler since the last time this flag was cleared by the application software.
     * |        |          |1 = The Message Handler or the application software has written new data into the data portion of this Message Object.
     * @var CAN_T::NDAT2
     * Offset: 0x124  New Data Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |NewData[32:17]|New Data Bits 32-17 (Of All Message Objects)
     * |        |          |0 = No new data has been written into the data portion of this Message Object by the Message Handler since the last time this flag was cleared by the application software.
     * |        |          |1 = The Message Handler or the application software has written new data into the data portion of this Message Object.
     * @var CAN_T::IPND1
     * Offset: 0x140  Interrupt Pending Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |IntPnd[16:1]|Interrupt Pending Bits 16-1 (Of All Message Objects)
     * |        |          |0 = This message object is not the source of an interrupt.
     * |        |          |1 = This message object is the source of an interrupt.
     * @var CAN_T::IPND2
     * Offset: 0x144  Interrupt Pending Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |IntPnd[32:17]|Interrupt Pending Bits 32-17(Of All Message Objects)
     * |        |          |0 = This message object is not the source of an interrupt.
     * |        |          |1 = This message object is the source of an interrupt.
     * @var CAN_T::MVLD1
     * Offset: 0x160  Message Valid Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MsgVal[16:1]|Message Valid Bits 16-1 (Of All Message Objects) (Read Only)
     * |        |          |0 = This Message Object is ignored by the Message Handler.
     * |        |          |1 = This Message Object is configured and should be considered by the Message Handler.
     * |        |          |Ex.
     * |        |          |CAN_MVLD1[0] means Message object No.1 is valid or not.
     * |        |          |If CAN_MVLD1[0] is set, message object No.1 is configured.
     * @var CAN_T::MVLD2
     * Offset: 0x164  Message Valid Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MsgVal[32:17]|Message Valid Bits 32-17 (Of All Message Objects) (Read Only)
     * |        |          |0 = This Message Object is ignored by the Message Handler.
     * |        |          |1 = This Message Object is configured and should be considered by the Message Handler.
     * |        |          |Ex.CAN_MVLD2[15] means Message object No.32 is valid or not.
     * |        |          |If CAN_MVLD2[15] is set, message object No.32 is configured.
     * @var CAN_T::WU_EN
     * Offset: 0x168  Wake-up Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WAKUP_EN  |Wake-Up Enable Control
     * |        |          |0 = The wake-up function Disabled.
     * |        |          |1 = The wake-up function Enabled.
     * |        |          |Note: User can wake-up system when there is a falling edge in the CAN_Rx pin.
     * @var CAN_T::WU_STATUS
     * Offset: 0x16C  Wake-up Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WAKUP_STS |Wake-Up Status
     * |        |          |0 = No wake-up event occurred.
     * |        |          |1 = Wake-up event occurred.
     * |        |          |Note: This bit can be cleared by writing '0'.
     */

    __IO uint32_t CON;           /* Offset: 0x00  Control Register                                                   */
    __IO uint32_t STATUS;        /* Offset: 0x04  Status Register                                                    */
    __I  uint32_t ERR;           /* Offset: 0x08  Error Counter Register                                             */
    __IO uint32_t BTIME;         /* Offset: 0x0C  Bit Timing Register                                                */
    __I  uint32_t IIDR;          /* Offset: 0x10  Interrupt Identifier Register                                      */
    __IO uint32_t TEST;          /* Offset: 0x14  Test Register (Register Map Note 1)                                */
    __IO uint32_t BRPE;          /* Offset: 0x18  Baud Rate Prescaler Extension Register                             */
    __I  uint32_t RESERVE0[1];
    __IO CAN_IF_T IF[2];         /* Offset: 0x20~0xFC  CAN Interface Registers                                       */
    __I  uint32_t RESERVE1[8];
    __I  uint32_t TXREQ1;        /* Offset: 0x100  Transmission Request Register 1                                   */
    __I  uint32_t TXREQ2;        /* Offset: 0x104  Transmission Request Register 2                                   */
    __I  uint32_t RESERVE3[6];
    __I  uint32_t NDAT1;         /* Offset: 0x120  New Data Register 1                                               */
    __I  uint32_t NDAT2;         /* Offset: 0x124  New Data Register 2                                               */
    __I  uint32_t RESERVE4[6];
    __I  uint32_t IPND1;         /* Offset: 0x140  Interrupt Pending Register 1                                      */
    __I  uint32_t IPND2;         /* Offset: 0x144  Interrupt Pending Register 2                                      */
    __I  uint32_t RESERVE5[6];
    __I  uint32_t MVLD1;         /* Offset: 0x160  Message Valid Register 1                                          */
    __I  uint32_t MVLD2;         /* Offset: 0x164  Message Valid Register 2                                          */
    __IO uint32_t WU_EN;         /* Offset: 0x168  Wake-up Enable Register                                           */
    __IO uint32_t WU_STATUS;     /* Offset: 0x16C  Wake-up Status Register                                           */

} CAN_T;



/**
    @addtogroup CAN_CONST CAN Bit Field Definition
    Constant Definitions for CAN Controller
  @{
*/
/* CAN CON Bit Field Definitions */
#define CAN_CON_TEST_Pos           7                                    /*!< CAN_T::CON: TEST Position */
#define CAN_CON_TEST_Msk           (0x1ul << CAN_CON_TEST_Pos)          /*!< CAN_T::CON: TEST Mask     */

#define CAN_CON_CCE_Pos            6                                    /*!< CAN_T::CON: CCE Position  */
#define CAN_CON_CCE_Msk            (0x1ul << CAN_CON_CCE_Pos)           /*!< CAN_T::CON: CCE Mask      */

#define CAN_CON_DAR_Pos            5                                    /*!< CAN_T::CON: DAR Position  */
#define CAN_CON_DAR_Msk            (0x1ul << CAN_CON_DAR_Pos)           /*!< CAN_T::CON: DAR Mask      */

#define CAN_CON_EIE_Pos            3                                    /*!< CAN_T::CON: EIE Position  */
#define CAN_CON_EIE_Msk            (0x1ul << CAN_CON_EIE_Pos)           /*!< CAN_T::CON: EIE Mask      */

#define CAN_CON_SIE_Pos            2                                    /*!< CAN_T::CON: SIE Position  */
#define CAN_CON_SIE_Msk            (0x1ul << CAN_CON_SIE_Pos)           /*!< CAN_T::CON: SIE Mask      */

#define CAN_CON_IE_Pos             1                                    /*!< CAN_T::CON: IE Position   */
#define CAN_CON_IE_Msk             (0x1ul << CAN_CON_IE_Pos)            /*!< CAN_T::CON: IE Mask       */

#define CAN_CON_INIT_Pos           0                                    /*!< CAN_T::CON: INIT Position */
#define CAN_CON_INIT_Msk           (0x1ul << CAN_CON_INIT_Pos)          /*!< CAN_T::CON: INIT Mask     */

/* CAN STATUS Bit Field Definitions */
#define CAN_STATUS_BOFF_Pos        7                                    /*!< CAN_T::STATUS: BOFF Position  */
#define CAN_STATUS_BOFF_Msk        (0x1ul << CAN_STATUS_BOFF_Pos)       /*!< CAN_T::STATUS: BOFF Mask      */

#define CAN_STATUS_EWARN_Pos       6                                    /*!< CAN_T::STATUS: EWARN Position */
#define CAN_STATUS_EWARN_Msk       (0x1ul << CAN_STATUS_EWARN_Pos)      /*!< CAN_T::STATUS: EWARN Mask     */

#define CAN_STATUS_EPASS_Pos       5                                    /*!< CAN_T::STATUS: EPASS Position */
#define CAN_STATUS_EPASS_Msk       (0x1ul << CAN_STATUS_EPASS_Pos)      /*!< CAN_T::STATUS: EPASS Mask     */

#define CAN_STATUS_RXOK_Pos        4                                    /*!< CAN_T::STATUS: RXOK Position  */
#define CAN_STATUS_RXOK_Msk        (0x1ul << CAN_STATUS_RXOK_Pos)       /*!< CAN_T::STATUS: RXOK Mask      */

#define CAN_STATUS_TXOK_Pos        3                                    /*!< CAN_T::STATUS: TXOK Position  */
#define CAN_STATUS_TXOK_Msk        (0x1ul << CAN_STATUS_TXOK_Pos)       /*!< CAN_T::STATUS: TXOK Mask      */

#define CAN_STATUS_LEC_Pos         0                                    /*!< CAN_T::STATUS: LEC Position   */
#define CAN_STATUS_LEC_Msk         (0x7ul << CAN_STATUS_LEC_Pos)        /*!< CAN_T::STATUS: LEC Mask       */

/* CAN ERR Bit Field Definitions */
#define CAN_ERR_RP_Pos             15                                   /*!< CAN_T::ERR: RP Position       */
#define CAN_ERR_RP_Msk             (0x1ul << CAN_ERR_RP_Pos)            /*!< CAN_T::ERR: RP Mask           */

#define CAN_ERR_REC_Pos            8                                    /*!< CAN_T::ERR: REC Position      */
#define CAN_ERR_REC_Msk            (0x7Ful << CAN_ERR_REC_Pos)          /*!< CAN_T::ERR: REC Mask          */

#define CAN_ERR_TEC_Pos            0                                    /*!< CAN_T::ERR: TEC Position      */
#define CAN_ERR_TEC_Msk            (0xFFul << CAN_ERR_TEC_Pos)          /*!< CAN_T::ERR: TEC Mask          */

/* CAN BTIME Bit Field Definitions */
#define CAN_BTIME_TSEG2_Pos        12                                   /*!< CAN_T::BTIME: TSEG2 Position  */
#define CAN_BTIME_TSEG2_Msk        (0x7ul << CAN_BTIME_TSEG2_Pos)       /*!< CAN_T::BTIME: TSEG2 Mask      */

#define CAN_BTIME_TSEG1_Pos        8                                    /*!< CAN_T::BTIME: TSEG1 Position  */
#define CAN_BTIME_TSEG1_Msk        (0xFul << CAN_BTIME_TSEG1_Pos)       /*!< CAN_T::BTIME: TSEG1 Mask      */

#define CAN_BTIME_SJW_Pos          6                                    /*!< CAN_T::BTIME: SJW Position    */
#define CAN_BTIME_SJW_Msk          (0x3ul << CAN_BTIME_SJW_Pos)         /*!< CAN_T::BTIME: SJW Mask        */

#define CAN_BTIME_BRP_Pos          0                                    /*!< CAN_T::BTIME: BRP Position    */
#define CAN_BTIME_BRP_Msk          (0x3Ful << CAN_BTIME_BRP_Pos)        /*!< CAN_T::BTIME: BRP Mask        */

/* CAN IIDR Bit Field Definitions */
#define CAN_IIDR_INTID_Pos         0                                    /*!< CAN_T::IIDR: INTID Position   */
#define CAN_IIDR_INTID_Msk         (0xFFFFul << CAN_IIDR_INTID_Pos)     /*!< CAN_T::IIDR: INTID Mask       */

/* CAN TEST Bit Field Definitions */
#define CAN_TEST_RX_Pos            7                                    /*!< CAN_T::TEST: RX Position      */
#define CAN_TEST_RX_Msk            (0x1ul << CAN_TEST_RX_Pos)           /*!< CAN_T::TEST: RX Mask          */

#define CAN_TEST_TX_Pos            5                                    /*!< CAN_T::TEST: TX Position      */
#define CAN_TEST_TX_Msk            (0x3ul << CAN_TEST_TX_Pos)           /*!< CAN_T::TEST: TX Mask          */

#define CAN_TEST_LBACK_Pos         4                                    /*!< CAN_T::TEST: LBACK Position   */
#define CAN_TEST_LBACK_Msk         (0x1ul << CAN_TEST_LBACK_Pos)        /*!< CAN_T::TEST: LBACK Mask       */

#define CAN_TEST_SILENT_Pos        3                                    /*!< CAN_T::TEST: Silent Position  */
#define CAN_TEST_SILENT_Msk        (0x1ul << CAN_TEST_SILENT_Pos)       /*!< CAN_T::TEST: Silent Mask      */

#define CAN_TEST_BASIC_Pos         2                                    /*!< CAN_T::TEST: Basic Position   */
#define CAN_TEST_BASIC_Msk         (0x1ul << CAN_TEST_BASIC_Pos)        /*!< CAN_T::TEST: Basic Mask       */

/* CAN BPRE Bit Field Definitions */
#define CAN_BRPE_BRPE_Pos          0                                    /*!< CAN_T::BRPE: BRPE Position    */
#define CAN_BRPE_BRPE_Msk          (0xFul << CAN_BRPE_BRPE_Pos)         /*!< CAN_T::BRPE: BRPE Mask        */

/* CAN IFn_CREQ Bit Field Definitions */
#define CAN_IF_CREQ_BUSY_Pos       15                                     /*!< CAN_IF_T::CREQ: BUSY Position */
#define CAN_IF_CREQ_BUSY_Msk       (0x1ul << CAN_IF_CREQ_BUSY_Pos)        /*!< CAN_IF_T::CREQ: BUSY Mask     */

#define CAN_IF_CREQ_MSGNUM_Pos     0                                      /*!< CAN_IF_T::CREQ: MSGNUM Position */
#define CAN_IF_CREQ_MSGNUM_Msk     (0x3Ful << CAN_IF_CREQ_MSGNUM_Pos)     /*!< CAN_IF_T::CREQ: MSGNUM Mask     */

/* CAN IFn_CMASK Bit Field Definitions */
#define CAN_IF_CMASK_WRRD_Pos      7                                      /*!< CAN_IF_T::CMASK: WRRD Position */
#define CAN_IF_CMASK_WRRD_Msk      (0x1ul << CAN_IF_CMASK_WRRD_Pos)       /*!< CAN_IF_T::CMASK: WRRD Mask     */

#define CAN_IF_CMASK_MASK_Pos      6                                      /*!< CAN_IF_T::CMASK: MASK Position */
#define CAN_IF_CMASK_MASK_Msk      (0x1ul << CAN_IF_CMASK_MASK_Pos)       /*!< CAN_IF_T::CMASK: MASK Mask     */

#define CAN_IF_CMASK_ARB_Pos       5                                      /*!< CAN_IF_T::CMASK: ARB Position  */
#define CAN_IF_CMASK_ARB_Msk       (0x1ul << CAN_IF_CMASK_ARB_Pos)        /*!< CAN_IF_T::CMASK: ARB Mask      */

#define CAN_IF_CMASK_CONTROL_Pos   4                                     /*!< CAN_IF_T::CMASK: CONTROL Position */
#define CAN_IF_CMASK_CONTROL_Msk   (0x1ul << CAN_IF_CMASK_CONTROL_Pos)   /*!< CAN_IF_T::CMASK: CONTROL Mask */

#define CAN_IF_CMASK_CLRINTPND_Pos 3                                       /*!< CAN_IF_T::CMASK: CLRINTPND Position */
#define CAN_IF_CMASK_CLRINTPND_Msk (0x1ul << CAN_IF_CMASK_CLRINTPND_Pos)   /*!< CAN_IF_T::CMASK: CLRINTPND Mask */

#define CAN_IF_CMASK_TXRQSTNEWDAT_Pos 2                                         /*!< CAN_IF_T::CMASK: TXRQSTNEWDAT Position */
#define CAN_IF_CMASK_TXRQSTNEWDAT_Msk (0x1ul << CAN_IF_CMASK_TXRQSTNEWDAT_Pos)  /*!< CAN_IF_T::CMASK: TXRQSTNEWDAT Mask     */

#define CAN_IF_CMASK_DATAA_Pos     1                                    /*!< CAN_IF_T::CMASK: DATAA Position */
#define CAN_IF_CMASK_DATAA_Msk     (0x1ul << CAN_IF_CMASK_DATAA_Pos)    /*!< CAN_IF_T::CMASK: DATAA Mask     */

#define CAN_IF_CMASK_DATAB_Pos     0                                    /*!< CAN_IF_T::CMASK: DATAB Position */
#define CAN_IF_CMASK_DATAB_Msk     (0x1ul << CAN_IF_CMASK_DATAB_Pos)    /*!< CAN_IF_T::CMASK: DATAB Mask     */

/* CAN IFn_MASK1 Bit Field Definitions */
#define CAN_IF_MASK1_MSK_Pos       0                                    /*!< CAN_IF_T::MASK1: MSK Position   */
#define CAN_IF_MASK1_MSK_Msk       (0xFFul << CAN_IF_MASK1_MSK_Pos)     /*!< CAN_IF_T::MASK1: MSK Mask       */

/* CAN IFn_MASK2 Bit Field Definitions */
#define CAN_IF_MASK2_MXTD_Pos      15                                   /*!< CAN_IF_T::MASK2: MXTD Position */
#define CAN_IF_MASK2_MXTD_Msk      (0x1ul << CAN_IF_MASK2_MXTD_Pos)     /*!< CAN_IF_T::MASK2: MXTD Mask     */

#define CAN_IF_MASK2_MDIR_Pos      14                                   /*!< CAN_IF_T::MASK2: MDIR Position */
#define CAN_IF_MASK2_MDIR_Msk      (0x1ul << CAN_IF_MASK2_MDIR_Pos)     /*!< CAN_IF_T::MASK2: MDIR Mask     */

#define CAN_IF_MASK2_MSK_Pos       0                                    /*!< CAN_IF_T::MASK2: MSK Position */
#define CAN_IF_MASK2_MSK_Msk       (0x1FFul << CAN_IF_MASK2_MSK_Pos)    /*!< CAN_IF_T::MASK2: MSK Mask     */

/* CAN IFn_ARB1 Bit Field Definitions */
#define CAN_IF_ARB1_ID_Pos         0                                    /*!< CAN_IF_T::ARB1: ID Position   */
#define CAN_IF_ARB1_ID_Msk         (0xFFFFul << CAN_IF_ARB1_ID_Pos)     /*!< CAN_IF_T::ARB1: ID Mask       */

/* CAN IFn_ARB2 Bit Field Definitions */
#define CAN_IF_ARB2_MSGVAL_Pos     15                                   /*!< CAN_IF_T::ARB2: MSGVAL Position */
#define CAN_IF_ARB2_MSGVAL_Msk     (0x1ul << CAN_IF_ARB2_MSGVAL_Pos)    /*!< CAN_IF_T::ARB2: MSGVAL Mask     */

#define CAN_IF_ARB2_XTD_Pos        14                                   /*!< CAN_IF_T::ARB2: XTD Position    */
#define CAN_IF_ARB2_XTD_Msk        (0x1ul << CAN_IF_ARB2_XTD_Pos)       /*!< CAN_IF_T::ARB2: XTD Mask        */

#define CAN_IF_ARB2_DIR_Pos        13                                   /*!< CAN_IF_T::ARB2: DIR Position    */
#define CAN_IF_ARB2_DIR_Msk        (0x1ul << CAN_IF_ARB2_DIR_Pos)       /*!< CAN_IF_T::ARB2: DIR Mask        */

#define CAN_IF_ARB2_ID_Pos         0                                    /*!< CAN_IF_T::ARB2: ID Position     */
#define CAN_IF_ARB2_ID_Msk         (0x1FFFul << CAN_IF_ARB2_ID_Pos)     /*!< CAN_IF_T::ARB2: ID Mask         */

/* CAN IFn_MCON Bit Field Definitions */
#define CAN_IF_MCON_NEWDAT_Pos     15                                   /*!< CAN_IF_T::MCON: NEWDAT Position */
#define CAN_IF_MCON_NEWDAT_Msk     (0x1ul << CAN_IF_MCON_NEWDAT_Pos)    /*!< CAN_IF_T::MCON: NEWDAT Mask     */

#define CAN_IF_MCON_MSGLST_Pos     14                                   /*!< CAN_IF_T::MCON: MSGLST Position */
#define CAN_IF_MCON_MSGLST_Msk     (0x1ul << CAN_IF_MCON_MSGLST_Pos)    /*!< CAN_IF_T::MCON: MSGLST Mask     */

#define CAN_IF_MCON_INTPND_Pos     13                                   /*!< CAN_IF_T::MCON: INTPND Position */
#define CAN_IF_MCON_INTPND_Msk     (0x1ul << CAN_IF_MCON_INTPND_Pos)    /*!< CAN_IF_T::MCON: INTPND Mask     */

#define CAN_IF_MCON_UMASK_Pos      12                                   /*!< CAN_IF_T::MCON: UMASK Position  */
#define CAN_IF_MCON_UMASK_Msk      (0x1ul << CAN_IF_MCON_UMASK_Pos)     /*!< CAN_IF_T::MCON: UMASK Mask      */

#define CAN_IF_MCON_TXIE_Pos       11                                   /*!< CAN_IF_T::MCON: TXIE Position   */
#define CAN_IF_MCON_TXIE_Msk       (0x1ul << CAN_IF_MCON_TXIE_Pos)      /*!< CAN_IF_T::MCON: TXIE Mask       */

#define CAN_IF_MCON_RXIE_Pos       10                                   /*!< CAN_IF_T::MCON: RXIE Position   */
#define CAN_IF_MCON_RXIE_Msk       (0x1ul << CAN_IF_MCON_RXIE_Pos)      /*!< CAN_IF_T::MCON: RXIE Mask       */

#define CAN_IF_MCON_RMTEN_Pos      9                                    /*!< CAN_IF_T::MCON: RMTEN Position  */
#define CAN_IF_MCON_RMTEN_Msk      (0x1ul << CAN_IF_MCON_RMTEN_Pos)     /*!< CAN_IF_T::MCON: RMTEN Mask      */

#define CAN_IF_MCON_TXRQST_Pos     8                                    /*!< CAN_IF_T::MCON: TXRQST Position */
#define CAN_IF_MCON_TXRQST_Msk     (0x1ul << CAN_IF_MCON_TXRQST_Pos)    /*!< CAN_IF_T::MCON: TXRQST Mask     */

#define CAN_IF_MCON_EOB_Pos        7                                    /*!< CAN_IF_T::MCON: EOB Position    */
#define CAN_IF_MCON_EOB_Msk        (0x1ul << CAN_IF_MCON_EOB_Pos)       /*!< CAN_IF_T::MCON: EOB Mask        */

#define CAN_IF_MCON_DLC_Pos        0                                    /*!< CAN_IF_T::MCON: DLC Position    */
#define CAN_IF_MCON_DLC_Msk        (0xFul << CAN_IF_MCON_DLC_Pos)       /*!< CAN_IF_T::MCON: DLC Mask        */

/* CAN IFn_DATA_A1 Bit Field Definitions */
#define CAN_IF_DAT_A1_DATA1_Pos    8                                    /*!< CAN_IF_T::DATAA1: DATA1 Position */
#define CAN_IF_DAT_A1_DATA1_Msk    (0xFFul << CAN_IF_DAT_A1_DATA1_Pos)  /*!< CAN_IF_T::DATAA1: DATA1 Mask     */

#define CAN_IF_DAT_A1_DATA0_Pos    0                                    /*!< CAN_IF_T::DATAA1: DATA0 Position */
#define CAN_IF_DAT_A1_DATA0_Msk    (0xFFul << CAN_IF_DAT_A1_DATA0_Pos)  /*!< CAN_IF_T::DATAA1: DATA0 Mask     */

/* CAN IFn_DATA_A2 Bit Field Definitions */
#define CAN_IF_DAT_A2_DATA3_Pos    8                                    /*!< CAN_IF_T::DATAA1: DATA3 Position */
#define CAN_IF_DAT_A2_DATA3_Msk    (0xFFul << CAN_IF_DAT_A2_DATA3_Pos)  /*!< CAN_IF_T::DATAA1: DATA3 Mask     */

#define CAN_IF_DAT_A2_DATA2_Pos    0                                    /*!< CAN_IF_T::DATAA1: DATA2 Position */
#define CAN_IF_DAT_A2_DATA2_Msk    (0xFFul << CAN_IF_DAT_A2_DATA2_Pos)  /*!< CAN_IF_T::DATAA1: DATA2 Mask     */

/* CAN IFn_DATA_B1 Bit Field Definitions */
#define CAN_IF_DAT_B1_DATA5_Pos    8                                    /*!< CAN_IF_T::DATAB1: DATA5 Position */
#define CAN_IF_DAT_B1_DATA5_Msk    (0xFFul << CAN_IF_DAT_B1_DATA5_Pos)  /*!< CAN_IF_T::DATAB1: DATA5 Mask */

#define CAN_IF_DAT_B1_DATA4_Pos    0                                    /*!< CAN_IF_T::DATAB1: DATA4 Position */
#define CAN_IF_DAT_B1_DATA4_Msk    (0xFFul << CAN_IF_DAT_B1_DATA4_Pos)  /*!< CAN_IF_T::DATAB1: DATA4 Mask */

/* CAN IFn_DATA_B2 Bit Field Definitions */
#define CAN_IF_DAT_B2_DATA7_Pos    8                                    /*!< CAN_IF_T::DATAB2: DATA7 Position */
#define CAN_IF_DAT_B2_DATA7_Msk    (0xFFul << CAN_IF_DAT_B2_DATA7_Pos)  /*!< CAN_IF_T::DATAB2: DATA7 Mask     */

#define CAN_IF_DAT_B2_DATA6_Pos    0                                    /*!< CAN_IF_T::DATAB2: DATA6 Position */
#define CAN_IF_DAT_B2_DATA6_Msk    (0xFFul << CAN_IF_DAT_B2_DATA6_Pos)  /*!< CAN_IF_T::DATAB2: DATA6 Mask     */

/* CAN IFn_TXRQST1 Bit Field Definitions */
#define CAN_TXRQST1_TXRQST_Pos  0                                        /*!< CAN_T::TXRQST1: TXRQST Position */
#define CAN_TXRQST1_TXRQST_Msk  (0xFFFFul << CAN_TXRQST1_TXRQST_Pos)  /*!< CAN_T::TXRQST1: TXRQST Mask     */

/* CAN IFn_TXRQST2 Bit Field Definitions */
#define CAN_TXRQST2_TXRQST_Pos  0                                        /*!< CAN_T::TXRQST2: TXRQST Position  */
#define CAN_TXRQST2_TXRQST_Msk  (0xFFFFul << CAN_TXRQST2_TXRQST_Pos)  /*!< CAN_T::TXRQST2: TXRQST Mask      */

/* CAN IFn_NDAT1 Bit Field Definitions */
#define CAN_NDAT1_NEWDATA_Pos   0                                        /*!< CAN_T::NDAT1: NEWDATA Position */
#define CAN_NDAT1_NEWDATA_Msk   (0xFFFFul << CAN_NDAT1_NEWDATA_Pos)   /*!< CAN_T::NDAT1: NEWDATA Mask     */

/* CAN IFn_NDAT2 Bit Field Definitions */
#define CAN_NDAT2_NEWDATA_Pos   0                                        /*!< CAN_T::NDAT2: NEWDATA Position */
#define CAN_NDAT2_NEWDATA_Msk   (0xFFFFul << CAN_NDAT2_NEWDATA_Pos)   /*!< CAN_T::NDAT2: NEWDATA Mask     */

/* CAN IFn_IPND1 Bit Field Definitions */
#define CAN_IPND1_INTPND_Pos   0                                         /*!< CAN_T::IPND1: INTPND Position */
#define CAN_IPND1_INTPND_Msk   (0xFFFFul << CAN_IPND1_INTPND_Pos)     /*!< CAN_T::IPND1: INTPND Mask     */

/* CAN IFn_IPND2 Bit Field Definitions */
#define CAN_IPND2_INTPND_Pos   0                                         /*!< CAN_T::IPND2: INTPND Position */
#define CAN_IPND2_INTPND_Msk   (0xFFFFul << CAN_IPND2_INTPND_Pos)     /*!< CAN_T::IPND2: INTPND Mask     */

/* CAN IFn_MVLD1 Bit Field Definitions */
#define CAN_MVLD1_MSGVAL_Pos   0                                         /*!< CAN_T::MVLD1: MSGVAL Position */
#define CAN_MVLD1_MSGVAL_Msk   (0xFFFFul << CAN_MVLD1_MSGVAL_Pos)     /*!< CAN_T::MVLD1: MSGVAL Mask     */

/* CAN IFn_MVLD2 Bit Field Definitions */
#define CAN_MVLD2_MSGVAL_Pos   0                                         /*!< CAN_T::MVLD2: MSGVAL Position */
#define CAN_MVLD2_MSGVAL_Msk   (0xFFFFul << CAN_MVLD2_MSGVAL_Pos)     /*!< CAN_T::MVLD2: MSGVAL Mask     */

/* CAN WUEN Bit Field Definitions */
#define CAN_WU_EN_WAKUP_EN_Pos     0                                         /*!< CAN_T::WU_EN: WAKUP_EN Position */
#define CAN_WU_EN_WAKUP_EN_Msk    (0x1ul << CAN_WU_EN_WAKUP_EN_Pos)           /*!< CAN_T::WU_EN: WAKUP_EN Mask     */

/* CAN WUSTATUS Bit Field Definitions */
#define CAN_WU_STATUS_WAKUP_STS_Pos     0                                      /*!< CAN_T::WU_STATUS: WAKUP_STS Position */
#define CAN_WU_STATUS_WAKUP_STS_Msk    (0x1ul << CAN_WU_STATUS_WAKUP_STS_Pos)   /*!< CAN_T::WU_STATUS: WAKUP_STS Mask     */


/**@}*/ /* CAN_CONST */
/**@}*/ /* end of CAN register group */
/**@}*/ /* end of REGISTER group */


#endif /* __CAN_REG_H__ */
