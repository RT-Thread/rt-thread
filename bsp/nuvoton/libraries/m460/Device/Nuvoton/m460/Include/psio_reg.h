/**************************************************************************//**
 * @file     psio_reg.h
 * @version  V3.00
 * @brief    PSIO register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef __PSIO_REG_H__
#define __PSIO_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup PSIO Programmable Serial IO (PSIO)
    Memory Mapped Structure for PSIO Controller
@{ */

typedef struct
{
    /**
    * @var SCCT_T::SCCTL
     * Offset: 0x20/0x28/0x30/0x38  PSIO Slot Controller n Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |INISLOT   |Initial Slot Period
     * |        |          |The initial slot of the repeat period.
     * |        |          |0000 = No use.
     * |        |          |0001 = SLOT0.
     * |        |          |0010 = SLOT1.
     * |        |          |0011 = SLOT2.
     * |        |          |0100 = SLOT3.
     * |        |          |0101 = SLOT4.
     * |        |          |0110 = SLOT5.
     * |        |          |0111 = SLOT6.
     * |        |          |1000 = SLOT7.
     * |        |          |Others = Reserved.
     * |[7:4]   |ENDSLOT   |End Slot Period
     * |        |          |The end slot of the repeat period.
     * |        |          |0000 = No use.
     * |        |          |0001 = SLOT0.
     * |        |          |0010 = SLOT1.
     * |        |          |0011 = SLOT2.
     * |        |          |0100 = SLOT3.
     * |        |          |0101 = SLOT4.
     * |        |          |0110 = SLOT5.
     * |        |          |0111 = SLOT6.
     * |        |          |1000 = SLOT7.
     * |        |          |Others = Reserved.
     * |[13:8]  |SPLCNT    |Slot Period Loop Count
     * |        |          |000000 ~ 111110 is loop count.
     * |        |          |000000 = Slot period loop count function is disable.
     * |        |          |000001 = Repeat selection loop once, which means total go through selected repeat slots 2 times.
     * |        |          |111111 = Loop until stop PSIO slot controller.
     * |        |          |Note 1: If setting this register 111111 with PDMA mode and OUTPUT mode, it will stop automatically when PDMA is finish and output data in shift register is finished.
     * |        |          |Note 2: If setting this register 111111 with PDMA mode and INPUT mode, it will stop automatically when PDMA is finish.
     * |        |          |Note 3: If PSIO receives stop instruction during repeat mode, it will stop only when the current loop is finished.
     * |[15:14] |TRIGSRC   |PSIO_SCn Trigger Source
     * |        |          |00 = Trigger by software.
     * |        |          |01 = Trigger PSIO_SCn when related PSIO_PIN occurred falling edge.
     * |        |          |10 = Trigger PSIO_SCn when related PSIO_PIN occurred rising edge.
     * |        |          |11 = Trigger PSIO_SCn when related PSIO_PIN occurred rising edge or falling edge.
     * |        |          |Note 1: PSIO slot controller pin can only be trigger by related pins which is setting from SCSEL(PSIOn_GENCTL[25:24]).
     * |        |          |Note 2: Configuring rising or falling signal trigger PSIO, the signal need to hold for at least two PSIO_CLK for de-bounce or PSIO will not be triggered.
     * |[16]    |START     |PSIO_SCn Start
     * |        |          |0 = No use.
     * |        |          |1 = Start PSIO_SCn to count and active related PSIO_PIN.
     * |        |          |Note: this bit is always read as 0.
     * |[17]    |REPEAT    |Whole Repeat Mode
     * |        |          |Slot controller repeats counting forever.
     * |        |          |0 = Repeat mode disabled.
     * |        |          |1 = Repeat mode enabled.
     * |        |          |Note 1: If this bit is enabled with PDMA mode, slot controller will stop automatically when the PDMA finish transferring number of data.
     * |        |          |Note 2: If PSIO receives stop instruction during repeat mode, it will stop only when the current loop is finished.
     * |[18]    |STOP      |PSIO_SCn Stop
     * |        |          |0 = No use.
     * |        |          |1 = Stop PSIO_SCn.
     * |        |          |Note: This bit is always read as 0.
     * |[24]    |BUSY      |PSIO_SCn Busy Flag
     * |        |          |0 = PSIO_SCn is not busy.
     * |        |          |1 = PSIO_SCn is busy.
     * |        |          |Note: This bit will be set to 1 when slot controller starts to count automatically and it will be cleared to 0 automatically when slot controller stops counting, too.
     * |[25]    |IDLE      |PSIO_SCn Idle Flag
     * |        |          |0 = PSIO_SCn is not IDLE.
     * |        |          |1 = PSIO_SCn is IDLE.
     * |        |          |Note 1: This bit will be cleared to 0 when slot controller starts to count automatically.
     * |        |          |Note 2: This bit will be set to 1 when configuring it 1 by software.
     * |        |          |Note 3: This bit is set to distinguish INTERVAL(PSIOn_GENCTL[5:4]) and INITIAL(PSIOn_GENCTL[3:2]).
     * @var SCCT_T::SCSLOT
     * Offset: 0x24/0x2C/0x34/0x3C  PSIO Slot Controller n Slot Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |SLOT0     |PSIO Slot Controller Slot0 Tick Count
     * |        |          |0 to 15.
     * |        |          |Note 1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note 2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note 3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     * |[7:4]   |SLOT1     |PSIO Slot Controller Slot1 Tick Count
     * |        |          |0 to 15.
     * |        |          |Note 1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note 2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note 3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     * |[11:8]  |SLOT2     |PSIO Slot Controller Slot2 Tick Count
     * |        |          |0 to 15.
     * |        |          |Note 1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note 2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note 3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     * |[15:12] |SLOT3     |PSIO Slot Controller Slot3 Tick Count
     * |        |          |0 to 15.
     * |        |          |Note1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     * |[19:16] |SLOT4     |PSIO Slot Controller Slot4 Tick Count
     * |        |          |0 to 15.
     * |        |          |Note 1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note 2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note 3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     * |[23:20] |SLOT5     |PSIO Slot Controller Slot5 Tick Count
     * |        |          |0 to 15
     * |        |          |Note 1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note 2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note 3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     * |[27:24] |SLOT6     |PSIO Slot Controller Slot6 Tick Count
     * |        |          |0 to 15
     * |        |          |Note 1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note 2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note 3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     * |[31:28] |SLOT7     |PSIO Slot Controller Slot7 Tick Count
     * |        |          |0 to 15.
     * |        |          |Note 1: Filling in all 0 to this field indicates to disable this slot.
     * |        |          |Note 2: The disabled slot should not be set between the enabled slots, or the order of enabled slot which is after the disabled slot will not be enabled.
     * |        |          |Note 3: The shortest slot length is 6 when I/O mode is switched from output mode to input mode.
     */
    __IO uint32_t SCCTL;                 /*!< PSIO Slot Counter n Control register                                     */
    __IO uint32_t SCSLOT;                /*!< PSIO Slot Counter n Slot Register                                        */

} SCCT_T;

