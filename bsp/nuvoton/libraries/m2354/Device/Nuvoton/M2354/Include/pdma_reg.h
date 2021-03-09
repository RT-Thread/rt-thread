/**************************************************************************//**
 * @file     pdma_reg.h
 * @version  V1.00
 * @brief    PDMA register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PDMA_REG_H__
#define __PDMA_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- Peripheral Direct Memory Access Controller -------------------------*/
/**
    @addtogroup PDMA Peripheral Direct Memory Access Controller(PDMA)
    Memory Mapped Structure for PDMA Controller
  @{
*/



typedef struct
{
    /**
     * @var DSCT_T::CTL
     * Offset: 0x00/0x10/0x20/0x30/0x40/0x50/0x60/0x70  Descriptor Table Control Register of PDMA Channel 0~7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |OPMODE    |PDMA Operation Mode Selection
     * |        |          |00 = Idle state: Channel is stopped or this table is complete, when PDMA finish channel table task, OPMODE will be cleared to idle state automatically.
     * |        |          |01 = Basic mode: The descriptor table only has one task
     * |        |          |When this task is finished, the TDIF(PDMA_INTSTS[1]) will be asserted.
     * |        |          |10 = Scatter-Gather mode: When operating in this mode, user must give the first descriptor table address in PDMA_DSCT_FIRST register; PDMA controller will ignore this task, then load the next task to execute.
     * |        |          |11 = Reserved.
     * |        |          |Note: Before filling transfer task in the Descriptor Table, user must check if the descriptor table is complete.
     * |[2]     |TXTYPE    |Transfer Type
     * |        |          |0 = Burst transfer type.
     * |        |          |1 = Single transfer type.
     * |[6:4]   |BURSIZE   |Burst Size
     * |        |          |This field is used for peripheral to determine the burst size or used for determine the re-arbitration size.
     * |        |          |000 = 128 Transfers.
     * |        |          |001 = 64 Transfers.
     * |        |          |010 = 32 Transfers.
     * |        |          |011 = 16 Transfers.
     * |        |          |100 = 8 Transfers.
     * |        |          |101 = 4 Transfers.
     * |        |          |110 = 2 Transfers.
     * |        |          |111 = 1 Transfers.
     * |        |          |Note: This field is only useful in burst transfer type.
     * |[7]     |TBINTDIS  |Table Interrupt Disable Bit
     * |        |          |This field can be used to decide whether to enable table interrupt or not
     * |        |          |If the TBINTDIS bit is enabled when PDMA controller finishes transfer task, it will not generates transfer done interrupt.
     * |        |          |0 = Table interrupt Enabled.
     * |        |          |1 = Table interrupt Disabled.
     * |        |          |Note: If this bit set to 1, the TEMPTYF will not be set.
     * |[9:8]   |SAINC     |Source Address Increment
     * |        |          |This field is used to set the source address increment size.
     * |        |          |11 = No increment (fixed address).
     * |        |          |Others = Increment and size is depended on TXWIDTH selection.
     * |[11:10] |DAINC     |Destination Address Increment
     * |        |          |This field is used to set the destination address increment size.
     * |        |          |11 = No increment (fixed address).
     * |        |          |Others = Increment and size is depended on TXWIDTH selection.
     * |[13:12] |TXWIDTH   |Transfer Width Selection
     * |        |          |This field is used for transfer width.
     * |        |          |00 = One byte (8 bit) is transferred for every operation.
     * |        |          |01 = One half-word (16 bit) is transferred for every operation.
     * |        |          |10 = One word (32-bit) is transferred for every operation.
     * |        |          |11 = Reserved.
     * |        |          |Note: The PDMA transfer source address (PDMA_DSCT_SA) and PDMA transfer destination address (PDMA_DSCT_DA) should be alignment under the TXWIDTH selection
     * |        |          |For example, if source address is 0x2000_0202, but TXWIDTH is word transfer, the source address is not word alignment
     * |        |          |The source address is aligned when TXWIDTH is byte or half-word transfer.
     * |[14]    |TXACK     |Transfer Acknowledge Selection
     * |        |          |0 = transfer ack when transfer done.
     * |        |          |1 = transfer ack when PDMA get transfer data.
     * |[15]    |STRIDEEN |Stride Mode Enable Bit
     * |        |          |0 = Stride transfer mode Disabled.
     * |        |          |1 = Stride transfer mode Enabled.
     * |[31:16] |TXCNT     |Transfer Count
     * |        |          |The TXCNT represents the required number of PDMA transfer, the real transfer count is (TXCNT + 1); The maximum transfer count is 65536, every transfer may be byte, half-word or word that is dependent on TXWIDTH field.
     * |        |          |Note: When PDMA finish each transfer data, this field will be decrease immediately.
     * @var DSCT_T::SA
     * Offset: 0x04/0x14/0x24/0x34/0x44/0x54/0x64/0x74  Source Address Register of PDMA Channel 0~7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SA        |PDMA Transfer Source Address Register
     * |        |          |This field indicates a 32-bit source address of PDMA controller.
     * |        |          |Note: The PDMA transfer source address should be aligned with the TXWIDTH(PDMA_DSCTn_CTL[13:12], n=0,1..7) selection.
     * @var DSCT_T::DA
     * Offset: 0x08/0x18/0x28/0x38/0x48/0x58/0x68/0x78  Destination Address Register of PDMA Channel 0~7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DA        |PDMA Transfer Destination Address Register
     * |        |          |This field indicates a 32-bit destination address of PDMA controller.
     * |        |          |Note: The PDMA transfer destination address should be aligned with the TXWIDTH(PDMA_DSCTn_CTL[13:12], n=0,1..7) selection.
     * @var DSCT_T::NEXT
     * Offset: 0x0C/0x1C/0x2C/0x3C/0x4C/0x5C/0x6C/0x7C  First Scatter-Gather Descriptor Table Offset of PDMA Channel 0~7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FIRST     |PDMA First Descriptor Table Offset
     * |        |          |This field indicates the offset of the first descriptor table address in system memory.
     * |        |          |Write Operation:
     * |        |          |If the system memory based address is 0x2000_0000 (PDMA_SCATBA), and the first descriptor table is start from 0x2000_0100, then this field must fill in 0x0100.
     * |        |          |Read Operation:
     * |        |          |When operating in scatter-gather mode, the last two bits FIRST[1:0] will become reserved.
     * |        |          |Note1: The first descriptor table address must be word boundary.
     * |        |          |Note2: Before filled transfer task in the descriptor table, user must check if the descriptor table is complete.
     * |[31:16] |NEXT      |PDMA Next Descriptor Table Offset
     * |        |          |This field indicates the offset of next descriptor table address in system memory.
     * |        |          |Note: write operation is useless in this field.
     */

    __IO uint32_t CTL;             /*!< [0x00/0x10/0x20/0x30/0x40/0x50/0x60/0x70] Descriptor Table Control Register of PDMA Channel 0~7              */
    __IO uint32_t SA;              /*!< [0x04/0x14/0x24/0x34/0x44/0x54/0x64/0x74] Source Address Register of PDMA Channel 0~7                        */
    __IO uint32_t DA;              /*!< [0x08/0x18/0x28/0x38/0x48/0x58/0x68/0x78] Destination Address Register of PDMA Channel 0~7                   */
    __IO uint32_t NEXT;            /*!< [0x0C/0x1C/0x2C/0x3C/0x4C/0x5C/0x6C/0x7C]Next Scatter-Gather Descriptor Table Offset                         */

} DSCT_T;

