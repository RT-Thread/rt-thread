/**************************************************************************//**
 * @file     whc_reg.h
 * @brief    Wormhole controller register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020~2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __WHC_REG_H__
#define __WHC_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/
/**
    @addtogroup WHC Wormhole Controller (WHC)
    Memory Mapped Structure for WHC Controller
@{ */

typedef struct
{


    /**
     * @var WHC_T::WKCTL
     * Offset: 0x00  WHC Wakeup Event Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RST0WKEN  |Counterpart First Core Reset Interrupt Wake-up Enable Bit
     * |        |          |Counterpart reset event interrupt wake-up trigger event enable.
     * |        |          |0 = Counterpart reset event interrupt wake-up trigger event Disabled.
     * |        |          |1 = Counterpart reset event interrupt wake-up trigger event Enabled.
     * |[1]     |POFF0WKEN |Counterpart First Core Power Off State Interrupt Wake-up Enable Bit
     * |        |          |Counterpart power off interrupt wake-up trigger event enable.
     * |        |          |0 = Counterpart power off interrupt wake-up trigger event Disabled.
     * |        |          |1 = Counterpart power off interrupt wake-up trigger event Enabled.
     * |[2]     |PD0WKEN   |Counterpart First Core Power Down State Interrupt Wake-up Enable Bit
     * |        |          |Counterpart power down interrupt wake-up trigger event enable.
     * |        |          |0 = Counterpart power down interrupt wake-up trigger event Disabled.
     * |        |          |1 = Counterpart power down interrupt wake-up trigger event Enabled.
     * |[3]     |RST1WKEN  |A35 Second Core Reset Interrupt Wake-up Enable Bit
     * |        |          |Counterpart reset event interrupt wake-up trigger event enable.
     * |        |          |0 = Counterpart reset event interrupt wake-up trigger event Disabled.
     * |        |          |1 = Counterpart reset event interrupt wake-up trigger event Enabled.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[4]     |POFF1WKEN |A35 Second Core Power Off State Interrupt Wake-up Enable Bit
     * |        |          |Counterpart power off interrupt wake-up trigger event enable.
     * |        |          |0 = Counterpart power off interrupt wake-up trigger event Disabled.
     * |        |          |1 = Counterpart power off interrupt wake-up trigger event Enabled.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[5]     |PD1WKEN   |A35 Second Core Power Down State Interrupt Wake-up Enable Bit
     * |        |          |Counterpart power down interrupt wake-up trigger event enable.
     * |        |          |0 = Counterpart power down interrupt wake-up trigger event Disabled.
     * |        |          |1 = Counterpart power down interrupt wake-up trigger event Enabled.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[8]     |GI0WKEN   |General Interrupt 0 Wake-up Enable
     * |        |          |If this bit is set to 1, while general interrupt flag is set to 1 and interrupt enable bit is enabled, the general interrupt signal will generate a wake-up trigger event to chip.
     * |        |          |0 = Wake-up trigger event disabled if general interrupt 0 signal generated.
     * |        |          |1 = Wake-up trigger event enabled if general interrupt 0 signal generated.
     * |[9]     |GI1WKEN   |General Interrupt 1 Wake-up Enable
     * |        |          |If this bit is set to 1, while general interrupt flag is set to 1 and interrupt enable bit is enabled, the general interrupt signal will generate a wake-up trigger event to chip.
     * |        |          |0 = Wake-up trigger event disabled if general interrupt 1 signal generated.
     * |        |          |1 = Wake-up trigger event enabled if general interrupt 1 signal generated.
     * |[10]    |GI2WKEN   |General Interrupt 2 Wake-up Enable
     * |        |          |If this bit is set to 1, while general interrupt flag is set to 1 and interrupt enable bit is enabled, the general interrupt signal will generate a wake-up trigger event to chip.
     * |        |          |0 = Wake-up trigger event disabled if general interrupt 2 signal generated.
     * |        |          |1 = Wake-up trigger event enabled if general interrupt 2 signal generated.
     * |[11]    |GI3WKEN   |General Interrupt 3 Wake-up Enable
     * |        |          |If this bit is set to 1, while general interrupt flag is set to 1 and interrupt enable bit is enabled, the general interrupt signal will generate a wake-up trigger event to chip.
     * |        |          |0 = Wake-up trigger event disabled if general interrupt 3 signal generated.
     * |        |          |1 = Wake-up trigger event enabled if general interrupt 3 signal generated.
     * |[16]    |TX0WKEN   |TX Message Channel 0 Interrupt Wake-up Enable Bit
     * |        |          |TX message channel 0 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 0 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 0 interrupt wake-up trigger event Enabled.
     * |[17]    |TX1WKEN   |TX Message Channel 1 Interrupt Wake-up Enable Bit
     * |        |          |TX message channel 1 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 1 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 1 interrupt wake-up trigger event Enabled.
     * |[18]    |TX2WKEN   |TX Message Channel 2 Interrupt Wake-up Enable Bit
     * |        |          |TX message channel 2 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 2 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 2 interrupt wake-up trigger event Enabled.
     * |[19]    |TX3WKEN   |TX Message Channel 3 Interrupt Wake-up Enable Bit
     * |        |          |TX message channel 3 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 3 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 3 interrupt wake-up trigger event Enabled.
     * |[24]    |RX0WKEN   |RX Message Channel 0 Interrupt Wake-up Enable Bit
     * |        |          |RX message channel 0 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 0 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 0 interrupt wake-up trigger event Enabled.
     * |[25]    |RX1WKEN   |RX Message Channel 1 Interrupt Wake-up Enable Bit
     * |        |          |RX message channel 1 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 1 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 1 interrupt wake-up trigger event Enabled.
     * |[26]    |RX2WKEN   |RX Message Channel 2 Interrupt Wake-up Enable Bit
     * |        |          |RX message Channel 2 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 2 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 2 interrupt wake-up trigger event Enabled.
     * |[27]    |RX3WKEN   |RX Message Channel 3 Interrupt Wake-up Enable Bit
     * |        |          |RX message channel 3 interrupt wake-up trigger event enable.
     * |        |          |0 = Channel 3 interrupt wake-up trigger event Disabled.
     * |        |          |1 = Channel 3 interrupt wake-up trigger event Enabled.
     * @var WHC_T::INTEN
     * Offset: 0x04  WHC Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RST0IEN   |Counterpart First Core Reset Event Interrupt Enable Bit
     * |        |          |Counterpart reset event interrupt enable.
     * |        |          |0 = Counterpart status change interrupt Disabled.
     * |        |          |1 = Counterpart status change interrupt Enabled.
     * |[1]     |POFF0IEN  |Counterpart First Core Enter/Exit Power Off Mode Interrupt Enable Bit
     * |        |          |Counterpart Enter/Exit Power Off Mode Interrupt Enable
     * |        |          |0 = Counterpart power Off status change interrupt Disabled.
     * |        |          |1 = Counterpart power Off status change interrupt Enabled.
     * |[2]     |PD0IEN    |Counterpart First Core Enter/Exit Power-down mode Interrupt Enable Bit
     * |        |          |Counterpart Enter/Exit Power-down mode Interrupt Enable
     * |        |          |0 = Counterpart power down status change interrupt Disabled.
     * |        |          |1 = Counterpart power down status change interrupt Enabled.
     * |[3]     |RST1IEN   |A35 Second Core Reset Event Interrupt Enable Bit
     * |        |          |Counterpart reset event interrupt enable.
     * |        |          |0 = Counterpart status change interrupt Disabled.
     * |        |          |1 = Counterpart status change interrupt Enabled.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[4]     |POFF1IEN  |A35 Second Core Enter/Exit Power Off Mode Interrupt Enable Bit
     * |        |          |Counterpart Enter/Exit Power Off Mode Interrupt Enable
     * |        |          |0 = Counterpart power Off status change interrupt Disabled.
     * |        |          |1 = Counterpart power Off status change interrupt Enabled.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[5]     |PD1IEN    |A35 Second Core Enter/Exit Power-down mode Interrupt Enable Bit
     * |        |          |Counterpart Enter/Exit Power-down mode Interrupt Enable
     * |        |          |0 = Counterpart power down status change interrupt Disabled.
     * |        |          |1 = Counterpart power down status change interrupt Enabled.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[8]     |GI0IEN    |General Interrupt 0 Enable Bit
     * |        |          |General interrupt 0 interrupt enable.
     * |        |          |0 = General interrupt 0 interrupt Disabled.
     * |        |          |1 = General interrupt 0 interrupt Enabled.
     * |[9]     |GI1IEN    |General Interrupt 1 Enable Bit
     * |        |          |General interrupt 1 interrupt enable.
     * |        |          |0 = General interrupt 1 interrupt Disabled.
     * |        |          |1 = General interrupt 1 interrupt Enabled.
     * |[10]    |GI2IEN    |General Interrupt 2 Enable Bit
     * |        |          |General interrupt 2 interrupt enable.
     * |        |          |0 = General interrupt 2 interrupt Disabled.
     * |        |          |1 = General interrupt 2 interrupt Enabled.
     * |[11]    |GI3IEN    |General Interrupt 3 Enable Bit
     * |        |          |General interrupt 3 interrupt enable.
     * |        |          |0 = General interrupt 3 interrupt Disabled.
     * |        |          |1 = General interrupt 3 interrupt Enabled.
     * |[16]    |TX0IEN    |TX Message Channel 0 Interrupt Enable Bit
     * |        |          |TX message channel 0 ACK interrupt enable
     * |        |          |0 = Channel 0 ACK interrupt Disabled.
     * |        |          |1 = Channel 0 ACK interrupt Enabled.
     * |[17]    |TX1IEN    |TX Message Channel 1 Interrupt Enable Bit
     * |        |          |TX message channel 1 ACK interrupt enable.
     * |        |          |0 = Channel 1 ACK interrupt Disabled.
     * |        |          |1 = Channel 1 ACK interrupt Enabled.
     * |[18]    |TX2IEN    |TX Message Channel 2 Interrupt Enable Bit
     * |        |          |TX message channel 2 ACK interrupt enable.
     * |        |          |0 = Channel 2 ACK interrupt Disabled.
     * |        |          |1 = Channel 2 ACK interrupt Enabled.
     * |[19]    |TX3IEN    |TX Message Channel 3 Interrupt Enable Bit
     * |        |          |TX message channel 3 ACK interrupt enable
     * |        |          |0 = Channel 3 ACK interrupt Disabled.
     * |        |          |1 = Channel 3 ACK interrupt Enabled.
     * |[24]    |RX0IEN    |RX Message Channel 0 Interrupt Enable Bit
     * |        |          |RX message channel 0 arrive or recall interrupt enable
     * |        |          |0 = Channel 0 arrive or recall interrupt Disabled.
     * |        |          |1 = Channel 0 arrive or recall interrupt Enabled.
     * |[25]    |RX1IEN    |RX Message Channel 1 Interrupt Enable Bit
     * |        |          |RX message channel 1 arrive or recall interrupt enable.
     * |        |          |0 = Channel 1 arrive or recall interrupt Disabled.
     * |        |          |1 = Channel 1 arrive or recall interrupt Enabled.
     * |[26]    |RX2IEN    |RX Message Channel 2 Interrupt Enable Bit
     * |        |          |RX message channel 2 arrive or recall interrupt enable.
     * |        |          |0 = Channel 2 arrive or recall interrupt Disabled.
     * |        |          |1 = Channel 2 arrive or recall interrupt Enabled.
     * |[27]    |RX3IEN    |RX Message Channel 3 Interrupt Enable Bit
     * |        |          |RX message channel 3 arrive or recall interrupt enable
     * |        |          |0 = Channel 3 arrive or recall interrupt Disabled.
     * |        |          |1 = Channel 3 arrive or recall interrupt Enabled.
     * @var WHC_T::INTSTS
     * Offset: 0x08  WHC Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RST0IF    |Counterpart First Core Reset Event Interrupt Flag
     * |        |          |Counterpart reset event interrupt flag.
     * |        |          |0 = No counterpart reset status change interrupt generated.
     * |        |          |1 = Counterpart reset status change interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[1]     |POFF0IF   |Counterpart First Core Enter/Exit Power Off Mode Interrupt Flag
     * |        |          |Counterpart Enter/Exit Power Off Mode Interrupt Flag
     * |        |          |0 = No counterpart power off mode status change interrupt generated.
     * |        |          |1 = Counterpart power off mode status change interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0..
     * |[2]     |PD0IF     |Counterpart First Core Enter/Exit Power-down mode Interrupt Flag
     * |        |          |Counterpart Enter/Exit Power-down mode Interrupt Flag
     * |        |          |0 = No counterpart Power-down mode status change interrupt generated.
     * |        |          |1 = Counterpart Power-down mode status change interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[3]     |RST1IF    |A35 Second Core Reset Event Interrupt Flag
     * |        |          |Counterpart reset event interrupt flag.
     * |        |          |0 = No counterpart reset status change interrupt generated.
     * |        |          |1 = Counterpart reset status change interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[4]     |POFF1IF   |A35 Second Core Enter/Exit Power Off Mode Interrupt Flag
     * |        |          |Counterpart Enter/Exit Power Off Mode Interrupt Flag
     * |        |          |0 = No counterpart power off mode status change interrupt generated.
     * |        |          |1 = Counterpart power off mode status change interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[5]     |PD1IF     |A35 Second Core Enter/Exit Power-down mode Interrupt Flag
     * |        |          |Counterpart Enter/Exit Power-down mode Interrupt Flag
     * |        |          |0 = No counterpart Power-down mode status change interrupt generated.
     * |        |          |1 = Counterpart Power-down mode status change interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |        |          |Note: This bit which indicates the second A35 core is only available for M4 side.
     * |[8]     |GI0IF     |General Event 0 Flag
     * |        |          |General event 0 interrupt flag.
     * |        |          |0 = No general event 0 interrupt generated.
     * |        |          |1 = General event 0 interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[9]     |GI1IF     |General Event 1 Flag
     * |        |          |General event 1 interrupt flag.
     * |        |          |0 = No general event 1 interrupt generated.
     * |        |          |1 = General event 1 interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[10]    |GI2IF     |General Event 2 Flag
     * |        |          |General event 2 interrupt flag.
     * |        |          |0 = No general event 2 interrupt generated.
     * |        |          |1 = General event 2 interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[11]    |GI3IF     |General Event 3 Flag
     * |        |          |General event 3 interrupt flag.
     * |        |          |0 = No general event 3 interrupt generated.
     * |        |          |1 = General event 3 interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[16]    |TX0IF     |TX Message Channel 0 Interrupt Flag
     * |        |          |Tx message channel 0 ACK interrupt flag.
     * |        |          |0 = No channel 0 ACK interrupt generated.
     * |        |          |1 = Channel 0 ACK interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[17]    |TX1IF     |TX Message Channel 1 Interrupt Flag
     * |        |          |Tx message channel 1 ACK interrupt flag.
     * |        |          |0 = No channel 1 ACK interrupt generated.
     * |        |          |1 = Channel 1 ACK interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[18]    |TX2IF     |TX Message Channel 2 Interrupt Flag
     * |        |          |Tx message channel 2 ACK interrupt flag.
     * |        |          |0 = No channel 2 ACK interrupt generated.
     * |        |          |1 = Channel 2 ACK interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[19]    |TX3IF     |TX Message Channel 3 Interrupt Flag
     * |        |          |Tx message channel 3 ACK interrupt flag.
     * |        |          |0 = No channel 3 ACK interrupt generated.
     * |        |          |1 = Channel 3 ACK interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[24]    |RX0IF     |RX Message Channel 0 Interrupt Flag
     * |        |          |Short message channel 0 arrive or recall interrupt flag.
     * |        |          |0 = No channel 0 arrive or recall interrupt generated.
     * |        |          |1 = Channel 0 arrive or recall interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[25]    |RX1IF     |RX Message Channel 1 Interrupt Flag
     * |        |          |Short message channel 1 arrive or recall interrupt flag.
     * |        |          |0 = No channel 1 arrive or recall interrupt generated.
     * |        |          |1 = Channel 1 arrive or recall interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[26]    |RX2IF     |RX Message Channel 2 Interrupt Flag
     * |        |          |Short message channel 2 arrive or recall interrupt flag.
     * |        |          |0 = No channel 2 arrive or recall interrupt generated.
     * |        |          |1 = Channel 2 arrive or recall interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[27]    |RX3IF     |RX Message Channel 3 Interrupt Flag
     * |        |          |RX message channel 3 arrive or recall interrupt flag.
     * |        |          |0 = No channel 3 arrive or recall interrupt generated.
     * |        |          |1 = Channel 3 arrive or recall interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * @var WHC_T::CPSTS
     * Offset: 0x40  WHC Counterpart Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |WDTRF     |WDT Reset Flag
     * |        |          |The WDT reset flag is set by the Reset Signal from the Watchdog Timer or Window Watchdog Timer to indicate the previous reset source.
     * |        |          |0 = No reset from watchdog timer or window watchdog timer.
     * |        |          |1 = The watchdog timer or window watchdog timer had issued the reset signal to reset the system.
     * |        |          |Note 1: Read only, write 1 to clear this bit to 0.
     * |        |          |Note 2: Watchdog Timer register RSTF(WDT_CTL[2]) bit is set if the system has been reset by WDT time-out reset
     * |        |          |Window Watchdog Timer register WWDTRF(WWDT_STATUS[1]) bit is set if the system has been reset by WWDT time-out reset.
     * |[5]     |SYSRF     |System Reset Flag
     * |        |          |The system reset flag is set by the Reset Signal from the Cortex-M4 Core to indicate the previous reset source.
     * |        |          |0 = No reset from Cortex-M4.
     * |        |          |1 = The Cortex-M4 had issued the reset signal to reset the system by writing 1 to the bit SYSRESETREQ(AIRCR[2], Application Interrupt and Reset Control Register, address = 0xE000ED0C) in system control registers of Cortex-M4 core.
     * |        |          |Note: Read only, write 1 to clear this bit to 0.
     * |[7]     |CPURF     |CPU Reset Flag
     * |        |          |The CPU reset flag is set by hardware if software writes CPURST (SYS_IPRST0[1]) 1 to reset Cortex-M4 Core and Flash Memory Controller (FMC).
     * |        |          |0 = No reset from CPU.
     * |        |          |1 = The Cortex-M4 Core and FMC are reset by software setting CPURST to 1.
     * |        |          |Note: Read only, write 1 to clear this bit to 0.
     * |[8]     |CPULKRF   |CPU Lockup Reset Flag
     * |        |          |0 = No reset from CPU lockup happened.
     * |        |          |1 = The Cortex-M4 lockup happened and chip is reset.
     * |        |          |Note 1: Read only, write 1 to clear this bit to 0.
     * |        |          |Note 2: When CPU lockup happened under ICE is connected, This flag will set to 1 but chip will not reset.
     * |[27:24] |OPMODE0   |Operating Mode of Other Side Core 0, Representing A35/M4 Core 0 (Read Only)
     * |        |          |This bit field indicates the operating mode of the core 0 of the other side.
     * |        |          |0000 = Run mode.
     * |        |          |0001 = Power off mode.
     * |        |          |0010 = Power-down mode.
     * |        |          |Others = Reserved.
     * |[31:28] |OPMODE1   |Operating Mode of Other Side Core 1, Representing A35 Core 1 (Read Only)
     * |        |          |This bit field indicates the operating mode of the core 1 of the other side.
     * |        |          |0000 = Run mode.
     * |        |          |0001 = Power off mode.
     * |        |          |0010 = Power-down mode.
     * |        |          |Others = Reserved.
     * |        |          |Note 1: This field can only be accessed by M4 side.
     * @var WHC_T::GINTTRG
     * Offset: 0x80  WHC General Interrupt Trigger Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TRGGI0    |Trigger General Interrupt 0
     * |        |          |Write this bit 1 to trigger general interrupt 0.
     * |[1]     |TRGGI1    |Trigger General Interrupt 1
     * |        |          |Write this bit 1 to trigger general interrupt 1.
     * |[2]     |TRGGI2    |Trigger General Interrupt 2
     * |        |          |Write this bit 1 to trigger general interrupt 2.
     * |[3]     |TRGGI3    |Trigger General Interrupt 3
     * |        |          |Write this bit 1 to trigger general interrupt 3.
     * @var WHC_T::TXCTL
     * Offset: 0xC0  WHC TX Message Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CH0SND    |Send Channel 0 Message
     * |        |          |Write 1 to this bit to send TX channel 0 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 1 or not
     * |        |          |Otherwise, the receiver may get unpredictable data.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * |[1]     |CH1SND    |Send Channel 1 Message
     * |        |          |Write 1 to this bit to send TX channel 1 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 1 or not
     * |        |          |Otherwise, the receiver may get unpredictable data.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * |[2]     |CH2SND    |Send Channel 2 Message
     * |        |          |Write 1 to this bit to send TX channel 2 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 1 or not
     * |        |          |Otherwise, the receiver may get unpredictable data.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * |[3]     |CH3SND    |Send Channel 3 Message
     * |        |          |Write 1 to this bit to send TX channel 3 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 1 or not
     * |        |          |Otherwise, the receiver may get unpredictable data.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * |[16]    |CH0RC     |Recall Channel 1 Message
     * |        |          |Write 1 to this bit to recall TX channel 1 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 0 or not.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * |[17]    |CH1RC     |Recall Channel 1 Message
     * |        |          |Write 1 to this bit to recall TX channel 1 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 0 or not.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * |[18]    |CH2RC     |Recall Channel 2 Message
     * |        |          |Write 1 to this bit to recall TX channel 2 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 0 or not.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * |[19]    |CH3RC     |Recall Channel 3 Message
     * |        |          |Write 1 to this bit to recall TX channel 3 message
     * |        |          |Before write 1 to this bit, sender should check the corresponding CHxRDY bit in TXSTS is 0 or not.
     * |        |          |Note: Write 0 to this bit has no effect
     * |        |          |Write 1 to SND and RC bits of the same channel simultaneously will yield unpredictable result.
     * @var WHC_T::TXSTS
     * Offset: 0xC4  WHC TX Message Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CH0RDY    |Channel 0 Message Ready
     * |        |          |0 = No recall event.
     * |        |          |1 = Message channel is available to send new data.
     * |        |          |This bit automatically cleared to 0 after write 1 to CH0SND
     * |        |          |Automatically set to 1 after recall complete or receiver notify message read.
     * |[1]     |CH1RDY    |Channel 1 Message Ready
     * |        |          |0 = No recall event.
     * |        |          |1 = Message channel is available to send new data.
     * |        |          |This bit automatically cleared to 0 after write 1 to CH1SND
     * |        |          |Automatically set to 1 after recall complete or receiver notify message read.
     * |[2]     |CH2RDY    |Channel 2 Message Ready
     * |        |          |0 = No recall event.
     * |        |          |1 = Message channel is available to send new data.
     * |        |          |This bit automatically cleared to 0 after write 1 to CH2SND
     * |        |          |Automatically set to 1 after recall complete or receiver notify message read.
     * |[3]     |CH3RDY    |Channel 3 Message Ready
     * |        |          |0 = No recall event.
     * |        |          |1 = Message channel is available to send new data.
     * |        |          |This bit automatically cleared to 0 after write 1 to CH3SND
     * |        |          |Automatically set to 1 after recall complete or receiver notify message read.
     * @var WHC_T::RXCTL
     * Offset: 0xC8  WHC RX Message Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CH0ACK    |RX Message Channel 0 ACK
     * |        |          |Write 1 to notify sender that channel 0 message has been read. Write 0 to this bit has no effect.
     * |        |          |Write 1 will clear CH0RDY.
     * |[1]     |CH1ACK    |RX Message Channel 1 ACK
     * |        |          |Write 1 to notify sender that channel 1 message has been read. Write 0 to this bit has no effect.
     * |        |          |Write 1 will clear CH1RDY.
     * |[2]     |CH2ACK    |RX Message Channel 2 ACK
     * |        |          |Write 1 to notify sender that channel 2 message has been read. Write 0 to this bit has no effect.
     * |        |          |Write 1 will clear CH2RDY.
     * |[3]     |CH3ACK    |RX Message Channel 3 ACK
     * |        |          |Write 1 to notify sender that channel 3 message has been read. Write 0 to this bit has no effect.
     * |        |          |Write 1 will clear CH3RDY.
     * @var WHC_T::RXSTS
     * Offset: 0xCC  WHC RX Message Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CH0RDY    |RX Channel 0 Message Ready
     * |        |          |0 = RX channel 0 message data is not ready.
     * |        |          |1 = RX channel 0 message data is ready.
     * |        |          |Note: This bit is automatically set to 1 after sender writes 1 to CH0SND
     * |        |          |It is automatically cleared to 0 after recall complete or write 1 to CH0ACK.
     * |[1]     |CH1RDY    |RX Channel 1 Message Ready
     * |        |          |0 = RX channel 1 message data is not ready.
     * |        |          |1 = RX channel 1 message data is ready.
     * |        |          |Note: This bit is automatically set to 1 after sender writes 1 to CH1SND
     * |        |          |It is automatically cleared to 0 after recall complete or write 1 to CH1ACK.
     * |[2]     |CH2RDY    |RX Channel 2 Message Ready
     * |        |          |0 = RX channel 2 message data is not ready.
     * |        |          |1 = RX channel 2 message data is ready.
     * |        |          |Note: This bit is automatically set to 1 after sender writes 1 to CH2SND
     * |        |          |It is automatically cleared to 0 after recall complete or write 1 to CH2ACK.
     * |[3]     |CH3RDY    |RX Channel 3 Message Ready
     * |        |          |0 = RX channel 3 message data is not ready.
     * |        |          |1 = RX channel 3 message data is ready.
     * |        |          |Note: This bit is automatically set to 1 after sender writes 1 to CH3SND
     * |        |          |It is automatically cleared to 0 after recall complete or write 1 to CH3ACK.
     * @var WHC_T::TM0DAT0
     * Offset: 0x100  WHC TX Message Channel 0 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM0DAT1
     * Offset: 0x104  WHC TX Message Channel 0 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM0DAT2
     * Offset: 0x108  WHC TX Message Channel 0 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM0DAT3
     * Offset: 0x10C  WHC TX Message Channel 0 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM1DAT0
     * Offset: 0x110  WHC TX Message Channel 1 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM1DAT1
     * Offset: 0x114  WHC TX Message Channel 1 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM1DAT2
     * Offset: 0x118  WHC TX Message Channel 1 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM1DAT3
     * Offset: 0x11C  WHC TX Message Channel 1 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM2DAT0
     * Offset: 0x120  WHC TX Message Channel 2 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM2DAT1
     * Offset: 0x124  WHC TX Message Channel 2 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM2DAT2
     * Offset: 0x128  WHC TX Message Channel 2 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM2DAT3
     * Offset: 0x12C  WHC TX Message Channel 2 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM3DAT0
     * Offset: 0x130  WHC TX Message Channel 3 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM3DAT1
     * Offset: 0x134  WHC TX Message Channel 3 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM3DAT2
     * Offset: 0x138  WHC TX Message Channel 3 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::TM3DAT3
     * Offset: 0x13C  WHC TX Message Channel 3 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |TX Message Data
     * |        |          |This field contains the TX message data field
     * |        |          |Sender should only write these registers while ready bit in TXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM0DAT0
     * Offset: 0x200  WHC RX Message Channel 0 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM0DAT1
     * Offset: 0x204  WHC RX Message Channel 0 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM0DAT2
     * Offset: 0x208  WHC RX Message Channel 0 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM0DAT3
     * Offset: 0x20C  WHC RX Message Channel 0 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM1DAT0
     * Offset: 0x210  WHC RX Message Channel 1 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM1DAT1
     * Offset: 0x214  WHC RX Message Channel 1 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM1DAT2
     * Offset: 0x218  WHC RX Message Channel 1 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM1DAT3
     * Offset: 0x21C  WHC RX Message Channel 1 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM2DAT0
     * Offset: 0x220  WHC RX Message Channel 2 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM2DAT1
     * Offset: 0x224  WHC RX Message Channel 2 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM2DAT2
     * Offset: 0x228  WHC RX Message Channel 2 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM2DAT3
     * Offset: 0x22C  WHC RX Message Channel 2 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM3DAT0
     * Offset: 0x230  WHC RX Message Channel 3 Data 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM3DAT1
     * Offset: 0x234  WHC RX Message Channel 3 Data 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM3DAT2
     * Offset: 0x238  WHC RX Message Channel 3 Data 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     * @var WHC_T::RM3DAT3
     * Offset: 0x23C  WHC RX Message Channel 3 Data 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |RX Message Data
     * |        |          |This field contains the RX message data field
     * |        |          |Receiver should only read these registers while ready bit in RXSTS register is 1
     * |        |          |Otherwise, the receiver can read unpredictable data.
     */
    __IO uint32_t WKCTL;                 /*!< [0x0000] WHC Wakeup Event Control Register                                */
    __IO uint32_t INTEN;                 /*!< [0x0004] WHC Interrupt Enable Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x0008] WHC Interrupt Status Register                                    */
    __I  uint32_t RESERVE0[13];
    __IO uint32_t CPSTS;                 /*!< [0x0040] WHC Counterpart Status Register                                  */
    __I  uint32_t RESERVE1[15];
    __O  uint32_t GINTTRG;               /*!< [0x0080] WHC General Interrupt Trigger Register                           */
    __I  uint32_t RESERVE2[15];
    __O  uint32_t TXCTL;                 /*!< [0x00c0] WHC TX Message Control Register                                  */
    __I  uint32_t TXSTS;                 /*!< [0x00c4] WHC TX Message Status Register                                   */
    __O  uint32_t RXCTL;                 /*!< [0x00c8] WHC RX Message Control Register                                  */
    __I  uint32_t RXSTS;                 /*!< [0x00cc] WHC RX Message Status Register                                   */
    __I  uint32_t RESERVE3[12];
    __O  uint32_t TMDAT[4][4];           /*!< [0x0100~0x013C] WHC TX Message Data Register                              */
    __I  uint32_t RESERVE4[48];
    __I  uint32_t RMDAT[4][4];           /*!< [0x0200~0x023C] WHC RX Message Data Register                              */
} WHC_T;

