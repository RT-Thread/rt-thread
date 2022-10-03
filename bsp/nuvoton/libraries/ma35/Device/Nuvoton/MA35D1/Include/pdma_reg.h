/**************************************************************************//**
 * @file     pdma_reg.h
 * @brief    PDMA register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PDMA_REG_H__
#define __PDMA_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

#define PDMA_CH_MAX    10UL   /*!< Specify Maximum Channels of PDMA  \hideinitializer */
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
     * |        |          |10 = Scatter-gather mode: When operating in this mode, user must give the next descriptor table address in PDMA_DSCT_NEXT register; PDMA controller will ignore this task, then load the next task to execute.
     * |        |          |11 = Reserved.
     * |        |          |Note: Before filling new transfer task in the Descriptor Table, user must check the PDMA_INTSTS[1] to make sure the current task is complete.
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
     * |        |          |If the TBINTDIS bit is enabled it will not generates TDIFn(PDMA_TDSTS[7:0]) when PDMA controller finishes transfer task.
     * |        |          |0 = Table interrupt Enabled.
     * |        |          |1 = Table interrupt Disabled.
     * |        |          |Note: This function is only for Scatter-gather mode.
     * |[9:8]   |SAINC     |Source Address Increment
     * |        |          |This field is used to set the source address increment size.
     * |        |          |11 = No increment (fixed address).
     * |        |          |Others = Increment and size is depended on TXWIDTH selection.
     * |        |          |Note: The fixed address function does not support in memory to memory transfer type.
     * |[11:10] |DAINC     |Destination Address Increment
     * |        |          |This field is used to set the destination address increment size.
     * |        |          |11 = No increment (fixed address).
     * |        |          |Others = Increment and size is depended on TXWIDTH selection.
     * |        |          |Note: The fixed address function does not support in memory to memory transfer type.
     * |[13:12] |TXWIDTH   |Transfer Width Selection
     * |        |          |This field is used for transfer width.
     * |        |          |00 = One byte (8 bit) is transferred for every operation.
     * |        |          |01= One half-word (16 bit) is transferred for every operation.
     * |        |          |10 = One word (32-bit) is transferred for every operation.
     * |        |          |11 = Reserved.
     * |        |          |Note: The PDMA transfer source address (PDMA_DSCTn_SA) and PDMA transfer destination address (PDMA_DSCTn_DA) should be alignment under the TXWIDTH selection
     * |[15]    |STRIDEEN |Stride Mode Enable Bit
     * |        |          |0 = Stride transfer mode Disabled.
     * |        |          |1 = Stride transfer mode Enabled.
     * |[31:16] |TXCNT     |Transfer Count
     * |        |          |The TXCNT represents the required number of PDMA transfer, the real transfer count is (TXCNT + 1); the maximum transfer count is 65536, every transfer may be byte, half-word or word that is dependent on TXWIDTH field.
     * |        |          |Note: When PDMA finishes each transfer data, this field will be decreased immediately.
     * @var DSCT_T::DSCT_SA
     * Offset: 0x04  Source Address Register of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SA        |PDMA Transfer Source Address
     * |        |          |This field indicates a 32-bit source address of PDMA controller.
     * @var DSCT_T::DA
     * Offset: 0x08  Destination Address Register of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DA        |PDMA Transfer Destination Address
     * |        |          |This field indicates a 32-bit destination address of PDMA controller.
     * @var DSCT_T::NEXT
     * Offset: 0x0C  Next Scatter-Gather Descriptor Table Offset Address of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |NEXT      |PDMA Next Descriptor Table Offset
     * |        |          |This field indicates the offset of the next descriptor table address in system memory.
     * |        |          |Write Operation:
     * |        |          |If the system memory based address is 0x2000_0000 (PDMA_SCATBA), and the next descriptor table is start from 0x2000_0100, then this field must fill in 0x0100.
     * |        |          |Read Operation:
     * |        |          |When operating in Scatter-gather mode, the last two bits NEXT[1:0] will become reserved, and indicate the first next address of system memory.
     * |        |          |Note 1: The descriptor table address must be word boundary.
     * |        |          |Note 2: Before filling transfer task in the descriptor table, user must check if the descriptor table is complete.
     * |[31:16] |EXENEXT   |PDMA Execution Next Descriptor Table Offset
     * |        |          |This field indicates the offset of next descriptor table address of current execution descriptor table in system memory.
     * |        |          |Note: Write operation is useless in this field.
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
     * Offset: 0xA0  Current Scatter-gather Descriptor Table Address of PDMA Channel n
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURADDR   |PDMA Current Description Address (Read Only)
     * |        |          |This field indicates a 32-bit current external description address of PDMA controller.
     * |        |          |Note: This field is read only and used for Scatter-gather mode only to indicate the current external description address.
     * @var PDMA_T::CHCTL
     * Offset: 0x400  PDMA Channel Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |CHENn     |PDMA Channel Enable Bit
     * |        |          |Set this bit to 1 to enable PDMAn operation. Channel cannot be active if it is not set as enabled.
     * |        |          |0 = PDMA channel [n] Disabled.
     * |        |          |1 = PDMA channel [n] Enabled.
     * |        |          |Note: Setting the corresponding bit of PDMA_PAUSE or PDMA_CHRST register will also clear this bit.
     * |        |          |Note: Setting the corresponding bit of PDMA_PAUSE or PDMA_CHRST register will also clear this bit.
     * @var PDMA_T::PAUSE
     * Offset: 0x404  PDMA Transfer Pause Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |PAUSEn    |PDMA Channel n Transfer Pause Control (Write Only))
     * |        |          |User can set PAUSEn bit field to pause the PDMA transfer
     * |        |          |When user sets PAUSEn bit, the PDMA controller will pause the on-going transfer, then clear the channel enable bit CHEN(PDMA_CHCTL [n], n=0,1..7) and clear request active flag
     * |        |          |If the paused channel is re-enabled again, the remaining transfers will be processed.
     * |        |          |0 = No effect.
     * |        |          |1 = Pause PDMA channel n transfer.
     * |        |          |Note: Only for memory to memory transfer.
     * @var PDMA_T::SWREQ
     * Offset: 0x408  PDMA Software Request Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]  |SWREQn    |PDMA Software Request (Write Only)
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
     * |[9:0]  |REQSTSn   |PDMA Channel Request Status (Read Only)
     * |        |          |This flag indicates whether channel[n] have a request or not, no matter request from software or peripheral
     * |        |          |When the PDMA controller finishes channel transfer, this bit will be cleared automatically.
     * |        |          |0 = PDMA Channel n has no request.
     * |        |          |1 = PDMA Channel n has a request.
     * |        |          |Note: If user pauses or resets each PDMA transfer by setting PDMA_PAUSE or PDMA_CHRST register respectively, this bit will be cleared automatically after finishing the current transfer.
     * @var PDMA_T::PRISET
     * Offset: 0x410  PDMA Fixed Priority Setting Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |FPRISETn  |PDMA Fixed Priority Setting
     * |        |          |Set this bit to 1 to enable fixed priority level.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set PDMA channel [n] to fixed priority channel.
     * |        |          |Read Operation:
     * |        |          |0 = Corresponding PDMA channel is round-robin priority.
     * |        |          |1 = Corresponding PDMA channel is fixed priority.
     * |        |          |Note: This field is only set to fixed priority. To clear fixed priority, use PDMA_PRICLR register.
     * @var PDMA_T::PRICLR
     * Offset: 0x414  PDMA Fixed Priority Clear Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |FPRICLRn  |PDMA Fixed Priority Clear Register (Write Only)
     * |        |          |Set this bit to 1 to clear fixed priority level.
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PDMA channel [n] fixed priority setting.
     * |        |          |Note: User can read PDMA_PRISET register to know the channel priority.
     * @var PDMA_T::INTEN
     * Offset: 0x418  PDMA Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |INTENn    |PDMA Interrupt Enable Bits
     * |        |          |This field is used to enable PDMA channel[n] interrupt.
     * |        |          |0 = PDMA channel n interrupt Disabled.
     * |        |          |1 = PDMA channel n interrupt Enabled.
     * |        |          |Note: The interrupt flag is time-out, abort, transfer done and align.
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
     * |[8]     |REQTOF0   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[9]     |REQTOF1   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[10]    |REQTOF2   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[11]    |REQTOF3   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[12]    |REQTOF4   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[13]    |REQTOF5   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[14]    |REQTOF6   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[15]    |REQTOF7   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[16]    |REQTOF8   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * |[17]    |REQTOF9   |Request Time-out Flag for Channel n
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by TOCn(PDMA_TOCn_n+1[n15:0].
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |        |          |Note 1: Please disable time-out function before clearing this bit.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * @var PDMA_T::ABTSTS
     * Offset: 0x420  PDMA Channel Read/Write Target Abort Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |ABTIFn    |PDMA Read/Write Target Abort Interrupt Status Flag
     * |        |          |This bit indicates which PDMA controller has target abort error.
     * |        |          |0 = No AHB bus ERROR response received when channel n transfer.
     * |        |          |1 = AHB bus ERROR response received when channel n transfer.
     * |        |          |Note 1: If channel n target abort, REQSRCn should be set0 to disable peripheral request.
     * |        |          |Note 2: User can write 1 to clear this bit.
     * @var PDMA_T::TDSTS
     * Offset: 0x424  PDMA Channel Transfer Done Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |TDIFn     |Transfer Done Flag
     * |        |          |This bit indicates whether PDMA controller channel transfer has been finished or not.
     * |        |          |0 = PDMA channel transfer has not finished.
     * |        |          |1 = PDMA channel has finished transmission.
     * |        |          |Note: User can write 1 to clear these bits.
     * @var PDMA_T::ALIGN
     * Offset: 0x428  PDMA Transfer Alignment Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |ALIGNn    |Transfer Alignment Flag Flag
     * |        |          |This bit indicates whether source and destination address both follow transfer width setting.
     * |        |          |0 = PDMA channel source address and destination address both follow transfer width setting.
     * |        |          |1 = PDMA channel source address or destination address is not follow transfer width setting.
     * |        |          |Note: User can write 1 to clear these bits.
     * @var PDMA_T::TACTSTS
     * Offset: 0x42C  PDMA Transfer Active Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |TXACTFn   |Transfer on Active Flag (Read Only)
     * |        |          |This bit indicates which PDMA channel is in active.
     * |        |          |0 = PDMA channel is finished.
     * |        |          |1 = PDMA channel is active.
     * @var PDMA_T::TOUTEN
     * Offset: 0x434  PDMA Time-out Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |TOUTENn   |PDMA Time-out Enable Bits
     * |        |          |0 = PDMA Channel n time-out function Disabled.
     * |        |          |1 = PDMA Channel n time-out function Enabled.
     * @var PDMA_T::TOUTIEN
     * Offset: 0x438  PDMA Time-out Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |TOUTIENn  |PDMA Time-out Interrupt Enable Bits
     * |        |          |0 = PDMA Channel n time-out interrupt Disabled.
     * |        |          |1 = PDMA Channel n time-out interrupt Enabled.
     * @var PDMA_T::TOC0_1
     * Offset: 0x440  PDMA Time-out Counter Ch1 and Ch0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC0      |Time-out Counter for Channel 0
     * |        |          |This controls the period of time-out function for channel 0
     * |        |          |The calculation unit is based on TOUTPSC0 (PDMA_TOUTPSC[2:0]) clock.
     * |        |          |Time-out period = (Period of time-out clock) * (16-bit TOCn), n = 0,1..9.
     * |[31:16] |TOC1      |Time-out Counter for Channel 1
     * |        |          |This controls the period of time-out function for channel 1
     * |        |          |The calculation unit is based on TOUTPSC1 (PDMA_TOUTPSC[6:4]) clock
     * |        |          |The example of time-out period can refer TOC0 bit description.
     * @var PDMA_T::TOC2_3
     * Offset: 0x444  PDMA Time-out Counter Ch3 and Ch2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC2      |Time-out Counter for Channel 2
     * |        |          |This controls the period of time-out function for channel 2
     * |        |          |The calculation unit is based on TOUTPSC2 (PDMA_TOUTPSC[10:8]) clock.
     * |        |          |Time-out period = (Period of time-out clock) * (16-bit TOCn), n = 0,1..9.
     * |[31:16] |TOC3      |Time-out Counter for Channel 3
     * |        |          |This controls the period of time-out function for channel 3
     * |        |          |The calculation unit is based on TOUTPSC3 (PDMA_TOUTPSC[14:12]) clock
     * |        |          |The example of time-out period can refer TOC2 bit description.
     * @var PDMA_T::TOC4_5
     * Offset: 0x448  PDMA Time-out Counter Ch5 and Ch4 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC4      |Time-out Counter for Channel 4
     * |        |          |This controls the period of time-out function for channel 4
     * |        |          |The calculation unit is based on TOUTPSC4 (PDMA_TOUTPSC[18:16]) clock.
     * |        |          |Time-out period = (Period of time-out clock) * (16-bit TOCn), n = 0,1..9.
     * |[31:16] |TOC5      |Time-out Counter for Channel 5
     * |        |          |This controls the period of time-out function for channel 5
     * |        |          |The calculation unit is based on TOUTPSC5 (PDMA_TOUTPSC[22:20]) clock
     * |        |          |The example of time-out period can refer TOC4 bit description.
     * @var PDMA_T::TOC6_7
     * Offset: 0x44C  PDMA Time-out Counter Ch7 and Ch6 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC6      |Time-out Counter for Channel 6
     * |        |          |This controls the period of time-out function for channel 6
     * |        |          |The calculation unit is based on TOUTPSC6 (PDMA_TOUTPSC[26:24]) clock.
     * |        |          |Time-out period = (Period of time-out clock) * (16-bit TOCn), n = 0,1..9.
     * |[31:16] |TOC7      |Time-out Counter for Channel 7
     * |        |          |This controls the period of time-out function for channel 7
     * |        |          |The calculation unit is based on TOUTPSC7 (PDMA_TOUTPSC[30:28]) clock
     * |        |          |The example of time-out period can refer TOC6 bit description.
     * @var PDMA_T::TOC8_9
    * Offset: 0x450  PDMA Time-out Counter Ch9 and Ch8 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC8      |Time-out Counter for Channel 8
     * |        |          |This controls the period of time-out function for channel 8
     * |        |          |The calculation unit is based on TOUTPSC8 (PDMA_TOUTPSC1[2:0]) clock.
     * |        |          |Time-out period = (Period of time-out clock) * (16-bit TOCn), n = 0,1..9.
     * |[31:16] |TOC9      |Time-out Counter for Channel 9
     * |        |          |This controls the period of time-out function for channel 9
     * |        |          |The calculation unit is based on TOUTPSC9 (PDMA_TOUTPSC1[6:4]) clock
     * |        |          |The example of time-out period can refer TOC8 bit description.
     * @var PDMA_T::CHRST
     * Offset: 0x460  PDMA Channel Reset Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]  |CHnRST    |Channel N Reset
     * |        |          |0 = corresponding channel n is not reset.
     * |        |          |1 = corresponding channel n is reset.
    * @var PDMA_T::TOUTPSC
    * Offset: 0x470  PDMA Time-out Prescaler Register
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[2:0]   |TOUTPSC0  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[6:4]   |TOUTPSC1  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[10:8]  |TOUTPSC2  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[14:12] |TOUTPSC3  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[18:16] |TOUTPSC4  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[22:20] |TOUTPSC5  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[26:24] |TOUTPSC6  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[30:28] |TOUTPSC7  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * @var PDMA_T::TOUTPSC1
    * Offset: 0x474  PDMA Time-out Prescaler Register1
    * ---------------------------------------------------------------------------------------------------
    * |Bits    |Field     |Descriptions
    * | :----: | :----:   | :---- |
    * |[2:0]   |TOUTPSC8  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
    * |[6:4]   |TOUTPSC9  |PDMA Channel n Time-out Clock Source Prescaler Bits
    * |        |          |000 = PDMA channel n time-out clock source is HCLK/28.
    * |        |          |001 = PDMA channel n time-out clock source is HCLK/29.
    * |        |          |010 = PDMA channel n time-out clock source is HCLK/210.
    * |        |          |011 = PDMA channel n time-out clock source is HCLK/211.
    * |        |          |100 = PDMA channel n time-out clock source is HCLK/212.
    * |        |          |101 = PDMA channel n time-out clock source is HCLK/213.
    * |        |          |110 = PDMA channel n time-out clock source is HCLK/214.
    * |        |          |111 = PDMA channel n time-out clock source is HCLK/215.
     * @var PDMA_T::REQSEL0_3
     * Offset: 0x480  PDMA Request Source Select Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REQSRC0   |Channel 0 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 0
     * |        |          |User can configure the peripheral by setting REQSRC0.
     * |        |          |00 = Disable PDMA peripheral request.
     * |        |          |01 = Reserved.
     * |        |          |02 = Reserved.
     * |        |          |03 = Reserved.
     * |        |          |04 = Channel connects to UART0_TX.
     * |        |          |05 = Channel connects to UART0_RX.
     * |        |          |06 = Channel connects to UART1_TX.
     * |        |          |07 = Channel connects to UART1_RX.
     * |        |          |08 = Channel connects to UART2_TX.
     * |        |          |09 = Channel connects to UART2_RX.
     * |        |          |10 = Channel connects to UART3_TX.
     * |        |          |11 = Channel connects to UART3_RX.
     * |        |          |12 = Channel connects to UART4_TX.
     * |        |          |13 = Channel connects to UART4_RX.
     * |        |          |14 = Channel connects to UART5_TX.
     * |        |          |15 = Channel connects to UART5_RX.
     * |        |          |16 = Channel connects to UART6_TX.
     * |        |          |17 = Channel connects to UART6_RX.
     * |        |          |18 = Channel connects to UART7_TX.
     * |        |          |19 = Channel connects to UART7_RX.
     * |        |          |20 = Channel connects to UART8_TX.
     * |        |          |21 = Channel connects to UART8_RX.
     * |        |          |22 = Channel connects to UART9_TX.
     * |        |          |23 = Channel connects to UART9_RX.
     * |        |          |24 = Channel connects to UART10_TX.
     * |        |          |25 = Channel connects to UART10_RX.
     * |        |          |26 = Channel connects to UART11_TX.
     * |        |          |27 = Channel connects to UART11_RX.
     * |        |          |28 = Channel connects to UART12_TX.
     * |        |          |29 = Channel connects to UART12_RX.
     * |        |          |30 = Channel connects to UART13_TX.
     * |        |          |31 = Channel connects to UART13_RX.
     * |        |          |32 = Channel connects to UART14_TX.
     * |        |          |33 = Channel connects to UART14_RX.
     * |        |          |34 = Channel connects to UART15_TX.
     * |        |          |35 = Channel connects to UART15_RX.
     * |        |          |36 = Channel connects to UART16_TX.
     * |        |          |37 = Channel connects to UART16_RX.
     * |        |          |54 = Channel connects to QSPI0_TX.
     * |        |          |55 = Channel connects to QSPI0_RX.
     * |        |          |56 = Channel connects to QSPI1_TX.
     * |        |          |57 = Channel connects to QSPI1_RX.
     * |        |          |60 = Channel connects to SPI0_TX.
     * |        |          |61 = Channel connects to SPI0_RX.
     * |        |          |62 = Channel connects to SPI1_TX.
     * |        |          |63 = Channel connects to SPI1_RX.
     * |        |          |64 = Channel connects to SPI2_TX.
     * |        |          |65 = Channel connects to SPI2_RX.
     * |        |          |66 = Channel connects to SPI3_TX.
     * |        |          |67 = Channel connects to SPI3_RX.
     * |        |          |70 = Channel connects to I2C0_TX.
     * |        |          |71 = Channel connects to I2C0_RX.
     * |        |          |72 = Channel connects to I2C1_TX.
     * |        |          |73 = Channel connects to I2C1_RX.
     * |        |          |74 = Channel connects to I2C2_TX.
     * |        |          |75 = Channel connects to I2C2_RX.
     * |        |          |76 = Channel connects to I2C3_TX.
     * |        |          |77 = Channel connects to I2C3_RX.
     * |        |          |78 = Channel connects to I2C4_TX.
     * |        |          |79 = Channel connects to I2C4_RX.
     * |        |          |80 = Channel connects to I2C5_TX.
     * |        |          |81 = Channel connects to I2C5_RX.
     * |        |          |86 = Channel connects to I2S0_TX.
     * |        |          |87 = Channel connects to I2S0_RX.
     * |        |          |88= Channel connects to I2S1_TX.
     * |        |          |89= Channel connects to I2S1_RX.
     * |        |          |94 = Channel connects to TMR0.
     * |        |          |95 = Channel connects to TMR1.
     * |        |          |96 = Channel connects to TMR2.
     * |        |          |97 = Channel connects to TMR3.
     * |        |          |98 = Channel connects to TMR4.
     * |        |          |99 = Channel connects to TMR5.
     * |        |          |100 = Channel connects to TMR6.
     * |        |          |101 = Channel connects to TMR7.
     * |        |          |102 = Channel connects to TMR8.
     * |        |          |103 = Channel connects to TMR9.
     * |        |          |104 = Channel connects to TMR10.
     * |        |          |105 = Channel connects to TMR11.
     * |        |          |110 = Channel connects to EPWM0_P1_RX.
     * |        |          |111 = Channel connects to EPWM0_P2_RX.
     * |        |          |112 = Channel connects to EPWM0_P3_RX.
     * |        |          |113 = Channel connects to EPWM1_P1_RX.
     * |        |          |114 = Channel connects to EPWM1_P2_RX.
     * |        |          |115 = Channel connects to EPWM1_P3_RX.
     * |        |          |116 = Channel connects to EPWM2_P1_RX.
     * |        |          |117 = Channel connects to EPWM2_P2_RX.
     * |        |          |118 = Channel connects to EPWM2_P3_RX.
     * |        |          |122 = Channel connects to EPWM0_CH0_TX.
     * |        |          |123 = Channel connects to EPWM0_CH1_TX.
     * |        |          |124 = Channel connects to EPWM0_CH2_TX.
     * |        |          |125 = Channel connects to EPWM0_CH3_TX.
     * |        |          |126 = Channel connects to EPWM0_CH4_TX.
     * |        |          |127 = Channel connects to EPWM0_CH5_TX.
     * |        |          |128 = Channel connects to EPWM1_CH0_TX.
     * |        |          |129 = Channel connects to EPWM1_CH1_TX.
     * |        |          |130 = Channel connects to EPWM1_CH2_TX.
     * |        |          |131 = Channel connects to EPWM1_CH3_TX.
     * |        |          |132 = Channel connects to EPWM1_CH4_TX.
     * |        |          |133 = Channel connects to EPWM1_CH5_TX.
     * |        |          |134 = Channel connects to EPWM2_CH0_TX.
     * |        |          |135 = Channel connects to EPWM2_CH1_TX.
     * |        |          |136 = Channel connects to EPWM2_CH2_TX.
     * |        |          |137 = Channel connects to EPWM2_CH3_TX.
     * |        |          |138 = Channel connects to EPWM2_CH4_TX.
     * |        |          |139 = Channel connects to EPWM2_CH5_TX.
     * |        |          |146 = Channel connects to ADC_RX.
     * |        |          |Others = Reserved.
     * |        |          |Note 1: A peripheral cannot be assigned to two channels at the same time.
     * |        |          |Note 2: This field is useless when transfer between memory and memory.
     * |[15:8]  |REQSRC1   |Channel 1 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 1
     * |        |          |User can configure the peripheral setting by REQSRC1.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[23:16] |REQSRC2   |Channel 2 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 2
     * |        |          |User can configure the peripheral setting by REQSRC2.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[31:24] |REQSRC3   |Channel 3 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 3
     * |        |          |User can configure the peripheral setting by REQSRC3.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * @var PDMA_T::REQSEL4_7
     * Offset: 0x484  PDMA Request Source Select Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REQSRC4   |Channel 4 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 4
     * |        |          |User can configure the peripheral setting by REQSRC4.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[15:8]  |REQSRC5   |Channel 5 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 5
     * |        |          |User can configure the peripheral setting by REQSRC5.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[23:16] |REQSRC6   |Channel 6 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 6
     * |        |          |User can configure the peripheral setting by REQSRC6.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[31:24] |REQSRC7   |Channel 7 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 7
     * |        |          |User can configure the peripheral setting by REQSRC7.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * @var PDMA_T::REQSEL8_11
     * Offset: 0x488  PDMA Request Source Select Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REQSRC8   |Channel 8 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 8
     * |        |          |User can configure the peripheral setting by REQSRC8.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[15:8]  |REQSRC9   |Channel 9 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 9
     * |        |          |User can configure the peripheral setting by REQSRC9.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     */
    DSCT_T DSCT[PDMA_CH_MAX];            /*!< [0x0000] Descriptor Table Control Register of PDMA Channel n. */
    __I  uint32_t CURSCAT[PDMA_CH_MAX];  /*!< [0x00A0] Current Scatter-Gather Descriptor Table Address of PDMA Channel n */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[206];
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
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TOUTEN;                /*!< [0x0434] PDMA Time-out Enable Register                                    */
    __IO uint32_t TOUTIEN;               /*!< [0x0438] PDMA Time-out Interrupt Enable Register                          */
    /// @cond HIDDEN_SYMBOLS
    __IO uint32_t RESERVE5[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TOC0_1;                /*!< [0x0440] PDMA Time-out Counter Ch1 and Ch0 Register                       */
    __IO uint32_t TOC2_3;                /*!< [0x0444] PDMA Time-out Counter Ch3 and Ch2 Register                       */
    __IO uint32_t TOC4_5;                /*!< [0x0448] PDMA Time-out Counter Ch5 and Ch4 Register                       */
    __IO uint32_t TOC6_7;                /*!< [0x044C] PDMA Time-out Counter Ch7 and Ch6 Register                       */
    __IO uint32_t TOC8_9;                /*!< [0x0450] PDMA Time-out Counter Ch9 and Ch8 Register                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE6[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CHRST;                 /*!< [0x0460] PDMA Channel Reset Register                                      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE7[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TOUTPSC;               /*!< [0x0470] PDMA Time-out Prescaler Register                                 */
    __IO uint32_t TOUTPSC1;              /*!< [0x0474] PDMA Time-out Prescaler Register1                                */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE8[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t REQSEL0_3;             /*!< [0x0480] PDMA Request Source Select Register 0                            */
    __IO uint32_t REQSEL4_7;             /*!< [0x0484] PDMA Request Source Select Register 1                            */
    __IO uint32_t REQSEL8_11;            /*!< [0x0488] PDMA Request Source Select Register 2                            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE9[29];
    /// @endcond //HIDDEN_SYMBOLS
    STRIDE_T     STRIDE[6];
    /// @cond HIDDEN_SYMBOLS
    __IO uint32_t RESERVE10[52];
    /// @endcond //HIDDEN_SYMBOLS
    REPEAT_T    REPEAT[2];
} PDMA_T;

/**
    @addtogroup PDMA_CONST PDMA Bit Field Definition
    Constant Definitions for PDMA Controller
@{ */

#define PDMA_DSCT_CTL_OPMODE_Pos        (0)                                                /*!< PDMA_T::DSCT_CTL: OPMODE Position     */
#define PDMA_DSCT_CTL_OPMODE_Msk        (0x3ul << PDMA_DSCT_CTL_OPMODE_Pos)                /*!< PDMA_T::DSCT_CTL: OPMODE Mask         */

#define PDMA_DSCT_CTL_TXTYPE_Pos        (2)                                                /*!< PDMA_T::DSCT_CTL: TXTYPE Position     */
#define PDMA_DSCT_CTL_TXTYPE_Msk        (0x1ul << PDMA_DSCT_CTL_TXTYPE_Pos)                /*!< PDMA_T::DSCT_CTL: TXTYPE Mask         */

#define PDMA_DSCT_CTL_BURSIZE_Pos       (4)                                                /*!< PDMA_T::DSCT_CTL: BURSIZE Position    */
#define PDMA_DSCT_CTL_BURSIZE_Msk       (0x7ul << PDMA_DSCT_CTL_BURSIZE_Pos)               /*!< PDMA_T::DSCT_CTL: BURSIZE Mask        */

#define PDMA_DSCT_CTL_TBINTDIS_Pos      (7)                                                /*!< PDMA_T::DSCT_CTL: TBINTDIS Position      */
#define PDMA_DSCT_CTL_TBINTDIS_Msk      (0x1ul << PDMA_DSCT_CTL_TBINTDIS_Pos)              /*!< PDMA_T::DSCT_CTL: TBINTDIS Mask          */

#define PDMA_DSCT_CTL_SAINC_Pos         (8)                                                /*!< PDMA_T::DSCT_CTL: SAINC Position      */
#define PDMA_DSCT_CTL_SAINC_Msk         (0x3ul << PDMA_DSCT_CTL_SAINC_Pos)                 /*!< PDMA_T::DSCT_CTL: SAINC Mask          */

#define PDMA_DSCT_CTL_DAINC_Pos         (10)                                               /*!< PDMA_T::DSCT_CTL: DAINC Position      */
#define PDMA_DSCT_CTL_DAINC_Msk         (0x3ul << PDMA_DSCT_CTL_DAINC_Pos)                 /*!< PDMA_T::DSCT_CTL: DAINC Mask          */

#define PDMA_DSCT_CTL_TXWIDTH_Pos       (12)                                               /*!< PDMA_T::DSCT_CTL: TXWIDTH Position    */
#define PDMA_DSCT_CTL_TXWIDTH_Msk       (0x3ul << PDMA_DSCT_CTL_TXWIDTH_Pos)               /*!< PDMA_T::DSCT_CTL: TXWIDTH Mask        */

#define PDMA_DSCT_CTL_TXACK_Pos         (14)                                               /*!< PDMA_T::DSCT_CTL: TXACK Position      */
#define PDMA_DSCT_CTL_TXACK_Msk         (0x1ul << PDMA_DSCT_CTL_TXACK_Pos)                 /*!< PDMA_T::DSCT_CTL: TXACK Mask          */

#define PDMA_DSCT_CTL_STRIDEEN_Pos      (15)                                               /*!< PDMA_T::DSCT_CTL: STRIDEEN Position  */
#define PDMA_DSCT_CTL_STRIDEEN_Msk      (0x1ul << PDMA_DSCT_CTL_STRIDEEN_Pos)              /*!< PDMA_T::DSCT_CTL: STRIDEEN Mask      */

#define PDMA_DSCT_CTL_TXCNT_Pos         (16)                                               /*!< PDMA_T::DSCT_CTL: TXCNT Position      */
#define PDMA_DSCT_CTL_TXCNT_Msk         (0xfffful << PDMA_DSCT_CTL_TXCNT_Pos)              /*!< PDMA_T::DSCT_CTL: TXCNT Mask          */

#define PDMA_DSCT_SA_SA_Pos             (0)                                                /*!< PDMA_T::DSCT_SA: SA Position          */
#define PDMA_DSCT_SA_SA_Msk             (0xfffffffful << PDMA_DSCT_SA_SA_Pos)              /*!< PDMA_T::DSCT_SA: SA Mask              */

#define PDMA_DSCT_DA_DA_Pos             (0)                                                /*!< PDMA_T::DSCT_DA: DA Position          */
#define PDMA_DSCT_DA_DA_Msk             (0xfffffffful << PDMA_DSCT_DA_DA_Pos)              /*!< PDMA_T::DSCT_DA: DA Mask              */

#define PDMA_DSCT_NEXT_NEXT_Pos         (0)                                                /*!< PDMA_T::DSCT_NEXT: NEXT Position      */
#define PDMA_DSCT_NEXT_NEXT_Msk         (0xfffful << PDMA_DSCT_NEXT_NEXT_Pos)              /*!< PDMA_T::DSCT_NEXT: NEXT Mask          */

#define PDMA_DSCT_NEXT_EXENEXT_Pos      (16)                                               /*!< PDMA_T::DSCT_FIRST: NEXT Position     */
#define PDMA_DSCT_NEXT_EXENEXT_Msk      (0xfffful << PDMA_DSCT_NEXT_EXENEXT_Pos)           /*!< PDMA_T::DSCT_FIRST: NEXT Mask         */

#define PDMA_CURSCAT_CURADDR_Pos        (0)                                                /*!< PDMA_T::CURSCAT: CURADDR Position     */
#define PDMA_CURSCAT_CURADDR_Msk        (0xfffffffful << PDMA_CURSCAT_CURADDR_Pos)         /*!< PDMA_T::CURSCAT: CURADDR Mask         */

#define PDMA_CHCTL_CHENn_Pos            (0)                                                /*!< PDMA_T::CHCTL: CHENn Position          */
#define PDMA_CHCTL_CHENn_Msk            (PDMA_CH_Msk << PDMA_CHCTL_CHENn_Pos)              /*!< PDMA_T::CHCTL: CHENn Mask              */

#define PDMA_PAUSE_PAUSEn_Pos           (0)                                                /*!< PDMA_T::PAUSE: PAUSEn Position           */
#define PDMA_PAUSE_PAUSEn_Msk           (PDMA_CH_Msk << PDMA_PAUSE_PAUSEn_Pos)             /*!< PDMA_T::PAUSE: PAUSEn Mask               */

#define PDMA_SWREQ_SWREQn_Pos            (0)                                               /*!< PDMA_T::SWREQ: SWREQn Position         */
#define PDMA_SWREQ_SWREQn_Msk            (PDMA_CH_Msk << PDMA_SWREQ_SWREQn_Pos)            /*!< PDMA_T::SWREQ: SWREQn Mask             */

#define PDMA_TRGSTS_REQSTSn_Pos          (0)                                               /*!< PDMA_T::TRGSTS: REQSTSn Position       */
#define PDMA_TRGSTS_REQSTSn_Msk          (PDMA_CH_Msk << PDMA_TRGSTS_REQSTSn_Pos)          /*!< PDMA_T::TRGSTS: REQSTSn Mask           */

#define PDMA_PRISET_FPRISETn_Pos         (0)                                               /*!< PDMA_T::PRISET: FPRISETn Position      */
#define PDMA_PRISET_FPRISETn_Msk         (PDMA_CH_Msk << PDMA_PRISET_FPRISETn_Pos)         /*!< PDMA_T::PRISET: FPRISETn Mask          */

#define PDMA_PRICLR_FPRICLRn_Pos         (0)                                               /*!< PDMA_T::PRICLR: FPRICLRn Position      */
#define PDMA_PRICLR_FPRICLRn_Msk         (PDMA_CH_Msk << PDMA_PRICLR_FPRICLRn_Pos)         /*!< PDMA_T::PRICLR: FPRICLRn Mask          */

#define PDMA_INTEN_INTENn_Pos            (0)                                               /*!< PDMA_T::INTEN: INTENn Position         */
#define PDMA_INTEN_INTENn_Msk            (PDMA_CH_Msk << PDMA_INTEN_INTENn_Pos)            /*!< PDMA_T::INTEN: INTENn Mask             */

#define PDMA_INTSTS_ABTIF_Pos            (0)                                               /*!< PDMA_T::INTSTS: ABTIF Position         */
#define PDMA_INTSTS_ABTIF_Msk            (0x1ul << PDMA_INTSTS_ABTIF_Pos)                  /*!< PDMA_T::INTSTS: ABTIF Mask             */

#define PDMA_INTSTS_TDIF_Pos             (1)                                               /*!< PDMA_T::INTSTS: TDIF Position          */
#define PDMA_INTSTS_TDIF_Msk             (0x1ul << PDMA_INTSTS_TDIF_Pos)                   /*!< PDMA_T::INTSTS: TDIF Mask              */

#define PDMA_INTSTS_ALIGNF_Pos           (2)                                               /*!< PDMA_T::INTSTS: ALIGNF Position        */
#define PDMA_INTSTS_ALIGNF_Msk           (0x1ul << PDMA_INTSTS_ALIGNF_Pos)                 /*!< PDMA_T::INTSTS: ALIGNF Mask            */

#define PDMA_INTSTS_REQTOFn_Pos          (8)                                               /*!< PDMA_T::INTSTS: REQTOFn Position       */
#define PDMA_INTSTS_REQTOFn_Msk          (PDMA_CH_Msk << PDMA_INTSTS_REQTOFn_Pos)          /*!< PDMA_T::INTSTS: REQTOFn Mask           */

#define PDMA_ABTSTS_ABTIFn_Pos           (0)                                               /*!< PDMA_T::ABTSTS: ABTIFn Position        */
#define PDMA_ABTSTS_ABTIFn_Msk           (PDMA_CH_Msk << PDMA_ABTSTS_ABTIFn_Pos)           /*!< PDMA_T::ABTSTS: ABTIFn Mask            */

#define PDMA_TDSTS_TDIFn_Pos             (0)                                               /*!< PDMA_T::TDSTS: TDIFn Position          */
#define PDMA_TDSTS_TDIFn_Msk             (PDMA_CH_Msk << PDMA_TDSTS_TDIFn_Pos)             /*!< PDMA_T::TDSTS: TDIFn Mask              */

#define PDMA_ALIGN_ALIGNn_Pos            (0)                                               /*!< PDMA_T::ALIGN: ALIGNn Position         */
#define PDMA_ALIGN_ALIGNn_Msk            (PDMA_CH_Msk << PDMA_ALIGN_ALIGNn_Pos)            /*!< PDMA_T::ALIGN: ALIGNn Mask             */

#define PDMA_TACTSTS_TXACTFn_Pos         (0)                                               /*!< PDMA_T::TACTSTS: TXACTFn Position      */
#define PDMA_TACTSTS_TXACTFn_Msk         (PDMA_CH_Msk << PDMA_TACTSTS_TXACTFn_Pos)         /*!< PDMA_T::TACTSTS: TXACTFn Mask          */

#define PDMA_TOUTEN_TOUTENn_Pos          (0)                                               /*!< PDMA_T::TOUTEN: TOUTENn Position       */
#define PDMA_TOUTEN_TOUTENn_Msk          (PDMA_CH_Msk << PDMA_TOUTEN_TOUTENn_Pos)          /*!< PDMA_T::TOUTEN: TOUTENn Mask           */

#define PDMA_TOUTIEN_TOUTIENn_Pos        (0)                                               /*!< PDMA_T::TOUTIEN: TOUTIENn Position     */
#define PDMA_TOUTIEN_TOUTIENn_Msk        (PDMA_CH_Msk << PDMA_TOUTIEN_TOUTIENn_Pos)        /*!< PDMA_T::TOUTIEN: TOUTIENn Mask         */

#define PDMA_TOC0_1_TOC0_Pos             (0)                                               /*!< PDMA_T::TOC0_1: TOC0 Position          */
#define PDMA_TOC0_1_TOC0_Msk             (0xfffful << PDMA_TOC0_1_TOC0_Pos)                /*!< PDMA_T::TOC0_1: TOC0 Mask              */

#define PDMA_TOC0_1_TOC1_Pos             (16)                                              /*!< PDMA_T::TOC0_1: TOC1 Position          */
#define PDMA_TOC0_1_TOC1_Msk             (0xfffful << PDMA_TOC0_1_TOC1_Pos)                /*!< PDMA_T::TOC0_1: TOC1 Mask              */

#define PDMA_TOC2_3_TOC2_Pos             (0)                                               /*!< PDMA_T::TOC2_3: TOC2 Position          */
#define PDMA_TOC2_3_TOC2_Msk             (0xfffful << PDMA_TOC2_3_TOC2_Pos)                /*!< PDMA_T::TOC2_3: TOC2 Mask              */

#define PDMA_TOC2_3_TOC3_Pos             (16)                                              /*!< PDMA_T::TOC2_3: TOC3 Position          */
#define PDMA_TOC2_3_TOC3_Msk             (0xfffful << PDMA_TOC2_3_TOC3_Pos)                /*!< PDMA_T::TOC2_3: TOC3 Mask              */

#define PDMA_TOC4_5_TOC4_Pos             (0)                                               /*!< PDMA_T::TOC4_5: TOC4 Position          */
#define PDMA_TOC4_5_TOC4_Msk             (0xfffful << PDMA_TOC4_5_TOC4_Pos)                /*!< PDMA_T::TOC4_5: TOC4 Mask              */

#define PDMA_TOC4_5_TOC5_Pos             (16)                                              /*!< PDMA_T::TOC4_5: TOC5 Position          */
#define PDMA_TOC4_5_TOC5_Msk             (0xfffful << PDMA_TOC4_5_TOC5_Pos)                /*!< PDMA_T::TOC4_5: TOC5 Mask              */

#define PDMA_TOC6_7_TOC6_Pos             (0)                                               /*!< PDMA_T::TOC6_7: TOC6 Position          */
#define PDMA_TOC6_7_TOC6_Msk             (0xfffful << PDMA_TOC6_7_TOC6_Pos)                /*!< PDMA_T::TOC6_7: TOC6 Mask              */

#define PDMA_TOC6_7_TOC7_Pos             (16)                                              /*!< PDMA_T::TOC6_7: TOC7 Position          */
#define PDMA_TOC6_7_TOC7_Msk             (0xfffful << PDMA_TOC6_7_TOC7_Pos)                /*!< PDMA_T::TOC6_7: TOC7 Mask              */

#define PDMA_TOC8_9_TOC8_Pos             (0)                                               /*!< PDMA_T::TOC8_9: TOC8 Position          */
#define PDMA_TOC8_9_TOC8_Msk             (0xfffful << PDMA_TOC8_9_TOC8_Pos)                /*!< PDMA_T::TOC8_9: TOC8 Mask              */

#define PDMA_TOC8_9_TOC9_Pos             (16)                                              /*!< PDMA_T::TOC8_9: TOC9 Position          */
#define PDMA_TOC8_9_TOC9_Msk             (0xfffful << PDMA_TOC8_9_TOC9_Pos)                /*!< PDMA_T::TOC8_9: TOC9 Mask              */

#define PDMA_CHRST_CHnRST_Pos            (0)                                               /*!< PDMA_T::CHRST: CHnRST Position         */
#define PDMA_CHRST_CHnRST_Msk            (PDMA_CH_Msk << PDMA_CHRST_CHnRST_Pos)            /*!< PDMA_T::CHRST: CHnRST Mask             */

#define PDMA_TOUTPSC_TOUTPSC0_Pos        (0)                                               /*!< PDMA_T::TOUTPSC: TOUTPSC0 Position     */
#define PDMA_TOUTPSC_TOUTPSC0_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC0_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC0 Mask         */

#define PDMA_TOUTPSC_TOUTPSC1_Pos        (4)                                               /*!< PDMA_T::TOUTPSC: TOUTPSC1 Position     */
#define PDMA_TOUTPSC_TOUTPSC1_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC1_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC1 Mask         */

#define PDMA_TOUTPSC_TOUTPSC2_Pos        (8)                                               /*!< PDMA_T::TOUTPSC: TOUTPSC2 Position     */
#define PDMA_TOUTPSC_TOUTPSC2_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC2_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC2 Mask         */

#define PDMA_TOUTPSC_TOUTPSC3_Pos        (12)                                              /*!< PDMA_T::TOUTPSC: TOUTPSC3 Position     */
#define PDMA_TOUTPSC_TOUTPSC3_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC3_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC3 Mask         */

#define PDMA_TOUTPSC_TOUTPSC4_Pos        (16)                                              /*!< PDMA_T::TOUTPSC: TOUTPSC4 Position     */
#define PDMA_TOUTPSC_TOUTPSC4_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC4_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC4 Mask         */

#define PDMA_TOUTPSC_TOUTPSC5_Pos        (20)                                              /*!< PDMA_T::TOUTPSC: TOUTPSC5 Position     */
#define PDMA_TOUTPSC_TOUTPSC5_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC5_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC5 Mask         */

#define PDMA_TOUTPSC_TOUTPSC6_Pos        (24)                                              /*!< PDMA_T::TOUTPSC: TOUTPSC6 Position     */
#define PDMA_TOUTPSC_TOUTPSC6_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC6_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC6 Mask         */

#define PDMA_TOUTPSC_TOUTPSC7_Pos        (28)                                              /*!< PDMA_T::TOUTPSC: TOUTPSC7 Position     */
#define PDMA_TOUTPSC_TOUTPSC7_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC7_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC7 Mask         */

#define PDMA_TOUTPSC1_TOUTPSC8_Pos       (0)                                               /*!< PDMA_T::TOUTPSC1: TOUTPSC8 Position    */
#define PDMA_TOUTPSC1_TOUTPSC8_Msk       (0x7ul << PDMA_TOUTPSC1_TOUTPSC8_Pos)             /*!< PDMA_T::TOUTPSC1: TOUTPSC8 Mask        */

#define PDMA_TOUTPSC1_TOUTPSC9_Pos       (4)                                               /*!< PDMA_T::TOUTPSC1: TOUTPSC9 Position    */
#define PDMA_TOUTPSC1_TOUTPSC9_Msk       (0x7ul << PDMA_TOUTPSC1_TOUTPSC9_Pos)             /*!< PDMA_T::TOUTPSC1: TOUTPSC9 Mask        */

#define PDMA_REQSEL0_3_REQSRC0_Pos       (0)                                               /*!< PDMA_T::REQSEL0_3: REQSRC0 Position    */
#define PDMA_REQSEL0_3_REQSRC0_Msk       (0xfful << PDMA_REQSEL0_3_REQSRC0_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC0 Mask        */

#define PDMA_REQSEL0_3_REQSRC1_Pos       (8)                                               /*!< PDMA_T::REQSEL0_3: REQSRC1 Position    */
#define PDMA_REQSEL0_3_REQSRC1_Msk       (0xfful << PDMA_REQSEL0_3_REQSRC1_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC1 Mask        */

#define PDMA_REQSEL0_3_REQSRC2_Pos       (16)                                              /*!< PDMA_T::REQSEL0_3: REQSRC2 Position    */
#define PDMA_REQSEL0_3_REQSRC2_Msk       (0xfful << PDMA_REQSEL0_3_REQSRC2_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC2 Mask        */

#define PDMA_REQSEL0_3_REQSRC3_Pos       (24)                                              /*!< PDMA_T::REQSEL0_3: REQSRC3 Position    */
#define PDMA_REQSEL0_3_REQSRC3_Msk       (0xfful << PDMA_REQSEL0_3_REQSRC3_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC3 Mask        */

#define PDMA_REQSEL4_7_REQSRC4_Pos       (0)                                               /*!< PDMA_T::REQSEL4_7: REQSRC4 Position    */
#define PDMA_REQSEL4_7_REQSRC4_Msk       (0xfful << PDMA_REQSEL4_7_REQSRC4_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC4 Mask        */

#define PDMA_REQSEL4_7_REQSRC5_Pos       (8)                                               /*!< PDMA_T::REQSEL4_7: REQSRC5 Position    */
#define PDMA_REQSEL4_7_REQSRC5_Msk       (0xfful << PDMA_REQSEL4_7_REQSRC5_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC5 Mask        */

#define PDMA_REQSEL4_7_REQSRC6_Pos       (16)                                              /*!< PDMA_T::REQSEL4_7: REQSRC6 Position    */
#define PDMA_REQSEL4_7_REQSRC6_Msk       (0xfful << PDMA_REQSEL4_7_REQSRC6_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC6 Mask        */

#define PDMA_REQSEL4_7_REQSRC7_Pos       (24)                                              /*!< PDMA_T::REQSEL4_7: REQSRC7 Position    */
#define PDMA_REQSEL4_7_REQSRC7_Msk       (0xfful << PDMA_REQSEL4_7_REQSRC7_Pos)            /*!< PDMA_T::REQSEL4_7: REQSRC7 Mask        */

#define PDMA_REQSEL8_11_REQSRC8_Pos      (0)                                               /*!< PDMA_T::REQSEL8_11: REQSRC8 Position   */
#define PDMA_REQSEL8_11_REQSRC8_Msk      (0xfful << PDMA_REQSEL8_11_REQSRC8_Pos)           /*!< PDMA_T::REQSEL8_11: REQSRC8 Mask       */

#define PDMA_REQSEL8_11_REQSRC9_Pos      (8)                                               /*!< PDMA_T::REQSEL8_11: REQSRC9 Position   */
#define PDMA_REQSEL8_11_REQSRC9_Msk      (0xfful << PDMA_REQSEL8_11_REQSRC9_Pos)           /*!< PDMA_T::REQSEL8_11: REQSRC9 Mask       */

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