typedef struct
{
    /**
    * @var GNCT_T::GENCTL
    * Offset: 0x40/0x60/0x80/0xA0/0xC0/0xE0/0x100/0x120  PSIOn General Control Register
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[1:0]   |IOMODE    |IO Mode
    * |        |          |I/O mode state represent the I/O state when slot controller has not started counting or slot controller has started counting but has not cross the switch I/O mode check point.
    * |        |          |00 = Input mode.
    * |        |          |01 = Output mode.
    * |        |          |10 = Open-drain mode.
    * |        |          |11 = Quasi-bidirectional mode.
    * |        |          |Note 1: When slot controller stops counting, it will switch to the current I/O mode setting.
    * |        |          |Note 2: When PSIO uses quasi-bidirectional mode or open-drain mode to trigger slot controller, the initial or interval output state need to be set output high level, or the pin will not be trigger.
    * |[3:2]   |INITIAL   |Initial Output
    * |        |          |The output state of PSIO when slot controller stops counting and IDLE (PSIO_SCnCTL[25]) is 1.
    * |        |          |00 = Low level.
    * |        |          |01 = High level.
    * |        |          |10 = Last output.
    * |        |          |11 = Toggle.
    * |        |          |Note 1: Only when IOMODE is not input mode, then this register is effective.
    * |        |          |Note 2: This bit is effective only when IDLE(PSIO_SCnCTL[25]) is high.
    * |[5:4]   |INTERVAL  |Interval Output
    * |        |          |The output of PSIO when slot controller stops counting and IDLE (PSIO_SCnCTL[25]) is 0.
    * |        |          |00 = Low level.
    * |        |          |01 = High level.
    * |        |          |10 = Last output.
    * |        |          |11 = Toggle.
    * |        |          |Note 1: Only when IOMODE is not input mode, then this register is effective.
    * |        |          |Note 2: This bit is effective only when IDLE(PSIO_SCnCTL[25]) is low.
    * |[11:8]  |SW0CP     |Switch0 Check Point
    * |        |          |0000 = No use.
    * |        |          |0001 = CHECK POINT 0.
    * |        |          |0010 = CHECK POINT 1.
    * |        |          |0011 = CHECK POINT 2.
    * |        |          |0100 = CHECK POINT 3.
    * |        |          |0101 = CHECK POINT 4.
    * |        |          |0110 = CHECK POINT 5.
    * |        |          |0111 = CHECK POINT 6.
    * |        |          |1000 = CHECK POINT 7.
    * |        |          |Others = Reserved.
    * |[15:12] |SW1CP     |Switch1 Check Point
    * |        |          |0000 = No use.
    * |        |          |0001 = CHECK POINT 0.
    * |        |          |0010 = CHECK POINT 1.
    * |        |          |0011 = CHECK POINT 2.
    * |        |          |0100 = CHECK POINT 3.
    * |        |          |0101 = CHECK POINT 4.
    * |        |          |0110 = CHECK POINT 5.
    * |        |          |0111 = CHECK POINT 6.
    * |        |          |1000 = CHECK POINT 7.
    * |        |          |Others = Reserved.
    * |[17:16] |MODESW0   |Mode Switch0 Point
    * |        |          |Mode at the switch0 point
    * |        |          |00 = Input mode.
    * |        |          |01 = Output mode.
    * |        |          |10 = Open-drain mode.
    * |        |          |11 = Quasi-bidirectional mode.
    * |[19:18] |MODESW1   |Mode Switch1 Point
    * |        |          |Mode at the switch1 point
    * |        |          |00 = Input mode.
    * |        |          |01 = Output mode.
    * |        |          |10 = Open-drain mode.
    * |        |          |11 = Quasi-bidirectional mode.
    * |[25:24] |SCSEL     |Slot Controller Selection
    * |        |          |Select slot controller for check point.
    * |        |          |00 = SLOT CONTROLLER0.
    * |        |          |01 = SLOT CONTROLLER1.
    * |        |          |10 = SLOT CONTROLLER2.
    * |        |          |11 = SLOT CONTROLLER3.
    * |[26]    |PINEN     |Pin Enable Bit
    * |        |          |0 = Pin Disabled.
    * |        |          |1 = Pin Enabled.
    * @var GNCT_T::DATCTL
    * Offset: 0x44/0x64/0x84/0xA4/0xC4/0xE4/0x104/0x124  PSIOn Data Control Register
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[4:0]   |OUTDATWD  |Output Data Width
    * |        |          |Indicate the data width of OUTPUT DATA register.
    * |        |          |Output data size = OUTDATWD +1.
    * |        |          |e.g.
    * |        |          |5'b00000 = 1 bit.
    * |        |          |5'b11111 = 32 bit.
    * |[12:8]  |INDATWD   |Input Data Width
    * |        |          |Indicate the data width of INPUT DATA register.
    * |        |          |Input data size = INDATWD +1.
    * |        |          |e.g.
    * |        |          |5'b00000 = 1 bit.
    * |        |          |5'b11111 = 32 bit.
    * |[16]    |ORDER     |Order
    * |        |          |The order of output data and input data.
    * |        |          |0 = Data transfer start form LSB.
    * |        |          |1 = Data transfer start form MSB.
    * |[25:24] |OUTDEPTH  |Output Data Depth
    * |        |          |Represent the data depth of the output buffer, when data width is larger than 16-bit, this setting can be ignored.
    * |        |          |When the data width is between 9-bit and 16 bit,
    * |        |          |0 = OUTDEPTH [0], the data depth is 1.
    * |        |          |1 = OUTDEPTH [0], the data depth is 2.
    * |        |          |When the data width is less than or equal to 8-bit,
    * |        |          |0 = OUTDEPTH, the data depth is 1.
    * |        |          |1 = OUTDEPTH, the data depth is 2.
    * |        |          |2 = OUTDEPTH, the data depth is 3.
    * |        |          |3 = OUTDEPTH, the data depth is 4.
    * |        |          |Note 1: The output data depth impacts when the output data empty flag and output under flow data flag is set to 1.
    * |        |          |Note 2: There is no difference of data depth no matter using software program data or PDMA program data.
    * |[29:28] |INDEPTH   |Input Data Depth
    * |        |          |Represent the data depth of the input buffer, when data width is larger than 16-bit, this setting can be ignored.
    * |        |          |When the data width is between 9-bit and 16 bit,
    * |        |          |0 = INDEPTH[0], the data depth is 1.
    * |        |          |1 = INDEPTH[0], the data depth is 2.
    * |        |          |When the data width is less than or equal to 8-bit,
    * |        |          |0 = INDEPTH, the data depth is 1.
    * |        |          |1 = INDEPTH, the data depth is 2.
    * |        |          |2 = INDEPTH, the data depth is 3.
    * |        |          |3 = INDEPTH, the data depth is 4.
    * |        |          |Note 1: The input data depth impacts when the input data full flag and input data over flow flag is set to 1.
    * |        |          |Note 2: There is no difference of data depth no matter using software program data or PDMA program data.
    * @var GNCT_T::INSTS
    * Offset: 0x48/0x68/0x88/0xA8/0xC8/0xE8/0x108/0x128  PSIOn Input Status Register
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[7:0]   |INSTS     |Input Status
    * |        |          |Status input buffer. This register can be read clear.
    * |        |          |Note: When the valid bit is set, the valid bits number of INSTS is equal to the number of check points from the previous time INSTS update to the current INSTS update.
    * @var GNCT_T::INDAT
    * Offset: 0x4C/0x6C/0x8C/0xAC/0xCC/0xEC/0x10C/0x12C  PSIOn Input Data Register
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[31:0]  |INDAT     |Input Data Buffer
    * |        |          |This register can be read clear.
    * |        |          |Note: The input data sample time is according to the slot length.
    * |        |          |The sampling time is near 3/4 slot.
    * |        |          |When the slot length is 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, PSIO sample input data when the slot controller count to 1, 2, 2, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9.
    * @var GNCT_T::OUTDAT
    * Offset: 0x50/0x70/0x90/0xB0/0xD0/0xF0/0x110/0x130  PSIOn Output Data Register
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[31:0]  |OUTDAT    |Output Data Buffer
    * |        |          |This field is used to configure output data.
    * @var GNCT_T::CPCTL0
    * Offset: 0x54/0x74/0x94/0xB4/0xD4/0xF4/0x114/0x134  PSIOn Check Point Control Register 0
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[2:0]   |CKPT0     |Check Point 0
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * |[6:4]   |CKPT1     |Check Point 1
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * |[10:8]  |CKPT2     |Check Point 2
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * |[14:12] |CKPT3     |Check Point 3
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * |[18:16] |CKPT4     |Check Point 4
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * |[22:20] |CKPT5     |Check Point 5
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * |[26:24] |CKPT6     |Check Point 6
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * |[30:28] |CKPT7     |Check Point 7
    * |        |          |This field is used to link check point and slot controller slot.
    * |        |          |0000 = No use.
    * |        |          |0001 = SLOT0.
    * |        |          |0010 = SLOT1.
    * |        |          |0011 = SLOT2.
    * |        |          |0100 = SLOT3.
    * |        |          |0101 = SLOT4.
    * |        |          |0110 = SLOT5.
    * |        |          |0111 = SLOT6.
    * |        |          |1000 = SLOT7.
    * |        |          |Others = Reserved.
    * |        |          |Note 1: If there are two check points that select the same SLOT, the pin will follow settings of the smaller check point number.
    * |        |          |Note 2: The correlated SLOT should be filled in order from SLOT0 to SLOT7, or the check point action will not be triggered.
    * @var GNCT_T::CPCTL1
    * Offset: 0x58/0x78/0x98/0xB8/0xD8/0xF8/0x118/0x138  PSIOn Check Point Control Register 1
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[2:0]   |CKPT0ACT  |Check Point 0 Action
    * |        |          |Select check point action at check point0.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    * |[6:4]   |CKPT1ACT  |Check Point 1 Action
    * |        |          |Select check point action at check point1.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    * |[10:8]  |CKPT2ACT  |Check Point 2 Action
    * |        |          |Select check point action at check point2.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    * |[14:12] |CKPT3ACT  |Check Point 3 Action
    * |        |          |Select check point action at check point3.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    * |[18:16] |CKPT4ACT  |Check Point 4 Action
    * |        |          |Select check point action at check point4.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    * |[22:20] |CKPT5ACT  |Check Point 5 Action
    * |        |          |Select check point action at check point5.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    * |[26:24] |CKPT6ACT  |Check Point 6 Action
    * |        |          |Select check point action at check point6.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    * |[30:28] |CKPT7ACT  |Check Point 7 Action
    * |        |          |Select check point action at check point7.
    * |        |          |000 = Output level low.
    * |        |          |001 = Output level high.
    * |        |          |010 = Output from data buffer.
    * |        |          |011 = Output toggle.
    * |        |          |100 = Input data buffer.
    * |        |          |101 = Input status.
    * |        |          |110 = Input status record and update.
    * |        |          |Others = Reserved.
    * |        |          |Note: Pin action must meet the correlated I/O mode (PSIOn_GENCTL[1:0]).
    */
    __IO uint32_t GENCTL;                /*!< PSIOn General Control Register                                           */
    __IO uint32_t DATCTL;                /*!< PSIOn Data Control Register                                              */
    __I  uint32_t INSTS;                 /*!< PSIOn Input Status Register                                              */
    __I  uint32_t INDAT;                 /*!< PSIOn Input Data Register                                                */
    __O  uint32_t OUTDAT;                /*!< PSIOn Output Data Register                                               */
    __IO uint32_t CPCTL0;                /*!< PSIOn Check Point Control Register 0                                     */
    __IO uint32_t CPCTL1;                /*!< PSIOn Check Point Control Register 1                                     */
    __I  uint32_t RESERVE0[1];
} GNCT_T;