/**
    @addtogroup WHC_CONST WHC Bit Field Definition
    Constant Definitions for WHC Controller
@{ */

#define WHC_WKCTL_RST0WKEN_Pos           (0)                                               /*!< WHC_T::WKCTL: RST0WKEN Position        */
#define WHC_WKCTL_RST0WKEN_Msk           (0x1ul << WHC_WKCTL_RST0WKEN_Pos)                 /*!< WHC_T::WKCTL: RST0WKEN Mask            */

#define WHC_WKCTL_POFF0WKEN_Pos          (1)                                               /*!< WHC_T::WKCTL: POFF0WKEN Position       */
#define WHC_WKCTL_POFF0WKEN_Msk          (0x1ul << WHC_WKCTL_POFF0WKEN_Pos)                /*!< WHC_T::WKCTL: POFF0WKEN Mask           */

#define WHC_WKCTL_PD0WKEN_Pos            (2)                                               /*!< WHC_T::WKCTL: PD0WKEN Position         */
#define WHC_WKCTL_PD0WKEN_Msk            (0x1ul << WHC_WKCTL_PD0WKEN_Pos)                  /*!< WHC_T::WKCTL: PD0WKEN Mask             */

#define WHC_WKCTL_RST1WKEN_Pos           (3)                                               /*!< WHC_T::WKCTL: RST1WKEN Position        */
#define WHC_WKCTL_RST1WKEN_Msk           (0x1ul << WHC_WKCTL_RST1WKEN_Pos)                 /*!< WHC_T::WKCTL: RST1WKEN Mask            */