typedef struct
{
    /**
     * @var STRIDE_T::STCR
     * Offset: 0x500/0x508/0x510/0x518/0x520/0x528  Stride Transfer Count Register of PDMA Channel 0~5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |STC       |PDMA Stride Transfer Count
     * |        |          |The 16-bit register defines the stride transfer count of each row.
     * @var STRIDE_T::ASOCR
     * Offset: 0x504/0x50C/0x514/0x51C/0x524/0x52C  Address Stride Offset Register of PDMA Channel 0~5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |SASOL     |VDMA Source Address Stride Offset Length
     * |        |          |The 16-bit register defines the source address stride transfer offset count of each row.
     * |[31:16] |DASOL     |VDMA Destination Address Stride Offset Length
     * |        |          |The 16-bit register defines the destination address stride transfer offset count of each row.
     */
    __IO uint32_t STCR;           /*!< [0x0500/0x508/0x510/0x518/0x520/0x528] Stride Transfer Count Register of PDMA Channel 0~7                 */
    __IO uint32_t ASOCR;          /*!< [0x0504/0x50C/0x514/0x51C/0x524/0x52C] Address Stride Offset Register of PDMA Channel 0                   */
} STRIDE_T;

typedef struct
{
    /**
     * @var REPEAT_T::AICTL
     * Offset: 0x600  Address Interval Control Register of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |SAICNT    |PDMA Source Address Interval Count
     * |        |          |The 16-bit register defines the source address interval count of each row.
     * |[31:16] |DAICNT    |PDMA Destination Address Interval Count
     * |        |          |The 16-bit register defines the destination  address interval count of each row.
     * @var REPEAT_T::RCNT
     * Offset: 0x604  Repeat Count Register of PDMA Channe n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |RCNT      |PDMA Repeat Count
     * |        |          |The 16-bit register defines the repeat times of block transfer.
     */
    __IO uint32_t AICTL;         /*!< [0x0600] Address Interval Control Register of PDMA Channel 0                 */
    __IO uint32_t RCNT;          /*!< [0x0604] Repeat Count Register of PDMA Channel 0                             */
} REPEAT_T;