typedef struct
{
    /**
     * @var PSIO_T::INTCTL
     * Offset: 0x00  PSIO Interrupt Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |CONI0SS   |Configurable Interrupt 0 Slot Selection
     * |        |          |0000 = No use.
     * |        |          |0001 = SLOT0.
     * |        |          |0010 = SLOT1.
     * |        |          |0011 = SLOT2.
     * |        |          |0100 = SLOT3.
     * |        |          |0101 = SLOT4.
     * |        |          |0110 = SLOT5.
     * |        |          |0111 = SLOT6.
     * |        |          |1000 = SLOT7.
     * |        |          |Others = Reserved.
     * |[6:4]   |CONI1SS   |Configurable Interrupt 1 Slot Selection
     * |        |          |0000 = No use.
     * |        |          |0001 = SLOT0.
     * |        |          |0010 = SLOT1.
     * |        |          |0011 = SLOT2.
     * |        |          |0100 = SLOT3.
     * |        |          |0101 = SLOT4.
     * |        |          |0110 = SLOT5.
     * |        |          |0111 = SLOT6.
     * |        |          |1000 = SLOT7.
     * |        |          |Others = Reserved.
     * |[9:8]   |CONI0SCS  |Configurable Interrupt 0 Slot Controller Selection
     * |        |          |Select Slot controller for interrupt 0.
     * |        |          |00 = Slot controller 0.
     * |        |          |01 = Slot controller 1.
     * |        |          |10 = Slot controller 2.
     * |        |          |11 = Slot controller 3.
     * |[13:12] |CONI1SCS  |Configurable Interrupt 1 Slot Controller Selection
     * |        |          |Select Slot controller for interrupt 1.
     * |        |          |00 = Slot controller 0.
     * |        |          |01 = Slot controller 1.
     * |        |          |10 = Slot controller 2.
     * |        |          |11 = Slot controller 3.
     * @var PSIO_T::INTEN
     * Offset: 0x04  PSIO Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CON0IE    |Configurable Interrupt 0 Enable Bit
     * |        |          |This field is used to enable selective interrupt 0.
     * |        |          |0 = Selective interrupt 0 Disabled.
     * |        |          |1 = Selective interrupt 0 Enabled.
     * |[1]     |CON1IE    |Configurable Interrupt 1 Enable Bit
     * |        |          |This field is used to enable selective interrupt 1.
     * |        |          |0 = Selective interrupt 1 Disabled.
     * |        |          |1 = Selective interrupt 1 Enabled.
     * |[2]     |MISMATIE  |Mismatch Interrupt Enable Bit
     * |        |          |This field is used to enable mismatch interrupt.
     * |        |          |0 = Mismatch interrupt Disabled.
     * |        |          |1 = Mismatch interrupt Enabled.
     * |[3]     |TERRIE    |Transfer Error Interrupt Enable Bit
     * |        |          |This field is used to enable transfer error interrupt.
     * |        |          |0 = Transfer error interrupt Disabled.
     * |        |          |1 = Transfer error interrupt Enabled.
     * |[4]     |SC0IE     |Slot Controller 0 Done Interrupt Enable Bit
     * |        |          |This field is used to enable Slot controller 0 finish interrupt.
     * |        |          |0 = Slot controller 0 finish interrupt Disabled.
     * |        |          |1 = Slot controller 0 finish interrupt Enabled.
     * |[5]     |SC1IE     |Slot Controller 1 Done Interrupt Enable Bit
     * |        |          |This field is used to enable Slot controller 1 finish interrupt.
     * |        |          |0 = Slot controller 1 finish interrupt Disabled.
     * |        |          |1 = Slot controller 1 finish interrupt Enabled.
     * |[6]     |SC2IE     |Slot Controller 2 Done Interrupt Enable Bit
     * |        |          |This field is used to enable Slot controller 2 finish interrupt.
     * |        |          |0 = Slot controller 2 finish interrupt Disabled.
     * |        |          |1 = Slot controller 2 finish interrupt Enabled.
     * |[7]     |SC3IE     |Slot Controller 3 Done Interrupt Enable Bit
     * |        |          |This field is used to enable Slot controller 3 finish interrupt.
     * |        |          |0 = Slot controller 3 finish interrupt Disabled.
     * |        |          |1 = Slot controller 3 finish interrupt Enabled.
     * @var PSIO_T::INTSTS
     * Offset: 0x08  PSIO Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CON0IF    |Configurable Interrupt 0 Flag
     * |        |          |The setting interrupt is trigger at the end of the check point of the pin.
     * |        |          |0 = Condition in PSIO_INTCTL is not triggered.
     * |        |          |1 = Condition in PSIO_INTCTL is triggered.
     * |        |          |Note: This bit can be cleared by writing 1.
     * |[1]     |CON1IF    |Configurable Interrupt 1 Flag
     * |        |          |The setting interrupt is trigger at the end of the check point of the pin.
     * |        |          |0 = Condition in PSIO_INTCTL is not triggered.
     * |        |          |1 = Condition in PSIO_INTCTL is triggered.
     * |        |          |Note: This bit can be cleared by writing 1.
     * |[2]     |MISMATIF  |Mismatch Interrupt Flag
     * |        |          |This flag shows the amounts of data are not the same in each pins with PDMA enabled.
     * |        |          |If this situation happens, all slot controllers stop counting.
     * |        |          |0 = Each pin with PDMA enabled receive or transfer data in the same rate.
     * |        |          |1 = Each pin with PDMA enabled receive or transfer data in different rate.
     * |        |          |Note 1: This flag is only effective on the pin with PDMA enabled.
     * |        |          |Note 2: This bit can be cleared by writing 1.
     * |[3]     |TERRIF    |Transfer Error Interrupt Status Flag
     * |        |          |This field is used for transfer error interrupt status flag.
     * |        |          |The transfer error states is at PSIO_TRANSTS register which includes input data overflow flag INOVERn (PSIO_TRANSTS[29,25,21,17,13,9,5,1] and output data underflow flag OUTUFn (PSIO_TRANSTS[31,27,23,19,15,11,7,3]).
     * |        |          |0 = Transfer error interrupt did not occur.
     * |        |          |1 = Transfer error interrupt occurred.
     * |        |          |Note 1: This field is the status flag of INOVER or OUTUFER.
     * |        |          |Note 2: This bit can only be cleared by writing 1 to coordinate transfer error.
     * |[4]     |SC0IF     |Slot Controller 0 Done Interrupt Status Flag
     * |        |          |This field is used for slot controller 0 finish interrupt status flag.
     * |        |          |0 = Slot controller 0 done interrupt did not occur.
     * |        |          |1 = Slot controller 0 done interrupt occurred.
     * |        |          |Note: This bit can be cleared by writing 1.
     * |[5]     |SC1IF     |Slot Controller 1 Done Interrupt Status Flag
     * |        |          |This field is used for slot controller 1 finish interrupt status flag.
     * |        |          |0 = Slot controller 1 done interrupt did not occur.
     * |        |          |1 = Slot controller 1 done interrupt occurred.
     * |        |          |Note: This bit can be cleared by writing 1.
     * |[6]     |SC2IF     |Slot Controller 2 Done Interrupt Status Flag
     * |        |          |This field is used for slot controller 2 finish interrupt status flag.
     * |        |          |0 = Slot controller 2 done interrupt did not occur.
     * |        |          |1 = Slot controller 2 done interrupt occurred.
     * |        |          |Note: This bit can be cleared by writing 1.
     * |[7]     |SC3IF     |Slot Controller 3 Done Interrupt Status Flag
     * |        |          |This field is used for slot controller 3 finish interrupt status flag.
     * |        |          |0 = Slot controller 3 done interrupt did not occur.
     * |        |          |1 = Slot controller 3 done interrupt occurred.
     * |        |          |Note: This bit can be cleared by writing 1.
     * @var PSIO_T::TRANSTS
     * Offset: 0x0C  PSIO Transfer Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INFULL0   |Input Data Full Flag0 (Read Only)
     * |        |          |0 = The pin0 input data is empty.
     * |        |          |1 = The pin0 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[1]     |INOVER0   |Input Data Overflow Flag0
     * |        |          |0 = The pin0 input data does not occur overflow.
     * |        |          |1 = The pin0 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[2]     |OUTEPY0   |Output Data Empty Flag0 (Read Only)
     * |        |          |0 = The pin0 output data is full.
     * |        |          |1 = The pin0 output data is empty.
     * |[3]     |OUTUF0    |Output Data Underflow Flag0
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready. This flag will be set to 1.
     * |        |          |0 = The pin0 output data is not underflow.
     * |        |          |1 = The pin0 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[4]     |INFULL1   |Input Data Full Flag1 (Read Only)
     * |        |          |0 = The pin1 input data is empty.
     * |        |          |1 = The pin1 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[5]     |INOVER1   |Input Data Overflow Flag1
     * |        |          |0 = The pin1 input data does not occur overflow.
     * |        |          |1 = The pin1 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[6]     |OUTEPY1   |Output Data Empty Flag1 (Read Only)
     * |        |          |0 = The pin1 output data is full.
     * |        |          |1 = The pin1 output data is empty.
     * |[7]     |OUTUF1    |Output Data Underflow Flag1
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready, this flag will be set to 1.
     * |        |          |0 = The pin1 output data is not underflow.
     * |        |          |1 = The pin1 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[8]     |INFULL2   |Input Data Full Flag2 (Read Only)
     * |        |          |0 = The pin2 input data is empty.
     * |        |          |1 = The pin2 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin is enabled.
     * |[9]     |INOVER2   |Input Data Overflow Flag2
     * |        |          |0 = The pin2 input data does not occur overflow.
     * |        |          |1 = The pin2 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller start and pin enabled.
     * |[10]    |OUTEPY2   |Output Data Empty Flag2 (Read Only)
     * |        |          |0 = The pin2 output data is full.
     * |        |          |1 = The pin2 output data is empty.
     * |[11]    |OUTUF2    |Output Data Underflow Flag2
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready, this flag will be set to 1.
     * |        |          |0 = The pin3 output data is not underflow.
     * |        |          |1 = The pin3 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[12]    |INFULL3   |Input Data Full Flag3 (Read Only)
     * |        |          |0 = The pin3 input data is empty.
     * |        |          |1 = The pin3 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin is enabled.
     * |[13]    |INOVER3   |Input Data Overflow Flag3
     * |        |          |0 = The pin3 input data does not occur overflow.
     * |        |          |1 = The pin3 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[14]    |OUTEPY3   |Output Data Empty Flag3 (Read Only)
     * |        |          |0 = The pin3 output data is full.
     * |        |          |1 = The pin3 output data is empty.
     * |[15]    |OUTUF3    |Output Data Underflow Flag3
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready, this flag will be set to 1.
     * |        |          |0 = The pin3 output data is not underflow.
     * |        |          |1 = The pin3 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[16]    |INFULL4   |Input Data Full Flag4 (Read Only)
     * |        |          |0 = The pin4 input data is empty.
     * |        |          |1 = The pin4 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin is enabled.
     * |[17]    |INOVER4   |Input Data Overflow Flag4
     * |        |          |0 = The pin4 input data does not occur overflow.
     * |        |          |1 = The pin4 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[18]    |OUTEPY4   |Output Data Empty Flag4 (Read Only)
     * |        |          |0 = The pin4 output data is full.
     * |        |          |1 = The pin4 output data is empty.
     * |[19]    |OUTUF4    |Output Data Underflow Flag4
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready, this flag will be set to 1.
     * |        |          |0 = The pin4 output data is not underflow.
     * |        |          |1 = The pin4 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[20]    |INFULL5   |Input Data Full Flag5 (Read Only)
     * |        |          |0 = The pin5 input data is empty.
     * |        |          |1 = The pin5 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[21]    |INOVER5   |Input Data Overflow Flag5
     * |        |          |0 = The pin5 input data does not occur overflow.
     * |        |          |1 = The pin5 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[22]    |OUTEPY5   |Output Data Empty Flag5 (Read Only)
     * |        |          |0 = The pin5 output data is full.
     * |        |          |1 = The pin5 output data is empty.
     * |[23]    |OUTUF5    |Output Data Underflow Flag5
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready, this flag will be set to 1.
     * |        |          |0 = The pin5 output data is not underflow.
     * |        |          |1 = The pin5 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin is enabled.
     * |[24]    |INFULL6   |Input Data Full Flag6 (Read Only)
     * |        |          |0 = The pin6 input data is empty.
     * |        |          |1 = The pin6 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[25]    |INOVER6   |Input Data Overflow Flag6
     * |        |          |0 = The pin6 input data does not occur overflow.
     * |        |          |1 = The pin6 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller start and pin enabled.
     * |[26]    |OUTEPY6   |Output Data Empty Flag6 (Read Only)
     * |        |          |0 = The pin6 output data is full.
     * |        |          |1 = The pin6 output data is empty.
     * |[27]    |OUTUF6    |Output Data Underflow Flag6
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready, this flag will be set to 1.
     * |        |          |0 = The pin6 output data is not underflow.
     * |        |          |1 = The pin6 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[28]    |INFULL7   |Input Data Full Flag7 (Read Only)
     * |        |          |0 = The pin7 input data is empty.
     * |        |          |1 = The pin7 input data is full.
     * |        |          |Note: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[29]    |INOVER7   |Input Data Overflow Flag7
     * |        |          |0 = The pin7 input data does not occur overflow.
     * |        |          |1 = The pin7 input data occurs overflow.
     * |        |          |Note 1: When input Overflow happened, it will keep the current data, and discard the upcoming data.
     * |        |          |Note 2: When overflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * |[30]    |OUTEPY7   |Output Data Empty Flag7 (Read Only)
     * |        |          |0 = The pin7 output data is full.
     * |        |          |1 = The pin7 output data is empty.
     * |[31]    |OUTUF7    |Output Data Underflow Flag7
     * |        |          |When PSIO is still output data but PSIOn_OUTDAT have not been ready, this flag will be set to 1.
     * |        |          |0 = The pin7 output data is not underflow.
     * |        |          |1 = The pin7 output data is underflow.
     * |        |          |Note 1: When output data shortage happened, it will output 0.
     * |        |          |Note 2: When underflow happens, related slot controller will be stopped.
     * |        |          |Note 3: This bit can be cleared by configure 1 to it.
     * |        |          |Note 4: This bit will be cleared automatically when related slot controller started and pin enabled.
     * @var PSIO_T::ISSTS
     * Offset: 0x10  PSIO Input Status State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |VALID0    |Input Status Valid 0
     * |        |          |0 = The pin 0 input status is not ready.
     * |        |          |1 = The pin 0 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[1]     |INSTSOV0  |Input Status Overflow 0
     * |        |          |0 = The pin 0 input status does not overflow.
     * |        |          |1 = The pin 0 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * |[2]     |VALID1    |Input Status Valid 1
     * |        |          |0 = The pin 1 input status is not ready.
     * |        |          |1 = The pin 1 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[3]     |INSTSOV1  |Input Status Overflow 1
     * |        |          |0 = The pin 1 input status does not overflow.
     * |        |          |1 = The pin 1 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * |[4]     |VALID2    |Input Status Valid 2
     * |        |          |0 = The pin 2 input status is not ready.
     * |        |          |1 = The pin 2 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[5]     |INSTSOV2  |Input Status Overflow 2
     * |        |          |0 = The pin 2 input status does not overflow.
     * |        |          |1 = The pin 2 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * |[6]     |VALID3    |Input Status Valid 3
     * |        |          |0 = The pin 3 input status is not ready.
     * |        |          |1 = The pin 3 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[7]     |INSTSOV3  |Input Status Overflow 3
     * |        |          |0 = The pin 3 input status does not overflow.
     * |        |          |1 = The pin 3 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * |[8]     |VALID4    |Input Status Valid 4
     * |        |          |0 = The pin 4 input status is not ready.
     * |        |          |1 = The pin 4 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[9]     |INSTSOV4  |Input Status Overflow 4
     * |        |          |0 = The pin 4 input status does not overflow.
     * |        |          |1 = The pin 4 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * |[10]    |VALID5    |Input Status Valid 5
     * |        |          |0 = The pin 5 input status is not ready.
     * |        |          |1 = The pin 5 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[11]    |INSTSOV5  |Input Status Overflow 5
     * |        |          |0 = The pin 5 input status does not overflow.
     * |        |          |1 = The pin 5 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * |[12]    |VALID6    |Input Status Valid 6
     * |        |          |0 = The pin 6 input status is not ready.
     * |        |          |1 = The pin 6 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[13]    |INSTSOV6  |Input Status Overflow 6
     * |        |          |0 = The pin 6 input status does not overflow.
     * |        |          |1 = The pin 6 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * |[14]    |VALID7    |Input Status Valid 7
     * |        |          |0 = The pin7 input status is not ready.
     * |        |          |1 = The pin7 input status is ready.
     * |        |          |Note: This valid bit will be cleared automatically if PSIOn_INSTS is read.
     * |[15]    |INSTSOV7  |Input Status Overflow 7
     * |        |          |0 = The pin7 input status does not overflow.
     * |        |          |1 = The pin7 input status occur overflow.
     * |        |          |Note: This overflow bit can be cleared by writing 1.
     * @var PSIO_T::PDMACTL
     * Offset: 0x14  PSIO PDMA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |OPIN0EN   |Output PDMA Pin0 Enable Bit
     * |        |          |0 = Pin0 output PDMA function Disabled.
     * |        |          |1 = Pin0 output PDMA function Enabled.
     * |[1]     |OPIN1EN   |Output PDMA Pin1 Enable Bit
     * |        |          |0 = Pin1 output PDMA function Disabled.
     * |        |          |1 = Pin1 output PDMA function Enabled.
     * |[2]     |OPIN2EN   |Output PDMA Pin2 Enable Bit
     * |        |          |0 = Pin2 output PDMA function Disabled.
     * |        |          |1 = Pin2 output PDMA function Enabled.
     * |[3]     |OPIN3EN   |Output PDMA Pin3 Enable Bit
     * |        |          |0 = Pin3 output PDMA function Disabled.
     * |        |          |1 = Pin3 output PDMA function Enabled.
     * |[4]     |OPIN4EN   |Output PDMA Pin4 Enable Bit
     * |        |          |0 = Pin4 output PDMA function Disabled.
     * |        |          |1 = Pin4 output PDMA function Enabled.
     * |[5]     |OPIN5EN   |Output PDMA Pin5 Enable Bit
     * |        |          |0 = Pin5 output PDMA function Disabled.
     * |        |          |1 = Pin5 output PDMA function Enabled.
     * |[6]     |OPIN6EN   |Output PDMA Pin6 Enable Bit
     * |        |          |0 = Pin6 output PDMA function Disabled.
     * |        |          |1 = Pin6 output PDMA function Enabled.
     * |[7]     |OPIN7EN   |Output PDMA Pin7 Enable Bit
     * |        |          |0 = Pin7 output PDMA function Disabled.
     * |        |          |1 = Pin7 output PDMA function Enabled.
     * |[8]     |IPIN0EN   |Input PDMA Pin0 Enable Bit
     * |        |          |0 = Pin0 input PDMA function Disabled.
     * |        |          |1 = Pin0 input PDMA function Enabled.
     * |[9]     |IPIN1EN   |Input PDMA Pin1 Enable Bit
     * |        |          |0 = Pin1 input PDMA function Disabled.
     * |        |          |1 = Pin1 input PDMA function Enabled.
     * |[10]    |IPIN2EN   |Input PDMA Pin2 Enable Bit
     * |        |          |0 = Pin2 input PDMA function Disabled.
     * |        |          |1 = Pin2 input PDMA function Enabled.
     * |[11]    |IPIN3EN   |Input PDMA Pin3 Enable Bit
     * |        |          |0 = Pin3 input PDMA function Disabled.
     * |        |          |1 = Pin3 input PDMA function Enabled.
     * |[12]    |IPIN4EN   |Input PDMA Pin4 Enable Bit
     * |        |          |0 = Pin4 input PDMA function Disabled.
     * |        |          |1 = Pin4 input PDMA function Enabled.
     * |[13]    |IPIN5EN   |Input PDMA Pin5 Enable Bit
     * |        |          |0 = Pin5 input PDMA function Disabled.
     * |        |          |1 = Pin5 input PDMA function Enabled.
     * |[14]    |IPIN6EN   |Input PDMA Pin6 Enable Bit
     * |        |          |0 = Pin6 input PDMA function Disabled.
     * |        |          |1 = Pin6 input PDMA function Enabled.
     * |[15]    |IPIN7EN   |Input PDMA Pin7 Enable Bit
     * |        |          |0 = Pin7 input PDMA function Disabled.
     * |        |          |1 = Pin7 input PDMA function Enabled.
     * |[19:16] |OUTNUM    |PDMA Output Current Number (Read Only)
     * |        |          |0000 = PDMA IDLE.
     * |        |          |0001 = Pin 0.
     * |        |          |0010 = Pin 1.
     * |        |          |0011 = Pin 2.
     * |        |          |0100 = Pin 3.
     * |        |          |0101 = Pin 4.
     * |        |          |0110 = Pin 5.
     * |        |          |0111 = Pin 6.
     * |        |          |1000 = Pin 7.
     * |        |          |1001 = PDMA WAIT.
     * |        |          |Others = Reserved.
     * |        |          |This register shows the current pin number of output register write by PDMA.
     * |[21:20] |OUTSCSEL  |PDMA Output Data Slot Controller Selection
     * |        |          |00 = Slot controller 0.
     * |        |          |01 = Slot controller 1.
     * |        |          |10 = Slot controller 2.
     * |        |          |11 = Slot controller 3.
     * |[27:24] |INNUM     |PDMA Input Current Number (Read Only)
     * |        |          |0000 = PDMA IDLE.
     * |        |          |0001 = Pin 0.
     * |        |          |0010 = Pin 1.
     * |        |          |0011 = Pin 2.
     * |        |          |0100 = Pin 3.
     * |        |          |0101 = Pin 4.
     * |        |          |0110 = Pin 5.
     * |        |          |0111 = Pin 6.
     * |        |          |1000 = Pin 7.
     * |        |          |1001 = PDMA WAIT.
     * |        |          |Others = reserved.
     * |        |          |This register shows the current pin number of input register read by PDMA.
     * |[29:28] |INSCSEL   |PDMA Input Data Slot Controller Selection
     * |        |          |00 = Slot controller 0.
     * |        |          |01 = Slot controller 1.
     * |        |          |10 = Slot controller 2.
     * |        |          |11 = Slot controller 3.
     * @var PSIO_T::PODAT
     * Offset: 0x18  PSIO PDMA Output Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PDMAOUT   |PDMA Output Data
     * |        |          |This register is used for PSIO with PDMA single mode, and set PDMA with fixed address.
     * |        |          |When PSIO in PDMA mode, setting PDMA to write data to this register.
     * |        |          |The data in this register will be placed to corresponding PSIOn_OUTDAT register in order, when Output Data Empty Flag is 1 and PDMA mode enabled.
     * @var PSIO_T::PIDAT
     * Offset: 0x1C  PSIO PDMA Input Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PDMAIN    |PDMA Input Data
     * |        |          |This register is used for PSIO with PDMA single mode, and set PDMA with fixed address.
     * |        |          |When PSIO in PDMA mode, setting PDMA to read data from this register.
     * |        |          |The data in this register will be updated from corresponding PSIOn_INDAT register in order, when Input Data Full Flag is 1 and PDMA mode enable.
     */
    __IO uint32_t INTCTL;                /*!< [0x0000] PSIO Interrupt Control Register                                  */
    __IO uint32_t INTEN;                 /*!< [0x0004] PSIO Interrupt Enable Register                                   */
    __IO uint32_t INTSTS;                /*!< [0x0008] PSIO Interrupt Status Register                                   */
    __IO uint32_t TRANSTS;               /*!< [0x000c] PSIO Transfer Status Register                                    */
    __IO uint32_t ISSTS;                 /*!< [0x0010] PSIO Input Status State Register                                 */
    __IO uint32_t PDMACTL;               /*!< [0x0014] PSIO PDMA Control Register                                       */
    __O  uint32_t PODAT;                 /*!< [0x0018] PSIO PDMA Output Data Register                                   */
    __IO uint32_t PIDAT;                 /*!< [0x001c] PSIO PDMA Input Data Register                                    */
    SCCT_T        SCCT[4];               /*!< [0x0020 ~ 0x0048] PSIO Slot Controller n Registers                        */
    GNCT_T        GNCT[8];               /*!< [0x0040 ~ 0x0138] PSIOn Control Registers                                 */
} PSIO_T;