#define WHC_WKCTL_POFF1WKEN_Pos          (4)                                               /*!< WHC_T::WKCTL: POFF1WKEN Position       */
#define WHC_WKCTL_POFF1WKEN_Msk          (0x1ul << WHC_WKCTL_POFF1WKEN_Pos)                /*!< WHC_T::WKCTL: POFF1WKEN Mask           */

#define WHC_WKCTL_PD1WKEN_Pos            (5)                                               /*!< WHC_T::WKCTL: PD1WKEN Position         */
#define WHC_WKCTL_PD1WKEN_Msk            (0x1ul << WHC_WKCTL_PD1WKEN_Pos)                  /*!< WHC_T::WKCTL: PD1WKEN Mask             */

#define WHC_WKCTL_GI0WKEN_Pos            (8)                                               /*!< WHC_T::WKCTL: GI0WKEN Position         */
#define WHC_WKCTL_GI0WKEN_Msk            (0x1ul << WHC_WKCTL_GI0WKEN_Pos)                  /*!< WHC_T::WKCTL: GI0WKEN Mask             */

#define WHC_WKCTL_GI1WKEN_Pos            (9)                                               /*!< WHC_T::WKCTL: GI1WKEN Position         */
#define WHC_WKCTL_GI1WKEN_Msk            (0x1ul << WHC_WKCTL_GI1WKEN_Pos)                  /*!< WHC_T::WKCTL: GI1WKEN Mask             */