typedef struct
{


    /**
     * @var PDMA_T::CURSCAT
     * Offset: 0x80/0x84/0x88/0x8C/0x90/0x94/0x98/0x9C  Current Scatter-Gather Descriptor Table Address of PDMA Channel 0~7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURADDR   |PDMA Current Description Address Register (Read Only)
     * |        |          |This field indicates a 32-bit current external description address of PDMA controller.
     * |        |          |Note: This field is read only and only used for Scatter-Gather mode to indicate the current external description address.
     * @var PDMA_T::CHCTL
     * Offset: 0x400  PDMA Channel Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CHENn     |PDMA Channel Enable Bit
     * |        |          |Set this bit to 1 to enable PDMAn operation. Channel cannot be active if it is not set as enabled.
     * |        |          |0 = PDMA channel [n] Disabled.
     * |        |          |1 = PDMA channel [n] Enabled.
     * |        |          |Note: Set corresponding bit of PDMA_PAUSE or PDMA_CHRST register will also clear this bit.
     * @var PDMA_T::PAUSE
     * Offset: 0x404  PDMA Transfer Pause Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PAUSEn    |PDMA Transfer Pause Control Register (Write Only)
     * |        |          |User can set PAUSEn bit field to pause the PDMA transfer
     * |        |          |When user sets PAUSEn bit, the PDMA controller will pause the on-going transfer, then clear the channel enable bit CHEN(PDMA_CHCTL [n], n=0,1..7) and clear request active flag
     * |        |          |If re-enable the paused channel again, the remaining transfers will be processed.
     * |        |          |0 = No effect.
     * |        |          |1 = Pause PDMA channel n transfer.
     * @var PDMA_T::SWREQ
     * Offset: 0x408  PDMA Software Request Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |SWREQn    |PDMA Software Request Register (Write Only)
     * |        |          |Set this bit to 1 to generate a software request to PDMA [n].
     * |        |          |0 = No effect.
     * |        |          |1 = Generate a software request.
     * |        |          |Note1: User can read PDMA_TRGSTS register to know which channel is on active
     * |        |          |Active flag may be triggered by software request or peripheral request.
     * |        |          |Note2: If user does not enable corresponding PDMA channel, the software request will be ignored.
     * @var PDMA_T::TRGSTS
     * Offset: 0x40C  PDMA Channel Request Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |REQSTSn   |PDMA Channel Request Status (Read Only)
     * |        |          |This flag indicates whether channel[n] have a request or not, no matter request from software or peripheral
     * |        |          |When PDMA controller finishes channel transfer, this bit will be cleared automatically.
     * |        |          |0 = PDMA Channel n has no request.
     * |        |          |1 = PDMA Channel n has a request.
     * |        |          |Note: If user pauses or resets each PDMA transfer by setting PDMA_PAUSE or PDMA_CHRST register respectively, this bit will be cleared automatically after finishing current transfer.
     * @var PDMA_T::PRISET
     * Offset: 0x410  PDMA Fixed Priority Setting Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FPRISETn  |PDMA Fixed Priority Setting Register
     * |        |          |Set this bit to 1 to enable fixed priority level.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set PDMA channel [n] to fixed priority channel.
     * |        |          |Read Operation:
     * |        |          |0 = Corresponding PDMA channel is round-robin priority.
     * |        |          |1 = Corresponding PDMA channel is fixed priority.
     * |        |          |Note: This field only set to fixed priority, clear fixed priority use PDMA_PRICLR register.
     * @var PDMA_T::PRICLR
     * Offset: 0x414  PDMA Fixed Priority Clear Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FPRICLRn  |PDMA Fixed Priority Clear Register (Write Only)
     * |        |          |Set this bit to 1 to clear fixed priority level.
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PDMA channel [n] fixed priority setting.
     * |        |          |Note: User can read PDMA_PRISET register to know the channel priority.
     * @var PDMA_T::INTEN
     * Offset: 0x418  PDMA Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |INTENn    |PDMA Interrupt Enable Register
     * |        |          |This field is used for enabling PDMA channel[n] interrupt.
     * |        |          |0 = PDMA channel n interrupt Disabled.
     * |        |          |1 = PDMA channel n interrupt Enabled.
     * @var PDMA_T::INTSTS
     * Offset: 0x41C  PDMA Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ABTIF     |PDMA Read/Write Target Abort Interrupt Flag (Read Only)
     * |        |          |This bit indicates that PDMA has target abort error; Software can read PDMA_ABTSTS register to find which channel has target abort error.
     * |        |          |0 = No AHB bus ERROR response received.
     * |        |          |1 = AHB bus ERROR response received.
     * |[1]     |TDIF      |Transfer Done Interrupt Flag (Read Only)
     * |        |          |This bit indicates that PDMA controller has finished transmission; User can read PDMA_TDSTS register to indicate which channel finished transfer.
     * |        |          |0 = Not finished yet.
     * |        |          |1 = PDMA channel has finished transmission.
     * |[2]     |ALIGNF    |Transfer Alignment Interrupt Flag (Read Only)
     * |        |          |0 = PDMA channel source address and destination address both follow transfer width setting.
     * |        |          |1 = PDMA channel source address or destination address is not follow transfer width setting.
     * |[8]     |REQTOF0   |Request Time-out Flag for Channel 0
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by PDMA_TOC0, user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[9]     |REQTOF1   |Request Time-out Flag for Channel 1
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by PDMA_TOC1, user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * @var PDMA_T::ABTSTS
     * Offset: 0x420  PDMA Channel Read/Write Target Abort Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |ABTIFn    |PDMA Read/Write Target Abort Interrupt Status Flag
     * |        |          |This bit indicates which PDMA controller has target abort error; User can write 1 to clear these bits.
     * |        |          |0 = No AHB bus ERROR response received when channel n transfer.
     * |        |          |1 = AHB bus ERROR response received when channel n transfer.
     * @var PDMA_T::TDSTS
     * Offset: 0x424  PDMA Channel Transfer Done Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TDIFn     |Transfer Done Flag Register
     * |        |          |This bit indicates whether PDMA controller channel transfer has been finished or not, user can write 1 to clear these bits.
     * |        |          |0 = PDMA channel transfer has not finished.
     * |        |          |1 = PDMA channel has finished transmission.
     * @var PDMA_T::ALIGN
     * Offset: 0x428  PDMA Transfer Alignment Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |ALIGNn    |Transfer Alignment Flag Register
     * |        |          |0 = PDMA channel source address and destination address both follow transfer width setting.
     * |        |          |1 = PDMA channel source address or destination address is not follow transfer width setting.
     * @var PDMA_T::TACTSTS
     * Offset: 0x42C  PDMA Transfer Active Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TXACTFn   |Transfer on Active Flag Register (Read Only)
     * |        |          |This bit indicates which PDMA channel is in active.
     * |        |          |0 = PDMA channel is not finished.
     * |        |          |1 = PDMA channel is active.
     * @var PDMA_T::TOUTPSC
     * Offset: 0x430  PDMA Time-out Prescaler Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TOUTPSC0  |PDMA Channel 0 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 0 time-out clock source is HCLK/2^8.
     * |        |          |001 = PDMA channel 0 time-out clock source is HCLK/2^9.
     * |        |          |010 = PDMA channel 0 time-out clock source is HCLK/2^10.
     * |        |          |011 = PDMA channel 0 time-out clock source is HCLK/2^11.
     * |        |          |100 = PDMA channel 0 time-out clock source is HCLK/2^12.
     * |        |          |101 = PDMA channel 0 time-out clock source is HCLK/2^13.
     * |        |          |110 = PDMA channel 0 time-out clock source is HCLK/2^14.
     * |        |          |111 = PDMA channel 0 time-out clock source is HCLK/2^15.
     * |[6:4]   |TOUTPSC1  |PDMA Channel 1 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 1 time-out clock source is HCLK/2^8.
     * |        |          |001 = PDMA channel 1 time-out clock source is HCLK/2^9.
     * |        |          |010 = PDMA channel 1 time-out clock source is HCLK/2^10.
     * |        |          |011 = PDMA channel 1 time-out clock source is HCLK/2^11.
     * |        |          |100 = PDMA channel 1 time-out clock source is HCLK/2^12.
     * |        |          |101 = PDMA channel 1 time-out clock source is HCLK/2^13.
     * |        |          |110 = PDMA channel 1 time-out clock source is HCLK/2^14.
     * |        |          |111 = PDMA channel 1 time-out clock source is HCLK/2^15.
     * @var PDMA_T::TOUTEN
     * Offset: 0x434  PDMA Time-out Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TOUTEN0   |PDMA Channel 0 Time-out Enable Bit
     * |        |          |0 = PDMA Channel 0 time-out function Disable.
     * |        |          |1 = PDMA Channel 0 time-out function Enable.
     * |[1]     |TOUTEN1   |PDMA Channel 1 Time-out Enable Bit
     * |        |          |0 = PDMA Channel 1 time-out function Disable.
     * |        |          |1 = PDMA Channel 1 time-out function Enable.
     * @var PDMA_T::TOUTIEN
     * Offset: 0x438  PDMA Time-out Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TOUTIEN0  |PDMA Channel 0 Time-out Interrupt Enable Bit
     * |        |          |0 = PDMA Channel 0 time-out interrupt Disable.
     * |        |          |1 = PDMA Channel 0 time-out interrupt Enable.
     * |[1]     |TOUTIEN1  |PDMA Channel 1 Time-out Interrupt Enable Bit
     * |        |          |0 = PDMA Channel 1 time-out interrupt Disable.
     * |        |          |1 = PDMA Channel 1 time-out interrupt Enable.
     * @var PDMA_T::SCATBA
     * Offset: 0x43C  PDMA Scatter-Gather Descriptor Table Base Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:16] |SCATBA    |PDMA Scatter-gather Descriptor Table Address Register
     * |        |          |In Scatter-Gather mode, this is the base address for calculating the next link - list address
     * |        |          |The next link address equation is
     * |        |          |Next Link Address = PDMA_SCATBA + PDMA_DSCT_NEXT.
     * |        |          |Note: Only useful in Scatter-Gather mode.
     * @var PDMA_T::TOC0_1
     * Offset: 0x440  PDMA Channel 0 and Channel 1 Time-out Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC0      |Time-out Counter for Channel 0
     * |        |          |This controls the period of time-out function for channel 0
     * |        |          |The calculation unit is based on TOUTPSC0 (PDMA_TOUTPSC[2:0]) clock.
     * |        |          |Time-out period = (Period of time-out clock) * (16-bit TOCn),n = 0,1.
     * |[31:16] |TOC1      |Time-out Counter for Channel 1
     * |        |          |This controls the period of time-out function for channel 1
     * |        |          |The calculation unit is based on TOUTPSC1 (PDMA_TOUTPSC[5:3]) clock
     * |        |          |The example of time-out period can refer TOC0 bit description.
     * @var PDMA_T::CHRST
     * Offset: 0x460  PDMA Channel Reset Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CHnRST    |Channel N Reset
     * |        |          |0 = corresponding channel n not reset.
     * |        |          |1 = corresponding channel n is reset.
     * @var PDMA_T::REQSEL0_3
     * Offset: 0x480  PDMA Channel 0 to Channel 3 Request Source Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |REQSRC0   |Channel 0 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 0
     * |        |          |User can configure the peripheral by setting REQSRC0.
     * |        |          |0 = Disable PDMA.
     * |        |          |1 = Reserved.
     * |        |          |2 = Channel connects to USB_TX.
     * |        |          |3 = Channel connects to USB_RX.
     * |        |          |4 = Channel connects to UART0_TX.
     * |        |          |5 = Channel connects to UART0_RX.
     * |        |          |6 = Channel connects to UART1_TX.
     * |        |          |7 = Channel connects to UART1_RX.
     * |        |          |8 = Channel connects to UART2_TX.
     * |        |          |9 = Channel connects to UART2_RX.
     * |        |          |10 = Channel connects to UART3_TX.
     * |        |          |11 = Channel connects to UART3_RX.
     * |        |          |12 = Channel connects to UART4_TX.
     * |        |          |13 = Channel connects to UART4_RX.
     * |        |          |14 = Channel connects to UART5_TX.
     * |        |          |15 = Channel connects to UART5_RX.
     * |        |          |16 = Channel connects to USCI0_TX.
     * |        |          |17 = Channel connects to USCI0_RX.
     * |        |          |18 = Channel connects to USCI1_TX.
     * |        |          |19 = Channel connects to USCI1_RX.
     * |        |          |20 = Channel connects to QSPI0_TX.
     * |        |          |21 = Channel connects to QSPI0_RX.
     * |        |          |22 = Channel connects to SPI0_TX.
     * |        |          |23 = Channel connects to SPI0_RX.
     * |        |          |24 = Channel connects to SPI1_TX.
     * |        |          |25 = Channel connects to SPI1_RX.
     * |        |          |26 = Channel connects to SPI2_TX.
     * |        |          |27 = Channel connects to SPI2_RX.
     * |        |          |28 = Channel connects to SPI3_TX.
     * |        |          |29 = Channel connects to SPI3_RX.
     * |        |          |30 = Channel connects to ADC_RX.
     * |        |          |32 = Channel connects to EPWM0_P1_RX.
     * |        |          |33 = Channel connects to EPWM0_P2_RX.
     * |        |          |34 = Channel connects to EPWM0_P3_RX.
     * |        |          |35 = Channel connects to EPWM1_P1_RX.
     * |        |          |36 = Channel connects to EPWM1_P2_RX.
     * |        |          |37 = Channel connects to EPWM1_P3_RX.
     * |        |          |38 = Channel connects to I2C0_TX.
     * |        |          |39 = Channel connects to I2C0_RX.
     * |        |          |40 = Channel connects to I2C1_TX.
     * |        |          |41 = Channel connects to I2C1_RX.
     * |        |          |42 = Channel connects to I2C2_TX.
     * |        |          |43 = Channel connects to I2C2_RX.
     * |        |          |44 = Channel connects to I2S0_TX.
     * |        |          |45 = Channel connects to I2S0_RX.
     * |        |          |46 = Channel connects to TMR0.
     * |        |          |47 = Channel connects to TMR1.
     * |        |          |48 = Channel connects to TMR2.
     * |        |          |49 = Channel connects to TMR3.
     * |        |          |50 = Channel connects to TMR4.
     * |        |          |51 = Channel connects to TMR5.
     * |        |          |52 = Channel connects to DAC0_TX.
     * |        |          |53 = Channel connects to DAC1_TX.
     * |        |          |54 = Channel connects to EPWM0_CH0_TX.
     * |        |          |55 = Channel connects to EPWM0_CH1_TX.
     * |        |          |56 = Channel connects to EPWM0_CH2_TX.
     * |        |          |57 = Channel connects to EPWM0_CH3_TX.
     * |        |          |58 = Channel connects to EPWM0_CH4_TX.
     * |        |          |59 = Channel connects to EPWM0_CH5_TX.
     * |        |          |60 = Channel connects to EPWM1_CH0_TX.
     * |        |          |61 = Channel connects to EPWM1_CH1_TX.
     * |        |          |62 = Channel connects to EPWM1_CH2_TX.
     * |        |          |63 = Channel connects to EPWM1_CH3_TX.
     * |        |          |64 = Channel connects to EPWM1_CH4_TX.
     * |        |          |65 = Channel connects to EPWM1_CH5_TX.
     * |        |          |Others = Reserved.
     * |        |          |Note 1: A request source cannot assign to two channels at the same time.
     * |        |          |Note 2: This field is useless when transfer between memory and memory.
     * |[14:8]  |REQSRC1   |Channel 1 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 1
     * |        |          |User can configure the peripheral setting by REQSRC1.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[22:16] |REQSRC2   |Channel 2 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 2
     * |        |          |User can configure the peripheral setting by REQSRC2.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[30:24] |REQSRC3   |Channel 3 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 3
     * |        |          |User can configure the peripheral setting by REQSRC3.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * @var PDMA_T::REQSEL4_7
     * Offset: 0x484  PDMA Request Source Select Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |REQSRC4   |Channel 4 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 4
     * |        |          |User can configure the peripheral setting by REQSRC4.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[14:8]  |REQSRC5   |Channel 5 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 5
     * |        |          |User can configure the peripheral setting by REQSRC5.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[22:16] |REQSRC6   |Channel 6 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 6
     * |        |          |User can configure the peripheral setting by REQSRC6.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[30:24] |REQSRC7   |Channel 7 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 7
     * |        |          |User can configure the peripheral setting by REQSRC7.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     */

    DSCT_T        DSCT[8];               /*!< [0x0000 ~ 0x007C] DMA Embedded Description Table 0~7                      */
    __I  uint32_t CURSCAT[8];            /*!< [0x0080~0x009C] Current Scatter-Gather Descriptor Table Address of PDMA Channel 0~7 */
    __I  uint32_t RESERVE0[216];
    __IO uint32_t CHCTL;                 /*!< [0x0400] PDMA Channel Control Register                                    */
    __O  uint32_t PAUSE;                 /*!< [0x0404] PDMA Transfer Pause Control Register                             */
    __O  uint32_t SWREQ;                 /*!< [0x0408] PDMA Software Request Register                                   */
    __I  uint32_t TRGSTS;                /*!< [0x040c] PDMA Channel Request Status Register                             */
    __IO uint32_t PRISET;                /*!< [0x0410] PDMA Fixed Priority Setting Register                             */
    __O  uint32_t PRICLR;                /*!< [0x0414] PDMA Fixed Priority Clear Register                               */
    __IO uint32_t INTEN;                 /*!< [0x0418] PDMA Interrupt Enable Register                                   */
    __IO uint32_t INTSTS;                /*!< [0x041c] PDMA Interrupt Status Register                                   */
    __IO uint32_t ABTSTS;                /*!< [0x0420] PDMA Channel Read/Write Target Abort Flag Register               */
    __IO uint32_t TDSTS;                 /*!< [0x0424] PDMA Channel Transfer Done Flag Register                         */
    __IO uint32_t ALIGN;                 /*!< [0x0428] PDMA Transfer Alignment Status Register                          */
    __I  uint32_t TACTSTS;               /*!< [0x042c] PDMA Transfer Active Flag Register                               */
    __IO uint32_t TOUTPSC;               /*!< [0x0430] PDMA Time-out Prescaler Register                                 */
    __IO uint32_t TOUTEN;                /*!< [0x0434] PDMA Time-out Enable Register                                    */
    __IO uint32_t TOUTIEN;               /*!< [0x0438] PDMA Time-out Interrupt Enable Register                          */
    __IO uint32_t SCATBA;                /*!< [0x043c] PDMA Scatter-Gather Descriptor Table Base Address Register       */
    __IO uint32_t TOC0_1;                /*!< [0x0440] PDMA Channel 0 and Channel 1 Time-out Counter Register           */
    __I  uint32_t RESERVE1[7];
    __IO uint32_t CHRST;                 /*!< [0x0460] PDMA Channel Reset Register                                      */
    __I  uint32_t RESERVE2[7];
    __IO uint32_t REQSEL0_3;             /*!< [0x0480] PDMA Channel 0 to Channel 3 Request Source Select Register       */
    __IO uint32_t REQSEL4_7;             /*!< [0x0484] PDMA Channel 4 to Channel 7 Request Source Select Register       */
    __I  uint32_t RESERVE4[30];
    STRIDE_T      STRIDE[6];             /*!< [0x0500 ~ 0x052C] Stride function control register of PDMA Channel 0 ~ 5  */
    __IO uint32_t RESERVE5[52];
    REPEAT_T    REPEAT[2];               /*!< [0x0600 ~ 0x060C] Repeat Count Function Control Register of PDMA Channel 0 ~ 1 */
} PDMA_T;