/**
    @addtogroup PSIO_CONST PSIO Bit Field Definition
    Constant Definitions for PSIO Controller
@{ */

#define PSIO_INTCTL_CONI0SS_Pos          (0)                                               /*!< PSIO_T::INTCTL: INT0CSEL Position      */
#define PSIO_INTCTL_CONI0SS_Msk          (0xful << PSIO_INTCTL_CONI0SS_Pos)                /*!< PSIO_T::INTCTL: INT0CSEL Mask          */

#define PSIO_INTCTL_CONI1SS_Pos          (4)                                               /*!< PSIO_T::INTCTL: INT1CSEL Position      */
#define PSIO_INTCTL_CONI1SS_Msk          (0xful << PSIO_INTCTL_CONI1SS_Pos)                /*!< PSIO_T::INTCTL: INT1CSEL Mask          */

#define PSIO_INTCTL_CONI0SCS_Pos         (8)                                               /*!< PSIO_T::INTCTL: INT0SSEL Position      */
#define PSIO_INTCTL_CONI0SCS_Msk         (0x3ul << PSIO_INTCTL_CONI0SCS_Pos)               /*!< PSIO_T::INTCTL: INT0SSEL Mask          */

#define PSIO_INTCTL_CONI1SCS_Pos         (12)                                              /*!< PSIO_T::INTCTL: INT1SSEL Position      */
#define PSIO_INTCTL_CONI1SCS_Msk         (0x3ul << PSIO_INTCTL_CONI1SCS_Pos)               /*!< PSIO_T::INTCTL: INT1SSEL Mask          */