#define WHC_WKCTL_GI2WKEN_Pos            (10)                                              /*!< WHC_T::WKCTL: GI2WKEN Position         */
#define WHC_WKCTL_GI2WKEN_Msk            (0x1ul << WHC_WKCTL_GI2WKEN_Pos)                  /*!< WHC_T::WKCTL: GI2WKEN Mask             */

#define WHC_WKCTL_GI3WKEN_Pos            (11)                                              /*!< WHC_T::WKCTL: GI3WKEN Position         */
#define WHC_WKCTL_GI3WKEN_Msk            (0x1ul << WHC_WKCTL_GI3WKEN_Pos)                  /*!< WHC_T::WKCTL: GI3WKEN Mask             */

#define WHC_WKCTL_TX0WKEN_Pos            (16)                                              /*!< WHC_T::WKCTL: TX0WKEN Position         */
#define WHC_WKCTL_TX0WKEN_Msk            (0x1ul << WHC_WKCTL_TX0WKEN_Pos)                  /*!< WHC_T::WKCTL: TX0WKEN Mask             */

#define WHC_WKCTL_TX1WKEN_Pos            (17)                                              /*!< WHC_T::WKCTL: TX1WKEN Position         */
#define WHC_WKCTL_TX1WKEN_Msk            (0x1ul << WHC_WKCTL_TX1WKEN_Pos)                  /*!< WHC_T::WKCTL: TX1WKEN Mask             */