/**
    @addtogroup PDMA_CONST PDMA Bit Field Definition
    Constant Definitions for PDMA Controller
  @{
*/

#define PDMA_DSCT_CTL_OPMODE_Pos        (0)                                               /*!< PDMA_T::DSCT_CTL: OPMODE Position     */
#define PDMA_DSCT_CTL_OPMODE_Msk        (0x3ul << PDMA_DSCT_CTL_OPMODE_Pos)               /*!< PDMA_T::DSCT_CTL: OPMODE Mask         */

#define PDMA_DSCT_CTL_TXTYPE_Pos        (2)                                               /*!< PDMA_T::DSCT_CTL: TXTYPE Position     */
#define PDMA_DSCT_CTL_TXTYPE_Msk        (0x1ul << PDMA_DSCT_CTL_TXTYPE_Pos)               /*!< PDMA_T::DSCT_CTL: TXTYPE Mask         */

#define PDMA_DSCT_CTL_BURSIZE_Pos       (4)                                               /*!< PDMA_T::DSCT_CTL: BURSIZE Position    */
#define PDMA_DSCT_CTL_BURSIZE_Msk       (0x7ul << PDMA_DSCT_CTL_BURSIZE_Pos)              /*!< PDMA_T::DSCT_CTL: BURSIZE Mask        */