#define PSIO_INTEN_CON0IE_Pos            (0)                                               /*!< PSIO_T::INTEN: INTEN0 Position         */
#define PSIO_INTEN_CON0IE_Msk            (0x1ul << PSIO_INTEN_CON0IE_Pos)                  /*!< PSIO_T::INTEN: INTEN0 Mask             */

#define PSIO_INTEN_CON1IE_Pos            (1)                                               /*!< PSIO_T::INTEN: INTEN1 Position         */
#define PSIO_INTEN_CON1IE_Msk            (0x1ul << PSIO_INTEN_CON1IE_Pos)                  /*!< PSIO_T::INTEN: INTEN1 Mask             */

#define PSIO_INTEN_MISMATIE_Pos          (2)                                               /*!< PSIO_T::INTEN: MISMATIE Position       */
#define PSIO_INTEN_MISMATIE_Msk          (0x1ul << PSIO_INTEN_MISMATIE_Pos)                /*!< PSIO_T::INTEN: MISMATIE Mask           */

#define PSIO_INTEN_TERRIE_Pos            (3)                                               /*!< PSIO_T::INTEN: TERRIE Position         */
#define PSIO_INTEN_TERRIE_Msk            (0x1ul << PSIO_INTEN_TERRIE_Pos)                  /*!< PSIO_T::INTEN: TERRIE Mask             */

#define PSIO_INTEN_SC0IE_Pos             (4)                                                /*!< PSIO_T::INTEN: SC0IE Position         */
#define PSIO_INTEN_SC0IE_Msk             (0x1ul << PSIO_INTEN_SC0IE_Pos)                    /*!< PSIO_T::INTEN: SC0IE Mask             */

#define PSIO_INTEN_SC1IE_Pos             (5)                                                /*!< PSIO_T::INTEN: SC1IE Position         */
#define PSIO_INTEN_SC1IE_Msk             (0x1ul << PSIO_INTEN_SC1IE_Pos)                    /*!< PSIO_T::INTEN: SC1IE Mask             */

#define PSIO_INTEN_SC2IE_Pos             (6)                                                /*!< PSIO_T::INTEN: SC2IE Position         */
#define PSIO_INTEN_SC2IE_Msk             (0x1ul << PSIO_INTEN_SC2IE_Pos)                    /*!< PSIO_T::INTEN: SC2IE Mask             */

#define PSIO_INTEN_SC3IE_Pos             (7)                                                /*!< PSIO_T::INTEN: SC3IE Position         */
#define PSIO_INTEN_SC3IE_Msk             (0x1ul << PSIO_INTEN_SC3IE_Pos)                    /*!< PSIO_T::INTEN: SC3IE Mask             */

#define PSIO_INTSTS_CON0IF_Pos           (0)                                               /*!< PSIO_T::INTSTS: INTIF0 Position        */
#define PSIO_INTSTS_CON0IF_Msk           (0x1ul << PSIO_INTSTS_CON0IF_Pos)                 /*!< PSIO_T::INTSTS: INTIF0 Mask            */

#define PSIO_INTSTS_CON1IF_Pos           (1)                                               /*!< PSIO_T::INTSTS: INTIF1 Position        */
#define PSIO_INTSTS_CON1IF_Msk           (0x1ul << PSIO_INTSTS_CON1IF_Pos)                 /*!< PSIO_T::INTSTS: INTIF1 Mask            */

#define PSIO_INTSTS_MISMATIF_Pos         (2)                                               /*!< PSIO_T::INTSTS: MISMATIF Position      */
#define PSIO_INTSTS_MISMATIF_Msk         (0x1ul << PSIO_INTSTS_MISMATIF_Pos)               /*!< PSIO_T::INTSTS: MISMATIF Mask          */

#define PSIO_INTSTS_TERRIF_Pos           (3)                                               /*!< PSIO_T::INTSTS: TERRIF Position        */
#define PSIO_INTSTS_TERRIF_Msk           (0x1ul << PSIO_INTSTS_TERRIF_Pos)                 /*!< PSIO_T::INTSTS: TERRIF Mask            */

#define PSIO_INTSTS_SC0IF_Pos            (4)                                               /*!< PSIO_T::INTSTS: SC0IF Position         */
#define PSIO_INTSTS_SC0IF_Msk            (0x1ul << PSIO_INTSTS_SC0IF_Pos)                  /*!< PSIO_T::INTSTS: SC0IF Mask             */

#define PSIO_INTSTS_SC1IF_Pos            (5)                                               /*!< PSIO_T::INTSTS: SC1IF Position         */
#define PSIO_INTSTS_SC1IF_Msk            (0x1ul << PSIO_INTSTS_SC1IF_Pos)                  /*!< PSIO_T::INTSTS: SC1IF Mask             */

#define PSIO_INTSTS_SC2IF_Pos            (6)                                               /*!< PSIO_T::INTSTS: SC2IF Position         */
#define PSIO_INTSTS_SC2IF_Msk            (0x1ul << PSIO_INTSTS_SC2IF_Pos)                  /*!< PSIO_T::INTSTS: SC2IF Mask             */

#define PSIO_INTSTS_SC3IF_Pos            (7)                                               /*!< PSIO_T::INTSTS: SC3IF Position         */
#define PSIO_INTSTS_SC3IF_Msk            (0x1ul << PSIO_INTSTS_SC3IF_Pos)                  /*!< PSIO_T::INTSTS: SC3IF Mask             */

#define PSIO_TRANSTS_INFULL0_Pos         (0)                                               /*!< PSIO_T::TRANSTS: INFULL0 Position      */
#define PSIO_TRANSTS_INFULL0_Msk         (0x1ul << PSIO_TRANSTS_INFULL0_Pos)               /*!< PSIO_T::TRANSTS: INFULL0 Mask          */

#define PSIO_TRANSTS_INOVER0_Pos         (1)                                               /*!< PSIO_T::TRANSTS: INOVER0 Position      */
#define PSIO_TRANSTS_INOVER0_Msk         (0x1ul << PSIO_TRANSTS_INOVER0_Pos)               /*!< PSIO_T::TRANSTS: INOVER0 Mask          */

#define PSIO_TRANSTS_OUTEPY0_Pos         (2)                                               /*!< PSIO_T::TRANSTS: OUTEPY0 Position      */
#define PSIO_TRANSTS_OUTEPY0_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY0_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY0 Mask          */

#define PSIO_TRANSTS_OUTUF0_Pos          (3)                                               /*!< PSIO_T::TRANSTS: OUTUF0 Position       */
#define PSIO_TRANSTS_OUTUF0_Msk          (0x1ul << PSIO_TRANSTS_OUTUF0_Pos)                /*!< PSIO_T::TRANSTS: OUTUF0 Mask           */

#define PSIO_TRANSTS_INFULL1_Pos         (4)                                               /*!< PSIO_T::TRANSTS: INFULL1 Position      */
#define PSIO_TRANSTS_INFULL1_Msk         (0x1ul << PSIO_TRANSTS_INFULL1_Pos)               /*!< PSIO_T::TRANSTS: INFULL1 Mask          */

#define PSIO_TRANSTS_INOVER1_Pos         (5)                                               /*!< PSIO_T::TRANSTS: INOVER1 Position      */
#define PSIO_TRANSTS_INOVER1_Msk         (0x1ul << PSIO_TRANSTS_INOVER1_Pos)               /*!< PSIO_T::TRANSTS: INOVER1 Mask          */

#define PSIO_TRANSTS_OUTEPY1_Pos         (6)                                               /*!< PSIO_T::TRANSTS: OUTEPY1 Position      */
#define PSIO_TRANSTS_OUTEPY1_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY1_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY1 Mask          */

#define PSIO_TRANSTS_OUTUF1_Pos          (7)                                               /*!< PSIO_T::TRANSTS: OUTUF1 Position       */
#define PSIO_TRANSTS_OUTUF1_Msk          (0x1ul << PSIO_TRANSTS_OUTUF1_Pos)                /*!< PSIO_T::TRANSTS: OUTUF1 Mask           */

#define PSIO_TRANSTS_INFULL2_Pos         (8)                                               /*!< PSIO_T::TRANSTS: INFULL2 Position      */
#define PSIO_TRANSTS_INFULL2_Msk         (0x1ul << PSIO_TRANSTS_INFULL2_Pos)               /*!< PSIO_T::TRANSTS: INFULL2 Mask          */

#define PSIO_TRANSTS_INOVER2_Pos         (9)                                               /*!< PSIO_T::TRANSTS: INOVER2 Position      */
#define PSIO_TRANSTS_INOVER2_Msk         (0x1ul << PSIO_TRANSTS_INOVER2_Pos)               /*!< PSIO_T::TRANSTS: INOVER2 Mask          */

#define PSIO_TRANSTS_OUTEPY2_Pos         (10)                                              /*!< PSIO_T::TRANSTS: OUTEPY2 Position      */
#define PSIO_TRANSTS_OUTEPY2_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY2_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY2 Mask          */

#define PSIO_TRANSTS_OUTUF2_Pos          (11)                                              /*!< PSIO_T::TRANSTS: OUTUF2 Position       */
#define PSIO_TRANSTS_OUTUF2_Msk          (0x1ul << PSIO_TRANSTS_OUTUF2_Pos)                /*!< PSIO_T::TRANSTS: OUTUF2 Mask           */

#define PSIO_TRANSTS_INFULL3_Pos         (12)                                              /*!< PSIO_T::TRANSTS: INFULL3 Position      */
#define PSIO_TRANSTS_INFULL3_Msk         (0x1ul << PSIO_TRANSTS_INFULL3_Pos)               /*!< PSIO_T::TRANSTS: INFULL3 Mask          */

#define PSIO_TRANSTS_INOVER3_Pos         (13)                                              /*!< PSIO_T::TRANSTS: INOVER3 Position      */
#define PSIO_TRANSTS_INOVER3_Msk         (0x1ul << PSIO_TRANSTS_INOVER3_Pos)               /*!< PSIO_T::TRANSTS: INOVER3 Mask          */

#define PSIO_TRANSTS_OUTEPY3_Pos         (14)                                              /*!< PSIO_T::TRANSTS: OUTEPY3 Position      */
#define PSIO_TRANSTS_OUTEPY3_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY3_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY3 Mask          */

#define PSIO_TRANSTS_OUTUF3_Pos          (15)                                              /*!< PSIO_T::TRANSTS: OUTUF3 Position       */
#define PSIO_TRANSTS_OUTUF3_Msk          (0x1ul << PSIO_TRANSTS_OUTUF3_Pos)                /*!< PSIO_T::TRANSTS: OUTUF3 Mask           */