#define WHC_WKCTL_TX2WKEN_Pos            (18)                                              /*!< WHC_T::WKCTL: TX2WKEN Position         */
#define WHC_WKCTL_TX2WKEN_Msk            (0x1ul << WHC_WKCTL_TX2WKEN_Pos)                  /*!< WHC_T::WKCTL: TX2WKEN Mask             */

#define WHC_WKCTL_TX3WKEN_Pos            (19)                                              /*!< WHC_T::WKCTL: TX3WKEN Position         */
#define WHC_WKCTL_TX3WKEN_Msk            (0x1ul << WHC_WKCTL_TX3WKEN_Pos)                  /*!< WHC_T::WKCTL: TX3WKEN Mask             */

#define WHC_WKCTL_RX0WKEN_Pos            (24)                                              /*!< WHC_T::WKCTL: RX0WKEN Position         */
#define WHC_WKCTL_RX0WKEN_Msk            (0x1ul << WHC_WKCTL_RX0WKEN_Pos)                  /*!< WHC_T::WKCTL: RX0WKEN Mask             */

#define WHC_WKCTL_RX1WKEN_Pos            (25)                                              /*!< WHC_T::WKCTL: RX1WKEN Position         */
#define WHC_WKCTL_RX1WKEN_Msk            (0x1ul << WHC_WKCTL_RX1WKEN_Pos)                  /*!< WHC_T::WKCTL: RX1WKEN Mask             */

#define WHC_WKCTL_RX2WKEN_Pos            (26)                                              /*!< WHC_T::WKCTL: RX2WKEN Position         */
#define WHC_WKCTL_RX2WKEN_Msk            (0x1ul << WHC_WKCTL_RX2WKEN_Pos)                  /*!< WHC_T::WKCTL: RX2WKEN Mask             */

#define WHC_WKCTL_RX3WKEN_Pos            (27)                                              /*!< WHC_T::WKCTL: RX3WKEN Position         */
#define WHC_WKCTL_RX3WKEN_Msk            (0x1ul << WHC_WKCTL_RX3WKEN_Pos)                  /*!< WHC_T::WKCTL: RX3WKEN Mask             */

#define WHC_INTEN_RST0IEN_Pos            (0)                                               /*!< WHC_T::INTEN: RST0IEN Position         */
#define WHC_INTEN_RST0IEN_Msk            (0x1ul << WHC_INTEN_RST0IEN_Pos)                  /*!< WHC_T::INTEN: RST0IEN Mask             */