#define PDMA_DSCT_CTL_TBINTDIS_Pos      (7)                                               /*!< PDMA_T::DSCT_CTL: TBINTDIS Position      */
#define PDMA_DSCT_CTL_TBINTDIS_Msk      (0x1ul << PDMA_DSCT_CTL_TBINTDIS_Pos)             /*!< PDMA_T::DSCT_CTL: TBINTDIS Mask          */

#define PDMA_DSCT_CTL_SAINC_Pos         (8)                                               /*!< PDMA_T::DSCT_CTL: SAINC Position      */
#define PDMA_DSCT_CTL_SAINC_Msk         (0x3ul << PDMA_DSCT_CTL_SAINC_Pos)                /*!< PDMA_T::DSCT_CTL: SAINC Mask          */

#define PDMA_DSCT_CTL_DAINC_Pos         (10)                                              /*!< PDMA_T::DSCT_CTL: DAINC Position      */
#define PDMA_DSCT_CTL_DAINC_Msk         (0x3ul << PDMA_DSCT_CTL_DAINC_Pos)                /*!< PDMA_T::DSCT_CTL: DAINC Mask          */

#define PDMA_DSCT_CTL_TXWIDTH_Pos       (12)                                              /*!< PDMA_T::DSCT_CTL: TXWIDTH Position    */
#define PDMA_DSCT_CTL_TXWIDTH_Msk       (0x3ul << PDMA_DSCT_CTL_TXWIDTH_Pos)              /*!< PDMA_T::DSCT_CTL: TXWIDTH Mask        */

#define PDMA_DSCT_CTL_TXACK_Pos         (14)                                              /*!< PDMA_T::DSCT_CTL: TXACK Position      */
#define PDMA_DSCT_CTL_TXACK_Msk         (0x1ul << PDMA_DSCT_CTL_TXACK_Pos)                /*!< PDMA_T::DSCT_CTL: TXACK Mask          */

#define PDMA_DSCT_CTL_STRIDEEN_Pos     (15)                                               /*!< PDMA_T::DSCT_CTL: STRIDEEN Position  */
#define PDMA_DSCT_CTL_STRIDEEN_Msk     (0x1ul << PDMA_DSCT_CTL_STRIDEEN_Pos)              /*!< PDMA_T::DSCT_CTL: STRIDEEN Mask      */

#define PDMA_DSCT_CTL_TXCNT_Pos         (16)                                              /*!< PDMA_T::DSCT_CTL: TXCNT Position      */
#define PDMA_DSCT_CTL_TXCNT_Msk         (0xfffful << PDMA_DSCT_CTL_TXCNT_Pos)             /*!< PDMA_T::DSCT_CTL: TXCNT Mask          */

#define PDMA_DSCT_SA_SA_Pos             (0)                                               /*!< PDMA_T::DSCT_SA: SA Position          */
#define PDMA_DSCT_SA_SA_Msk             (0xfffffffful << PDMA_DSCT_SA_SA_Pos)             /*!< PDMA_T::DSCT_SA: SA Mask              */

#define PDMA_DSCT_DA_DA_Pos             (0)                                               /*!< PDMA_T::DSCT_DA: DA Position          */
#define PDMA_DSCT_DA_DA_Msk             (0xfffffffful << PDMA_DSCT_DA_DA_Pos)             /*!< PDMA_T::DSCT_DA: DA Mask              */

#define PDMA_DSCT_NEXT_NEXT_Pos         (0)                                               /*!< PDMA_T::DSCT_NEXT: NEXT Position      */
#define PDMA_DSCT_NEXT_NEXT_Msk         (0xfffful << PDMA_DSCT_NEXT_NEXT_Pos)             /*!< PDMA_T::DSCT_NEXT: NEXT Mask          */

#define PDMA_DSCT_NEXT_EXENEXT_Pos      (16)                                              /*!< PDMA_T::DSCT_FIRST: NEXT Position     */
#define PDMA_DSCT_NEXT_EXENEXT_Msk      (0xfffful << PDMA_DSCT_NEXT_EXENEXT_Pos)           /*!< PDMA_T::DSCT_FIRST: NEXT Mask         */

#define PDMA_CURSCAT_CURADDR_Pos        (0)                                               /*!< PDMA_T::CURSCAT: CURADDR Position     */
#define PDMA_CURSCAT_CURADDR_Msk        (0xfffffffful << PDMA_CURSCAT_CURADDR_Pos)        /*!< PDMA_T::CURSCAT: CURADDR Mask         */

#define PDMA_CHCTL_CHENn_Pos            (0)                                               /*!< PDMA_T::CHCTL: CHENn Position          */
#define PDMA_CHCTL_CHENn_Msk            (0xfffful << PDMA_CHCTL_CHENn_Pos)                /*!< PDMA_T::CHCTL: CHENn Mask              */

#define PDMA_PAUSE_PAUSEn_Pos           (0)                                               /*!< PDMA_T::PAUSE: PAUSEn Position           */
#define PDMA_PAUSE_PAUSEn_Msk           (0xfffful << PDMA_PAUSE_PAUSEn_Pos)              /*!< PDMA_T::PAUSE: PAUSEn Mask               */