#define PSIO_TRANSTS_INFULL4_Pos         (16)                                              /*!< PSIO_T::TRANSTS: INFULL4 Position      */
#define PSIO_TRANSTS_INFULL4_Msk         (0x1ul << PSIO_TRANSTS_INFULL4_Pos)               /*!< PSIO_T::TRANSTS: INFULL4 Mask          */

#define PSIO_TRANSTS_INOVER4_Pos         (17)                                              /*!< PSIO_T::TRANSTS: INOVER4 Position      */
#define PSIO_TRANSTS_INOVER4_Msk         (0x1ul << PSIO_TRANSTS_INOVER4_Pos)               /*!< PSIO_T::TRANSTS: INOVER4 Mask          */

#define PSIO_TRANSTS_OUTEPY4_Pos         (18)                                              /*!< PSIO_T::TRANSTS: OUTEPY4 Position      */
#define PSIO_TRANSTS_OUTEPY4_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY4_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY4 Mask          */

#define PSIO_TRANSTS_OUTUF4_Pos          (19)                                              /*!< PSIO_T::TRANSTS: OUTUF4 Position       */
#define PSIO_TRANSTS_OUTUF4_Msk          (0x1ul << PSIO_TRANSTS_OUTUF4_Pos)                /*!< PSIO_T::TRANSTS: OUTUF4 Mask           */

#define PSIO_TRANSTS_INFULL5_Pos         (20)                                              /*!< PSIO_T::TRANSTS: INFULL5 Position      */
#define PSIO_TRANSTS_INFULL5_Msk         (0x1ul << PSIO_TRANSTS_INFULL5_Pos)               /*!< PSIO_T::TRANSTS: INFULL5 Mask          */

#define PSIO_TRANSTS_INOVER5_Pos         (21)                                              /*!< PSIO_T::TRANSTS: INOVER5 Position      */
#define PSIO_TRANSTS_INOVER5_Msk         (0x1ul << PSIO_TRANSTS_INOVER5_Pos)               /*!< PSIO_T::TRANSTS: INOVER5 Mask          */

#define PSIO_TRANSTS_OUTEPY5_Pos         (22)                                              /*!< PSIO_T::TRANSTS: OUTEPY5 Position      */
#define PSIO_TRANSTS_OUTEPY5_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY5_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY5 Mask          */

#define PSIO_TRANSTS_OUTUF5_Pos          (23)                                              /*!< PSIO_T::TRANSTS: OUTUF5 Position       */
#define PSIO_TRANSTS_OUTUF5_Msk          (0x1ul << PSIO_TRANSTS_OUTUF5_Pos)                /*!< PSIO_T::TRANSTS: OUTUF5 Mask           */

#define PSIO_TRANSTS_INFULL6_Pos         (24)                                              /*!< PSIO_T::TRANSTS: INFULL6 Position      */
#define PSIO_TRANSTS_INFULL6_Msk         (0x1ul << PSIO_TRANSTS_INFULL6_Pos)               /*!< PSIO_T::TRANSTS: INFULL6 Mask          */

#define PSIO_TRANSTS_INOVER6_Pos         (25)                                              /*!< PSIO_T::TRANSTS: INOVER6 Position      */
#define PSIO_TRANSTS_INOVER6_Msk         (0x1ul << PSIO_TRANSTS_INOVER6_Pos)               /*!< PSIO_T::TRANSTS: INOVER6 Mask          */

#define PSIO_TRANSTS_OUTEPY6_Pos         (26)                                              /*!< PSIO_T::TRANSTS: OUTEPY6 Position      */
#define PSIO_TRANSTS_OUTEPY6_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY6_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY6 Mask          */

#define PSIO_TRANSTS_OUTUF6_Pos          (27)                                              /*!< PSIO_T::TRANSTS: OUTUF6 Position       */
#define PSIO_TRANSTS_OUTUF6_Msk          (0x1ul << PSIO_TRANSTS_OUTUF6_Pos)                /*!< PSIO_T::TRANSTS: OUTUF6 Mask           */

#define PSIO_TRANSTS_INFULL7_Pos         (28)                                              /*!< PSIO_T::TRANSTS: INFULL7 Position      */
#define PSIO_TRANSTS_INFULL7_Msk         (0x1ul << PSIO_TRANSTS_INFULL7_Pos)               /*!< PSIO_T::TRANSTS: INFULL7 Mask          */

#define PSIO_TRANSTS_INOVER7_Pos         (29)                                              /*!< PSIO_T::TRANSTS: INOVER7 Position      */
#define PSIO_TRANSTS_INOVER7_Msk         (0x1ul << PSIO_TRANSTS_INOVER7_Pos)               /*!< PSIO_T::TRANSTS: INOVER7 Mask          */

#define PSIO_TRANSTS_OUTEPY7_Pos         (30)                                              /*!< PSIO_T::TRANSTS: OUTEPY7 Position      */
#define PSIO_TRANSTS_OUTEPY7_Msk         (0x1ul << PSIO_TRANSTS_OUTEPY7_Pos)               /*!< PSIO_T::TRANSTS: OUTEPY7 Mask          */

#define PSIO_TRANSTS_OUTUF7_Pos          (31)                                              /*!< PSIO_T::TRANSTS: OUTUF7 Position       */
#define PSIO_TRANSTS_OUTUF7_Msk          (0x1ul << PSIO_TRANSTS_OUTUF7_Pos)                /*!< PSIO_T::TRANSTS: OUTUF7 Mask           */

#define PSIO_ISSTS_VALID0_Pos            (0)                                               /*!< PSIO_T::ISSTS: VALID0 Position         */
#define PSIO_ISSTS_VALID0_Msk            (0x1ul << PSIO_ISSTS_VALID0_Pos)                  /*!< PSIO_T::ISSTS: VALID0 Mask             */

#define PSIO_ISSTS_INSTSOV0_Pos          (1)                                               /*!< PSIO_T::ISSTS: INSTSOV0 Position       */
#define PSIO_ISSTS_INSTSOV0_Msk          (0x1ul << PSIO_ISSTS_INSTSOV0_Pos)                /*!< PSIO_T::ISSTS: INSTSOV0 Mask           */

#define PSIO_ISSTS_VALID1_Pos            (2)                                               /*!< PSIO_T::ISSTS: VALID1 Position         */
#define PSIO_ISSTS_VALID1_Msk            (0x1ul << PSIO_ISSTS_VALID1_Pos)                  /*!< PSIO_T::ISSTS: VALID1 Mask             */

#define PSIO_ISSTS_INSTSOV1_Pos          (3)                                               /*!< PSIO_T::ISSTS: INSTSOV1 Position       */
#define PSIO_ISSTS_INSTSOV1_Msk          (0x1ul << PSIO_ISSTS_INSTSOV1_Pos)                /*!< PSIO_T::ISSTS: INSTSOV1 Mask           */

#define PSIO_ISSTS_VALID2_Pos            (4)                                               /*!< PSIO_T::ISSTS: VALID2 Position         */
#define PSIO_ISSTS_VALID2_Msk            (0x1ul << PSIO_ISSTS_VALID2_Pos)                  /*!< PSIO_T::ISSTS: VALID2 Mask             */

#define PSIO_ISSTS_INSTSOV2_Pos          (5)                                               /*!< PSIO_T::ISSTS: INSTSOV2 Position       */
#define PSIO_ISSTS_INSTSOV2_Msk          (0x1ul << PSIO_ISSTS_INSTSOV2_Pos)                /*!< PSIO_T::ISSTS: INSTSOV2 Mask           */

#define PSIO_ISSTS_VALID3_Pos            (6)                                               /*!< PSIO_T::ISSTS: VALID3 Position         */
#define PSIO_ISSTS_VALID3_Msk            (0x1ul << PSIO_ISSTS_VALID3_Pos)                  /*!< PSIO_T::ISSTS: VALID3 Mask             */

#define PSIO_ISSTS_INSTSOV3_Pos          (7)                                               /*!< PSIO_T::ISSTS: INSTSOV3 Position       */
#define PSIO_ISSTS_INSTSOV3_Msk          (0x1ul << PSIO_ISSTS_INSTSOV3_Pos)                /*!< PSIO_T::ISSTS: INSTSOV3 Mask           */

#define PSIO_ISSTS_VALID4_Pos            (8)                                               /*!< PSIO_T::ISSTS: VALID4 Position         */
#define PSIO_ISSTS_VALID4_Msk            (0x1ul << PSIO_ISSTS_VALID4_Pos)                  /*!< PSIO_T::ISSTS: VALID4 Mask             */

#define PSIO_ISSTS_INSTSOV4_Pos          (9)                                               /*!< PSIO_T::ISSTS: INSTSOV4 Position       */
#define PSIO_ISSTS_INSTSOV4_Msk          (0x1ul << PSIO_ISSTS_INSTSOV4_Pos)                /*!< PSIO_T::ISSTS: INSTSOV4 Mask           */

#define PSIO_ISSTS_VALID5_Pos            (10)                                              /*!< PSIO_T::ISSTS: VALID5 Position         */
#define PSIO_ISSTS_VALID5_Msk            (0x1ul << PSIO_ISSTS_VALID5_Pos)                  /*!< PSIO_T::ISSTS: VALID5 Mask             */

#define PSIO_ISSTS_INSTSOV5_Pos          (11)                                              /*!< PSIO_T::ISSTS: INSTSOV5 Position       */
#define PSIO_ISSTS_INSTSOV5_Msk          (0x1ul << PSIO_ISSTS_INSTSOV5_Pos)                /*!< PSIO_T::ISSTS: INSTSOV5 Mask           */

#define PSIO_ISSTS_VALID6_Pos            (12)                                              /*!< PSIO_T::ISSTS: VALID6 Position         */
#define PSIO_ISSTS_VALID6_Msk            (0x1ul << PSIO_ISSTS_VALID6_Pos)                  /*!< PSIO_T::ISSTS: VALID6 Mask             */

#define PSIO_ISSTS_INSTSOV6_Pos          (13)                                              /*!< PSIO_T::ISSTS: INSTSOV6 Position       */
#define PSIO_ISSTS_INSTSOV6_Msk          (0x1ul << PSIO_ISSTS_INSTSOV6_Pos)                /*!< PSIO_T::ISSTS: INSTSOV6 Mask           */

#define PSIO_ISSTS_VALID7_Pos            (14)                                              /*!< PSIO_T::ISSTS: VALID7 Position         */
#define PSIO_ISSTS_VALID7_Msk            (0x1ul << PSIO_ISSTS_VALID7_Pos)                  /*!< PSIO_T::ISSTS: VALID7 Mask             */

#define PSIO_ISSTS_INSTSOV7_Pos          (15)                                              /*!< PSIO_T::ISSTS: INSTSOV7 Position       */
#define PSIO_ISSTS_INSTSOV7_Msk          (0x1ul << PSIO_ISSTS_INSTSOV7_Pos)                /*!< PSIO_T::ISSTS: INSTSOV7 Mask           */