#define WHC_INTEN_POFF0IEN_Pos           (1)                                               /*!< WHC_T::INTEN: POFF0IEN Position        */
#define WHC_INTEN_POFF0IEN_Msk           (0x1ul << WHC_INTEN_POFF0IEN_Pos)                 /*!< WHC_T::INTEN: POFF0IEN Mask            */

#define WHC_INTEN_PD0IEN_Pos             (2)                                               /*!< WHC_T::INTEN: PD0IEN Position          */
#define WHC_INTEN_PD0IEN_Msk             (0x1ul << WHC_INTEN_PD0IEN_Pos)                   /*!< WHC_T::INTEN: PD0IEN Mask              */

#define WHC_INTEN_RST1IEN_Pos            (3)                                               /*!< WHC_T::INTEN: RST1IEN Position         */
#define WHC_INTEN_RST1IEN_Msk            (0x1ul << WHC_INTEN_RST1IEN_Pos)                  /*!< WHC_T::INTEN: RST1IEN Mask             */

#define WHC_INTEN_POFF1IEN_Pos           (4)                                               /*!< WHC_T::INTEN: POFF1IEN Position        */
#define WHC_INTEN_POFF1IEN_Msk           (0x1ul << WHC_INTEN_POFF1IEN_Pos)                 /*!< WHC_T::INTEN: POFF1IEN Mask            */

#define WHC_INTEN_PD1IEN_Pos             (5)                                               /*!< WHC_T::INTEN: PD1IEN Position          */
#define WHC_INTEN_PD1IEN_Msk             (0x1ul << WHC_INTEN_PD1IEN_Pos)                   /*!< WHC_T::INTEN: PD1IEN Mask              */

#define WHC_INTEN_GI0IEN_Pos             (8)                                               /*!< WHC_T::INTEN: GI0IEN Position          */
#define WHC_INTEN_GI0IEN_Msk             (0x1ul << WHC_INTEN_GI0IEN_Pos)                   /*!< WHC_T::INTEN: GI0IEN Mask              */

#define WHC_INTEN_GI1IEN_Pos             (9)                                               /*!< WHC_T::INTEN: GI1IEN Position          */
#define WHC_INTEN_GI1IEN_Msk             (0x1ul << WHC_INTEN_GI1IEN_Pos)                   /*!< WHC_T::INTEN: GI1IEN Mask              */

#define WHC_INTEN_GI2IEN_Pos             (10)                                              /*!< WHC_T::INTEN: GI2IEN Position          */
#define WHC_INTEN_GI2IEN_Msk             (0x1ul << WHC_INTEN_GI2IEN_Pos)                   /*!< WHC_T::INTEN: GI2IEN Mask              */

#define WHC_INTEN_GI3IEN_Pos             (11)                                              /*!< WHC_T::INTEN: GI3IEN Position          */
#define WHC_INTEN_GI3IEN_Msk             (0x1ul << WHC_INTEN_GI3IEN_Pos)                   /*!< WHC_T::INTEN: GI3IEN Mask              */

#define WHC_INTEN_TX0IEN_Pos             (16)                                              /*!< WHC_T::INTEN: TX0IEN Position          */
#define WHC_INTEN_TX0IEN_Msk             (0x1ul << WHC_INTEN_TX0IEN_Pos)                   /*!< WHC_T::INTEN: TX0IEN Mask              */

#define WHC_INTEN_TX1IEN_Pos             (17)                                              /*!< WHC_T::INTEN: TX1IEN Position          */
#define WHC_INTEN_TX1IEN_Msk             (0x1ul << WHC_INTEN_TX1IEN_Pos)                   /*!< WHC_T::INTEN: TX1IEN Mask              */

#define WHC_INTEN_TX2IEN_Pos             (18)                                              /*!< WHC_T::INTEN: TX2IEN Position          */
#define WHC_INTEN_TX2IEN_Msk             (0x1ul << WHC_INTEN_TX2IEN_Pos)                   /*!< WHC_T::INTEN: TX2IEN Mask              */

#define WHC_INTEN_TX3IEN_Pos             (19)                                              /*!< WHC_T::INTEN: TX3IEN Position          */
#define WHC_INTEN_TX3IEN_Msk             (0x1ul << WHC_INTEN_TX3IEN_Pos)                   /*!< WHC_T::INTEN: TX3IEN Mask              */

#define WHC_INTEN_RX0IEN_Pos             (24)                                              /*!< WHC_T::INTEN: RX0IEN Position          */
#define WHC_INTEN_RX0IEN_Msk             (0x1ul << WHC_INTEN_RX0IEN_Pos)                   /*!< WHC_T::INTEN: RX0IEN Mask              */

#define WHC_INTEN_RX1IEN_Pos             (25)                                              /*!< WHC_T::INTEN: RX1IEN Position          */
#define WHC_INTEN_RX1IEN_Msk             (0x1ul << WHC_INTEN_RX1IEN_Pos)                   /*!< WHC_T::INTEN: RX1IEN Mask              */

#define WHC_INTEN_RX2IEN_Pos             (26)                                              /*!< WHC_T::INTEN: RX2IEN Position          */
#define WHC_INTEN_RX2IEN_Msk             (0x1ul << WHC_INTEN_RX2IEN_Pos)                   /*!< WHC_T::INTEN: RX2IEN Mask              */

#define WHC_INTEN_RX3IEN_Pos             (27)                                              /*!< WHC_T::INTEN: RX3IEN Position          */
#define WHC_INTEN_RX3IEN_Msk             (0x1ul << WHC_INTEN_RX3IEN_Pos)                   /*!< WHC_T::INTEN: RX3IEN Mask              */

#define WHC_INTSTS_RST0IF_Pos            (0)                                               /*!< WHC_T::INTSTS: RST0IF Position         */
#define WHC_INTSTS_RST0IF_Msk            (0x1ul << WHC_INTSTS_RST0IF_Pos)                  /*!< WHC_T::INTSTS: RST0IF Mask             */

#define WHC_INTSTS_POFF0IF_Pos           (1)                                               /*!< WHC_T::INTSTS: POFF0IF Position        */
#define WHC_INTSTS_POFF0IF_Msk           (0x1ul << WHC_INTSTS_POFF0IF_Pos)                 /*!< WHC_T::INTSTS: POFF0IF Mask            */

#define WHC_INTSTS_PD0IF_Pos             (2)                                               /*!< WHC_T::INTSTS: PD0IF Position          */
#define WHC_INTSTS_PD0IF_Msk             (0x1ul << WHC_INTSTS_PD0IF_Pos)                   /*!< WHC_T::INTSTS: PD0IF Mask              */

#define WHC_INTSTS_RST1IF_Pos            (3)                                               /*!< WHC_T::INTSTS: RST1IF Position         */
#define WHC_INTSTS_RST1IF_Msk            (0x1ul << WHC_INTSTS_RST1IF_Pos)                  /*!< WHC_T::INTSTS: RST1IF Mask             */

#define WHC_INTSTS_POFF1IF_Pos           (4)                                               /*!< WHC_T::INTSTS: POFF1IF Position        */
#define WHC_INTSTS_POFF1IF_Msk           (0x1ul << WHC_INTSTS_POFF1IF_Pos)                 /*!< WHC_T::INTSTS: POFF1IF Mask            */