#define PDMA_SWREQ_SWREQn_Pos            (0)                                               /*!< PDMA_T::SWREQ: SWREQn Position         */
#define PDMA_SWREQ_SWREQn_Msk            (0xfffful << PDMA_SWREQ_SWREQn_Pos)               /*!< PDMA_T::SWREQ: SWREQn Mask             */

#define PDMA_TRGSTS_REQSTSn_Pos          (0)                                               /*!< PDMA_T::TRGSTS: REQSTSn Position       */
#define PDMA_TRGSTS_REQSTSn_Msk          (0xfffful << PDMA_TRGSTS_REQSTSn_Pos)             /*!< PDMA_T::TRGSTS: REQSTSn Mask           */

#define PDMA_PRISET_FPRISETn_Pos         (0)                                               /*!< PDMA_T::PRISET: FPRISETn Position      */
#define PDMA_PRISET_FPRISETn_Msk         (0xfffful << PDMA_PRISET_FPRISETn_Pos)            /*!< PDMA_T::PRISET: FPRISETn Mask          */

#define PDMA_PRICLR_FPRICLRn_Pos         (0)                                               /*!< PDMA_T::PRICLR: FPRICLRn Position      */
#define PDMA_PRICLR_FPRICLRn_Msk         (0xfffful << PDMA_PRICLR_FPRICLRn_Pos)            /*!< PDMA_T::PRICLR: FPRICLRn Mask          */

#define PDMA_INTEN_INTENn_Pos            (0)                                               /*!< PDMA_T::INTEN: INTENn Position         */
#define PDMA_INTEN_INTENn_Msk            (0xfffful << PDMA_INTEN_INTENn_Pos)               /*!< PDMA_T::INTEN: INTENn Mask             */

#define PDMA_INTSTS_ABTIF_Pos            (0)                                               /*!< PDMA_T::INTSTS: ABTIF Position         */
#define PDMA_INTSTS_ABTIF_Msk            (0x1ul << PDMA_INTSTS_ABTIF_Pos)                  /*!< PDMA_T::INTSTS: ABTIF Mask             */

#define PDMA_INTSTS_TDIF_Pos             (1)                                               /*!< PDMA_T::INTSTS: TDIF Position          */
#define PDMA_INTSTS_TDIF_Msk             (0x1ul << PDMA_INTSTS_TDIF_Pos)                   /*!< PDMA_T::INTSTS: TDIF Mask              */

#define PDMA_INTSTS_ALIGNF_Pos           (2)                                               /*!< PDMA_T::INTSTS: ALIGNF Position        */
#define PDMA_INTSTS_ALIGNF_Msk           (0x1ul << PDMA_INTSTS_ALIGNF_Pos)                 /*!< PDMA_T::INTSTS: ALIGNF Mask            */

#define PDMA_INTSTS_REQTOF0_Pos          (8)                                               /*!< PDMA_T::INTSTS: REQTOF0 Position       */
#define PDMA_INTSTS_REQTOF0_Msk          (0x1ul << PDMA_INTSTS_REQTOF0_Pos)                /*!< PDMA_T::INTSTS: REQTOF0 Mask           */

#define PDMA_INTSTS_REQTOF1_Pos          (9)                                               /*!< PDMA_T::INTSTS: REQTOF1 Position       */
#define PDMA_INTSTS_REQTOF1_Msk          (0x1ul << PDMA_INTSTS_REQTOF1_Pos)                /*!< PDMA_T::INTSTS: REQTOF1 Mask           */

#define PDMA_ABTSTS_ABTIF0_Pos           (0)                                               /*!< PDMA_T::ABTSTS: ABTIF0 Position        */
#define PDMA_ABTSTS_ABTIF0_Msk           (0x1ul << PDMA_ABTSTS_ABTIF0_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF0 Mask            */

#define PDMA_ABTSTS_ABTIF1_Pos           (1)                                               /*!< PDMA_T::ABTSTS: ABTIF1 Position        */
#define PDMA_ABTSTS_ABTIF1_Msk           (0x1ul << PDMA_ABTSTS_ABTIF1_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF1 Mask            */

#define PDMA_ABTSTS_ABTIF2_Pos           (2)                                               /*!< PDMA_T::ABTSTS: ABTIF2 Position        */
#define PDMA_ABTSTS_ABTIF2_Msk           (0x1ul << PDMA_ABTSTS_ABTIF2_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF2 Mask            */

#define PDMA_ABTSTS_ABTIF3_Pos           (3)                                               /*!< PDMA_T::ABTSTS: ABTIF3 Position        */
#define PDMA_ABTSTS_ABTIF3_Msk           (0x1ul << PDMA_ABTSTS_ABTIF3_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF3 Mask            */

#define PDMA_ABTSTS_ABTIF4_Pos           (4)                                               /*!< PDMA_T::ABTSTS: ABTIF4 Position        */
#define PDMA_ABTSTS_ABTIF4_Msk           (0x1ul << PDMA_ABTSTS_ABTIF4_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF4 Mask            */

#define PDMA_ABTSTS_ABTIF5_Pos           (5)                                               /*!< PDMA_T::ABTSTS: ABTIF5 Position        */
#define PDMA_ABTSTS_ABTIF5_Msk           (0x1ul << PDMA_ABTSTS_ABTIF5_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF5 Mask            */

#define PDMA_ABTSTS_ABTIF6_Pos           (6)                                               /*!< PDMA_T::ABTSTS: ABTIF6 Position        */
#define PDMA_ABTSTS_ABTIF6_Msk           (0x1ul << PDMA_ABTSTS_ABTIF6_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF6 Mask            */

#define PDMA_ABTSTS_ABTIF7_Pos           (7)                                               /*!< PDMA_T::ABTSTS: ABTIF7 Position        */
#define PDMA_ABTSTS_ABTIF7_Msk           (0x1ul << PDMA_ABTSTS_ABTIF7_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF7 Mask            */

#define PDMA_ABTSTS_ABTIF8_Pos           (8)                                               /*!< PDMA_T::ABTSTS: ABTIF8 Position        */
#define PDMA_ABTSTS_ABTIF8_Msk           (0x1ul << PDMA_ABTSTS_ABTIF8_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF8 Mask            */

#define PDMA_ABTSTS_ABTIF9_Pos           (9)                                               /*!< PDMA_T::ABTSTS: ABTIF9 Position        */
#define PDMA_ABTSTS_ABTIF9_Msk           (0x1ul << PDMA_ABTSTS_ABTIF9_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF9 Mask            */

#define PDMA_ABTSTS_ABTIF10_Pos           (10)                                               /*!< PDMA_T::ABTSTS: ABTIF10 Position        */
#define PDMA_ABTSTS_ABTIF10_Msk           (0x1ul << PDMA_ABTSTS_ABTIF10_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF10 Mask            */

#define PDMA_ABTSTS_ABTIF11_Pos           (11)                                               /*!< PDMA_T::ABTSTS: ABTIF11 Position        */
#define PDMA_ABTSTS_ABTIF11_Msk           (0x1ul << PDMA_ABTSTS_ABTIF11_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF11 Mask            */

#define PDMA_ABTSTS_ABTIF12_Pos           (12)                                               /*!< PDMA_T::ABTSTS: ABTIF12 Position        */
#define PDMA_ABTSTS_ABTIF12_Msk           (0x1ul << PDMA_ABTSTS_ABTIF12_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF12 Mask            */

