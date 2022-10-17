/**************************************************************************//**
 * @file     pdma_reg.h
 * @version  V1.00
 * @brief    PDMA register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PDMA_REG_H__
#define __PDMA_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

#define PDMA_CH_MAX    16UL   /*!< Specify Maximum Channels of PDMA  \hideinitializer */
#define PDMA_CH_Msk    ((1ul<<PDMA_CH_MAX)-1)

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup PDMA Peripheral Direct Memory Access Controller(PDMA)
    Memory Mapped Structure for PDMA Controller
@{ */


typedef struct
{

    /**
     * @var DSCT_T::CTL
     * Offset: 0x00  Descriptor Table Control Register of PDMA Channel n.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |OPMODE    |PDMA Operation Mode Selection
     * |        |          |00 = Idle state: Channel is stopped or this table is complete, when PDMA finish channel table task, OPMODE will be cleared to idle state automatically.
     * |        |          |01 = Basic mode: The descriptor table only has one task
     * |        |          |When this task is finished, the PDMA_INTSTS[n] will be asserted.
     * |        |          |10 = Scatter-Gather mode: When operating in this mode, user must give the next descriptor table address in PDMA_DSCT_NEXT register; PDMA controller will ignore this task, then load the next task to execute.
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
     * |        |          |01= One half-word (16 bit) is transferred for every operation.
     * |        |          |10 = One word (32-bit) is transferred for every operation.
     * |        |          |11 = Reserved.
     * |        |          |Note: The PDMA transfer source address (PDMA_DSCT_SA) and PDMA transfer destination address (PDMA_DSCT_DA) should be alignment under the TXWIDTH selection
     * |[14]    |TXACK     |Transfer Acknowledge Selection
     * |        |          |0 = transfer ack when transfer done.
     * |        |          |1 = transfer ack when PDMA get transfer data.
     * |[15]    |STRIDEEN |Stride Mode Enable Bit
     * |        |          |0 = Stride transfer mode Disabled.
     * |        |          |1 = Stride transfer mode Enabled.
     * |[31:16] |TXCNT     |Transfer Count
     * |        |          |The TXCNT represents the required number of PDMA transfer, the real transfer count is (TXCNT + 1); The maximum transfer count is 32768, every transfer may be byte, half-word or word that is dependent on TXWIDTH field.
     * |        |          |Note: When PDMA finish each transfer data, this field will be decrease immediately.
     * @var DSCT_T::SA
     * Offset: 0x04  Source Address Register of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SA        |PDMA Transfer Source Address Register
     * |        |          |This field indicates a 32-bit source address of PDMA controller.
     * @var DSCT_T::DA
     * Offset: 0x08  Destination Address Register of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DA        |PDMA Transfer Destination Address Register
     * |        |          |This field indicates a 32-bit destination address of PDMA controller.
     * @var DSCT_T::NEXT
     * Offset: 0x0C  Next Scatter-Gather Descriptor Table Offset Address of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |EXENEXT   |PDMA Execution Next Descriptor Table Offset
     * |        |          |This field indicates the offset of next descriptor table address of current execution descriptor table in system memory.
     * |        |          |Note: write operation is useless in this field.
     * |[31:16] |NEXT      |PDMA Next Descriptor Table Offset.
     * |        |          |This field indicates the offset of the next descriptor table address in system memory.
     * |        |          |Write Operation:
     * |        |          |If the system memory based address is 0x2000_0000 (PDMA_SCATBA), and the next descriptor table is start from 0x2000_0100, then this field must fill in 0x0100.
     * |        |          |Read Operation:
     * |        |          |When operating in scatter-gather mode, the last two bits NEXT[1:0] will become reserved, and indicate the first next address of system memory.
     * |        |          |Note1: The descriptor table address must be word boundary.
     * |        |          |Note2: Before filled transfer task in the descriptor table, user must check if the descriptor table is complete.
     */
    __IO uint32_t CTL;             /*!< [0x0000] Descriptor Table Control Register of PDMA Channel n.             */
    __IO uint32_t SA;              /*!< [0x0004] Source Address Register of PDMA Channel n                        */
    __IO uint32_t DA;              /*!< [0x0008] Destination Address Register of PDMA Channel n                   */
    __IO uint32_t NEXT;            /*!< [0x000c] First Scatter-Gather Descriptor Table Offset Address of PDMA Channel n */
} DSCT_T;


typedef struct
{
    /**
     * @var STRIDE_T::STCR
     * Offset: 0x500  Stride Transfer Count Register of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |STC       |PDMA Stride Transfer Count
     * |        |          |The 16-bit register defines the stride transfer count of each row.
     * @var STRIDE_T::ASOCR
     * Offset: 0x504  Address Stride Offset Register of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |SASOL     |VDMA Source Address Stride Offset Length
     * |        |          |The 16-bit register defines the source address stride transfer offset count of each row.
     * |[31:16] |DASOL     |VDMA Destination Address Stride Offset Length
     * |        |          |The 16-bit register defines the destination address stride transfer offset count of each row.
     */
    __IO uint32_t STCR;           /*!< [0x0500] Stride Transfer Count Register of PDMA Channel 0                 */
    __IO uint32_t ASOCR;          /*!< [0x0504] Address Stride Offset Register of PDMA Channel 0                 */
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
     * Offset: 0x100  Current Scatter-Gather Descriptor Table Address of PDMA Channel n
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
     * Offset: 0x404  PDMA Transfer Stop Control Register
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
     * |[0]     |ABTIF     |PDMA Read/Write Target Abort Interrupt Flag (Read-only)
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
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC0(PDMA_TOC0_1[15:0], user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[9]     |REQTOF1   |Request Time-out Flag for Channel 1
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC1(PDMA_TOC0_1[31:16]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[10]    |REQTOF2   |Request Time-out Flag for Channel 2
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC2(PDMA_TOC2_3[15:0]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[11]    |REQTOF3   |Request Time-out Flag for Channel 3
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC3(PDMA_TOC2_3[31:16]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[12]    |REQTOF4   |Request Time-out Flag for Channel 4
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC4(PDMA_TOC4_5[15:0]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[13]    |REQTOF5   |Request Time-out Flag for Channel 5
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC5(PDMA_TOC4_5[31:16]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[14]    |REQTOF6   |Request Time-out Flag for Channel 6
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC6(PDMA_TOC6_7[15:0]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[15]    |REQTOF7   |Request Time-out Flag for Channel 7
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC7(PDMA_TOC6_7[31:16]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[16]    |REQTOF8   |Request Time-out Flag for Channel 8
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC8(PDMA_TOC8_9[15:0]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[17]    |REQTOF9   |Request Time-out Flag for Channel 9
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC9(PDMA_TOC8_9[31:16]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[18]    |REQTOF10  |Request Time-out Flag for Channel 10
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC10(PDMA_TOC10_11[15:0]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[19]    |REQTOF11  |Request Time-out Flag for Channel 11
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC11(PDMA_TOC10_11[31:16]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[20]    |REQTOF12  |Request Time-out Flag for Channel 12
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC12(PDMA_TOC13_12[15:0]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[21]    |REQTOF13  |Request Time-out Flag for Channel 13
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC13(PDMA_TOC13_12[31:16]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[22]    |REQTOF14  |Request Time-out Flag for Channel 14
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC14(PDMA_TOC15_14[15:0]), user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[23]    |REQTOF15  |Request Time-out Flag for Channel 15
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOC15(PDMA_TOC15_14[31:16]), user can write 1 to clear these bits.
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
     * @var PDMA_T::TOUTPSC0_7
     * Offset: 0x430  PDMA Time-out Prescaler Register(CH0 to CH7)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TOUTPSC0  |PDMA Channel 0 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 0 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 0 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 0 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 0 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 0 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 0 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 0 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 0 time-out clock source is HCLK/215.
     * |[6:4]   |TOUTPSC1  |PDMA Channel 1 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 1 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 1 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 1 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 1 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 1 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 1 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 1 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 1 time-out clock source is HCLK/215.
     * |[10:8]  |TOUTPSC2  |PDMA Channel 2 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 2 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 2 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 2 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 2 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 2 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 2 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 2 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 2 time-out clock source is HCLK/215.
     * |[14:12] |TOUTPSC3  |PDMA Channel 3 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 3 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 3 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 3 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 3 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 3 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 3 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 3 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 3 time-out clock source is HCLK/215.
     * |[18:16] |TOUTPSC4  |PDMA Channel 4 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 4 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 4 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 4 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 4 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 4 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 4 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 4 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 4 time-out clock source is HCLK/215.
     * |[22:20] |TOUTPSC5  |PDMA Channel 5 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 5 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 5 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 5 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 5 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 5 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 5 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 5 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 5 time-out clock source is HCLK/215.
     * |[26:24] |TOUTPSC6  |PDMA Channel 6 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 6 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 6 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 6 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 6 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 6 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 6 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 6 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 6 time-out clock source is HCLK/215.
     * |[30:28] |TOUTPSC7  |PDMA Channel 7 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 7 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 7 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 7 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 7 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 7 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 7 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 7 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 7 time-out clock source is HCLK/215.
     * @var PDMA_T::TOUTEN
     * Offset: 0x434  PDMA Time-out Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOUTENn   |PDMA Time-out Enable Bits
     * |        |          |0 = PDMA Channel n time-out function Disable.
     * |        |          |1 = PDMA Channel n time-out function Enable.
     * @var PDMA_T::TOUTIEN
     * Offset: 0x438  PDMA Time-out Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOUTIENn  |PDMA Time-out Interrupt Enable Bits
     * |        |          |0 = PDMA Channel n time-out interrupt Disable.
     * |        |          |1 = PDMA Channel n time-out interrupt Enable.
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
     * Offset: 0x440  PDMA Time-out Counter Ch0 and Ch1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC0      |Time-out Counter for Channel 0
     * |        |          |This controls the period of time-out function for channel 0
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC1      |Time-out Counter for Channel 1
     * |        |          |This controls the period of time-out function for channel 1
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::TOC2_3
     * Offset: 0x444  PDMA Time-out Counter Ch2 and Ch3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC2      |Time-out Counter for Channel 2
     * |        |          |This controls the period of time-out function for channel 2
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC3      |Time-out Counter for Channel 3
     * |        |          |This controls the period of time-out function for channel 3
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::TOC4_5
     * Offset: 0x448  PDMA Time-out Counter Ch4 and Ch5 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC4      |Time-out Counter for Channel 4
     * |        |          |This controls the period of time-out function for channel 4
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC5      |Time-out Counter for Channel 5
     * |        |          |This controls the period of time-out function for channel 5
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::TOC6_7
     * Offset: 0x44C  PDMA Time-out Counter Ch6 and Ch7 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC6      |Time-out Counter for Channel 6
     * |        |          |This controls the period of time-out function for channel 6
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC7      |Time-out Counter for Channel 7
     * |        |          |This controls the period of time-out function for channel 7
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::TOC8_9
     * Offset: 0x450  PDMA Time-out Counter Ch8 and Ch9 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC8      |Time-out Counter for Channel 8
     * |        |          |This controls the period of time-out function for channel 8
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC9      |Time-out Counter for Channel 9
     * |        |          |This controls the period of time-out function for channel 9
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::TOC10_11
     * Offset: 0x454  PDMA Time-out Counter Ch10 and Ch11 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC10     |Time-out Counter for Channel 10
     * |        |          |This controls the period of time-out function for channel 10
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC11     |Time-out Counter for Channel 11
     * |        |          |This controls the period of time-out function for channel 11
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::TOC12_13
     * Offset: 0x458  PDMA Time-out Counter Ch12 and Ch13 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC12     |Time-out Counter for Channel 12
     * |        |          |This controls the period of time-out function for channel 12
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC13     |Time-out Counter for Channel 13
     * |        |          |This controls the period of time-out function for channel 13
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::TOC14_15
     * Offset: 0x45C  PDMA Time-out Counter Ch14 and Ch15 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC14     |Time-out Counter for Channel 14
     * |        |          |This controls the period of time-out function for channel 14
     * |        |          |The calculation unit is based on 10 kHz clock.
     * |[31:16] |TOC15     |Time-out Counter for Channel 15
     * |        |          |This controls the period of time-out function for channel 15
     * |        |          |The calculation unit is based on 10 kHz clock.
     * @var PDMA_T::CHRST
     * Offset: 0x460  PDMA Channel Reset Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CHnRST    |Channel N Reset
     * |        |          |0 = corresponding channel n not reset.
     * |        |          |1 = corresponding channel n is reset.
     * @var PDMA_T::TOUTPSC8_15
     * Offset: 0x468  PDMA Time-out Prescaler Register(CH8 to CH15)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TOUTPSC8  |PDMA Channel 8 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 8 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 8 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 8 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 8 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 8 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 8 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 8 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 8 time-out clock source is HCLK/215.
     * |[6:4]   |TOUTPSC9  |PDMA Channel 9 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 9 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 9 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 9 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 9 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 9 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 9 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 9 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 9 time-out clock source is HCLK/215.
     * |[10:8]  |TOUTPSC10 |PDMA Channel 10 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 10 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 10 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 10 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 10 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 10 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 10 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 10 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 10 time-out clock source is HCLK/215.
     * |[14:12] |TOUTPSC11 |PDMA Channel 11 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 11 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 11 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 11 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 11 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 11 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 11 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 11 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 11 time-out clock source is HCLK/215.
     * |[18:16] |TOUTPSC12 |PDMA Channel 12 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 12 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 12 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 12 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 12 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 12 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 12 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 12 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 12 time-out clock source is HCLK/215.
     * |[22:20] |TOUTPSC13 |PDMA Channel 13 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 13 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 13 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 13 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 13 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 13 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 13 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 13 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 13 time-out clock source is HCLK/215.
     * |[26:24] |TOUTPSC14 |PDMA Channel 14 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 14 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 14 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 14 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 14 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 14 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 14 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 14 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 14 time-out clock source is HCLK/215.
     * |[30:28] |TOUTPSC15 |PDMA Channel 15 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 15 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 15 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 15 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 15 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 15 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 15 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 15 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 15 time-out clock source is HCLK/215.
     * @var PDMA_T::REQSEL0_3
     * Offset: 0x480  PDMA Request Source Select Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |REQSRC0   |Channel 0 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 0
     * |        |          |User can configure the peripheral by setting REQSRC0.
     * |        |          |0 = Disable PDMA peripheral request.
     * |        |          |1 = Reserved.
     * |        |          |2 = Channel connects to USB_TX.
     * |        |          |3 = Channel connects to USB_RX.
     * |        |          |4 = Channel connects to UART0_TX.
     * |        |          |5 = Channel connects to UART0_RX.
     * |        |          |6 = Channel connects to UART1_TX.
     * |        |          |7 = Channel connects to UART1_RX.
     * |        |          |8 = Channel connects to UART2_TX.
     * |        |          |9 = Channel connects to UART2_RX.
     * |        |          |10=Channel connects to UART3_TX.
     * |        |          |11 = Channel connects to UART3_RX.
     * |        |          |12 = Channel connects to UART4_TX.
     * |        |          |13 = Channel connects to UART4_RX.
     * |        |          |14 = Channel connects to UART5_TX.
     * |        |          |15 = Channel connects to UART5_RX.
     * |        |          |16 = Channel connects to USCI0_TX.
     * |        |          |17 = Channel connects to USCI0_RX.
     * |        |          |18 = Reserved.
     * |        |          |19 = Reserved.
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
     * |        |          |30 = Channel connects to QSPI1_TX
     * |        |          |31 = Channel connects to QSPI1_RX.
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
     * |        |          |50 = Channel connects to ADC0_RX.
     * |        |          |51 = Channel connects to DAC0_TX.
     * |        |          |52 = Channel connects to DAC1_TX.
     * |        |          |53 = Channel connects to EPWM0_CH0_TX.
     * |        |          |54 = Channel connects to EPWM0_CH1_TX.
     * |        |          |55 = Channel connects to EPWM0_CH2_TX.
     * |        |          |56 = Channel connects to EPWM0_CH3_TX.
     * |        |          |57 = Channel connects to EPWM0_CH4_TX.
     * |        |          |58 = Channel connects to EPWM0_CH5_TX.
     * |        |          |59 = Channel connects to EPWM1_CH0_TX.
     * |        |          |60 = Channel connects to EPWM1_CH1_TX.
     * |        |          |61 = Channel connects to EPWM1_CH2_TX.
     * |        |          |62 = Channel connects to EPWM1_CH3_TX.
     * |        |          |63 = Channel connects to EPWM1_CH4_TX.
     * |        |          |64 = Channel connects to EPWM1_CH5_TX.
     * |        |          |65 = Reserved.
     * |        |          |66 = Channel connects to UART6_TX.
     * |        |          |67 = Channel connects to UART6_RX.
     * |        |          |68 = Channel connects to UART7_TX.
     * |        |          |69 = Channel connects to UART7_RX.
     * |        |          |70 = Channel connects to ADC1_RX.
     * |        |          |71 = Channel connects to ACMP0.
     * |        |          |72 = Channel connects to ACMP1.
     * |        |          |73 = Channel connects to PSIO_TX.
     * |        |          |74 = Channel connects to PSIO_RX.
     * |        |          |75 = Channel connects to I2C3_TX.
     * |        |          |76 = Channel connects to I2C3_RX.
     * |        |          |77 = Channel connects to I2C4_TX.
     * |        |          |78 = Channel connects to I2C4_RX.
     * |        |          |79 = Channel connects to I2S1_TX.
     * |        |          |80 = Channel connects to I2S1_RX.
     * |        |          |81 = Channel connects to EINT0.
     * |        |          |82 = Channel connects to EINT1.
     * |        |          |83 = Channel connects to EINT2.
     * |        |          |84 = Channel connects to EINT3.
     * |        |          |85 = Channel connects to EINT4.
     * |        |          |86 = Channel connects to EINT5.
     * |        |          |87 = Channel connects to EINT6.
     * |        |          |88 = Channel connects to EINT7.
     * |        |          |89 = Channel connects to UART8_TX.
     * |        |          |90 = Channel connects to UART8_RX.
     * |        |          |91 = Channel connects to UART9_TX.
     * |        |          |92 = Channel connects to UART9_RX.
     * |        |          |93 = Channel connects to ADC2_RX.
     * |        |          |94 = Channel connects to ACMP2.
     * |        |          |95 = Channel connects to ACMP3.
     * |        |          |Others = Reserved.
     * |        |          |Note 1: A peripheral can't assign to two channels at the same time.
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
     * @var PDMA_T::REQSEL8_11
     * Offset: 0x488  PDMA Request Source Select Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |REQSRC8   |Channel 8 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 8
     * |        |          |User can configure the peripheral setting by REQSRC8.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[14:8]  |REQSRC9   |Channel 9 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 9
     * |        |          |User can configure the peripheral setting by REQSRC9.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[22:16] |REQSRC10  |Channel 10 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 10
     * |        |          |User can configure the peripheral setting by REQSRC10.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[30:24] |REQSRC11  |Channel 11 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 11
     * |        |          |User can configure the peripheral setting by REQSRC11.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * @var PDMA_T::REQSEL12_15
     * Offset: 0x48C  PDMA Request Source Select Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |REQSRC12  |Channel 12 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 12
     * |        |          |User can configure the peripheral setting by REQSRC12.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[14:8]  |REQSRC13  |Channel 13 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 13
     * |        |          |User can configure the peripheral setting by REQSRC13.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[22:16] |REQSRC14  |Channel 14 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 14
     * |        |          |User can configure the peripheral setting by REQSRC14.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[30:24] |REQSRC15  |Channel 15 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 15
     * |        |          |User can configure the peripheral setting by REQSRC15.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     */
    DSCT_T DSCT[16];
    __I  uint32_t CURSCAT[16];           /*!< [0x0100] Current Scatter-Gather Descriptor Table Address of PDMA Channel n */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[176];
    /// @endcond //HIDDEN_SYMBOLS
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
    __IO uint32_t TOUTPSC0_7;            /*!< [0x0430] PDMA Time-out Prescaler Register(CH0 to CH7)                     */
    __IO uint32_t TOUTEN;                /*!< [0x0434] PDMA Time-out Enable Register                                    */
    __IO uint32_t TOUTIEN;               /*!< [0x0438] PDMA Time-out Interrupt Enable Register                          */
    __IO uint32_t SCATBA;                /*!< [0x043c] PDMA Scatter-Gather Descriptor Table Base Address Register       */
    __IO uint32_t TOC0_1;                /*!< [0x0440] PDMA Time-out Counter Ch0 and Ch1 Register                       */
    __IO uint32_t TOC2_3;                /*!< [0x0444] PDMA Time-out Counter Ch2 and Ch3 Register                       */
    __IO uint32_t TOC4_5;                /*!< [0x0448] PDMA Time-out Counter Ch4 and Ch5 Register                       */
    __IO uint32_t TOC6_7;                /*!< [0x044C] PDMA Time-out Counter Ch6 and Ch7 Register                       */
    __IO uint32_t TOC8_9;                /*!< [0x0450] PDMA Time-out Counter Ch8 and Ch9 Register                       */
    __IO uint32_t TOC10_11;              /*!< [0x0454] PDMA Time-out Counter Ch10 and Ch11 Register                     */
    __IO uint32_t TOC12_13;              /*!< [0x0458] PDMA Time-out Counter Ch12 and Ch13 Register                     */
    __IO uint32_t TOC14_15;              /*!< [0x045C] PDMA Time-out Counter Ch14 and Ch15 Register                     */
    __IO uint32_t CHRST;                 /*!< [0x0460] PDMA Channel Reset Register                                      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TOUTPSC8_15;           /*!< [0x0468] PDMA Time-out Prescaler Register(CH8 to CH15)                    */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t REQSEL0_3;             /*!< [0x0480] PDMA Request Source Select Register 0                            */
    __IO uint32_t REQSEL4_7;             /*!< [0x0484] PDMA Request Source Select Register 1                            */
    __IO uint32_t REQSEL8_11;            /*!< [0x0488] PDMA Request Source Select Register 2                            */
    __IO uint32_t REQSEL12_15;           /*!< [0x048c] PDMA Request Source Select Register 3                            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[28];
    /// @endcond //HIDDEN_SYMBOLS
    STRIDE_T     STRIDE[6];
    /// @cond HIDDEN_SYMBOLS
    __IO uint32_t RESERVE5[52];
    /// @endcond //HIDDEN_SYMBOLS
    REPEAT_T    REPEAT[2];
} PDMA_T;

/**
    @addtogroup PDMA_CONST PDMA Bit Field Definition
    Constant Definitions for PDMA Controller
@{ */

#define PDMA_DSCT_CTL_OPMODE_Pos         (0)                                               /*!< PDMA_T::DSCT_CTL: OPMODE Position     */
#define PDMA_DSCT_CTL_OPMODE_Msk         (0x3ul << PDMA_DSCT_CTL_OPMODE_Pos)               /*!< PDMA_T::DSCT_CTL: OPMODE Mask         */

#define PDMA_DSCT_CTL_TXTYPE_Pos         (2)                                               /*!< PDMA_T::DSCT_CTL: TXTYPE Position     */
#define PDMA_DSCT_CTL_TXTYPE_Msk         (0x1ul << PDMA_DSCT_CTL_TXTYPE_Pos)               /*!< PDMA_T::DSCT_CTL: TXTYPE Mask         */

#define PDMA_DSCT_CTL_BURSIZE_Pos        (4)                                               /*!< PDMA_T::DSCT_CTL: BURSIZE Position    */
#define PDMA_DSCT_CTL_BURSIZE_Msk        (0x7ul << PDMA_DSCT_CTL_BURSIZE_Pos)              /*!< PDMA_T::DSCT_CTL: BURSIZE Mask        */

#define PDMA_DSCT_CTL_TBINTDIS_Pos       (7)                                               /*!< PDMA_T::DSCT_CTL: TBINTDIS Position   */
#define PDMA_DSCT_CTL_TBINTDIS_Msk       (0x1ul << PDMA_DSCT_CTL_TBINTDIS_Pos)             /*!< PDMA_T::DSCT_CTL: TBINTDIS Mask       */

#define PDMA_DSCT_CTL_SAINC_Pos          (8)                                               /*!< PDMA_T::DSCT_CTL: SAINC Position      */
#define PDMA_DSCT_CTL_SAINC_Msk          (0x3ul << PDMA_DSCT_CTL_SAINC_Pos)                /*!< PDMA_T::DSCT_CTL: SAINC Mask          */

#define PDMA_DSCT_CTL_DAINC_Pos          (10)                                              /*!< PDMA_T::DSCT_CTL: DAINC Position      */
#define PDMA_DSCT_CTL_DAINC_Msk          (0x3ul << PDMA_DSCT_CTL_DAINC_Pos)                /*!< PDMA_T::DSCT_CTL: DAINC Mask          */

#define PDMA_DSCT_CTL_TXWIDTH_Pos        (12)                                              /*!< PDMA_T::DSCT_CTL: TXWIDTH Position    */
#define PDMA_DSCT_CTL_TXWIDTH_Msk        (0x3ul << PDMA_DSCT_CTL_TXWIDTH_Pos)              /*!< PDMA_T::DSCT_CTL: TXWIDTH Mask        */

#define PDMA_DSCT_CTL_STRIDEEN_Pos       (15)                                              /*!< PDMA_T::DSCT_CTL: STRIDEEN Position   */
#define PDMA_DSCT_CTL_STRIDEEN_Msk       (0x1ul << PDMA_DSCT_CTL_STRIDEEN_Pos)             /*!< PDMA_T::DSCT_CTL: STRIDEEN Mask       */

#define PDMA_DSCT_CTL_TXCNT_Pos          (16)                                              /*!< PDMA_T::DSCT_CTL: TXCNT Position      */
#define PDMA_DSCT_CTL_TXCNT_Msk          (0xfffful << PDMA_DSCT_CTL_TXCNT_Pos)             /*!< PDMA_T::DSCT_CTL: TXCNT Mask          */

#define PDMA_DSCT_SA_SA_Pos              (0)                                               /*!< PDMA_T::DSCT_SA: SA Position          */
#define PDMA_DSCT_SA_SA_Msk              (0xfffffffful << PDMA_DSCT_SA_SA_Pos)             /*!< PDMA_T::DSCT_SA: SA Mask              */

#define PDMA_DSCT_DA_DA_Pos              (0)                                               /*!< PDMA_T::DSCT_DA: DA Position          */
#define PDMA_DSCT_DA_DA_Msk              (0xfffffffful << PDMA_DSCT_DA_DA_Pos)             /*!< PDMA_T::DSCT_DA: DA Mask              */

#define PDMA_DSCT_NEXT_NEXT_Pos          (0)                                               /*!< PDMA_T::DSCT_NEXT: NEXT Position      */
#define PDMA_DSCT_NEXT_NEXT_Msk          (0xfffful << PDMA_DSCT_NEXT_NEXT_Pos)             /*!< PDMA_T::DSCT_NEXT: NEXT Mask          */

#define PDMA_DSCT_NEXT_EXENEXT_Pos       (16)                                              /*!< PDMA_T::DSCT_FIRST: NEXT Position     */
#define PDMA_DSCT_NEXT_EXENEXT_Msk       (0xfffful << PDMA_DSCT_NEXT_EXENEXT_Pos)          /*!< PDMA_T::DSCT_FIRST: NEXT Mask         */

#define PDMA_CURSCAT_CURADDR_Pos         (0)                                               /*!< PDMA_T::CURSCAT: CURADDR Position     */
#define PDMA_CURSCAT_CURADDR_Msk         (0xfffffffful << PDMA_CURSCAT_CURADDR_Pos)        /*!< PDMA_T::CURSCAT: CURADDR Mask         */

#define PDMA_CHCTL_CHENn_Pos             (0)                                               /*!< PDMA_T::CHCTL: CHENn Position         */
#define PDMA_CHCTL_CHENn_Msk             (0xfffful << PDMA_CHCTL_CHENn_Pos)                /*!< PDMA_T::CHCTL: CHENn Mask             */

#define PDMA_CHCTL_CHEN0_Pos             (0)                                               /*!< PDMA_T::CHCTL: CHEN0 Position         */
#define PDMA_CHCTL_CHEN0_Msk             (0x1ul << PDMA_CHCTL_CHEN0_Pos)                   /*!< PDMA_T::CHCTL: CHEN0 Mask             */

#define PDMA_CHCTL_CHEN1_Pos             (1)                                               /*!< PDMA_T::CHCTL: CHEN1 Position         */
#define PDMA_CHCTL_CHEN1_Msk             (0x1ul << PDMA_CHCTL_CHEN1_Pos)                   /*!< PDMA_T::CHCTL: CHEN1 Mask             */

#define PDMA_CHCTL_CHEN2_Pos             (2)                                               /*!< PDMA_T::CHCTL: CHEN2 Position         */
#define PDMA_CHCTL_CHEN2_Msk             (0x1ul << PDMA_CHCTL_CHEN2_Pos)                   /*!< PDMA_T::CHCTL: CHEN2 Mask             */

#define PDMA_CHCTL_CHEN3_Pos             (3)                                               /*!< PDMA_T::CHCTL: CHEN3 Position         */
#define PDMA_CHCTL_CHEN3_Msk             (0x1ul << PDMA_CHCTL_CHEN3_Pos)                   /*!< PDMA_T::CHCTL: CHEN3 Mask             */

#define PDMA_CHCTL_CHEN4_Pos             (4)                                               /*!< PDMA_T::CHCTL: CHEN4 Position         */
#define PDMA_CHCTL_CHEN4_Msk             (0x1ul << PDMA_CHCTL_CHEN4_Pos)                   /*!< PDMA_T::CHCTL: CHEN4 Mask             */

#define PDMA_CHCTL_CHEN5_Pos             (5)                                               /*!< PDMA_T::CHCTL: CHEN5 Position         */
#define PDMA_CHCTL_CHEN5_Msk             (0x1ul << PDMA_CHCTL_CHEN5_Pos)                   /*!< PDMA_T::CHCTL: CHEN5 Mask             */

#define PDMA_CHCTL_CHEN6_Pos             (6)                                               /*!< PDMA_T::CHCTL: CHEN6 Position         */
#define PDMA_CHCTL_CHEN6_Msk             (0x1ul << PDMA_CHCTL_CHEN6_Pos)                   /*!< PDMA_T::CHCTL: CHEN6 Mask             */

#define PDMA_CHCTL_CHEN7_Pos             (7)                                               /*!< PDMA_T::CHCTL: CHEN7 Position         */
#define PDMA_CHCTL_CHEN7_Msk             (0x1ul << PDMA_CHCTL_CHEN7_Pos)                   /*!< PDMA_T::CHCTL: CHEN7 Mask             */

#define PDMA_CHCTL_CHEN8_Pos             (8)                                               /*!< PDMA_T::CHCTL: CHEN8 Position         */
#define PDMA_CHCTL_CHEN8_Msk             (0x1ul << PDMA_CHCTL_CHEN8_Pos)                   /*!< PDMA_T::CHCTL: CHEN8 Mask             */

#define PDMA_CHCTL_CHEN9_Pos             (9)                                               /*!< PDMA_T::CHCTL: CHEN9 Position         */
#define PDMA_CHCTL_CHEN9_Msk             (0x1ul << PDMA_CHCTL_CHEN9_Pos)                   /*!< PDMA_T::CHCTL: CHEN9 Mask             */

#define PDMA_CHCTL_CHEN10_Pos            (10)                                              /*!< PDMA_T::CHCTL: CHEN10 Position        */
#define PDMA_CHCTL_CHEN10_Msk            (0x1ul << PDMA_CHCTL_CHEN10_Pos)                  /*!< PDMA_T::CHCTL: CHEN10 Mask            */

#define PDMA_CHCTL_CHEN11_Pos            (11)                                              /*!< PDMA_T::CHCTL: CHEN11 Position        */
#define PDMA_CHCTL_CHEN11_Msk            (0x1ul << PDMA_CHCTL_CHEN11_Pos)                  /*!< PDMA_T::CHCTL: CHEN11 Mask            */

#define PDMA_CHCTL_CHEN12_Pos            (12)                                              /*!< PDMA_T::CHCTL: CHEN12 Position        */
#define PDMA_CHCTL_CHEN12_Msk            (0x1ul << PDMA_CHCTL_CHEN12_Pos)                  /*!< PDMA_T::CHCTL: CHEN12 Mask            */

#define PDMA_CHCTL_CHEN13_Pos            (13)                                              /*!< PDMA_T::CHCTL: CHEN13 Position        */
#define PDMA_CHCTL_CHEN13_Msk            (0x1ul << PDMA_CHCTL_CHEN13_Pos)                  /*!< PDMA_T::CHCTL: CHEN13 Mask            */

#define PDMA_CHCTL_CHEN14_Pos            (14)                                              /*!< PDMA_T::CHCTL: CHEN14 Position        */
#define PDMA_CHCTL_CHEN14_Msk            (0x1ul << PDMA_CHCTL_CHEN14_Pos)                  /*!< PDMA_T::CHCTL: CHEN14 Mask            */

#define PDMA_CHCTL_CHEN15_Pos            (15)                                              /*!< PDMA_T::CHCTL: CHEN15 Position        */
#define PDMA_CHCTL_CHEN15_Msk            (0x1ul << PDMA_CHCTL_CHEN15_Pos)                  /*!< PDMA_T::CHCTL: CHEN15 Mask            */

#define PDMA_PAUSE_PAUSEn_Pos            (0)                                               /*!< PDMA_T::PAUSE: PAUSEn Position        */
#define PDMA_PAUSE_PAUSEn_Msk            (0xfffful << PDMA_PAUSE_PAUSEn_Pos)               /*!< PDMA_T::PAUSE: PAUSEn Mask            */

#define PDMA_PAUSE_PAUSE0_Pos            (0)                                               /*!< PDMA_T::PAUSE: PAUSE0 Position        */
#define PDMA_PAUSE_PAUSE0_Msk            (0x1ul << PDMA_PAUSE_PAUSE0_Pos)                  /*!< PDMA_T::PAUSE: PAUSE0 Mask            */

#define PDMA_PAUSE_PAUSE1_Pos            (1)                                               /*!< PDMA_T::PAUSE: PAUSE1 Position        */
#define PDMA_PAUSE_PAUSE1_Msk            (0x1ul << PDMA_PAUSE_PAUSE1_Pos)                  /*!< PDMA_T::PAUSE: PAUSE1 Mask            */

#define PDMA_PAUSE_PAUSE2_Pos            (2)                                               /*!< PDMA_T::PAUSE: PAUSE2 Position        */
#define PDMA_PAUSE_PAUSE2_Msk            (0x1ul << PDMA_PAUSE_PAUSE2_Pos)                  /*!< PDMA_T::PAUSE: PAUSE2 Mask            */

#define PDMA_PAUSE_PAUSE3_Pos            (3)                                               /*!< PDMA_T::PAUSE: PAUSE3 Position        */
#define PDMA_PAUSE_PAUSE3_Msk            (0x1ul << PDMA_PAUSE_PAUSE3_Pos)                  /*!< PDMA_T::PAUSE: PAUSE3 Mask            */

#define PDMA_PAUSE_PAUSE4_Pos            (4)                                               /*!< PDMA_T::PAUSE: PAUSE4 Position        */
#define PDMA_PAUSE_PAUSE4_Msk            (0x1ul << PDMA_PAUSE_PAUSE4_Pos)                  /*!< PDMA_T::PAUSE: PAUSE4 Mask            */

#define PDMA_PAUSE_PAUSE5_Pos            (5)                                               /*!< PDMA_T::PAUSE: PAUSE5 Position        */
#define PDMA_PAUSE_PAUSE5_Msk            (0x1ul << PDMA_PAUSE_PAUSE5_Pos)                  /*!< PDMA_T::PAUSE: PAUSE5 Mask            */

#define PDMA_PAUSE_PAUSE6_Pos            (6)                                               /*!< PDMA_T::PAUSE: PAUSE6 Position        */
#define PDMA_PAUSE_PAUSE6_Msk            (0x1ul << PDMA_PAUSE_PAUSE6_Pos)                  /*!< PDMA_T::PAUSE: PAUSE6 Mask            */

#define PDMA_PAUSE_PAUSE7_Pos            (7)                                               /*!< PDMA_T::PAUSE: PAUSE7 Position        */
#define PDMA_PAUSE_PAUSE7_Msk            (0x1ul << PDMA_PAUSE_PAUSE7_Pos)                  /*!< PDMA_T::PAUSE: PAUSE7 Mask            */

#define PDMA_PAUSE_PAUSE8_Pos            (8)                                               /*!< PDMA_T::PAUSE: PAUSE8 Position        */
#define PDMA_PAUSE_PAUSE8_Msk            (0x1ul << PDMA_PAUSE_PAUSE8_Pos)                  /*!< PDMA_T::PAUSE: PAUSE8 Mask            */

#define PDMA_PAUSE_PAUSE9_Pos            (9)                                               /*!< PDMA_T::PAUSE: PAUSE9 Position        */
#define PDMA_PAUSE_PAUSE9_Msk            (0x1ul << PDMA_PAUSE_PAUSE9_Pos)                  /*!< PDMA_T::PAUSE: PAUSE9 Mask            */

#define PDMA_PAUSE_PAUSE10_Pos           (10)                                              /*!< PDMA_T::PAUSE: PAUSE10 Position       */
#define PDMA_PAUSE_PAUSE10_Msk           (0x1ul << PDMA_PAUSE_PAUSE10_Pos)                 /*!< PDMA_T::PAUSE: PAUSE10 Mask           */

#define PDMA_PAUSE_PAUSE11_Pos           (11)                                              /*!< PDMA_T::PAUSE: PAUSE11 Position       */
#define PDMA_PAUSE_PAUSE11_Msk           (0x1ul << PDMA_PAUSE_PAUSE11_Pos)                 /*!< PDMA_T::PAUSE: PAUSE11 Mask           */

#define PDMA_PAUSE_PAUSE12_Pos           (12)                                              /*!< PDMA_T::PAUSE: PAUSE12 Position       */
#define PDMA_PAUSE_PAUSE12_Msk           (0x1ul << PDMA_PAUSE_PAUSE12_Pos)                 /*!< PDMA_T::PAUSE: PAUSE12 Mask           */

#define PDMA_PAUSE_PAUSE13_Pos           (13)                                              /*!< PDMA_T::PAUSE: PAUSE13 Position       */
#define PDMA_PAUSE_PAUSE13_Msk           (0x1ul << PDMA_PAUSE_PAUSE13_Pos)                 /*!< PDMA_T::PAUSE: PAUSE13 Mask           */

#define PDMA_PAUSE_PAUSE14_Pos           (14)                                              /*!< PDMA_T::PAUSE: PAUSE14 Position       */
#define PDMA_PAUSE_PAUSE14_Msk           (0x1ul << PDMA_PAUSE_PAUSE14_Pos)                 /*!< PDMA_T::PAUSE: PAUSE14 Mask           */

#define PDMA_PAUSE_PAUSE15_Pos           (15)                                              /*!< PDMA_T::PAUSE: PAUSE15 Position       */
#define PDMA_PAUSE_PAUSE15_Msk           (0x1ul << PDMA_PAUSE_PAUSE15_Pos)                 /*!< PDMA_T::PAUSE: PAUSE15 Mask           */

#define PDMA_SWREQ_SWREQn_Pos            (0)                                               /*!< PDMA_T::SWREQ: SWREQn Position        */
#define PDMA_SWREQ_SWREQn_Msk            (0xfffful << PDMA_SWREQ_SWREQn_Pos)               /*!< PDMA_T::SWREQ: SWREQn Mask            */

#define PDMA_SWREQ_SWREQ0_Pos            (0)                                               /*!< PDMA_T::SWREQ: SWREQ0 Position        */
#define PDMA_SWREQ_SWREQ0_Msk            (0x1ul << PDMA_SWREQ_SWREQ0_Pos)                  /*!< PDMA_T::SWREQ: SWREQ0 Mask            */

#define PDMA_SWREQ_SWREQ1_Pos            (1)                                               /*!< PDMA_T::SWREQ: SWREQ1 Position        */
#define PDMA_SWREQ_SWREQ1_Msk            (0x1ul << PDMA_SWREQ_SWREQ1_Pos)                  /*!< PDMA_T::SWREQ: SWREQ1 Mask            */

#define PDMA_SWREQ_SWREQ2_Pos            (2)                                               /*!< PDMA_T::SWREQ: SWREQ2 Position        */
#define PDMA_SWREQ_SWREQ2_Msk            (0x1ul << PDMA_SWREQ_SWREQ2_Pos)                  /*!< PDMA_T::SWREQ: SWREQ2 Mask            */

#define PDMA_SWREQ_SWREQ3_Pos            (3)                                               /*!< PDMA_T::SWREQ: SWREQ3 Position        */
#define PDMA_SWREQ_SWREQ3_Msk            (0x1ul << PDMA_SWREQ_SWREQ3_Pos)                  /*!< PDMA_T::SWREQ: SWREQ3 Mask            */

#define PDMA_SWREQ_SWREQ4_Pos            (4)                                               /*!< PDMA_T::SWREQ: SWREQ4 Position        */
#define PDMA_SWREQ_SWREQ4_Msk            (0x1ul << PDMA_SWREQ_SWREQ4_Pos)                  /*!< PDMA_T::SWREQ: SWREQ4 Mask            */

#define PDMA_SWREQ_SWREQ5_Pos            (5)                                               /*!< PDMA_T::SWREQ: SWREQ5 Position        */
#define PDMA_SWREQ_SWREQ5_Msk            (0x1ul << PDMA_SWREQ_SWREQ5_Pos)                  /*!< PDMA_T::SWREQ: SWREQ5 Mask            */

#define PDMA_SWREQ_SWREQ6_Pos            (6)                                               /*!< PDMA_T::SWREQ: SWREQ6 Position        */
#define PDMA_SWREQ_SWREQ6_Msk            (0x1ul << PDMA_SWREQ_SWREQ6_Pos)                  /*!< PDMA_T::SWREQ: SWREQ6 Mask            */

#define PDMA_SWREQ_SWREQ7_Pos            (7)                                               /*!< PDMA_T::SWREQ: SWREQ7 Position        */
#define PDMA_SWREQ_SWREQ7_Msk            (0x1ul << PDMA_SWREQ_SWREQ7_Pos)                  /*!< PDMA_T::SWREQ: SWREQ7 Mask            */

#define PDMA_SWREQ_SWREQ8_Pos            (8)                                               /*!< PDMA_T::SWREQ: SWREQ8 Position        */
#define PDMA_SWREQ_SWREQ8_Msk            (0x1ul << PDMA_SWREQ_SWREQ8_Pos)                  /*!< PDMA_T::SWREQ: SWREQ8 Mask            */

#define PDMA_SWREQ_SWREQ9_Pos            (9)                                               /*!< PDMA_T::SWREQ: SWREQ9 Position        */
#define PDMA_SWREQ_SWREQ9_Msk            (0x1ul << PDMA_SWREQ_SWREQ9_Pos)                  /*!< PDMA_T::SWREQ: SWREQ9 Mask            */

#define PDMA_SWREQ_SWREQ10_Pos           (10)                                              /*!< PDMA_T::SWREQ: SWREQ10 Position       */
#define PDMA_SWREQ_SWREQ10_Msk           (0x1ul << PDMA_SWREQ_SWREQ10_Pos)                 /*!< PDMA_T::SWREQ: SWREQ10 Mask           */

#define PDMA_SWREQ_SWREQ11_Pos           (11)                                              /*!< PDMA_T::SWREQ: SWREQ11 Position       */
#define PDMA_SWREQ_SWREQ11_Msk           (0x1ul << PDMA_SWREQ_SWREQ11_Pos)                 /*!< PDMA_T::SWREQ: SWREQ11 Mask           */

#define PDMA_SWREQ_SWREQ12_Pos           (12)                                              /*!< PDMA_T::SWREQ: SWREQ12 Position       */
#define PDMA_SWREQ_SWREQ12_Msk           (0x1ul << PDMA_SWREQ_SWREQ12_Pos)                 /*!< PDMA_T::SWREQ: SWREQ12 Mask           */

#define PDMA_SWREQ_SWREQ13_Pos           (13)                                              /*!< PDMA_T::SWREQ: SWREQ13 Position       */
#define PDMA_SWREQ_SWREQ13_Msk           (0x1ul << PDMA_SWREQ_SWREQ13_Pos)                 /*!< PDMA_T::SWREQ: SWREQ13 Mask           */

#define PDMA_SWREQ_SWREQ14_Pos           (14)                                              /*!< PDMA_T::SWREQ: SWREQ14 Position       */
#define PDMA_SWREQ_SWREQ14_Msk           (0x1ul << PDMA_SWREQ_SWREQ14_Pos)                 /*!< PDMA_T::SWREQ: SWREQ14 Mask           */

#define PDMA_SWREQ_SWREQ15_Pos           (15)                                              /*!< PDMA_T::SWREQ: SWREQ15 Position       */
#define PDMA_SWREQ_SWREQ15_Msk           (0x1ul << PDMA_SWREQ_SWREQ15_Pos)                 /*!< PDMA_T::SWREQ: SWREQ15 Mask           */

#define PDMA_TRGSTS_REQSTSn_Pos          (0)                                               /*!< PDMA_T::TRGSTS: REQSTSn Position      */
#define PDMA_TRGSTS_REQSTSn_Msk          (0xfffful << PDMA_TRGSTS_REQSTSn_Pos)             /*!< PDMA_T::TRGSTS: REQSTSn Mask          */

#define PDMA_TRGSTS_REQSTS0_Pos          (0)                                               /*!< PDMA_T::TRGSTS: REQSTS0 Position      */
#define PDMA_TRGSTS_REQSTS0_Msk          (0x1ul << PDMA_TRGSTS_REQSTS0_Pos)                /*!< PDMA_T::TRGSTS: REQSTS0 Mask          */

#define PDMA_TRGSTS_REQSTS1_Pos          (1)                                               /*!< PDMA_T::TRGSTS: REQSTS1 Position      */
#define PDMA_TRGSTS_REQSTS1_Msk          (0x1ul << PDMA_TRGSTS_REQSTS1_Pos)                /*!< PDMA_T::TRGSTS: REQSTS1 Mask          */

#define PDMA_TRGSTS_REQSTS2_Pos          (2)                                               /*!< PDMA_T::TRGSTS: REQSTS2 Position      */
#define PDMA_TRGSTS_REQSTS2_Msk          (0x1ul << PDMA_TRGSTS_REQSTS2_Pos)                /*!< PDMA_T::TRGSTS: REQSTS2 Mask          */

#define PDMA_TRGSTS_REQSTS3_Pos          (3)                                               /*!< PDMA_T::TRGSTS: REQSTS3 Position      */
#define PDMA_TRGSTS_REQSTS3_Msk          (0x1ul << PDMA_TRGSTS_REQSTS3_Pos)                /*!< PDMA_T::TRGSTS: REQSTS3 Mask          */

#define PDMA_TRGSTS_REQSTS4_Pos          (4)                                               /*!< PDMA_T::TRGSTS: REQSTS4 Position      */
#define PDMA_TRGSTS_REQSTS4_Msk          (0x1ul << PDMA_TRGSTS_REQSTS4_Pos)                /*!< PDMA_T::TRGSTS: REQSTS4 Mask          */

#define PDMA_TRGSTS_REQSTS5_Pos          (5)                                               /*!< PDMA_T::TRGSTS: REQSTS5 Position      */
#define PDMA_TRGSTS_REQSTS5_Msk          (0x1ul << PDMA_TRGSTS_REQSTS5_Pos)                /*!< PDMA_T::TRGSTS: REQSTS5 Mask          */

#define PDMA_TRGSTS_REQSTS6_Pos          (6)                                               /*!< PDMA_T::TRGSTS: REQSTS6 Position      */
#define PDMA_TRGSTS_REQSTS6_Msk          (0x1ul << PDMA_TRGSTS_REQSTS6_Pos)                /*!< PDMA_T::TRGSTS: REQSTS6 Mask          */

#define PDMA_TRGSTS_REQSTS7_Pos          (7)                                               /*!< PDMA_T::TRGSTS: REQSTS7 Position      */
#define PDMA_TRGSTS_REQSTS7_Msk          (0x1ul << PDMA_TRGSTS_REQSTS7_Pos)                /*!< PDMA_T::TRGSTS: REQSTS7 Mask          */

#define PDMA_TRGSTS_REQSTS8_Pos          (8)                                               /*!< PDMA_T::TRGSTS: REQSTS8 Position      */
#define PDMA_TRGSTS_REQSTS8_Msk          (0x1ul << PDMA_TRGSTS_REQSTS8_Pos)                /*!< PDMA_T::TRGSTS: REQSTS8 Mask          */

#define PDMA_TRGSTS_REQSTS9_Pos          (9)                                               /*!< PDMA_T::TRGSTS: REQSTS9 Position      */
#define PDMA_TRGSTS_REQSTS9_Msk          (0x1ul << PDMA_TRGSTS_REQSTS9_Pos)                /*!< PDMA_T::TRGSTS: REQSTS9 Mask          */

#define PDMA_TRGSTS_REQSTS10_Pos         (10)                                              /*!< PDMA_T::TRGSTS: REQSTS10 Position     */
#define PDMA_TRGSTS_REQSTS10_Msk         (0x1ul << PDMA_TRGSTS_REQSTS10_Pos)               /*!< PDMA_T::TRGSTS: REQSTS10 Mask         */

#define PDMA_TRGSTS_REQSTS11_Pos         (11)                                              /*!< PDMA_T::TRGSTS: REQSTS11 Position     */
#define PDMA_TRGSTS_REQSTS11_Msk         (0x1ul << PDMA_TRGSTS_REQSTS11_Pos)               /*!< PDMA_T::TRGSTS: REQSTS11 Mask         */

#define PDMA_TRGSTS_REQSTS12_Pos         (12)                                              /*!< PDMA_T::TRGSTS: REQSTS12 Position     */
#define PDMA_TRGSTS_REQSTS12_Msk         (0x1ul << PDMA_TRGSTS_REQSTS12_Pos)               /*!< PDMA_T::TRGSTS: REQSTS12 Mask         */

#define PDMA_TRGSTS_REQSTS13_Pos         (13)                                              /*!< PDMA_T::TRGSTS: REQSTS13 Position     */
#define PDMA_TRGSTS_REQSTS13_Msk         (0x1ul << PDMA_TRGSTS_REQSTS13_Pos)               /*!< PDMA_T::TRGSTS: REQSTS13 Mask         */

#define PDMA_TRGSTS_REQSTS14_Pos         (14)                                              /*!< PDMA_T::TRGSTS: REQSTS14 Position     */
#define PDMA_TRGSTS_REQSTS14_Msk         (0x1ul << PDMA_TRGSTS_REQSTS14_Pos)               /*!< PDMA_T::TRGSTS: REQSTS14 Mask         */

#define PDMA_TRGSTS_REQSTS15_Pos         (15)                                              /*!< PDMA_T::TRGSTS: REQSTS15 Position     */
#define PDMA_TRGSTS_REQSTS15_Msk         (0x1ul << PDMA_TRGSTS_REQSTS15_Pos)               /*!< PDMA_T::TRGSTS: REQSTS15 Mask         */

#define PDMA_PRISET_FPRISETn_Pos         (0)                                               /*!< PDMA_T::PRISET: FPRISETn Position     */
#define PDMA_PRISET_FPRISETn_Msk         (0xfffful << PDMA_PRISET_FPRISETn_Pos)            /*!< PDMA_T::PRISET: FPRISETn Mask         */

#define PDMA_PRISET_FPRISET0_Pos         (0)                                               /*!< PDMA_T::PRISET: FPRISET0 Position     */
#define PDMA_PRISET_FPRISET0_Msk         (0x1ul << PDMA_PRISET_FPRISET0_Pos)               /*!< PDMA_T::PRISET: FPRISET0 Mask         */

#define PDMA_PRISET_FPRISET1_Pos         (1)                                               /*!< PDMA_T::PRISET: FPRISET1 Position     */
#define PDMA_PRISET_FPRISET1_Msk         (0x1ul << PDMA_PRISET_FPRISET1_Pos)               /*!< PDMA_T::PRISET: FPRISET1 Mask         */

#define PDMA_PRISET_FPRISET2_Pos         (2)                                               /*!< PDMA_T::PRISET: FPRISET2 Position     */
#define PDMA_PRISET_FPRISET2_Msk         (0x1ul << PDMA_PRISET_FPRISET2_Pos)               /*!< PDMA_T::PRISET: FPRISET2 Mask         */

#define PDMA_PRISET_FPRISET3_Pos         (3)                                               /*!< PDMA_T::PRISET: FPRISET3 Position     */
#define PDMA_PRISET_FPRISET3_Msk         (0x1ul << PDMA_PRISET_FPRISET3_Pos)               /*!< PDMA_T::PRISET: FPRISET3 Mask         */

#define PDMA_PRISET_FPRISET4_Pos         (4)                                               /*!< PDMA_T::PRISET: FPRISET4 Position     */
#define PDMA_PRISET_FPRISET4_Msk         (0x1ul << PDMA_PRISET_FPRISET4_Pos)               /*!< PDMA_T::PRISET: FPRISET4 Mask         */

#define PDMA_PRISET_FPRISET5_Pos         (5)                                               /*!< PDMA_T::PRISET: FPRISET5 Position     */
#define PDMA_PRISET_FPRISET5_Msk         (0x1ul << PDMA_PRISET_FPRISET5_Pos)               /*!< PDMA_T::PRISET: FPRISET5 Mask         */

#define PDMA_PRISET_FPRISET6_Pos         (6)                                               /*!< PDMA_T::PRISET: FPRISET6 Position     */
#define PDMA_PRISET_FPRISET6_Msk         (0x1ul << PDMA_PRISET_FPRISET6_Pos)               /*!< PDMA_T::PRISET: FPRISET6 Mask         */

#define PDMA_PRISET_FPRISET7_Pos         (7)                                               /*!< PDMA_T::PRISET: FPRISET7 Position     */
#define PDMA_PRISET_FPRISET7_Msk         (0x1ul << PDMA_PRISET_FPRISET7_Pos)               /*!< PDMA_T::PRISET: FPRISET7 Mask         */

#define PDMA_PRISET_FPRISET8_Pos         (8)                                               /*!< PDMA_T::PRISET: FPRISET8 Position     */
#define PDMA_PRISET_FPRISET8_Msk         (0x1ul << PDMA_PRISET_FPRISET8_Pos)               /*!< PDMA_T::PRISET: FPRISET8 Mask         */

#define PDMA_PRISET_FPRISET9_Pos         (9)                                               /*!< PDMA_T::PRISET: FPRISET9 Position     */
#define PDMA_PRISET_FPRISET9_Msk         (0x1ul << PDMA_PRISET_FPRISET9_Pos)               /*!< PDMA_T::PRISET: FPRISET9 Mask         */

#define PDMA_PRISET_FPRISET10_Pos        (10)                                              /*!< PDMA_T::PRISET: FPRISET10 Position    */
#define PDMA_PRISET_FPRISET10_Msk        (0x1ul << PDMA_PRISET_FPRISET10_Pos)              /*!< PDMA_T::PRISET: FPRISET10 Mask        */

#define PDMA_PRISET_FPRISET11_Pos        (11)                                              /*!< PDMA_T::PRISET: FPRISET11 Position    */
#define PDMA_PRISET_FPRISET11_Msk        (0x1ul << PDMA_PRISET_FPRISET11_Pos)              /*!< PDMA_T::PRISET: FPRISET11 Mask        */

#define PDMA_PRISET_FPRISET12_Pos        (12)                                              /*!< PDMA_T::PRISET: FPRISET12 Position    */
#define PDMA_PRISET_FPRISET12_Msk        (0x1ul << PDMA_PRISET_FPRISET12_Pos)              /*!< PDMA_T::PRISET: FPRISET12 Mask        */

#define PDMA_PRISET_FPRISET13_Pos        (13)                                              /*!< PDMA_T::PRISET: FPRISET13 Position    */
#define PDMA_PRISET_FPRISET13_Msk        (0x1ul << PDMA_PRISET_FPRISET13_Pos)              /*!< PDMA_T::PRISET: FPRISET13 Mask        */

#define PDMA_PRISET_FPRISET14_Pos        (14)                                              /*!< PDMA_T::PRISET: FPRISET14 Position    */
#define PDMA_PRISET_FPRISET14_Msk        (0x1ul << PDMA_PRISET_FPRISET14_Pos)              /*!< PDMA_T::PRISET: FPRISET14 Mask        */

#define PDMA_PRISET_FPRISET15_Pos        (15)                                              /*!< PDMA_T::PRISET: FPRISET15 Position    */
#define PDMA_PRISET_FPRISET15_Msk        (0x1ul << PDMA_PRISET_FPRISET15_Pos)              /*!< PDMA_T::PRISET: FPRISET15 Mask        */

#define PDMA_PRICLR_FPRICLRn_Pos         (0)                                               /*!< PDMA_T::PRICLR: FPRICLRn Position     */
#define PDMA_PRICLR_FPRICLRn_Msk         (0xfffful << PDMA_PRICLR_FPRICLRn_Pos)            /*!< PDMA_T::PRICLR: FPRICLRn Mask         */

#define PDMA_PRICLR_FPRICLR0_Pos         (0)                                               /*!< PDMA_T::PRICLR: FPRICLR0 Position     */
#define PDMA_PRICLR_FPRICLR0_Msk         (0x1ul << PDMA_PRICLR_FPRICLR0_Pos)               /*!< PDMA_T::PRICLR: FPRICLR0 Mask         */

#define PDMA_PRICLR_FPRICLR1_Pos         (1)                                               /*!< PDMA_T::PRICLR: FPRICLR1 Position     */
#define PDMA_PRICLR_FPRICLR1_Msk         (0x1ul << PDMA_PRICLR_FPRICLR1_Pos)               /*!< PDMA_T::PRICLR: FPRICLR1 Mask         */

#define PDMA_PRICLR_FPRICLR2_Pos         (2)                                               /*!< PDMA_T::PRICLR: FPRICLR2 Position     */
#define PDMA_PRICLR_FPRICLR2_Msk         (0x1ul << PDMA_PRICLR_FPRICLR2_Pos)               /*!< PDMA_T::PRICLR: FPRICLR2 Mask         */

#define PDMA_PRICLR_FPRICLR3_Pos         (3)                                               /*!< PDMA_T::PRICLR: FPRICLR3 Position     */
#define PDMA_PRICLR_FPRICLR3_Msk         (0x1ul << PDMA_PRICLR_FPRICLR3_Pos)               /*!< PDMA_T::PRICLR: FPRICLR3 Mask         */

#define PDMA_PRICLR_FPRICLR4_Pos         (4)                                               /*!< PDMA_T::PRICLR: FPRICLR4 Position     */
#define PDMA_PRICLR_FPRICLR4_Msk         (0x1ul << PDMA_PRICLR_FPRICLR4_Pos)               /*!< PDMA_T::PRICLR: FPRICLR4 Mask         */

#define PDMA_PRICLR_FPRICLR5_Pos         (5)                                               /*!< PDMA_T::PRICLR: FPRICLR5 Position     */
#define PDMA_PRICLR_FPRICLR5_Msk         (0x1ul << PDMA_PRICLR_FPRICLR5_Pos)               /*!< PDMA_T::PRICLR: FPRICLR5 Mask         */

#define PDMA_PRICLR_FPRICLR6_Pos         (6)                                               /*!< PDMA_T::PRICLR: FPRICLR6 Position     */
#define PDMA_PRICLR_FPRICLR6_Msk         (0x1ul << PDMA_PRICLR_FPRICLR6_Pos)               /*!< PDMA_T::PRICLR: FPRICLR6 Mask         */

#define PDMA_PRICLR_FPRICLR7_Pos         (7)                                               /*!< PDMA_T::PRICLR: FPRICLR7 Position     */
#define PDMA_PRICLR_FPRICLR7_Msk         (0x1ul << PDMA_PRICLR_FPRICLR7_Pos)               /*!< PDMA_T::PRICLR: FPRICLR7 Mask         */

#define PDMA_PRICLR_FPRICLR8_Pos         (8)                                               /*!< PDMA_T::PRICLR: FPRICLR8 Position     */
#define PDMA_PRICLR_FPRICLR8_Msk         (0x1ul << PDMA_PRICLR_FPRICLR8_Pos)               /*!< PDMA_T::PRICLR: FPRICLR8 Mask         */

#define PDMA_PRICLR_FPRICLR9_Pos         (9)                                               /*!< PDMA_T::PRICLR: FPRICLR9 Position     */
#define PDMA_PRICLR_FPRICLR9_Msk         (0x1ul << PDMA_PRICLR_FPRICLR9_Pos)               /*!< PDMA_T::PRICLR: FPRICLR9 Mask         */

#define PDMA_PRICLR_FPRICLR10_Pos        (10)                                              /*!< PDMA_T::PRICLR: FPRICLR10 Position    */
#define PDMA_PRICLR_FPRICLR10_Msk        (0x1ul << PDMA_PRICLR_FPRICLR10_Pos)              /*!< PDMA_T::PRICLR: FPRICLR10 Mask        */

#define PDMA_PRICLR_FPRICLR11_Pos        (11)                                              /*!< PDMA_T::PRICLR: FPRICLR11 Position    */
#define PDMA_PRICLR_FPRICLR11_Msk        (0x1ul << PDMA_PRICLR_FPRICLR11_Pos)              /*!< PDMA_T::PRICLR: FPRICLR11 Mask        */

#define PDMA_PRICLR_FPRICLR12_Pos        (12)                                              /*!< PDMA_T::PRICLR: FPRICLR12 Position    */
#define PDMA_PRICLR_FPRICLR12_Msk        (0x1ul << PDMA_PRICLR_FPRICLR12_Pos)              /*!< PDMA_T::PRICLR: FPRICLR12 Mask        */

#define PDMA_PRICLR_FPRICLR13_Pos        (13)                                              /*!< PDMA_T::PRICLR: FPRICLR13 Position    */
#define PDMA_PRICLR_FPRICLR13_Msk        (0x1ul << PDMA_PRICLR_FPRICLR13_Pos)              /*!< PDMA_T::PRICLR: FPRICLR13 Mask        */

#define PDMA_PRICLR_FPRICLR14_Pos        (14)                                              /*!< PDMA_T::PRICLR: FPRICLR14 Position    */
#define PDMA_PRICLR_FPRICLR14_Msk        (0x1ul << PDMA_PRICLR_FPRICLR14_Pos)              /*!< PDMA_T::PRICLR: FPRICLR14 Mask        */

#define PDMA_PRICLR_FPRICLR15_Pos        (15)                                              /*!< PDMA_T::PRICLR: FPRICLR15 Position    */
#define PDMA_PRICLR_FPRICLR15_Msk        (0x1ul << PDMA_PRICLR_FPRICLR15_Pos)              /*!< PDMA_T::PRICLR: FPRICLR15 Mask        */

#define PDMA_INTEN_INTENn_Pos            (0)                                               /*!< PDMA_T::INTEN: INTENn Position        */
#define PDMA_INTEN_INTENn_Msk            (0xfffful << PDMA_INTEN_INTENn_Pos)               /*!< PDMA_T::INTEN: INTENn Mask            */

#define PDMA_INTEN_INTEN0_Pos            (0)                                               /*!< PDMA_T::INTEN: INTEN0 Position        */
#define PDMA_INTEN_INTEN0_Msk            (0x1ul << PDMA_INTEN_INTEN0_Pos)                  /*!< PDMA_T::INTEN: INTEN0 Mask            */

#define PDMA_INTEN_INTEN1_Pos            (1)                                               /*!< PDMA_T::INTEN: INTEN1 Position        */
#define PDMA_INTEN_INTEN1_Msk            (0x1ul << PDMA_INTEN_INTEN1_Pos)                  /*!< PDMA_T::INTEN: INTEN1 Mask            */

#define PDMA_INTEN_INTEN2_Pos            (2)                                               /*!< PDMA_T::INTEN: INTEN2 Position        */
#define PDMA_INTEN_INTEN2_Msk            (0x1ul << PDMA_INTEN_INTEN2_Pos)                  /*!< PDMA_T::INTEN: INTEN2 Mask            */

#define PDMA_INTEN_INTEN3_Pos            (3)                                               /*!< PDMA_T::INTEN: INTEN3 Position        */
#define PDMA_INTEN_INTEN3_Msk            (0x1ul << PDMA_INTEN_INTEN3_Pos)                  /*!< PDMA_T::INTEN: INTEN3 Mask            */

#define PDMA_INTEN_INTEN4_Pos            (4)                                               /*!< PDMA_T::INTEN: INTEN4 Position        */
#define PDMA_INTEN_INTEN4_Msk            (0x1ul << PDMA_INTEN_INTEN4_Pos)                  /*!< PDMA_T::INTEN: INTEN4 Mask            */

#define PDMA_INTEN_INTEN5_Pos            (5)                                               /*!< PDMA_T::INTEN: INTEN5 Position        */
#define PDMA_INTEN_INTEN5_Msk            (0x1ul << PDMA_INTEN_INTEN5_Pos)                  /*!< PDMA_T::INTEN: INTEN5 Mask            */

#define PDMA_INTEN_INTEN6_Pos            (6)                                               /*!< PDMA_T::INTEN: INTEN6 Position        */
#define PDMA_INTEN_INTEN6_Msk            (0x1ul << PDMA_INTEN_INTEN6_Pos)                  /*!< PDMA_T::INTEN: INTEN6 Mask            */

#define PDMA_INTEN_INTEN7_Pos            (7)                                               /*!< PDMA_T::INTEN: INTEN7 Position        */
#define PDMA_INTEN_INTEN7_Msk            (0x1ul << PDMA_INTEN_INTEN7_Pos)                  /*!< PDMA_T::INTEN: INTEN7 Mask            */

#define PDMA_INTEN_INTEN8_Pos            (8)                                               /*!< PDMA_T::INTEN: INTEN8 Position        */
#define PDMA_INTEN_INTEN8_Msk            (0x1ul << PDMA_INTEN_INTEN8_Pos)                  /*!< PDMA_T::INTEN: INTEN8 Mask            */

#define PDMA_INTEN_INTEN9_Pos            (9)                                               /*!< PDMA_T::INTEN: INTEN9 Position        */
#define PDMA_INTEN_INTEN9_Msk            (0x1ul << PDMA_INTEN_INTEN9_Pos)                  /*!< PDMA_T::INTEN: INTEN9 Mask            */

#define PDMA_INTEN_INTEN10_Pos           (10)                                              /*!< PDMA_T::INTEN: INTEN10 Position       */
#define PDMA_INTEN_INTEN10_Msk           (0x1ul << PDMA_INTEN_INTEN10_Pos)                 /*!< PDMA_T::INTEN: INTEN10 Mask           */

#define PDMA_INTEN_INTEN11_Pos           (11)                                              /*!< PDMA_T::INTEN: INTEN11 Position       */
#define PDMA_INTEN_INTEN11_Msk           (0x1ul << PDMA_INTEN_INTEN11_Pos)                 /*!< PDMA_T::INTEN: INTEN11 Mask           */

#define PDMA_INTEN_INTEN12_Pos           (12)                                              /*!< PDMA_T::INTEN: INTEN12 Position       */
#define PDMA_INTEN_INTEN12_Msk           (0x1ul << PDMA_INTEN_INTEN12_Pos)                 /*!< PDMA_T::INTEN: INTEN12 Mask           */

#define PDMA_INTEN_INTEN13_Pos           (13)                                              /*!< PDMA_T::INTEN: INTEN13 Position       */
#define PDMA_INTEN_INTEN13_Msk           (0x1ul << PDMA_INTEN_INTEN13_Pos)                 /*!< PDMA_T::INTEN: INTEN13 Mask           */

#define PDMA_INTEN_INTEN14_Pos           (14)                                              /*!< PDMA_T::INTEN: INTEN14 Position       */
#define PDMA_INTEN_INTEN14_Msk           (0x1ul << PDMA_INTEN_INTEN14_Pos)                 /*!< PDMA_T::INTEN: INTEN14 Mask           */

#define PDMA_INTEN_INTEN15_Pos           (15)                                              /*!< PDMA_T::INTEN: INTEN15 Position       */
#define PDMA_INTEN_INTEN15_Msk           (0x1ul << PDMA_INTEN_INTEN15_Pos)                 /*!< PDMA_T::INTEN: INTEN15 Mask           */

#define PDMA_INTSTS_ABTIF_Pos            (0)                                               /*!< PDMA_T::INTSTS: ABTIF Position        */
#define PDMA_INTSTS_ABTIF_Msk            (0x1ul << PDMA_INTSTS_ABTIF_Pos)                  /*!< PDMA_T::INTSTS: ABTIF Mask            */

#define PDMA_INTSTS_TDIF_Pos             (1)                                               /*!< PDMA_T::INTSTS: TDIF Position         */
#define PDMA_INTSTS_TDIF_Msk             (0x1ul << PDMA_INTSTS_TDIF_Pos)                   /*!< PDMA_T::INTSTS: TDIF Mask             */

#define PDMA_INTSTS_ALIGNF_Pos           (2)                                               /*!< PDMA_T::INTSTS: ALIGNF Position       */
#define PDMA_INTSTS_ALIGNF_Msk           (0x1ul << PDMA_INTSTS_ALIGNF_Pos)                 /*!< PDMA_T::INTSTS: ALIGNF Mask           */

#define PDMA_INTSTS_REQTOFn_Pos          (8)                                               /*!< PDMA_T::INTSTS: REQTOFn Position       */
#define PDMA_INTSTS_REQTOFn_Msk          (PDMA_CH_Msk << PDMA_INTSTS_REQTOFn_Pos)          /*!< PDMA_T::INTSTS: REQTOFn Mask           */

#define PDMA_INTSTS_REQTOF0_Pos          (8)                                               /*!< PDMA_T::INTSTS: REQTOF0 Position      */
#define PDMA_INTSTS_REQTOF0_Msk          (0x1ul << PDMA_INTSTS_REQTOF0_Pos)                /*!< PDMA_T::INTSTS: REQTOF0 Mask          */

#define PDMA_INTSTS_REQTOF1_Pos          (9)                                               /*!< PDMA_T::INTSTS: REQTOF1 Position      */
#define PDMA_INTSTS_REQTOF1_Msk          (0x1ul << PDMA_INTSTS_REQTOF1_Pos)                /*!< PDMA_T::INTSTS: REQTOF1 Mask          */

#define PDMA_INTSTS_REQTOF2_Pos          (10)                                              /*!< PDMA_T::INTSTS: REQTOF2 Position      */
#define PDMA_INTSTS_REQTOF2_Msk          (0x1ul << PDMA_INTSTS_REQTOF2_Pos)                /*!< PDMA_T::INTSTS: REQTOF2 Mask          */

#define PDMA_INTSTS_REQTOF3_Pos          (11)                                              /*!< PDMA_T::INTSTS: REQTOF3 Position      */
#define PDMA_INTSTS_REQTOF3_Msk          (0x1ul << PDMA_INTSTS_REQTOF3_Pos)                /*!< PDMA_T::INTSTS: REQTOF3 Mask          */

#define PDMA_INTSTS_REQTOF4_Pos          (12)                                              /*!< PDMA_T::INTSTS: REQTOF4 Position      */
#define PDMA_INTSTS_REQTOF4_Msk          (0x1ul << PDMA_INTSTS_REQTOF4_Pos)                /*!< PDMA_T::INTSTS: REQTOF4 Mask          */

#define PDMA_INTSTS_REQTOF5_Pos          (13)                                              /*!< PDMA_T::INTSTS: REQTOF5 Position      */
#define PDMA_INTSTS_REQTOF5_Msk          (0x1ul << PDMA_INTSTS_REQTOF5_Pos)                /*!< PDMA_T::INTSTS: REQTOF5 Mask          */

#define PDMA_INTSTS_REQTOF6_Pos          (14)                                              /*!< PDMA_T::INTSTS: REQTOF6 Position      */
#define PDMA_INTSTS_REQTOF6_Msk          (0x1ul << PDMA_INTSTS_REQTOF6_Pos)                /*!< PDMA_T::INTSTS: REQTOF6 Mask          */

#define PDMA_INTSTS_REQTOF7_Pos          (15)                                              /*!< PDMA_T::INTSTS: REQTOF7 Position      */
#define PDMA_INTSTS_REQTOF7_Msk          (0x1ul << PDMA_INTSTS_REQTOF7_Pos)                /*!< PDMA_T::INTSTS: REQTOF7 Mask          */

#define PDMA_INTSTS_REQTOF8_Pos          (16)                                              /*!< PDMA_T::INTSTS: REQTOF8 Position      */
#define PDMA_INTSTS_REQTOF8_Msk          (0x1ul << PDMA_INTSTS_REQTOF8_Pos)                /*!< PDMA_T::INTSTS: REQTOF8 Mask          */

#define PDMA_INTSTS_REQTOF9_Pos          (17)                                              /*!< PDMA_T::INTSTS: REQTOF9 Position      */
#define PDMA_INTSTS_REQTOF9_Msk          (0x1ul << PDMA_INTSTS_REQTOF9_Pos)                /*!< PDMA_T::INTSTS: REQTOF9 Mask          */

#define PDMA_INTSTS_REQTOF10_Pos         (18)                                              /*!< PDMA_T::INTSTS: REQTOF10 Position     */
#define PDMA_INTSTS_REQTOF10_Msk         (0x1ul << PDMA_INTSTS_REQTOF10_Pos)               /*!< PDMA_T::INTSTS: REQTOF10 Mask         */

#define PDMA_INTSTS_REQTOF11_Pos         (19)                                              /*!< PDMA_T::INTSTS: REQTOF11 Position     */
#define PDMA_INTSTS_REQTOF11_Msk         (0x1ul << PDMA_INTSTS_REQTOF11_Pos)               /*!< PDMA_T::INTSTS: REQTOF11 Mask         */

#define PDMA_INTSTS_REQTOF12_Pos         (20)                                              /*!< PDMA_T::INTSTS: REQTOF12 Position     */
#define PDMA_INTSTS_REQTOF12_Msk         (0x1ul << PDMA_INTSTS_REQTOF12_Pos)               /*!< PDMA_T::INTSTS: REQTOF12 Mask         */

#define PDMA_INTSTS_REQTOF13_Pos         (21)                                              /*!< PDMA_T::INTSTS: REQTOF13 Position     */
#define PDMA_INTSTS_REQTOF13_Msk         (0x1ul << PDMA_INTSTS_REQTOF13_Pos)               /*!< PDMA_T::INTSTS: REQTOF13 Mask         */

#define PDMA_INTSTS_REQTOF14_Pos         (22)                                              /*!< PDMA_T::INTSTS: REQTOF14 Position     */
#define PDMA_INTSTS_REQTOF14_Msk         (0x1ul << PDMA_INTSTS_REQTOF14_Pos)               /*!< PDMA_T::INTSTS: REQTOF14 Mask         */

#define PDMA_INTSTS_REQTOF15_Pos         (23)                                              /*!< PDMA_T::INTSTS: REQTOF15 Position     */
#define PDMA_INTSTS_REQTOF15_Msk         (0x1ul << PDMA_INTSTS_REQTOF15_Pos)               /*!< PDMA_T::INTSTS: REQTOF15 Mask         */

#define PDMA_ABTSTS_ABTIFn_Pos           (0)                                               /*!< PDMA_T::ABTSTS: ABTIFn Position        */
#define PDMA_ABTSTS_ABTIFn_Msk           (PDMA_CH_Msk << PDMA_ABTSTS_ABTIFn_Pos)           /*!< PDMA_T::ABTSTS: ABTIFn Mask            */

#define PDMA_ABTSTS_ABTIF0_Pos           (0)                                               /*!< PDMA_T::ABTSTS: ABTIF0 Position       */
#define PDMA_ABTSTS_ABTIF0_Msk           (0x1ul << PDMA_ABTSTS_ABTIF0_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF0 Mask           */

#define PDMA_ABTSTS_ABTIF1_Pos           (1)                                               /*!< PDMA_T::ABTSTS: ABTIF1 Position       */
#define PDMA_ABTSTS_ABTIF1_Msk           (0x1ul << PDMA_ABTSTS_ABTIF1_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF1 Mask           */

#define PDMA_ABTSTS_ABTIF2_Pos           (2)                                               /*!< PDMA_T::ABTSTS: ABTIF2 Position       */
#define PDMA_ABTSTS_ABTIF2_Msk           (0x1ul << PDMA_ABTSTS_ABTIF2_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF2 Mask           */

#define PDMA_ABTSTS_ABTIF3_Pos           (3)                                               /*!< PDMA_T::ABTSTS: ABTIF3 Position       */
#define PDMA_ABTSTS_ABTIF3_Msk           (0x1ul << PDMA_ABTSTS_ABTIF3_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF3 Mask           */

#define PDMA_ABTSTS_ABTIF4_Pos           (4)                                               /*!< PDMA_T::ABTSTS: ABTIF4 Position       */
#define PDMA_ABTSTS_ABTIF4_Msk           (0x1ul << PDMA_ABTSTS_ABTIF4_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF4 Mask           */

#define PDMA_ABTSTS_ABTIF5_Pos           (5)                                               /*!< PDMA_T::ABTSTS: ABTIF5 Position       */
#define PDMA_ABTSTS_ABTIF5_Msk           (0x1ul << PDMA_ABTSTS_ABTIF5_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF5 Mask           */

#define PDMA_ABTSTS_ABTIF6_Pos           (6)                                               /*!< PDMA_T::ABTSTS: ABTIF6 Position       */
#define PDMA_ABTSTS_ABTIF6_Msk           (0x1ul << PDMA_ABTSTS_ABTIF6_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF6 Mask           */

#define PDMA_ABTSTS_ABTIF7_Pos           (7)                                               /*!< PDMA_T::ABTSTS: ABTIF7 Position       */
#define PDMA_ABTSTS_ABTIF7_Msk           (0x1ul << PDMA_ABTSTS_ABTIF7_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF7 Mask           */

#define PDMA_ABTSTS_ABTIF8_Pos           (8)                                               /*!< PDMA_T::ABTSTS: ABTIF8 Position       */
#define PDMA_ABTSTS_ABTIF8_Msk           (0x1ul << PDMA_ABTSTS_ABTIF8_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF8 Mask           */

#define PDMA_ABTSTS_ABTIF9_Pos           (9)                                               /*!< PDMA_T::ABTSTS: ABTIF9 Position       */
#define PDMA_ABTSTS_ABTIF9_Msk           (0x1ul << PDMA_ABTSTS_ABTIF9_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF9 Mask           */

#define PDMA_ABTSTS_ABTIF10_Pos          (10)                                              /*!< PDMA_T::ABTSTS: ABTIF10 Position      */
#define PDMA_ABTSTS_ABTIF10_Msk          (0x1ul << PDMA_ABTSTS_ABTIF10_Pos)                /*!< PDMA_T::ABTSTS: ABTIF10 Mask          */

#define PDMA_ABTSTS_ABTIF11_Pos          (11)                                              /*!< PDMA_T::ABTSTS: ABTIF11 Position      */
#define PDMA_ABTSTS_ABTIF11_Msk          (0x1ul << PDMA_ABTSTS_ABTIF11_Pos)                /*!< PDMA_T::ABTSTS: ABTIF11 Mask          */

#define PDMA_ABTSTS_ABTIF12_Pos          (12)                                              /*!< PDMA_T::ABTSTS: ABTIF12 Position      */
#define PDMA_ABTSTS_ABTIF12_Msk          (0x1ul << PDMA_ABTSTS_ABTIF12_Pos)                /*!< PDMA_T::ABTSTS: ABTIF12 Mask          */

#define PDMA_ABTSTS_ABTIF13_Pos          (13)                                              /*!< PDMA_T::ABTSTS: ABTIF13 Position      */
#define PDMA_ABTSTS_ABTIF13_Msk          (0x1ul << PDMA_ABTSTS_ABTIF13_Pos)                /*!< PDMA_T::ABTSTS: ABTIF13 Mask          */

#define PDMA_ABTSTS_ABTIF14_Pos          (14)                                              /*!< PDMA_T::ABTSTS: ABTIF14 Position      */
#define PDMA_ABTSTS_ABTIF14_Msk          (0x1ul << PDMA_ABTSTS_ABTIF14_Pos)                /*!< PDMA_T::ABTSTS: ABTIF14 Mask          */

#define PDMA_ABTSTS_ABTIF15_Pos          (15)                                              /*!< PDMA_T::ABTSTS: ABTIF15 Position      */
#define PDMA_ABTSTS_ABTIF15_Msk          (0x1ul << PDMA_ABTSTS_ABTIF15_Pos)                /*!< PDMA_T::ABTSTS: ABTIF15 Mask          */

#define PDMA_TDSTS_TDIFn_Pos             (0)                                               /*!< PDMA_T::TDSTS: TDIFn Position          */
#define PDMA_TDSTS_TDIFn_Msk             (PDMA_CH_Msk << PDMA_TDSTS_TDIFn_Pos)             /*!< PDMA_T::TDSTS: TDIFn Mask              */

#define PDMA_TDSTS_TDIF0_Pos             (0)                                               /*!< PDMA_T::TDSTS: TDIF0 Position         */
#define PDMA_TDSTS_TDIF0_Msk             (0x1ul << PDMA_TDSTS_TDIF0_Pos)                   /*!< PDMA_T::TDSTS: TDIF0 Mask             */

#define PDMA_TDSTS_TDIF1_Pos             (1)                                               /*!< PDMA_T::TDSTS: TDIF1 Position         */
#define PDMA_TDSTS_TDIF1_Msk             (0x1ul << PDMA_TDSTS_TDIF1_Pos)                   /*!< PDMA_T::TDSTS: TDIF1 Mask             */

#define PDMA_TDSTS_TDIF2_Pos             (2)                                               /*!< PDMA_T::TDSTS: TDIF2 Position         */
#define PDMA_TDSTS_TDIF2_Msk             (0x1ul << PDMA_TDSTS_TDIF2_Pos)                   /*!< PDMA_T::TDSTS: TDIF2 Mask             */

#define PDMA_TDSTS_TDIF3_Pos             (3)                                               /*!< PDMA_T::TDSTS: TDIF3 Position         */
#define PDMA_TDSTS_TDIF3_Msk             (0x1ul << PDMA_TDSTS_TDIF3_Pos)                   /*!< PDMA_T::TDSTS: TDIF3 Mask             */

#define PDMA_TDSTS_TDIF4_Pos             (4)                                               /*!< PDMA_T::TDSTS: TDIF4 Position         */
#define PDMA_TDSTS_TDIF4_Msk             (0x1ul << PDMA_TDSTS_TDIF4_Pos)                   /*!< PDMA_T::TDSTS: TDIF4 Mask             */

#define PDMA_TDSTS_TDIF5_Pos             (5)                                               /*!< PDMA_T::TDSTS: TDIF5 Position         */
#define PDMA_TDSTS_TDIF5_Msk             (0x1ul << PDMA_TDSTS_TDIF5_Pos)                   /*!< PDMA_T::TDSTS: TDIF5 Mask             */

#define PDMA_TDSTS_TDIF6_Pos             (6)                                               /*!< PDMA_T::TDSTS: TDIF6 Position         */
#define PDMA_TDSTS_TDIF6_Msk             (0x1ul << PDMA_TDSTS_TDIF6_Pos)                   /*!< PDMA_T::TDSTS: TDIF6 Mask             */

#define PDMA_TDSTS_TDIF7_Pos             (7)                                               /*!< PDMA_T::TDSTS: TDIF7 Position         */
#define PDMA_TDSTS_TDIF7_Msk             (0x1ul << PDMA_TDSTS_TDIF7_Pos)                   /*!< PDMA_T::TDSTS: TDIF7 Mask             */

#define PDMA_TDSTS_TDIF8_Pos             (8)                                               /*!< PDMA_T::TDSTS: TDIF8 Position         */
#define PDMA_TDSTS_TDIF8_Msk             (0x1ul << PDMA_TDSTS_TDIF8_Pos)                   /*!< PDMA_T::TDSTS: TDIF8 Mask             */

#define PDMA_TDSTS_TDIF9_Pos             (9)                                               /*!< PDMA_T::TDSTS: TDIF9 Position         */
#define PDMA_TDSTS_TDIF9_Msk             (0x1ul << PDMA_TDSTS_TDIF9_Pos)                   /*!< PDMA_T::TDSTS: TDIF9 Mask             */

#define PDMA_TDSTS_TDIF10_Pos            (10)                                              /*!< PDMA_T::TDSTS: TDIF10 Position        */
#define PDMA_TDSTS_TDIF10_Msk            (0x1ul << PDMA_TDSTS_TDIF10_Pos)                  /*!< PDMA_T::TDSTS: TDIF10 Mask            */

#define PDMA_TDSTS_TDIF11_Pos            (11)                                              /*!< PDMA_T::TDSTS: TDIF11 Position        */
#define PDMA_TDSTS_TDIF11_Msk            (0x1ul << PDMA_TDSTS_TDIF11_Pos)                  /*!< PDMA_T::TDSTS: TDIF11 Mask            */

#define PDMA_TDSTS_TDIF12_Pos            (12)                                              /*!< PDMA_T::TDSTS: TDIF12 Position        */
#define PDMA_TDSTS_TDIF12_Msk            (0x1ul << PDMA_TDSTS_TDIF12_Pos)                  /*!< PDMA_T::TDSTS: TDIF12 Mask            */

#define PDMA_TDSTS_TDIF13_Pos            (13)                                              /*!< PDMA_T::TDSTS: TDIF13 Position        */
#define PDMA_TDSTS_TDIF13_Msk            (0x1ul << PDMA_TDSTS_TDIF13_Pos)                  /*!< PDMA_T::TDSTS: TDIF13 Mask            */

#define PDMA_TDSTS_TDIF14_Pos            (14)                                              /*!< PDMA_T::TDSTS: TDIF14 Position        */
#define PDMA_TDSTS_TDIF14_Msk            (0x1ul << PDMA_TDSTS_TDIF14_Pos)                  /*!< PDMA_T::TDSTS: TDIF14 Mask            */

#define PDMA_TDSTS_TDIF15_Pos            (15)                                              /*!< PDMA_T::TDSTS: TDIF15 Position        */
#define PDMA_TDSTS_TDIF15_Msk            (0x1ul << PDMA_TDSTS_TDIF15_Pos)                  /*!< PDMA_T::TDSTS: TDIF15 Mask            */

#define PDMA_ALIGN_ALIGNn_Pos            (0)                                               /*!< PDMA_T::ALIGN: ALIGNn Position         */
#define PDMA_ALIGN_ALIGNn_Msk            (PDMA_CH_Msk << PDMA_ALIGN_ALIGNn_Pos)            /*!< PDMA_T::ALIGN: ALIGNn Mask             */

#define PDMA_ALIGN_ALIGN0_Pos            (0)                                               /*!< PDMA_T::ALIGN: ALIGN0 Position        */
#define PDMA_ALIGN_ALIGN0_Msk            (0x1ul << PDMA_ALIGN_ALIGN0_Pos)                  /*!< PDMA_T::ALIGN: ALIGN0 Mask            */

#define PDMA_ALIGN_ALIGN1_Pos            (1)                                               /*!< PDMA_T::ALIGN: ALIGN1 Position        */
#define PDMA_ALIGN_ALIGN1_Msk            (0x1ul << PDMA_ALIGN_ALIGN1_Pos)                  /*!< PDMA_T::ALIGN: ALIGN1 Mask            */

#define PDMA_ALIGN_ALIGN2_Pos            (2)                                               /*!< PDMA_T::ALIGN: ALIGN2 Position        */
#define PDMA_ALIGN_ALIGN2_Msk            (0x1ul << PDMA_ALIGN_ALIGN2_Pos)                  /*!< PDMA_T::ALIGN: ALIGN2 Mask            */

#define PDMA_ALIGN_ALIGN3_Pos            (3)                                               /*!< PDMA_T::ALIGN: ALIGN3 Position        */
#define PDMA_ALIGN_ALIGN3_Msk            (0x1ul << PDMA_ALIGN_ALIGN3_Pos)                  /*!< PDMA_T::ALIGN: ALIGN3 Mask            */

#define PDMA_ALIGN_ALIGN4_Pos            (4)                                               /*!< PDMA_T::ALIGN: ALIGN4 Position        */
#define PDMA_ALIGN_ALIGN4_Msk            (0x1ul << PDMA_ALIGN_ALIGN4_Pos)                  /*!< PDMA_T::ALIGN: ALIGN4 Mask            */

#define PDMA_ALIGN_ALIGN5_Pos            (5)                                               /*!< PDMA_T::ALIGN: ALIGN5 Position        */
#define PDMA_ALIGN_ALIGN5_Msk            (0x1ul << PDMA_ALIGN_ALIGN5_Pos)                  /*!< PDMA_T::ALIGN: ALIGN5 Mask            */

#define PDMA_ALIGN_ALIGN6_Pos            (6)                                               /*!< PDMA_T::ALIGN: ALIGN6 Position        */
#define PDMA_ALIGN_ALIGN6_Msk            (0x1ul << PDMA_ALIGN_ALIGN6_Pos)                  /*!< PDMA_T::ALIGN: ALIGN6 Mask            */

#define PDMA_ALIGN_ALIGN7_Pos            (7)                                               /*!< PDMA_T::ALIGN: ALIGN7 Position        */
#define PDMA_ALIGN_ALIGN7_Msk            (0x1ul << PDMA_ALIGN_ALIGN7_Pos)                  /*!< PDMA_T::ALIGN: ALIGN7 Mask            */

#define PDMA_ALIGN_ALIGN8_Pos            (8)                                               /*!< PDMA_T::ALIGN: ALIGN8 Position        */
#define PDMA_ALIGN_ALIGN8_Msk            (0x1ul << PDMA_ALIGN_ALIGN8_Pos)                  /*!< PDMA_T::ALIGN: ALIGN8 Mask            */

#define PDMA_ALIGN_ALIGN9_Pos            (9)                                               /*!< PDMA_T::ALIGN: ALIGN9 Position        */
#define PDMA_ALIGN_ALIGN9_Msk            (0x1ul << PDMA_ALIGN_ALIGN9_Pos)                  /*!< PDMA_T::ALIGN: ALIGN9 Mask            */

#define PDMA_ALIGN_ALIGN10_Pos           (10)                                              /*!< PDMA_T::ALIGN: ALIGN10 Position       */
#define PDMA_ALIGN_ALIGN10_Msk           (0x1ul << PDMA_ALIGN_ALIGN10_Pos)                 /*!< PDMA_T::ALIGN: ALIGN10 Mask           */

#define PDMA_ALIGN_ALIGN11_Pos           (11)                                              /*!< PDMA_T::ALIGN: ALIGN11 Position       */
#define PDMA_ALIGN_ALIGN11_Msk           (0x1ul << PDMA_ALIGN_ALIGN11_Pos)                 /*!< PDMA_T::ALIGN: ALIGN11 Mask           */

#define PDMA_ALIGN_ALIGN12_Pos           (12)                                              /*!< PDMA_T::ALIGN: ALIGN12 Position       */
#define PDMA_ALIGN_ALIGN12_Msk           (0x1ul << PDMA_ALIGN_ALIGN12_Pos)                 /*!< PDMA_T::ALIGN: ALIGN12 Mask           */

#define PDMA_ALIGN_ALIGN13_Pos           (13)                                              /*!< PDMA_T::ALIGN: ALIGN13 Position       */
#define PDMA_ALIGN_ALIGN13_Msk           (0x1ul << PDMA_ALIGN_ALIGN13_Pos)                 /*!< PDMA_T::ALIGN: ALIGN13 Mask           */

#define PDMA_ALIGN_ALIGN14_Pos           (14)                                              /*!< PDMA_T::ALIGN: ALIGN14 Position       */
#define PDMA_ALIGN_ALIGN14_Msk           (0x1ul << PDMA_ALIGN_ALIGN14_Pos)                 /*!< PDMA_T::ALIGN: ALIGN14 Mask           */

#define PDMA_ALIGN_ALIGN15_Pos           (15)                                              /*!< PDMA_T::ALIGN: ALIGN15 Position       */
#define PDMA_ALIGN_ALIGN15_Msk           (0x1ul << PDMA_ALIGN_ALIGN15_Pos)                 /*!< PDMA_T::ALIGN: ALIGN15 Mask           */

#define PDMA_TACTSTS_TXACTFn_Pos         (0)                                               /*!< PDMA_T::TACTSTS: TXACTFn Position      */
#define PDMA_TACTSTS_TXACTFn_Msk         (PDMA_CH_Msk << PDMA_TACTSTS_TXACTFn_Pos)         /*!< PDMA_T::TACTSTS: TXACTFn Mask          */

#define PDMA_TACTSTS_TXACTF0_Pos         (0)                                               /*!< PDMA_T::TACTSTS: TXACTF0 Position     */
#define PDMA_TACTSTS_TXACTF0_Msk         (0x1ul << PDMA_TACTSTS_TXACTF0_Pos)               /*!< PDMA_T::TACTSTS: TXACTF0 Mask         */

#define PDMA_TACTSTS_TXACTF1_Pos         (1)                                               /*!< PDMA_T::TACTSTS: TXACTF1 Position     */
#define PDMA_TACTSTS_TXACTF1_Msk         (0x1ul << PDMA_TACTSTS_TXACTF1_Pos)               /*!< PDMA_T::TACTSTS: TXACTF1 Mask         */

#define PDMA_TACTSTS_TXACTF2_Pos         (2)                                               /*!< PDMA_T::TACTSTS: TXACTF2 Position     */
#define PDMA_TACTSTS_TXACTF2_Msk         (0x1ul << PDMA_TACTSTS_TXACTF2_Pos)               /*!< PDMA_T::TACTSTS: TXACTF2 Mask         */

#define PDMA_TACTSTS_TXACTF3_Pos         (3)                                               /*!< PDMA_T::TACTSTS: TXACTF3 Position     */
#define PDMA_TACTSTS_TXACTF3_Msk         (0x1ul << PDMA_TACTSTS_TXACTF3_Pos)               /*!< PDMA_T::TACTSTS: TXACTF3 Mask         */

#define PDMA_TACTSTS_TXACTF4_Pos         (4)                                               /*!< PDMA_T::TACTSTS: TXACTF4 Position     */
#define PDMA_TACTSTS_TXACTF4_Msk         (0x1ul << PDMA_TACTSTS_TXACTF4_Pos)               /*!< PDMA_T::TACTSTS: TXACTF4 Mask         */

#define PDMA_TACTSTS_TXACTF5_Pos         (5)                                               /*!< PDMA_T::TACTSTS: TXACTF5 Position     */
#define PDMA_TACTSTS_TXACTF5_Msk         (0x1ul << PDMA_TACTSTS_TXACTF5_Pos)               /*!< PDMA_T::TACTSTS: TXACTF5 Mask         */

#define PDMA_TACTSTS_TXACTF6_Pos         (6)                                               /*!< PDMA_T::TACTSTS: TXACTF6 Position     */
#define PDMA_TACTSTS_TXACTF6_Msk         (0x1ul << PDMA_TACTSTS_TXACTF6_Pos)               /*!< PDMA_T::TACTSTS: TXACTF6 Mask         */

#define PDMA_TACTSTS_TXACTF7_Pos         (7)                                               /*!< PDMA_T::TACTSTS: TXACTF7 Position     */
#define PDMA_TACTSTS_TXACTF7_Msk         (0x1ul << PDMA_TACTSTS_TXACTF7_Pos)               /*!< PDMA_T::TACTSTS: TXACTF7 Mask         */

#define PDMA_TACTSTS_TXACTF8_Pos         (8)                                               /*!< PDMA_T::TACTSTS: TXACTF8 Position     */
#define PDMA_TACTSTS_TXACTF8_Msk         (0x1ul << PDMA_TACTSTS_TXACTF8_Pos)               /*!< PDMA_T::TACTSTS: TXACTF8 Mask         */

#define PDMA_TACTSTS_TXACTF9_Pos         (9)                                               /*!< PDMA_T::TACTSTS: TXACTF9 Position     */
#define PDMA_TACTSTS_TXACTF9_Msk         (0x1ul << PDMA_TACTSTS_TXACTF9_Pos)               /*!< PDMA_T::TACTSTS: TXACTF9 Mask         */

#define PDMA_TACTSTS_TXACTF10_Pos        (10)                                              /*!< PDMA_T::TACTSTS: TXACTF10 Position    */
#define PDMA_TACTSTS_TXACTF10_Msk        (0x1ul << PDMA_TACTSTS_TXACTF10_Pos)              /*!< PDMA_T::TACTSTS: TXACTF10 Mask        */

#define PDMA_TACTSTS_TXACTF11_Pos        (11)                                              /*!< PDMA_T::TACTSTS: TXACTF11 Position    */
#define PDMA_TACTSTS_TXACTF11_Msk        (0x1ul << PDMA_TACTSTS_TXACTF11_Pos)              /*!< PDMA_T::TACTSTS: TXACTF11 Mask        */

#define PDMA_TACTSTS_TXACTF12_Pos        (12)                                              /*!< PDMA_T::TACTSTS: TXACTF12 Position    */
#define PDMA_TACTSTS_TXACTF12_Msk        (0x1ul << PDMA_TACTSTS_TXACTF12_Pos)              /*!< PDMA_T::TACTSTS: TXACTF12 Mask        */

#define PDMA_TACTSTS_TXACTF13_Pos        (13)                                              /*!< PDMA_T::TACTSTS: TXACTF13 Position    */
#define PDMA_TACTSTS_TXACTF13_Msk        (0x1ul << PDMA_TACTSTS_TXACTF13_Pos)              /*!< PDMA_T::TACTSTS: TXACTF13 Mask        */

#define PDMA_TACTSTS_TXACTF14_Pos        (14)                                              /*!< PDMA_T::TACTSTS: TXACTF14 Position    */
#define PDMA_TACTSTS_TXACTF14_Msk        (0x1ul << PDMA_TACTSTS_TXACTF14_Pos)              /*!< PDMA_T::TACTSTS: TXACTF14 Mask        */

#define PDMA_TACTSTS_TXACTF15_Pos        (15)                                              /*!< PDMA_T::TACTSTS: TXACTF15 Position    */
#define PDMA_TACTSTS_TXACTF15_Msk        (0x1ul << PDMA_TACTSTS_TXACTF15_Pos)              /*!< PDMA_T::TACTSTS: TXACTF15 Mask        */

#define PDMA_TOUTPSC0_7_TOUTPSC0_Pos     (0)                                               /*!< PDMA_T::TOUTPSC0_7: TOUTPSC0 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC0_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC0_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC0 Mask     */

#define PDMA_TOUTPSC0_7_TOUTPSC1_Pos     (4)                                               /*!< PDMA_T::TOUTPSC0_7: TOUTPSC1 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC1_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC1_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC1 Mask     */

#define PDMA_TOUTPSC0_7_TOUTPSC2_Pos     (8)                                               /*!< PDMA_T::TOUTPSC0_7: TOUTPSC2 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC2_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC2_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC2 Mask     */

#define PDMA_TOUTPSC0_7_TOUTPSC3_Pos     (12)                                              /*!< PDMA_T::TOUTPSC0_7: TOUTPSC3 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC3_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC3_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC3 Mask     */

#define PDMA_TOUTPSC0_7_TOUTPSC4_Pos     (16)                                              /*!< PDMA_T::TOUTPSC0_7: TOUTPSC4 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC4_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC4_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC4 Mask     */

#define PDMA_TOUTPSC0_7_TOUTPSC5_Pos     (20)                                              /*!< PDMA_T::TOUTPSC0_7: TOUTPSC5 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC5_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC5_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC5 Mask     */

#define PDMA_TOUTPSC0_7_TOUTPSC6_Pos     (24)                                              /*!< PDMA_T::TOUTPSC0_7: TOUTPSC6 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC6_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC6_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC6 Mask     */

#define PDMA_TOUTPSC0_7_TOUTPSC7_Pos     (28)                                              /*!< PDMA_T::TOUTPSC0_7: TOUTPSC7 Position */
#define PDMA_TOUTPSC0_7_TOUTPSC7_Msk     (0x7ul << PDMA_TOUTPSC0_7_TOUTPSC7_Pos)           /*!< PDMA_T::TOUTPSC0_7: TOUTPSC7 Mask     */

#define PDMA_TOUTEN_TOUTENn_Pos          (0)                                               /*!< PDMA_T::TOUTEN: TOUTENn Position       */
#define PDMA_TOUTEN_TOUTENn_Msk          (PDMA_CH_Msk << PDMA_TOUTEN_TOUTENn_Pos)          /*!< PDMA_T::TOUTEN: TOUTENn Mask           */

#define PDMA_TOUTEN_TOUTEN0_Pos          (0)                                               /*!< PDMA_T::TOUTEN: TOUTEN0 Position      */
#define PDMA_TOUTEN_TOUTEN0_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN0_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN0 Mask          */

#define PDMA_TOUTEN_TOUTEN1_Pos          (1)                                               /*!< PDMA_T::TOUTEN: TOUTEN1 Position      */
#define PDMA_TOUTEN_TOUTEN1_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN1_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN1 Mask          */

#define PDMA_TOUTEN_TOUTEN2_Pos          (2)                                               /*!< PDMA_T::TOUTEN: TOUTEN2 Position      */
#define PDMA_TOUTEN_TOUTEN2_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN2_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN2 Mask          */

#define PDMA_TOUTEN_TOUTEN3_Pos          (3)                                               /*!< PDMA_T::TOUTEN: TOUTEN3 Position      */
#define PDMA_TOUTEN_TOUTEN3_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN3_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN3 Mask          */

#define PDMA_TOUTEN_TOUTEN4_Pos          (4)                                               /*!< PDMA_T::TOUTEN: TOUTEN4 Position      */
#define PDMA_TOUTEN_TOUTEN4_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN4_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN4 Mask          */

#define PDMA_TOUTEN_TOUTEN5_Pos          (5)                                               /*!< PDMA_T::TOUTEN: TOUTEN5 Position      */
#define PDMA_TOUTEN_TOUTEN5_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN5_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN5 Mask          */

#define PDMA_TOUTEN_TOUTEN6_Pos          (6)                                               /*!< PDMA_T::TOUTEN: TOUTEN6 Position      */
#define PDMA_TOUTEN_TOUTEN6_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN6_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN6 Mask          */

#define PDMA_TOUTEN_TOUTEN7_Pos          (7)                                               /*!< PDMA_T::TOUTEN: TOUTEN7 Position      */
#define PDMA_TOUTEN_TOUTEN7_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN7_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN7 Mask          */

#define PDMA_TOUTEN_TOUTEN8_Pos          (8)                                               /*!< PDMA_T::TOUTEN: TOUTEN8 Position      */
#define PDMA_TOUTEN_TOUTEN8_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN8_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN8 Mask          */

#define PDMA_TOUTEN_TOUTEN9_Pos          (9)                                               /*!< PDMA_T::TOUTEN: TOUTEN9 Position      */
#define PDMA_TOUTEN_TOUTEN9_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN9_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN9 Mask          */

#define PDMA_TOUTEN_TOUTEN10_Pos         (10)                                              /*!< PDMA_T::TOUTEN: TOUTEN10 Position     */
#define PDMA_TOUTEN_TOUTEN10_Msk         (0x1ul << PDMA_TOUTEN_TOUTEN10_Pos)               /*!< PDMA_T::TOUTEN: TOUTEN10 Mask         */

#define PDMA_TOUTEN_TOUTEN11_Pos         (11)                                              /*!< PDMA_T::TOUTEN: TOUTEN11 Position     */
#define PDMA_TOUTEN_TOUTEN11_Msk         (0x1ul << PDMA_TOUTEN_TOUTEN11_Pos)               /*!< PDMA_T::TOUTEN: TOUTEN11 Mask         */

#define PDMA_TOUTEN_TOUTEN12_Pos         (12)                                              /*!< PDMA_T::TOUTEN: TOUTEN12 Position     */
#define PDMA_TOUTEN_TOUTEN12_Msk         (0x1ul << PDMA_TOUTEN_TOUTEN12_Pos)               /*!< PDMA_T::TOUTEN: TOUTEN12 Mask         */

#define PDMA_TOUTEN_TOUTEN13_Pos         (13)                                              /*!< PDMA_T::TOUTEN: TOUTEN13 Position     */
#define PDMA_TOUTEN_TOUTEN13_Msk         (0x1ul << PDMA_TOUTEN_TOUTEN13_Pos)               /*!< PDMA_T::TOUTEN: TOUTEN13 Mask         */

#define PDMA_TOUTEN_TOUTEN14_Pos         (14)                                              /*!< PDMA_T::TOUTEN: TOUTEN14 Position     */
#define PDMA_TOUTEN_TOUTEN14_Msk         (0x1ul << PDMA_TOUTEN_TOUTEN14_Pos)               /*!< PDMA_T::TOUTEN: TOUTEN14 Mask         */

#define PDMA_TOUTEN_TOUTEN15_Pos         (15)                                              /*!< PDMA_T::TOUTEN: TOUTEN15 Position     */
#define PDMA_TOUTEN_TOUTEN15_Msk         (0x1ul << PDMA_TOUTEN_TOUTEN15_Pos)               /*!< PDMA_T::TOUTEN: TOUTEN15 Mask         */

#define PDMA_TOUTIEN_TOUTIENn_Pos        (0)                                               /*!< PDMA_T::TOUTIEN: TOUTIENn Position     */
#define PDMA_TOUTIEN_TOUTIENn_Msk        (PDMA_CH_Msk << PDMA_TOUTIEN_TOUTIENn_Pos)        /*!< PDMA_T::TOUTIEN: TOUTIENn Mask         */

#define PDMA_TOUTIEN_TOUTIEN0_Pos        (0)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN0 Position    */
#define PDMA_TOUTIEN_TOUTIEN0_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN0_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN0 Mask        */

#define PDMA_TOUTIEN_TOUTIEN1_Pos        (1)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN1 Position    */
#define PDMA_TOUTIEN_TOUTIEN1_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN1_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN1 Mask        */

#define PDMA_TOUTIEN_TOUTIEN2_Pos        (2)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN2 Position    */
#define PDMA_TOUTIEN_TOUTIEN2_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN2_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN2 Mask        */

#define PDMA_TOUTIEN_TOUTIEN3_Pos        (3)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN3 Position    */
#define PDMA_TOUTIEN_TOUTIEN3_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN3_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN3 Mask        */

#define PDMA_TOUTIEN_TOUTIEN4_Pos        (4)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN4 Position    */
#define PDMA_TOUTIEN_TOUTIEN4_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN4_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN4 Mask        */

#define PDMA_TOUTIEN_TOUTIEN5_Pos        (5)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN5 Position    */
#define PDMA_TOUTIEN_TOUTIEN5_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN5_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN5 Mask        */

#define PDMA_TOUTIEN_TOUTIEN6_Pos        (6)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN6 Position    */
#define PDMA_TOUTIEN_TOUTIEN6_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN6_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN6 Mask        */

#define PDMA_TOUTIEN_TOUTIEN7_Pos        (7)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN7 Position    */
#define PDMA_TOUTIEN_TOUTIEN7_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN7_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN7 Mask        */

#define PDMA_TOUTIEN_TOUTIEN8_Pos        (8)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN8 Position    */
#define PDMA_TOUTIEN_TOUTIEN8_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN8_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN8 Mask        */

#define PDMA_TOUTIEN_TOUTIEN9_Pos        (9)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN9 Position    */
#define PDMA_TOUTIEN_TOUTIEN9_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN9_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN9 Mask        */

#define PDMA_TOUTIEN_TOUTIEN10_Pos       (10)                                              /*!< PDMA_T::TOUTIEN: TOUTIEN10 Position   */
#define PDMA_TOUTIEN_TOUTIEN10_Msk       (0x1ul << PDMA_TOUTIEN_TOUTIEN10_Pos)             /*!< PDMA_T::TOUTIEN: TOUTIEN10 Mask       */

#define PDMA_TOUTIEN_TOUTIEN11_Pos       (11)                                              /*!< PDMA_T::TOUTIEN: TOUTIEN11 Position   */
#define PDMA_TOUTIEN_TOUTIEN11_Msk       (0x1ul << PDMA_TOUTIEN_TOUTIEN11_Pos)             /*!< PDMA_T::TOUTIEN: TOUTIEN11 Mask       */

#define PDMA_TOUTIEN_TOUTIEN12_Pos       (12)                                              /*!< PDMA_T::TOUTIEN: TOUTIEN12 Position   */
#define PDMA_TOUTIEN_TOUTIEN12_Msk       (0x1ul << PDMA_TOUTIEN_TOUTIEN12_Pos)             /*!< PDMA_T::TOUTIEN: TOUTIEN12 Mask       */

#define PDMA_TOUTIEN_TOUTIEN13_Pos       (13)                                              /*!< PDMA_T::TOUTIEN: TOUTIEN13 Position   */
#define PDMA_TOUTIEN_TOUTIEN13_Msk       (0x1ul << PDMA_TOUTIEN_TOUTIEN13_Pos)             /*!< PDMA_T::TOUTIEN: TOUTIEN13 Mask       */

#define PDMA_TOUTIEN_TOUTIEN14_Pos       (14)                                              /*!< PDMA_T::TOUTIEN: TOUTIEN14 Position   */
#define PDMA_TOUTIEN_TOUTIEN14_Msk       (0x1ul << PDMA_TOUTIEN_TOUTIEN14_Pos)             /*!< PDMA_T::TOUTIEN: TOUTIEN14 Mask       */

#define PDMA_TOUTIEN_TOUTIEN15_Pos       (15)                                              /*!< PDMA_T::TOUTIEN: TOUTIEN15 Position   */
#define PDMA_TOUTIEN_TOUTIEN15_Msk       (0x1ul << PDMA_TOUTIEN_TOUTIEN15_Pos)             /*!< PDMA_T::TOUTIEN: TOUTIEN15 Mask       */

#define PDMA_SCATBA_SCATBA_Pos           (16)                                              /*!< PDMA_T::SCATBA: SCATBA Position       */
#define PDMA_SCATBA_SCATBA_Msk           (0xfffful << PDMA_SCATBA_SCATBA_Pos)              /*!< PDMA_T::SCATBA: SCATBA Mask           */

#define PDMA_TOC0_1_TOC0_Pos             (0)                                               /*!< PDMA_T::TOC0_1: TOC0 Position         */
#define PDMA_TOC0_1_TOC0_Msk             (0xfffful << PDMA_TOC0_1_TOC0_Pos)                /*!< PDMA_T::TOC0_1: TOC0 Mask             */

#define PDMA_TOC0_1_TOC1_Pos             (16)                                              /*!< PDMA_T::TOC0_1: TOC1 Position         */
#define PDMA_TOC0_1_TOC1_Msk             (0xfffful << PDMA_TOC0_1_TOC1_Pos)                /*!< PDMA_T::TOC0_1: TOC1 Mask             */

#define PDMA_TOC2_3_TOC2_Pos             (0)                                               /*!< PDMA_T::TOC2_3: TOC2 Position         */
#define PDMA_TOC2_3_TOC2_Msk             (0xfffful << PDMA_TOC2_3_TOC2_Pos)                /*!< PDMA_T::TOC2_3: TOC2 Mask             */

#define PDMA_TOC2_3_TOC3_Pos             (16)                                              /*!< PDMA_T::TOC2_3: TOC3 Position         */
#define PDMA_TOC2_3_TOC3_Msk             (0xfffful << PDMA_TOC2_3_TOC3_Pos)                /*!< PDMA_T::TOC2_3: TOC3 Mask             */

#define PDMA_TOC4_5_TOC4_Pos             (0)                                               /*!< PDMA_T::TOC4_5: TOC4 Position         */
#define PDMA_TOC4_5_TOC4_Msk             (0xfffful << PDMA_TOC4_5_TOC4_Pos)                /*!< PDMA_T::TOC4_5: TOC4 Mask             */

#define PDMA_TOC4_5_TOC5_Pos             (16)                                              /*!< PDMA_T::TOC4_5: TOC5 Position         */
#define PDMA_TOC4_5_TOC5_Msk             (0xfffful << PDMA_TOC4_5_TOC5_Pos)                /*!< PDMA_T::TOC4_5: TOC5 Mask             */

#define PDMA_TOC6_7_TOC6_Pos             (0)                                               /*!< PDMA_T::TOC6_7: TOC6 Position         */
#define PDMA_TOC6_7_TOC6_Msk             (0xfffful << PDMA_TOC6_7_TOC6_Pos)                /*!< PDMA_T::TOC6_7: TOC6 Mask             */

#define PDMA_TOC6_7_TOC7_Pos             (16)                                              /*!< PDMA_T::TOC6_7: TOC7 Position         */
#define PDMA_TOC6_7_TOC7_Msk             (0xfffful << PDMA_TOC6_7_TOC7_Pos)                /*!< PDMA_T::TOC6_7: TOC7 Mask             */

#define PDMA_TOC8_9_TOC8_Pos             (0)                                               /*!< PDMA_T::TOC8_9: TOC8 Position         */
#define PDMA_TOC8_9_TOC8_Msk             (0xfffful << PDMA_TOC8_9_TOC8_Pos)                /*!< PDMA_T::TOC8_9: TOC8 Mask             */

#define PDMA_TOC8_9_TOC9_Pos             (16)                                              /*!< PDMA_T::TOC8_9: TOC9 Position         */
#define PDMA_TOC8_9_TOC9_Msk             (0xfffful << PDMA_TOC8_9_TOC9_Pos)                /*!< PDMA_T::TOC8_9: TOC9 Mask             */

#define PDMA_TOC10_11_TOC10_Pos          (0)                                               /*!< PDMA_T::TOC10_11: TOC10 Position      */
#define PDMA_TOC10_11_TOC10_Msk          (0xfffful << PDMA_TOC10_11_TOC10_Pos)             /*!< PDMA_T::TOC10_11: TOC10 Mask          */

#define PDMA_TOC10_11_TOC11_Pos          (16)                                              /*!< PDMA_T::TOC10_11: TOC11 Position      */
#define PDMA_TOC10_11_TOC11_Msk          (0xfffful << PDMA_TOC10_11_TOC11_Pos)             /*!< PDMA_T::TOC10_11: TOC11 Mask          */

#define PDMA_TOC12_13_TOC12_Pos          (0)                                               /*!< PDMA_T::TOC12_13: TOC12 Position      */
#define PDMA_TOC12_13_TOC12_Msk          (0xfffful << PDMA_TOC12_13_TOC12_Pos)             /*!< PDMA_T::TOC12_13: TOC12 Mask          */

#define PDMA_TOC12_13_TOC13_Pos          (16)                                              /*!< PDMA_T::TOC12_13: TOC13 Position      */
#define PDMA_TOC12_13_TOC13_Msk          (0xfffful << PDMA_TOC12_13_TOC13_Pos)             /*!< PDMA_T::TOC12_13: TOC13 Mask          */

#define PDMA_TOC14_15_TOC14_Pos          (0)                                               /*!< PDMA_T::TOC14_15: TOC14 Position      */
#define PDMA_TOC14_15_TOC14_Msk          (0xfffful << PDMA_TOC14_15_TOC14_Pos)             /*!< PDMA_T::TOC14_15: TOC14 Mask          */

#define PDMA_TOC14_15_TOC15_Pos          (16)                                              /*!< PDMA_T::TOC14_15: TOC15 Position      */
#define PDMA_TOC14_15_TOC15_Msk          (0xfffful << PDMA_TOC14_15_TOC15_Pos)             /*!< PDMA_T::TOC14_15: TOC15 Mask          */

#define PDMA_CHRST_CHnRST_Pos            (0)                                               /*!< PDMA_T::CHRST: CHnRST Position        */
#define PDMA_CHRST_CHnRST_Msk            (0xfffful << PDMA_CHRST_CHnRST_Pos)               /*!< PDMA_T::CHRST: CHnRST Mask            */

#define PDMA_CHRST_CH0RST_Pos            (0)                                               /*!< PDMA_T::CHRST: CH0RST Position        */
#define PDMA_CHRST_CH0RST_Msk            (0x1ul << PDMA_CHRST_CH0RST_Pos)                  /*!< PDMA_T::CHRST: CH0RST Mask            */

#define PDMA_CHRST_CH1RST_Pos            (1)                                               /*!< PDMA_T::CHRST: CH1RST Position        */
#define PDMA_CHRST_CH1RST_Msk            (0x1ul << PDMA_CHRST_CH1RST_Pos)                  /*!< PDMA_T::CHRST: CH1RST Mask            */

#define PDMA_CHRST_CH2RST_Pos            (2)                                               /*!< PDMA_T::CHRST: CH2RST Position        */
#define PDMA_CHRST_CH2RST_Msk            (0x1ul << PDMA_CHRST_CH2RST_Pos)                  /*!< PDMA_T::CHRST: CH2RST Mask            */

#define PDMA_CHRST_CH3RST_Pos            (3)                                               /*!< PDMA_T::CHRST: CH3RST Position        */
#define PDMA_CHRST_CH3RST_Msk            (0x1ul << PDMA_CHRST_CH3RST_Pos)                  /*!< PDMA_T::CHRST: CH3RST Mask            */

#define PDMA_CHRST_CH4RST_Pos            (4)                                               /*!< PDMA_T::CHRST: CH4RST Position        */
#define PDMA_CHRST_CH4RST_Msk            (0x1ul << PDMA_CHRST_CH4RST_Pos)                  /*!< PDMA_T::CHRST: CH4RST Mask            */

#define PDMA_CHRST_CH5RST_Pos            (5)                                               /*!< PDMA_T::CHRST: CH5RST Position        */
#define PDMA_CHRST_CH5RST_Msk            (0x1ul << PDMA_CHRST_CH5RST_Pos)                  /*!< PDMA_T::CHRST: CH5RST Mask            */

#define PDMA_CHRST_CH6RST_Pos            (6)                                               /*!< PDMA_T::CHRST: CH6RST Position        */
#define PDMA_CHRST_CH6RST_Msk            (0x1ul << PDMA_CHRST_CH6RST_Pos)                  /*!< PDMA_T::CHRST: CH6RST Mask            */

#define PDMA_CHRST_CH7RST_Pos            (7)                                               /*!< PDMA_T::CHRST: CH7RST Position        */
#define PDMA_CHRST_CH7RST_Msk            (0x1ul << PDMA_CHRST_CH7RST_Pos)                  /*!< PDMA_T::CHRST: CH7RST Mask            */

#define PDMA_CHRST_CH8RST_Pos            (8)                                               /*!< PDMA_T::CHRST: CH8RST Position        */
#define PDMA_CHRST_CH8RST_Msk            (0x1ul << PDMA_CHRST_CH8RST_Pos)                  /*!< PDMA_T::CHRST: CH8RST Mask            */

#define PDMA_CHRST_CH9RST_Pos            (9)                                               /*!< PDMA_T::CHRST: CH9RST Position        */
#define PDMA_CHRST_CH9RST_Msk            (0x1ul << PDMA_CHRST_CH9RST_Pos)                  /*!< PDMA_T::CHRST: CH9RST Mask            */

#define PDMA_CHRST_CH10RST_Pos           (10)                                              /*!< PDMA_T::CHRST: CH10RST Position       */
#define PDMA_CHRST_CH10RST_Msk           (0x1ul << PDMA_CHRST_CH10RST_Pos)                 /*!< PDMA_T::CHRST: CH10RST Mask           */

#define PDMA_CHRST_CH11RST_Pos           (11)                                              /*!< PDMA_T::CHRST: CH11RST Position       */
#define PDMA_CHRST_CH11RST_Msk           (0x1ul << PDMA_CHRST_CH11RST_Pos)                 /*!< PDMA_T::CHRST: CH11RST Mask           */

#define PDMA_CHRST_CH12RST_Pos           (12)                                              /*!< PDMA_T::CHRST: CH12RST Position       */
#define PDMA_CHRST_CH12RST_Msk           (0x1ul << PDMA_CHRST_CH12RST_Pos)                 /*!< PDMA_T::CHRST: CH12RST Mask           */

#define PDMA_CHRST_CH13RST_Pos           (13)                                              /*!< PDMA_T::CHRST: CH13RST Position       */
#define PDMA_CHRST_CH13RST_Msk           (0x1ul << PDMA_CHRST_CH13RST_Pos)                 /*!< PDMA_T::CHRST: CH13RST Mask           */

#define PDMA_CHRST_CH14RST_Pos           (14)                                              /*!< PDMA_T::CHRST: CH14RST Position       */
#define PDMA_CHRST_CH14RST_Msk           (0x1ul << PDMA_CHRST_CH14RST_Pos)                 /*!< PDMA_T::CHRST: CH14RST Mask           */

#define PDMA_CHRST_CH15RST_Pos           (15)                                              /*!< PDMA_T::CHRST: CH15RST Position       */
#define PDMA_CHRST_CH15RST_Msk           (0x1ul << PDMA_CHRST_CH15RST_Pos)                 /*!< PDMA_T::CHRST: CH15RST Mask           */

#define PDMA_TOUTPSC8_15_TOUTPSC8_Pos    (0)                                               /*!< PDMA_T::TOUTPSC8_15: TOUTPSC8 Position  */
#define PDMA_TOUTPSC8_15_TOUTPSC8_Msk    (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC8_Pos)          /*!< PDMA_T::TOUTPSC8_15: TOUTPSC8 Mask      */

#define PDMA_TOUTPSC8_15_TOUTPSC9_Pos    (4)                                               /*!< PDMA_T::TOUTPSC8_15: TOUTPSC9 Position  */
#define PDMA_TOUTPSC8_15_TOUTPSC9_Msk    (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC9_Pos)          /*!< PDMA_T::TOUTPSC8_15: TOUTPSC9 Mask      */

#define PDMA_TOUTPSC8_15_TOUTPSC10_Pos   (8)                                               /*!< PDMA_T::TOUTPSC8_15: TOUTPSC10 Position */
#define PDMA_TOUTPSC8_15_TOUTPSC10_Msk   (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC10_Pos)         /*!< PDMA_T::TOUTPSC8_15: TOUTPSC10 Mask     */

#define PDMA_TOUTPSC8_15_TOUTPSC11_Pos   (12)                                              /*!< PDMA_T::TOUTPSC8_15: TOUTPSC11 Position */
#define PDMA_TOUTPSC8_15_TOUTPSC11_Msk   (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC11_Pos)         /*!< PDMA_T::TOUTPSC8_15: TOUTPSC11 Mask     */

#define PDMA_TOUTPSC8_15_TOUTPSC12_Pos   (16)                                              /*!< PDMA_T::TOUTPSC8_15: TOUTPSC12 Position */
#define PDMA_TOUTPSC8_15_TOUTPSC12_Msk   (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC12_Pos)         /*!< PDMA_T::TOUTPSC8_15: TOUTPSC12 Mask     */

#define PDMA_TOUTPSC8_15_TOUTPSC13_Pos   (20)                                              /*!< PDMA_T::TOUTPSC8_15: TOUTPSC13 Position */
#define PDMA_TOUTPSC8_15_TOUTPSC13_Msk   (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC13_Pos)         /*!< PDMA_T::TOUTPSC8_15: TOUTPSC13 Mask     */

#define PDMA_TOUTPSC8_15_TOUTPSC14_Pos   (24)                                              /*!< PDMA_T::TOUTPSC8_15: TOUTPSC14 Position */
#define PDMA_TOUTPSC8_15_TOUTPSC14_Msk   (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC14_Pos)         /*!< PDMA_T::TOUTPSC8_15: TOUTPSC14 Mask     */

#define PDMA_TOUTPSC8_15_TOUTPSC15_Pos   (28)                                              /*!< PDMA_T::TOUTPSC8_15: TOUTPSC15 Position */
#define PDMA_TOUTPSC8_15_TOUTPSC15_Msk   (0x7ul << PDMA_TOUTPSC8_15_TOUTPSC15_Pos)         /*!< PDMA_T::TOUTPSC8_15: TOUTPSC15 Mask     */

#define PDMA_REQSEL0_3_REQSRC0_Pos       (0)                                               /*!< PDMA_T::REQSEL0_3: REQSRC0 Position     */
#define PDMA_REQSEL0_3_REQSRC0_Msk       (0x7ful << PDMA_REQSEL0_3_REQSRC0_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC0 Mask         */

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

#define PDMA_REQSEL8_11_REQSRC8_Pos      (0)                                               /*!< PDMA_T::REQSEL8_11: REQSRC8 Position   */
#define PDMA_REQSEL8_11_REQSRC8_Msk      (0x7ful << PDMA_REQSEL8_11_REQSRC8_Pos)           /*!< PDMA_T::REQSEL8_11: REQSRC8 Mask       */

#define PDMA_REQSEL8_11_REQSRC9_Pos      (8)                                               /*!< PDMA_T::REQSEL8_11: REQSRC9 Position   */
#define PDMA_REQSEL8_11_REQSRC9_Msk      (0x7ful << PDMA_REQSEL8_11_REQSRC9_Pos)           /*!< PDMA_T::REQSEL8_11: REQSRC9 Mask       */

#define PDMA_REQSEL8_11_REQSRC10_Pos     (16)                                              /*!< PDMA_T::REQSEL8_11: REQSRC10 Position  */
#define PDMA_REQSEL8_11_REQSRC10_Msk     (0x7ful << PDMA_REQSEL8_11_REQSRC10_Pos)          /*!< PDMA_T::REQSEL8_11: REQSRC10 Mask      */

#define PDMA_REQSEL8_11_REQSRC11_Pos     (24)                                              /*!< PDMA_T::REQSEL8_11: REQSRC11 Position  */
#define PDMA_REQSEL8_11_REQSRC11_Msk     (0x7ful << PDMA_REQSEL8_11_REQSRC11_Pos)          /*!< PDMA_T::REQSEL8_11: REQSRC11 Mask      */

#define PDMA_REQSEL12_15_REQSRC12_Pos    (0)                                               /*!< PDMA_T::REQSEL12_15: REQSRC12 Position */
#define PDMA_REQSEL12_15_REQSRC12_Msk    (0x7ful << PDMA_REQSEL12_15_REQSRC12_Pos)         /*!< PDMA_T::REQSEL12_15: REQSRC12 Mask     */

#define PDMA_REQSEL12_15_REQSRC13_Pos    (8)                                               /*!< PDMA_T::REQSEL12_15: REQSRC13 Position */
#define PDMA_REQSEL12_15_REQSRC13_Msk    (0x7ful << PDMA_REQSEL12_15_REQSRC13_Pos)         /*!< PDMA_T::REQSEL12_15: REQSRC13 Mask     */

#define PDMA_REQSEL12_15_REQSRC14_Pos    (16)                                              /*!< PDMA_T::REQSEL12_15: REQSRC14 Position */
#define PDMA_REQSEL12_15_REQSRC14_Msk    (0x7ful << PDMA_REQSEL12_15_REQSRC14_Pos)         /*!< PDMA_T::REQSEL12_15: REQSRC14 Mask     */

#define PDMA_REQSEL12_15_REQSRC15_Pos    (24)                                              /*!< PDMA_T::REQSEL12_15: REQSRC15 Position */
#define PDMA_REQSEL12_15_REQSRC15_Msk    (0x7ful << PDMA_REQSEL12_15_REQSRC15_Pos)         /*!< PDMA_T::REQSEL12_15: REQSRC15 Mask     */

#define PDMA_STCRn_STC_Pos               (0)                                               /*!< PDMA_T::STCRn: STC Position            */
#define PDMA_STCRn_STC_Msk               (0xfffful << PDMA_STCRn_STC_Pos)                  /*!< PDMA_T::STCRn: STC Mask                */

#define PDMA_ASOCRn_SASOL_Pos            (0)                                               /*!< PDMA_T::ASOCRn: SASOL Position         */
#define PDMA_ASOCRn_SASOL_Msk            (0xfffful << PDMA_ASOCRn_SASOL_Pos)               /*!< PDMA_T::ASOCRn: SASOL Mask             */

#define PDMA_ASOCRn_DASOL_Pos            (16)                                              /*!< PDMA_T::ASOCRn: DASOL Position         */
#define PDMA_ASOCRn_DASOL_Msk            (0xfffful << PDMA_ASOCRn_DASOL_Pos)               /*!< PDMA_T::ASOCRn: DASOL Mask             */

#define PDMA_RCNTn_RCNT_Pos              (0)                                               /*!< PDMA_T::RCNTn: RCNT Position            */
#define PDMA_RCNTn_RCNT_Msk              (0xfffful << PDMA_STCRn_RCNT_Pos)                 /*!< PDMA_T::RCNTn: RCNT Mask                */

#define PDMA_AICTLn_SAICNT_Pos           (0)                                               /*!< PDMA_T::AICTLn: SAICNT Position         */
#define PDMA_AICTLn_SAICNT_Msk           (0xfffful << PDMA_ASOCRn_SASOL_Pos)               /*!< PDMA_T::AICTLn: SAICNT Mask             */

#define PDMA_AICTLn_DAICNT_Pos           (16)                                              /*!< PDMA_T::AICTLn: DAICNT Position         */
#define PDMA_AICTLn_DAICNT_Msk           (0xfffful << PDMA_ASOCRn_DASOL_Pos)               /*!< PDMA_T::AICTLn: DAICNT Mask             */

/**@}*/ /* PDMA_CONST */
/**@}*/ /* end of PDMA register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __PDMA_REG_H__ */