#define WHC_INTSTS_PD1IF_Pos             (5)                                               /*!< WHC_T::INTSTS: PD1IF Position          */
#define WHC_INTSTS_PD1IF_Msk             (0x1ul << WHC_INTSTS_PD1IF_Pos)                   /*!< WHC_T::INTSTS: PD1IF Mask              */

#define WHC_INTSTS_GI0IF_Pos             (8)                                               /*!< WHC_T::INTSTS: GI0IF Position          */
#define WHC_INTSTS_GI0IF_Msk             (0x1ul << WHC_INTSTS_GI0IF_Pos)                   /*!< WHC_T::INTSTS: GI0IF Mask              */

#define WHC_INTSTS_GI1IF_Pos             (9)                                               /*!< WHC_T::INTSTS: GI1IF Position          */
#define WHC_INTSTS_GI1IF_Msk             (0x1ul << WHC_INTSTS_GI1IF_Pos)                   /*!< WHC_T::INTSTS: GI1IF Mask              */

#define WHC_INTSTS_GI2IF_Pos             (10)                                              /*!< WHC_T::INTSTS: GI2IF Position          */
#define WHC_INTSTS_GI2IF_Msk             (0x1ul << WHC_INTSTS_GI2IF_Pos)                   /*!< WHC_T::INTSTS: GI2IF Mask              */

#define WHC_INTSTS_GI3IF_Pos             (11)                                              /*!< WHC_T::INTSTS: GI3IF Position          */
#define WHC_INTSTS_GI3IF_Msk             (0x1ul << WHC_INTSTS_GI3IF_Pos)                   /*!< WHC_T::INTSTS: GI3IF Mask              */

#define WHC_INTSTS_TX0IF_Pos             (16)                                              /*!< WHC_T::INTSTS: TX0IF Position          */
#define WHC_INTSTS_TX0IF_Msk             (0x1ul << WHC_INTSTS_TX0IF_Pos)                   /*!< WHC_T::INTSTS: TX0IF Mask              */

#define WHC_INTSTS_TX1IF_Pos             (17)                                              /*!< WHC_T::INTSTS: TX1IF Position          */
#define WHC_INTSTS_TX1IF_Msk             (0x1ul << WHC_INTSTS_TX1IF_Pos)                   /*!< WHC_T::INTSTS: TX1IF Mask              */

#define WHC_INTSTS_TX2IF_Pos             (18)                                              /*!< WHC_T::INTSTS: TX2IF Position          */
#define WHC_INTSTS_TX2IF_Msk             (0x1ul << WHC_INTSTS_TX2IF_Pos)                   /*!< WHC_T::INTSTS: TX2IF Mask              */

#define WHC_INTSTS_TX3IF_Pos             (19)                                              /*!< WHC_T::INTSTS: TX3IF Position          */
#define WHC_INTSTS_TX3IF_Msk             (0x1ul << WHC_INTSTS_TX3IF_Pos)                   /*!< WHC_T::INTSTS: TX3IF Mask              */

#define WHC_INTSTS_RX0IF_Pos             (24)                                              /*!< WHC_T::INTSTS: RX0IF Position          */
#define WHC_INTSTS_RX0IF_Msk             (0x1ul << WHC_INTSTS_RX0IF_Pos)                   /*!< WHC_T::INTSTS: RX0IF Mask              */

#define WHC_INTSTS_RX1IF_Pos             (25)                                              /*!< WHC_T::INTSTS: RX1IF Position          */
#define WHC_INTSTS_RX1IF_Msk             (0x1ul << WHC_INTSTS_RX1IF_Pos)                   /*!< WHC_T::INTSTS: RX1IF Mask              */

#define WHC_INTSTS_RX2IF_Pos             (26)                                              /*!< WHC_T::INTSTS: RX2IF Position          */
#define WHC_INTSTS_RX2IF_Msk             (0x1ul << WHC_INTSTS_RX2IF_Pos)                   /*!< WHC_T::INTSTS: RX2IF Mask              */

#define WHC_INTSTS_RX3IF_Pos             (27)                                              /*!< WHC_T::INTSTS: RX3IF Position          */
#define WHC_INTSTS_RX3IF_Msk             (0x1ul << WHC_INTSTS_RX3IF_Pos)                   /*!< WHC_T::INTSTS: RX3IF Mask              */

#define WHC_CPSTS_WDTRF_Pos              (2)                                               /*!< WHC_T::CPSTS: WDTRF Position           */
#define WHC_CPSTS_WDTRF_Msk              (0x1ul << WHC_CPSTS_WDTRF_Pos)                    /*!< WHC_T::CPSTS: WDTRF Mask               */

#define WHC_CPSTS_SYSRF_Pos              (5)                                               /*!< WHC_T::CPSTS: SYSRF Position           */
#define WHC_CPSTS_SYSRF_Msk              (0x1ul << WHC_CPSTS_SYSRF_Pos)                    /*!< WHC_T::CPSTS: SYSRF Mask               */

#define WHC_CPSTS_CPURF_Pos              (7)                                               /*!< WHC_T::CPSTS: CPURF Position           */
#define WHC_CPSTS_CPURF_Msk              (0x1ul << WHC_CPSTS_CPURF_Pos)                    /*!< WHC_T::CPSTS: CPURF Mask               */

#define WHC_CPSTS_CPULKRF_Pos            (8)                                               /*!< WHC_T::CPSTS: CPULKRF Position         */
#define WHC_CPSTS_CPULKRF_Msk            (0x1ul << WHC_CPSTS_CPULKRF_Pos)                  /*!< WHC_T::CPSTS: CPULKRF Mask             */

#define WHC_CPSTS_OPMODE0_Pos            (24)                                              /*!< WHC_T::CPSTS: OPMODE0 Position         */
#define WHC_CPSTS_OPMODE0_Msk            (0xful << WHC_CPSTS_OPMODE0_Pos)                  /*!< WHC_T::CPSTS: OPMODE0 Mask             */

#define WHC_CPSTS_OPMODE1_Pos            (28)                                              /*!< WHC_T::CPSTS: OPMODE1 Position         */
#define WHC_CPSTS_OPMODE1_Msk            (0xful << WHC_CPSTS_OPMODE1_Pos)                  /*!< WHC_T::CPSTS: OPMODE1 Mask             */

#define WHC_GINTTRG_TRGGI0_Pos           (0)                                               /*!< WHC_T::GINTTRG: TRGGI0 Position        */
#define WHC_GINTTRG_TRGGI0_Msk           (0x1ul << WHC_GINTTRG_TRGGI0_Pos)                 /*!< WHC_T::GINTTRG: TRGGI0 Mask            */

#define WHC_GINTTRG_TRGGI1_Pos           (1)                                               /*!< WHC_T::GINTTRG: TRGGI1 Position        */
#define WHC_GINTTRG_TRGGI1_Msk           (0x1ul << WHC_GINTTRG_TRGGI1_Pos)                 /*!< WHC_T::GINTTRG: TRGGI1 Mask            */

#define WHC_GINTTRG_TRGGI2_Pos           (2)                                               /*!< WHC_T::GINTTRG: TRGGI2 Position        */
#define WHC_GINTTRG_TRGGI2_Msk           (0x1ul << WHC_GINTTRG_TRGGI2_Pos)                 /*!< WHC_T::GINTTRG: TRGGI2 Mask            */

#define WHC_GINTTRG_TRGGI3_Pos           (3)                                               /*!< WHC_T::GINTTRG: TRGGI3 Position        */
#define WHC_GINTTRG_TRGGI3_Msk           (0x1ul << WHC_GINTTRG_TRGGI3_Pos)                 /*!< WHC_T::GINTTRG: TRGGI3 Mask            */