#define PDMA_ABTSTS_ABTIF13_Pos           (13)                                               /*!< PDMA_T::ABTSTS: ABTIF13 Position        */
#define PDMA_ABTSTS_ABTIF13_Msk           (0x1ul << PDMA_ABTSTS_ABTIF13_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF13 Mask            */

#define PDMA_ABTSTS_ABTIF14_Pos           (14)                                               /*!< PDMA_T::ABTSTS: ABTIF14 Position        */
#define PDMA_ABTSTS_ABTIF14_Msk           (0x1ul << PDMA_ABTSTS_ABTIF14_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF14 Mask            */

#define PDMA_ABTSTS_ABTIF15_Pos           (15)                                               /*!< PDMA_T::ABTSTS: ABTIF15 Position        */
#define PDMA_ABTSTS_ABTIF15_Msk           (0x1ul << PDMA_ABTSTS_ABTIF15_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF15 Mask            */

#define PDMA_TDSTS_TDIF0_Pos           (0)                                               /*!< PDMA_T::TDSTS: TDIF0 Position        */
#define PDMA_TDSTS_TDIF0_Msk           (0x1ul << PDMA_TDSTS_TDIF0_Pos)                   /*!< PDMA_T::TDSTS: TDIF0 Mask            */

#define PDMA_TDSTS_TDIF1_Pos           (1)                                               /*!< PDMA_T::TDSTS: TDIF1 Position        */
#define PDMA_TDSTS_TDIF1_Msk           (0x1ul << PDMA_TDSTS_TDIF1_Pos)                   /*!< PDMA_T::TDSTS: TDIF1 Mask            */

#define PDMA_TDSTS_TDIF2_Pos           (2)                                               /*!< PDMA_T::TDSTS: TDIF2 Position        */
#define PDMA_TDSTS_TDIF2_Msk           (0x1ul << PDMA_TDSTS_TDIF2_Pos)                   /*!< PDMA_T::TDSTS: TDIF2 Mask            */

#define PDMA_TDSTS_TDIF3_Pos           (3)                                               /*!< PDMA_T::TDSTS: TDIF3 Position        */
#define PDMA_TDSTS_TDIF3_Msk           (0x1ul << PDMA_TDSTS_TDIF3_Pos)                   /*!< PDMA_T::TDSTS: TDIF3 Mask            */

#define PDMA_TDSTS_TDIF4_Pos           (4)                                               /*!< PDMA_T::TDSTS: TDIF4 Position        */
#define PDMA_TDSTS_TDIF4_Msk           (0x1ul << PDMA_TDSTS_TDIF4_Pos)                   /*!< PDMA_T::TDSTS: TDIF4 Mask            */

#define PDMA_TDSTS_TDIF5_Pos           (5)                                               /*!< PDMA_T::TDSTS: TDIF5 Position        */
#define PDMA_TDSTS_TDIF5_Msk           (0x1ul << PDMA_TDSTS_TDIF5_Pos)                   /*!< PDMA_T::TDSTS: TDIF5 Mask            */

#define PDMA_TDSTS_TDIF6_Pos           (6)                                               /*!< PDMA_T::TDSTS: TDIF6 Position        */
#define PDMA_TDSTS_TDIF6_Msk           (0x1ul << PDMA_TDSTS_TDIF6_Pos)                   /*!< PDMA_T::TDSTS: TDIF6 Mask            */

#define PDMA_TDSTS_TDIF7_Pos           (7)                                               /*!< PDMA_T::TDSTS: TDIF7 Position        */
#define PDMA_TDSTS_TDIF7_Msk           (0x1ul << PDMA_TDSTS_TDIF7_Pos)                   /*!< PDMA_T::TDSTS: TDIF7 Mask            */

#define PDMA_TDSTS_TDIF8_Pos           (8)                                               /*!< PDMA_T::TDSTS: TDIF8 Position        */
#define PDMA_TDSTS_TDIF8_Msk           (0x1ul << PDMA_TDSTS_TDIF8_Pos)                   /*!< PDMA_T::TDSTS: TDIF8 Mask            */

#define PDMA_TDSTS_TDIF9_Pos           (9)                                               /*!< PDMA_T::TDSTS: TDIF9 Position        */
#define PDMA_TDSTS_TDIF9_Msk           (0x1ul << PDMA_TDSTS_TDIF9_Pos)                   /*!< PDMA_T::TDSTS: TDIF9 Mask            */

#define PDMA_TDSTS_TDIF10_Pos           (10)                                               /*!< PDMA_T::TDSTS: TDIF10 Position        */
#define PDMA_TDSTS_TDIF10_Msk           (0x1ul << PDMA_TDSTS_TDIF10_Pos)                   /*!< PDMA_T::TDSTS: TDIF10 Mask            */

#define PDMA_TDSTS_TDIF11_Pos           (11)                                               /*!< PDMA_T::TDSTS: TDIF11 Position        */
#define PDMA_TDSTS_TDIF11_Msk           (0x1ul << PDMA_TDSTS_TDIF11_Pos)                   /*!< PDMA_T::TDSTS: TDIF11 Mask            */

#define PDMA_TDSTS_TDIF12_Pos           (12)                                               /*!< PDMA_T::TDSTS: TDIF12 Position        */
#define PDMA_TDSTS_TDIF12_Msk           (0x1ul << PDMA_TDSTS_TDIF12_Pos)                   /*!< PDMA_T::TDSTS: TDIF12 Mask            */

#define PDMA_TDSTS_TDIF13_Pos           (13)                                               /*!< PDMA_T::TDSTS: TDIF13 Position        */
#define PDMA_TDSTS_TDIF13_Msk           (0x1ul << PDMA_TDSTS_TDIF13_Pos)                   /*!< PDMA_T::TDSTS: TDIF13 Mask            */

#define PDMA_TDSTS_TDIF14_Pos           (14)                                               /*!< PDMA_T::TDSTS: TDIF14 Position        */
#define PDMA_TDSTS_TDIF14_Msk           (0x1ul << PDMA_TDSTS_TDIF14_Pos)                   /*!< PDMA_T::TDSTS: TDIF14 Mask            */

#define PDMA_TDSTS_TDIF15_Pos           (15)                                               /*!< PDMA_T::TDSTS: TDIF15 Position        */
#define PDMA_TDSTS_TDIF15_Msk           (0x1ul << PDMA_TDSTS_TDIF15_Pos)                   /*!< PDMA_T::TDSTS: TDIF15 Mask            */

#define PDMA_ALIGN_ALIGNn_Pos           (0)                                                /*!< PDMA_T::ALIGN: ALIGNn Position        */
#define PDMA_ALIGN_ALIGNn_Msk           (0xfffful << PDMA_ALIGN_ALIGNn_Pos)                /*!< PDMA_T::ALIGN: ALIGNn Mask            */

#define PDMA_TACTSTS_TXACTFn_Pos         (0)                                               /*!< PDMA_T::TACTSTS: TXACTFn Position      */
#define PDMA_TACTSTS_TXACTFn_Msk         (0xfffful << PDMA_TACTSTS_TXACTFn_Pos)            /*!< PDMA_T::TACTSTS: TXACTFn Mask          */