#define PSIO_PDMACTL_OPIN0EN_Pos         (0)                                               /*!< PSIO_T::PDMACTL: OPIN0EN Position      */
#define PSIO_PDMACTL_OPIN0EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN0EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN0EN Mask          */

#define PSIO_PDMACTL_OPIN1EN_Pos         (1)                                               /*!< PSIO_T::PDMACTL: OPIN1EN Position      */
#define PSIO_PDMACTL_OPIN1EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN1EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN1EN Mask          */

#define PSIO_PDMACTL_OPIN2EN_Pos         (2)                                               /*!< PSIO_T::PDMACTL: OPIN2EN Position      */
#define PSIO_PDMACTL_OPIN2EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN2EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN2EN Mask          */

#define PSIO_PDMACTL_OPIN3EN_Pos         (3)                                               /*!< PSIO_T::PDMACTL: OPIN3EN Position      */
#define PSIO_PDMACTL_OPIN3EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN3EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN3EN Mask          */

#define PSIO_PDMACTL_OPIN4EN_Pos         (4)                                               /*!< PSIO_T::PDMACTL: OPIN4EN Position      */
#define PSIO_PDMACTL_OPIN4EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN4EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN4EN Mask          */

#define PSIO_PDMACTL_OPIN5EN_Pos         (5)                                               /*!< PSIO_T::PDMACTL: OPIN5EN Position      */
#define PSIO_PDMACTL_OPIN5EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN5EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN5EN Mask          */

#define PSIO_PDMACTL_OPIN6EN_Pos         (6)                                               /*!< PSIO_T::PDMACTL: OPIN6EN Position      */
#define PSIO_PDMACTL_OPIN6EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN6EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN6EN Mask          */

#define PSIO_PDMACTL_OPIN7EN_Pos         (7)                                               /*!< PSIO_T::PDMACTL: OPIN7EN Position      */
#define PSIO_PDMACTL_OPIN7EN_Msk         (0x1ul << PSIO_PDMACTL_OPIN7EN_Pos)               /*!< PSIO_T::PDMACTL: OPIN7EN Mask          */

#define PSIO_PDMACTL_IPIN0EN_Pos         (8)                                               /*!< PSIO_T::PDMACTL: IPIN0EN Position      */
#define PSIO_PDMACTL_IPIN0EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN0EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN0EN Mask          */

#define PSIO_PDMACTL_IPIN1EN_Pos         (9)                                               /*!< PSIO_T::PDMACTL: IPIN1EN Position      */
#define PSIO_PDMACTL_IPIN1EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN1EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN1EN Mask          */

#define PSIO_PDMACTL_IPIN2EN_Pos         (10)                                              /*!< PSIO_T::PDMACTL: IPIN2EN Position      */
#define PSIO_PDMACTL_IPIN2EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN2EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN2EN Mask          */

#define PSIO_PDMACTL_IPIN3EN_Pos         (11)                                              /*!< PSIO_T::PDMACTL: IPIN3EN Position      */
#define PSIO_PDMACTL_IPIN3EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN3EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN3EN Mask          */

#define PSIO_PDMACTL_IPIN4EN_Pos         (12)                                              /*!< PSIO_T::PDMACTL: IPIN4EN Position      */
#define PSIO_PDMACTL_IPIN4EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN4EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN4EN Mask          */

#define PSIO_PDMACTL_IPIN5EN_Pos         (13)                                              /*!< PSIO_T::PDMACTL: IPIN5EN Position      */
#define PSIO_PDMACTL_IPIN5EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN5EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN5EN Mask          */

#define PSIO_PDMACTL_IPIN6EN_Pos         (14)                                              /*!< PSIO_T::PDMACTL: IPIN6EN Position      */
#define PSIO_PDMACTL_IPIN6EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN6EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN6EN Mask          */

#define PSIO_PDMACTL_IPIN7EN_Pos         (15)                                              /*!< PSIO_T::PDMACTL: IPIN7EN Position      */
#define PSIO_PDMACTL_IPIN7EN_Msk         (0x1ul << PSIO_PDMACTL_IPIN7EN_Pos)               /*!< PSIO_T::PDMACTL: IPIN7EN Mask          */

#define PSIO_PDMACTL_OUTNUM_Pos          (16)                                              /*!< PSIO_T::PDMACTL: OUTNUM Position       */
#define PSIO_PDMACTL_OUTNUM_Msk          (0xful << PSIO_PDMACTL_OUTNUM_Pos)                /*!< PSIO_T::PDMACTL: OUTNUM Mask           */

#define PSIO_PDMACTL_OUTSCSEL_Pos        (20)                                              /*!< PSIO_T::PDMACTL: OUTSCSEL Position     */
#define PSIO_PDMACTL_OUTSCSEL_Msk        (0x3ul << PSIO_PDMACTL_OUTSCSEL_Pos)              /*!< PSIO_T::PDMACTL: OUTSCSEL Mask         */

#define PSIO_PDMACTL_INNUM_Pos           (24)                                              /*!< PSIO_T::PDMACTL: INNUM Position        */
#define PSIO_PDMACTL_INNUM_Msk           (0xful << PSIO_PDMACTL_INNUM_Pos)                 /*!< PSIO_T::PDMACTL: INNUM Mask            */

#define PSIO_PDMACTL_INSCSEL_Pos         (28)                                              /*!< PSIO_T::PDMACTL: INSCSEL Position      */
#define PSIO_PDMACTL_INSCSEL_Msk         (0x3ul << PSIO_PDMACTL_INSCSEL_Pos)               /*!< PSIO_T::PDMACTL: INSCSEL Mask          */

#define PSIO_PODAT_PDMAOUT_Pos           (0)                                               /*!< PSIO_T::PODAT: PDMAOUT Position        */
#define PSIO_PODAT_PDMAOUT_Msk           (0xfffffffful << PSIO_PODAT_PDMAOUT_Pos)          /*!< PSIO_T::PODAT: PDMAOUT Mask            */

#define PSIO_PIDAT_PDMAIN_Pos            (0)                                               /*!< PSIO_T::PIDAT: PDMAIN Position         */
#define PSIO_PIDAT_PDMAIN_Msk            (0xfffffffful << PSIO_PIDAT_PDMAIN_Pos)           /*!< PSIO_T::PIDAT: PDMAIN Mask             */

#define PSIO_SCCT_SCCTL_INISLOT_Pos      (0)                                               /*!< PSIO_T::SCCTL: INISLOT Position        */
#define PSIO_SCCT_SCCTL_INISLOT_Msk      (0xful << PSIO_SCCT_SCCTL_INISLOT_Pos)            /*!< PSIO_T::SCCTL: INISLOT Mask            */

#define PSIO_SCCT_SCCTL_ENDSLOT_Pos      (4)                                               /*!< PSIO_T::SCCTL: ENDSLOT Position        */
#define PSIO_SCCT_SCCTL_ENDSLOT_Msk      (0xful << PSIO_SCCT_SCCTL_ENDSLOT_Pos)            /*!< PSIO_T::SCCTL: ENDSLOT Mask            */

#define PSIO_SCCT_SCCTL_SPLCNT_Pos       (8)                                               /*!< PSIO_T::SCCTL: SPLCNT Position         */
#define PSIO_SCCT_SCCTL_SPLCNT_Msk       (0x3ful << PSIO_SCCT_SCCTL_SPLCNT_Pos)            /*!< PSIO_T::SCCTL: SPLCNT Mask             */

#define PSIO_SCCT_SCCTL_TRIGSRC_Pos      (14)                                              /*!< PSIO_T::SCCTL: TRIGSRC Position        */
#define PSIO_SCCT_SCCTL_TRIGSRC_Msk      (0x3ul << PSIO_SCCT_SCCTL_TRIGSRC_Pos)            /*!< PSIO_T::SCCTL: TRIGSRC Mask            */

#define PSIO_SCCT_SCCTL_START_Pos        (16)                                              /*!< PSIO_T::SCCTL: START Position          */
#define PSIO_SCCT_SCCTL_START_Msk        (0x1ul << PSIO_SCCT_SCCTL_START_Pos)              /*!< PSIO_T::SCCTL: START Mask              */

#define PSIO_SCCT_SCCTL_REPEAT_Pos       (17)                                              /*!< PSIO_T::SCCTL: REPEAT Position         */
#define PSIO_SCCT_SCCTL_REPEAT_Msk       (0x1ul << PSIO_SCCT_SCCTL_REPEAT_Pos)             /*!< PSIO_T::SCCTL: REPEAT Mask             */

#define PSIO_SCCT_SCCTL_STOP_Pos         (18)                                              /*!< PSIO_T::SCCTL: STOP Position           */
#define PSIO_SCCT_SCCTL_STOP_Msk         (0x1ul << PSIO_SCCT_SCCTL_STOP_Pos)               /*!< PSIO_T::SCCTL: STOP Mask               */

#define PSIO_SCCT_SCCTL_BUSY_Pos         (24)                                              /*!< PSIO_T::SCCTL: BUSY Position           */
#define PSIO_SCCT_SCCTL_BUSY_Msk         (0x1ul << PSIO_SCCT_SCCTL_BUSY_Pos)               /*!< PSIO_T::SCCTL: BUSY Mask               */

#define PSIO_SCCT_SCCTL_IDLE_Pos         (25)                                              /*!< PSIO_T::SCCTL: IDLE Position           */
#define PSIO_SCCT_SCCTL_IDLE_Msk         (0x1ul << PSIO_SCCT_SCCTL_IDLE_Pos)               /*!< PSIO_T::SCCTL: IDLE Mask               */

#define PSIO_SCCT_SCSLOT_SLOT0CNT_Pos    (0)                                               /*!< PSIO_T::SCSLOT: SLOT0CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT0CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT0CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT0CNT Mask          */

#define PSIO_SCCT_SCSLOT_SLOT1CNT_Pos    (4)                                               /*!< PSIO_T::SCSLOT: SLOT1CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT1CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT1CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT1CNT Mask          */

#define PSIO_SCCT_SCSLOT_SLOT2CNT_Pos    (8)                                               /*!< PSIO_T::SCSLOT: SLOT2CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT2CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT2CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT2CNT Mask          */

#define PSIO_SCCT_SCSLOT_SLOT3CNT_Pos    (12)                                              /*!< PSIO_T::SCSLOT: SLOT3CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT3CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT3CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT3CNT Mask          */

#define PSIO_SCCT_SCSLOT_SLOT4CNT_Pos    (16)                                              /*!< PSIO_T::SCSLOT: SLOT4CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT4CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT4CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT4CNT Mask          */

#define PSIO_SCCT_SCSLOT_SLOT5CNT_Pos    (20)                                              /*!< PSIO_T::SCSLOT: SLOT5CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT5CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT5CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT5CNT Mask          */

#define PSIO_SCCT_SCSLOT_SLOT6CNT_Pos    (24)                                              /*!< PSIO_T::SCSLOT: SLOT6CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT6CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT6CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT6CNT Mask          */