#define WHC_TXCTL_CH0SND_Pos             (0)                                               /*!< WHC_T::TXCTL: CH0SND Position          */
#define WHC_TXCTL_CH0SND_Msk             (0x1ul << WHC_TXCTL_CH0SND_Pos)                   /*!< WHC_T::TXCTL: CH0SND Mask              */

#define WHC_TXCTL_CH1SND_Pos             (1)                                               /*!< WHC_T::TXCTL: CH1SND Position          */
#define WHC_TXCTL_CH1SND_Msk             (0x1ul << WHC_TXCTL_CH1SND_Pos)                   /*!< WHC_T::TXCTL: CH1SND Mask              */

#define WHC_TXCTL_CH2SND_Pos             (2)                                               /*!< WHC_T::TXCTL: CH2SND Position          */
#define WHC_TXCTL_CH2SND_Msk             (0x1ul << WHC_TXCTL_CH2SND_Pos)                   /*!< WHC_T::TXCTL: CH2SND Mask              */

#define WHC_TXCTL_CH3SND_Pos             (3)                                               /*!< WHC_T::TXCTL: CH3SND Position          */
#define WHC_TXCTL_CH3SND_Msk             (0x1ul << WHC_TXCTL_CH3SND_Pos)                   /*!< WHC_T::TXCTL: CH3SND Mask              */

#define WHC_TXCTL_CH0RC_Pos              (16)                                              /*!< WHC_T::TXCTL: CH0RC Position           */
#define WHC_TXCTL_CH0RC_Msk              (0x1ul << WHC_TXCTL_CH0RC_Pos)                    /*!< WHC_T::TXCTL: CH0RC Mask               */

#define WHC_TXCTL_CH1RC_Pos              (17)                                              /*!< WHC_T::TXCTL: CH1RC Position           */
#define WHC_TXCTL_CH1RC_Msk              (0x1ul << WHC_TXCTL_CH1RC_Pos)                    /*!< WHC_T::TXCTL: CH1RC Mask               */

#define WHC_TXCTL_CH2RC_Pos              (18)                                              /*!< WHC_T::TXCTL: CH2RC Position           */
#define WHC_TXCTL_CH2RC_Msk              (0x1ul << WHC_TXCTL_CH2RC_Pos)                    /*!< WHC_T::TXCTL: CH2RC Mask               */

#define WHC_TXCTL_CH3RC_Pos              (19)                                              /*!< WHC_T::TXCTL: CH3RC Position           */
#define WHC_TXCTL_CH3RC_Msk              (0x1ul << WHC_TXCTL_CH3RC_Pos)                    /*!< WHC_T::TXCTL: CH3RC Mask               */

#define WHC_TXSTS_CH0RDY_Pos             (0)                                               /*!< WHC_T::TXSTS: CH0RDY Position          */
#define WHC_TXSTS_CH0RDY_Msk             (0x1ul << WHC_TXSTS_CH0RDY_Pos)                   /*!< WHC_T::TXSTS: CH0RDY Mask              */

#define WHC_TXSTS_CH1RDY_Pos             (1)                                               /*!< WHC_T::TXSTS: CH1RDY Position          */
#define WHC_TXSTS_CH1RDY_Msk             (0x1ul << WHC_TXSTS_CH1RDY_Pos)                   /*!< WHC_T::TXSTS: CH1RDY Mask              */

#define WHC_TXSTS_CH2RDY_Pos             (2)                                               /*!< WHC_T::TXSTS: CH2RDY Position          */
#define WHC_TXSTS_CH2RDY_Msk             (0x1ul << WHC_TXSTS_CH2RDY_Pos)                   /*!< WHC_T::TXSTS: CH2RDY Mask              */

#define WHC_TXSTS_CH3RDY_Pos             (3)                                               /*!< WHC_T::TXSTS: CH3RDY Position          */
#define WHC_TXSTS_CH3RDY_Msk             (0x1ul << WHC_TXSTS_CH3RDY_Pos)                   /*!< WHC_T::TXSTS: CH3RDY Mask              */

#define WHC_RXCTL_CH0ACK_Pos             (0)                                               /*!< WHC_T::RXCTL: CH0ACK Position          */
#define WHC_RXCTL_CH0ACK_Msk             (0x1ul << WHC_RXCTL_CH0ACK_Pos)                   /*!< WHC_T::RXCTL: CH0ACK Mask              */

#define WHC_RXCTL_CH1ACK_Pos             (1)                                               /*!< WHC_T::RXCTL: CH1ACK Position          */
#define WHC_RXCTL_CH1ACK_Msk             (0x1ul << WHC_RXCTL_CH1ACK_Pos)                   /*!< WHC_T::RXCTL: CH1ACK Mask              */

#define WHC_RXCTL_CH2ACK_Pos             (2)                                               /*!< WHC_T::RXCTL: CH2ACK Position          */
#define WHC_RXCTL_CH2ACK_Msk             (0x1ul << WHC_RXCTL_CH2ACK_Pos)                   /*!< WHC_T::RXCTL: CH2ACK Mask              */

#define WHC_RXCTL_CH3ACK_Pos             (3)                                               /*!< WHC_T::RXCTL: CH3ACK Position          */
#define WHC_RXCTL_CH3ACK_Msk             (0x1ul << WHC_RXCTL_CH3ACK_Pos)                   /*!< WHC_T::RXCTL: CH3ACK Mask              */

#define WHC_RXSTS_CH0RDY_Pos             (0)                                               /*!< WHC_T::RXSTS: CH0RDY Position          */
#define WHC_RXSTS_CH0RDY_Msk             (0x1ul << WHC_RXSTS_CH0RDY_Pos)                   /*!< WHC_T::RXSTS: CH0RDY Mask              */

#define WHC_RXSTS_CH1RDY_Pos             (1)                                               /*!< WHC_T::RXSTS: CH1RDY Position          */
#define WHC_RXSTS_CH1RDY_Msk             (0x1ul << WHC_RXSTS_CH1RDY_Pos)                   /*!< WHC_T::RXSTS: CH1RDY Mask              */

#define WHC_RXSTS_CH2RDY_Pos             (2)                                               /*!< WHC_T::RXSTS: CH2RDY Position          */
#define WHC_RXSTS_CH2RDY_Msk             (0x1ul << WHC_RXSTS_CH2RDY_Pos)                   /*!< WHC_T::RXSTS: CH2RDY Mask              */

#define WHC_RXSTS_CH3RDY_Pos             (3)                                               /*!< WHC_T::RXSTS: CH3RDY Position          */
#define WHC_RXSTS_CH3RDY_Msk             (0x1ul << WHC_RXSTS_CH3RDY_Pos)                   /*!< WHC_T::RXSTS: CH3RDY Mask              */

#define WHC_TMDAT_DAT_Pos                (0)                                               /*!< WHC_T::TMDAT: DATA Position            */
#define WHC_TMDAT_DAT_Msk                (0xfffffffful << WHC_TMDAT_DAT_Pos)               /*!< WHC_T::TMDAT: DATA Mask                */

#define WHC_RMDAT_DAT_Pos                (0)                                               /*!< WHC_T::RMDAT: DATA Position            */
#define WHC_RMDAT_DAT_Msk                (0xfffffffful << WHC_RMDAT_DAT_Pos)               /*!< WHC_T::RMDAT: DATA Mask                */

/**@}*/ /* WHC_CONST */
/**@}*/ /* end of WHC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __WHC_REG_H__ */