#define PDMA_TOUTPSC_TOUTPSC0_Pos        (0)                                               /*!< PDMA_T::TOUTPSC: TOUTPSC0 Position     */
#define PDMA_TOUTPSC_TOUTPSC0_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC0_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC0 Mask         */

#define PDMA_TOUTPSC_TOUTPSC1_Pos        (4)                                               /*!< PDMA_T::TOUTPSC: TOUTPSC1 Position     */
#define PDMA_TOUTPSC_TOUTPSC1_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC1_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC1 Mask         */

#define PDMA_TOUTEN_TOUTENn_Pos          (0)                                               /*!< PDMA_T::TOUTEN: TOUTENn Position       */
#define PDMA_TOUTEN_TOUTENn_Msk          (0x3ul << PDMA_TOUTEN_TOUTENn_Pos)                /*!< PDMA_T::TOUTEN: TOUTENn Mask           */

#define PDMA_TOUTIEN_TOUTIENn_Pos        (0)                                               /*!< PDMA_T::TOUTIEN: TOUTIENn Position     */
#define PDMA_TOUTIEN_TOUTIENn_Msk        (0x3ul << PDMA_TOUTIEN_TOUTIENn_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIENn Mask         */

#define PDMA_SCATBA_SCATBA_Pos           (16)                                              /*!< PDMA_T::SCATBA: SCATBA Position        */
#define PDMA_SCATBA_SCATBA_Msk           (0xfffful << PDMA_SCATBA_SCATBA_Pos)              /*!< PDMA_T::SCATBA: SCATBA Mask            */

#define PDMA_TOC0_1_TOC0_Pos             (0)                                               /*!< PDMA_T::TOC0_1: TOC0 Position          */
#define PDMA_TOC0_1_TOC0_Msk             (0xfffful << PDMA_TOC0_1_TOC0_Pos)                /*!< PDMA_T::TOC0_1: TOC0 Mask              */

#define PDMA_TOC0_1_TOC1_Pos             (16)                                              /*!< PDMA_T::TOC0_1: TOC1 Position          */
#define PDMA_TOC0_1_TOC1_Msk             (0xfffful << PDMA_TOC0_1_TOC1_Pos)                /*!< PDMA_T::TOC0_1: TOC1 Mask              */

#define PDMA_CHRST_CHnRST_Pos            (0)                                               /*!< PDMA_T::CHRST: CHnRST Position         */
#define PDMA_CHRST_CHnRST_Msk            (0xfffful << PDMA_CHRST_CHnRST_Pos)               /*!< PDMA_T::CHRST: CHnRST Mask             */

#define PDMA_REQSEL0_3_REQSRC0_Pos       (0)                                               /*!< PDMA_T::REQSEL0_3: REQSRC0 Position    */
#define PDMA_REQSEL0_3_REQSRC0_Msk       (0x7ful << PDMA_REQSEL0_3_REQSRC0_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC0 Mask        */

#define PDMA_REQSEL0_3_REQSRC1_Pos       (8)                                               /*!< PDMA_T::REQSEL0_3: REQSRC1 Position    */
#define PDMA_REQSEL0_3_REQSRC1_Msk       (0x7ful << PDMA_REQSEL0_3_REQSRC1_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC1 Mask        */

#define PDMA_REQSEL0_3_REQSRC2_Pos       (16)                                              /*!< PDMA_T::REQSEL0_3: REQSRC2 Position    */
#define PDMA_REQSEL0_3_REQSRC2_Msk       (0x7ful << PDMA_REQSEL0_3_REQSRC2_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC2 Mask        */

#define PDMA_REQSEL0_3_REQSRC3_Pos       (24)                                              /*!< PDMA_T::REQSEL0_3: REQSRC3 Position    */
#define PDMA_REQSEL0_3_REQSRC3_Msk       (0x7ful << PDMA_REQSEL0_3_REQSRC3_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC3 Mask        */

#define PDMA_REQSEL4_7_REQSRC4_Pos       (0)                                               /*!< PDMA_T::REQSEL4_7: REQSRC4 Position    */
#define PDMA_REQSEL4_7_REQSRC4_Msk       (0x7ful << PDMA_REQSEL4_7_REQSRC4_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC4 Mask        */

#define PDMA_REQSEL4_7_REQSRC5_Pos       (8)                                               /*!< PDMA_T::REQSEL4_7: REQSRC5 Position    */
#define PDMA_REQSEL4_7_REQSRC5_Msk       (0x7ful << PDMA_REQSEL4_7_REQSRC5_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC5 Mask        */

#define PDMA_REQSEL4_7_REQSRC6_Pos       (16)                                              /*!< PDMA_T::REQSEL4_7: REQSRC6 Position    */
#define PDMA_REQSEL4_7_REQSRC6_Msk       (0x7ful << PDMA_REQSEL4_7_REQSRC6_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC6 Mask        */

#define PDMA_REQSEL4_7_REQSRC7_Pos       (24)                                              /*!< PDMA_T::REQSEL4_7: REQSRC7 Position    */
#define PDMA_REQSEL4_7_REQSRC7_Msk       (0x7ful << PDMA_REQSEL4_7_REQSRC7_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC7 Mask        */

#define PDMA_STCRn_STC_Pos               (0)                                               /*!< PDMA_T::STCRn: STC Position            */
#define PDMA_STCRn_STC_Msk               (0xfffful << PDMA_STCRn_STC_Pos)                  /*!< PDMA_T::STCRn: STC Mask                */

#define PDMA_ASOCRn_SASOL_Pos            (0)                                               /*!< PDMA_T::ASOCRn: SASOL Position         */
#define PDMA_ASOCRn_SASOL_Msk            (0xfffful << PDMA_ASOCRn_SASOL_Pos)               /*!< PDMA_T::ASOCRn: SASOL Mask             */

#define PDMA_ASOCRn_DASOL_Pos            (16)                                              /*!< PDMA_T::ASOCRn: DASOL Position         */
#define PDMA_ASOCRn_DASOL_Msk            (0xfffful << PDMA_ASOCRn_DASOL_Pos)               /*!< PDMA_T::ASOCRn: DASOL Mask             */

#define PDMA_AICTLn_SAICNT_Pos           (0)                                               /*!< PDMA_T::AICTLn: SAICNT Position        */
#define PDMA_AICTLn_SAICNT_Msk           (0xfffful << PDMA_ASOCRn_SASOL_Pos)               /*!< PDMA_T::AICTLn: SAICNT Mask            */

#define PDMA_AICTLn_DAICNT_Pos           (16)                                              /*!< PDMA_T::AICTLn: DAICNT Position        */
#define PDMA_AICTLn_DAICNT_Msk           (0xfffful << PDMA_ASOCRn_DASOL_Pos)               /*!< PDMA_T::AICTLn: DAICNT Mask            */

#define PDMA_RCNTn_RCNT_Pos              (0)                                               /*!< PDMA_T::RCNTn: RCNT Position           */
#define PDMA_RCNTn_RCNT_Msk              (0xfffful << PDMA_STCRn_RCNT_Pos)                 /*!< PDMA_T::RCNTn: RCNT Mask               */

/**@}*/ /* PDMA_CONST */
/**@}*/ /* end of PDMA register group */
/**@}*/ /* end of REGISTER group */


#endif /* __PDMA_REG_H__ */