#define PSIO_SCCT_SCSLOT_SLOT7CNT_Pos    (28)                                              /*!< PSIO_T::SCSLOT: SLOT7CNT Position      */
#define PSIO_SCCT_SCSLOT_SLOT7CNT_Msk    (0xful << PSIO_SCCT_SCSLOT_SLOT7CNT_Pos)          /*!< PSIO_T::SCSLOT: SLOT7CNT Mask          */

#define PSIO_GNCT_GENCTL_IOMODE_Pos      (0)                                               /*!< PSIO_T::GENCTL: IOMODE Position        */
#define PSIO_GNCT_GENCTL_IOMODE_Msk      (0x3ul << PSIO_GNCT_GENCTL_IOMODE_Pos)            /*!< PSIO_T::GENCTL: IOMODE Mask            */

#define PSIO_GNCT_GENCTL_INITIAL_Pos     (2)                                               /*!< PSIO_T::GENCTL: INITIAL Position       */
#define PSIO_GNCT_GENCTL_INITIAL_Msk     (0x3ul << PSIO_GNCT_GENCTL_INITIAL_Pos)           /*!< PSIO_T::GENCTL: INITIAL Mask           */

#define PSIO_GNCT_GENCTL_INTERVAL_Pos    (4)                                               /*!< PSIO_T::GENCTL: INTERVAL Position      */
#define PSIO_GNCT_GENCTL_INTERVAL_Msk    (0x3ul << PSIO_GNCT_GENCTL_INTERVAL_Pos)          /*!< PSIO_T::GENCTL: INTERVAL Mask          */

#define PSIO_GNCT_GENCTL_SW0CP_Pos       (8)                                               /*!< PSIO_T::GENCTL: SW0CP Position         */
#define PSIO_GNCT_GENCTL_SW0CP_Msk       (0xful << PSIO_GNCT_GENCTL_SW0CP_Pos)             /*!< PSIO_T::GENCTL: SW0CP Mask             */

#define PSIO_GNCT_GENCTL_SW1CP_Pos       (12)                                              /*!< PSIO_T::GENCTL: SW1CP Position         */
#define PSIO_GNCT_GENCTL_SW1CP_Msk       (0xful << PSIO_GNCT_GENCTL_SW1CP_Pos)             /*!< PSIO_T::GENCTL: SW1CP Mask             */

#define PSIO_GNCT_GENCTL_MODESW0_Pos     (16)                                              /*!< PSIO_T::GENCTL: MODESW0 Position       */
#define PSIO_GNCT_GENCTL_MODESW0_Msk     (0x3ul << PSIO_GNCT_GENCTL_MODESW0_Pos)           /*!< PSIO_T::GENCTL: MODESW0 Mask           */

#define PSIO_GNCT_GENCTL_MODESW1_Pos     (18)                                              /*!< PSIO_T::GENCTL: MODESW1 Position       */
#define PSIO_GNCT_GENCTL_MODESW1_Msk     (0x3ul << PSIO_GNCT_GENCTL_MODESW1_Pos)           /*!< PSIO_T::GENCTL: MODESW1 Mask           */

#define PSIO_GNCT_GENCTL_SCSEL_Pos       (24)                                              /*!< PSIO_T::GENCTL: SCSEL Position         */
#define PSIO_GNCT_GENCTL_SCSEL_Msk       (0x3ul << PSIO_GNCT_GENCTL_SCSEL_Pos)             /*!< PSIO_T::GENCTL: SCSEL Mask             */

#define PSIO_GNCT_GENCTL_PINEN_Pos       (26)                                              /*!< PSIO_T::GENCTL: PINEN Position         */
#define PSIO_GNCT_GENCTL_PINEN_Msk       (0x1ul << PSIO_GNCT_GENCTL_PINEN_Pos)             /*!< PSIO_T::GENCTL: PINEN Mask             */

#define PSIO_GNCT_DATCTL_OUTDATWD_Pos    (0)                                               /*!< PSIO_T::DATCTL: OUTDATWD Position      */
#define PSIO_GNCT_DATCTL_OUTDATWD_Msk    (0x1ful << PSIO_GNCT_DATCTL_OUTDATWD_Pos)         /*!< PSIO_T::DATCTL: OUTDATWD Mask          */

#define PSIO_GNCT_DATCTL_INDATWD_Pos     (8)                                               /*!< PSIO_T::DATCTL: INDATWD Position       */
#define PSIO_GNCT_DATCTL_INDATWD_Msk     (0x1ful << PSIO_GNCT_DATCTL_INDATWD_Pos)          /*!< PSIO_T::DATCTL: INDATWD Mask           */

#define PSIO_GNCT_DATCTL_ORDER_Pos       (16)                                              /*!< PSIO_T::DATCTL: ORDER Position         */
#define PSIO_GNCT_DATCTL_ORDER_Msk       (0x1ul << PSIO_GNCT_DATCTL_ORDER_Pos)             /*!< PSIO_T::DATCTL: ORDER Mask             */

#define PSIO_GNCT_DATCTL_OUTDEPTH_Pos    (24)                                              /*!< PSIO_T::DATCTL: OUTDEPTH Position      */
#define PSIO_GNCT_DATCTL_OUTDEPTH_Msk    (0x3ul << PSIO_GNCT_DATCTL_OUTDEPTH_Pos)          /*!< PSIO_T::DATCTL: OUTDEPTH Mask          */

#define PSIO_GNCT_DATCTL_INDEPTH_Pos     (28)                                              /*!< PSIO_T::DATCTL: INDEPTH Position       */
#define PSIO_GNCT_DATCTL_INDEPTH_Msk     (0x3ul << PSIO_GNCT_DATCTL_INDEPTH_Pos)           /*!< PSIO_T::DATCTL: INDEPTH Mask           */

#define PSIO_GNCT_INSTS_INSTS_Pos        (0)                                               /*!< PSIO_T::INSTS: INSTS Position          */
#define PSIO_GNCT_INSTS_INSTS_Msk        (0xfful << PSIO_GNCT_INSTS_INSTS_Pos)             /*!< PSIO_T::INSTS: INSTS Mask              */

#define PSIO_GNCT_INDAT_INDAT_Pos        (0)                                               /*!< PSIO_T::INDAT: INDAT Position          */
#define PSIO_GNCT_INDAT_INDAT_Msk        (0xfffffffful << PSIO_GNCT_INDAT_INDAT_Pos)       /*!< PSIO_T::INDAT: INDAT Mask              */

#define PSIO_GNCT_OUTDAT_OUTDAT_Pos      (0)                                               /*!< PSIO_T::OUTDAT: OUTDAT Position        */
#define PSIO_GNCT_OUTDAT_OUTDAT_Msk      (0xfffffffful << PSIO_GNCT_OUTDAT_OUTDAT_Pos)     /*!< PSIO_T::OUTDAT: OUTDAT Mask            */

#define PSIO_GNCT_CPCTL0_CKPT0_Pos       (0)                                               /*!< PSIO_T::CPCTL0: CKPT0 Position         */
#define PSIO_GNCT_CPCTL0_CKPT0_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT0_Pos)             /*!< PSIO_T::CPCTL0: CKPT0 Mask             */

#define PSIO_GNCT_CPCTL0_CKPT1_Pos       (4)                                               /*!< PSIO_T::CPCTL0: CKPT1 Position         */
#define PSIO_GNCT_CPCTL0_CKPT1_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT1_Pos)             /*!< PSIO_T::CPCTL0: CKPT1 Mask             */

#define PSIO_GNCT_CPCTL0_CKPT2_Pos       (8)                                               /*!< PSIO_T::CPCTL0: CKPT2 Position         */
#define PSIO_GNCT_CPCTL0_CKPT2_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT2_Pos)             /*!< PSIO_T::CPCTL0: CKPT2 Mask             */

#define PSIO_GNCT_CPCTL0_CKPT3_Pos       (12)                                              /*!< PSIO_T::CPCTL0: CKPT3 Position         */
#define PSIO_GNCT_CPCTL0_CKPT3_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT3_Pos)             /*!< PSIO_T::CPCTL0: CKPT3 Mask             */

#define PSIO_GNCT_CPCTL0_CKPT4_Pos       (16)                                              /*!< PSIO_T::CPCTL0: CKPT4 Position         */
#define PSIO_GNCT_CPCTL0_CKPT4_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT4_Pos)             /*!< PSIO_T::CPCTL0: CKPT4 Mask             */

#define PSIO_GNCT_CPCTL0_CKPT5_Pos       (20)                                              /*!< PSIO_T::CPCTL0: CKPT5 Position         */
#define PSIO_GNCT_CPCTL0_CKPT5_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT5_Pos)             /*!< PSIO_T::CPCTL0: CKPT5 Mask             */

#define PSIO_GNCT_CPCTL0_CKPT6_Pos       (24)                                              /*!< PSIO_T::CPCTL0: CKPT6 Position         */
#define PSIO_GNCT_CPCTL0_CKPT6_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT6_Pos)             /*!< PSIO_T::CPCTL0: CKPT6 Mask             */

#define PSIO_GNCT_CPCTL0_CKPT7_Pos       (28)                                              /*!< PSIO_T::CPCTL0: CKPT7 Position         */
#define PSIO_GNCT_CPCTL0_CKPT7_Msk       (0xFul << PSIO_GNCT_CPCTL0_CKPT7_Pos)             /*!< PSIO_T::CPCTL0: CKPT7 Mask             */

#define PSIO_GNCT_CPCTL1_CKPT0ACT_Pos    (0)                                               /*!< PSIO_T::CPCTL1: CKPT0ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT0ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT0ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT0ACT Mask          */

#define PSIO_GNCT_CPCTL1_CKPT1ACT_Pos    (4)                                               /*!< PSIO_T::CPCTL1: CKPT1ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT1ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT1ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT1ACT Mask          */

#define PSIO_GNCT_CPCTL1_CKPT2ACT_Pos    (8)                                               /*!< PSIO_T::CPCTL1: CKPT2ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT2ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT2ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT2ACT Mask          */

#define PSIO_GNCT_CPCTL1_CKPT3ACT_Pos    (12)                                              /*!< PSIO_T::CPCTL1: CKPT3ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT3ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT3ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT3ACT Mask          */

#define PSIO_GNCT_CPCTL1_CKPT4ACT_Pos    (16)                                              /*!< PSIO_T::CPCTL1: CKPT4ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT4ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT4ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT4ACT Mask          */

#define PSIO_GNCT_CPCTL1_CKPT5ACT_Pos    (20)                                              /*!< PSIO_T::CPCTL1: CKPT5ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT5ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT5ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT5ACT Mask          */

#define PSIO_GNCT_CPCTL1_CKPT6ACT_Pos    (24)                                              /*!< PSIO_T::CPCTL1: CKPT6ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT6ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT6ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT6ACT Mask          */

#define PSIO_GNCT_CPCTL1_CKPT7ACT_Pos    (28)                                              /*!< PSIO_T::CPCTL1: CKPT7ACT Position      */
#define PSIO_GNCT_CPCTL1_CKPT7ACT_Msk    (0x7ul << PSIO_GNCT_CPCTL1_CKPT7ACT_Pos)          /*!< PSIO_T::CPCTL1: CKPT7ACT Mask          */

/**@}*/ /* PSIO_CONST */
/**@}*/ /* end of PSIO register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __PSIO_REG_H__ */
