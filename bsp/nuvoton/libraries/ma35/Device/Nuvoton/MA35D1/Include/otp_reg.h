/**************************************************************************//**
* @file     otp_reg.h
* @brief    OTP driver header file
*
* SPDX-License-Identifier: Apache-2.0
* @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __OTP_REG_H__
#define __OTP_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup OTP One-Time Programming Controller(OTP)
    Memory Mapped Structure for OTP Controller
@{ */

typedef struct
{


    /**
     * @var OTP_T::CTL
     * Offset: 0x00  OTP Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |OTP Start Control Bit
     * |        |          |0 = No operation.
     * |        |          |1 = Start the operation.
     * |[7:4]   |CMD       |OTP Command Selection Bits
     * |        |          |0x0 = Read command.
     * |        |          |0x1 = Program command.
     * |        |          |0x2 = Read only lock command.
     * |        |          |0x3 = Fault Tolerance Mechanism command.
     * |        |          |0x7 = Read checker command.
     * |        |          |0xB = Read company ID
     * |        |          |0xC = Read device ID
     * |        |          |0xD = Read unique ID
     * |        |          |Others = reserved.
     * @var OTP_T::STS
     * Offset: 0x04  OTP Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |OTP Busy Flag (Read Only)
     * |        |          |0 = OTP is idle or finished.
     * |        |          |1 = OTP is busy.
     * |[1]     |PFF       |OTP Program Fail Flag (Write 1 to Clear)
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No OTP programming operation failed.
     * |        |          |1 = OTP programming operation is failed.
     * |[2]     |ADDRFF    |OTP Address Fail Flag (Write 1 to Clear)
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = OTP Address is legal.
     * |        |          |1 = OTP Address is illegal.
     * |[3]     |FTMFF     |OTP Fault Tolerance Mechanism Fail Flag (Write 1 to Clear)
     * |        |          |This bit is set after Fault Tolerance Mechanism command is triggered and address is assigned to a block without available spare memory.
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No OTP fault tolerance mechanism failed.
     * |        |          |1 = OTP fault tolerance mechanism failed.
     * |[4]     |CMDFF     |OTP Command Fail Flag (Write 1 to Clear)
     * |        |          |This bit is set after program command or Fault Tolerance Mechanism command is triggered and address is assigned a locked block.
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No OTP command failed.
     * |        |          |1 = OTP command is failed.
     * @var OTP_T::ADDR
     * Offset: 0x08  OTP Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |ADDR      |OTP Address
     * |        |          |OTP_ADDR register is byte addressable.
     * |        |          |If OTP_ADDR is written to illegal region and START(OTP_CTL[0]) bit is triggered, ADDRFF(OTP_STS[2]) will be set and this operation will not be executed.
     * @var OTP_T::DATA
     * Offset: 0x0C  OTP Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |OTP Data
     * |        |          |Writing data to OTP_DATA register before OTP program operation.
     * |        |          |Reading data from OTP_DATA register after OTP read operation.
     * |        |          |Writing password, 0x55aa_92d6, before OTP read only lock operation or OTP Fault Tolerance Mechanism operation.
     * @var OTP_T::USMSTS0
     * Offset: 0x10  OTP Unused Spare Memory 0 Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:2]   |BLK1      |Block 1 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 2.
     * |[5:4]   |BLK2      |Block 2 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 0.
     * |[7:6]   |BLK3      |Block 3 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 2.
     * |[9:8]   |BLK4      |Block 4 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 2.
     * |[11:10] |BLK5      |Block 5 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 0.
     * |[13:12] |BLK6      |Block 6 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 0.
     * |[15:14] |BLK7      |Block 7 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 0.
     * |[17:16] |BLK8      |Block 8 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * |[19:18] |BLK9      |Block 9 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * |[21:20] |BLK10     |Block 10 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * |[23:22] |BLK11     |Block 11 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * |[25:24] |BLK12     |Block 12 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * |[27:26] |BLK13     |Block 13 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * |[29:28] |BLK14     |Block 14 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * |[31:30] |BLK15     |Block 15 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * @var OTP_T::USMSTS1
     * Offset: 0x14  OTP Unused Spare Memory 1 Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |BLK16     |Block 16 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 1.
     * @var OTP_T::OTP_CTL
     * Offset: 0x800  Non-secure OTP Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |OTP Start Control Bit
     * |        |          |0 = No operation.
     * |        |          |1 = Start the operation.
     * |[6:4]   |CMD       |OTP Command Selection Bits
     * |        |          |0x0 = Read command.
     * |        |          |0x1 = Program command.
     * |        |          |0x2 = Read only lock command.
     * |        |          |0x3 = Fault Tolerance Mechanism command.
     * |        |          |0x7 = Read checker command.
     * |        |          |0xB = Read company ID
     * |        |          |0xC = Read device ID
     * |        |          |0xD = Read unique ID
     * |        |          |Others = reserved.
     * @var OTP_T::OTP_STS
     * Offset: 0x804  Non-secure OTP Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |OTP Busy Flag (Read Only)
     * |        |          |0 = OTP is idle or finished.
     * |        |          |1 = OTP is busy.
     * |[1]     |PFF       |OTP Program Fail Flag (Write 1 to Clear)
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No OTP programming operation failed.
     * |        |          |1 = OTP programming operation failed.
     * |[2]     |ADDRFF    |OTP Address Fail Flag (Write 1 to Clear)
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = OTP Address is legal.
     * |        |          |1 = OTP Address is illegal.
     * |[3]     |FTMFF     |OTP Fault Tolerance Mechanism Fail Flag (Write 1 to Clear)
     * |        |          |This bit is set after Fault Tolerance Mechanism command is triggered and address is assigned to a block without available spare memory.
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No OTP fault tolerance mechanism failed.
     * |        |          |1 = OTP fault tolerance mechanism is failed.
     * |[4]     |CMDFF     |OTP Command Fail Flag (Write 1 to Clear)
     * |        |          |This bit is set after program command or Fault Tolerance Mechanism command is triggered and address is assigned to a locked block.
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No OTP command failed.
     * |        |          |1 = OTP command failed.
     * @var OTP_T::OTP_ADDR
     * Offset: 0x808  Non-secure OTP Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |ADDR      |OTP Address
     * |        |          |OTP_ADDR register is byte addressable.
     * |        |          |If OTP_ADDR is written to illegal region and START(OTP_CTL[0]) bit is triggered, ADDRFF(OTP_STS[2]) will be set and this operation will not be executed.
     * @var OTP_T::OTP_DATA
     * Offset: 0x80C  Non-secure OTP Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATA      |OTP Data
     * |        |          |Writing data to OTP_DATA register before OTP program operation.
     * |        |          |Reading data from OTP_DATA register after OTP read operation.
     * |        |          |Writing password, 0x55aa_92d6, before OTP read only lock operation or OTP Fault Tolerance Mechanism operation.
     * @var OTP_T::OTP_USMSTS
     * Offset: 0x810  Non-secure OTP Unused Spare Memory Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:6]   |BLK3      |Block 3 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 2.
     * |[9:8]   |BLK4      |Block 4 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 2.
     * |[15:14] |BLK7      |Block 7 Unused Spare Memory
     * |        |          |Maximum unused spare memory is 0.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] OTP Control Register                                             */
    __IO uint32_t STS;                   /*!< [0x0004] OTP Status Register                                              */
    __IO uint32_t ADDR;                  /*!< [0x0008] OTP Address Register                                             */
    __IO uint32_t DATA;                  /*!< [0x000c] OTP Data Register                                                */
    __I  uint32_t USMSTS0;               /*!< [0x0010] OTP Unused Spare Memory 0 Status Register                        */
    __I  uint32_t USMSTS1;               /*!< [0x0014] OTP Unused Spare Memory 1 Status Register                        */
    __I  uint32_t RESERVE0[506];
    __IO uint32_t OTP_CTL;               /*!< [0x0800] Non-secure OTP Control Register                                  */
    __IO uint32_t OTP_STS;               /*!< [0x0804] Non-secure OTP Status Register                                   */
    __IO uint32_t OTP_ADDR;              /*!< [0x0808] Non-secure OTP Address Register                                  */
    __IO uint32_t OTP_DATA;              /*!< [0x080c] Non-secure OTP Data Register                                     */
    __I  uint32_t OTP_USMSTS;            /*!< [0x0810] Non-secure OTP Unused Spare Memory Status Register               */

} OTP_T;

/**
    @addtogroup OTP_CONST OTP Bit Field Definition
    Constant Definitions for OTP Controller
@{ */

#define OTP_CTL_START_Pos                (0)                                               /*!< OTP_T::CTL: START Position             */
#define OTP_CTL_START_Msk                (0x1ul << OTP_CTL_START_Pos)                      /*!< OTP_T::CTL: START Mask                 */

#define OTP_CTL_CMD_Pos                  (4)                                               /*!< OTP_T::CTL: CMD Position               */
#define OTP_CTL_CMD_Msk                  (0xful << OTP_CTL_CMD_Pos)                        /*!< OTP_T::CTL: CMD Mask                   */

#define OTP_STS_BUSY_Pos                 (0)                                               /*!< OTP_T::STS: BUSY Position              */
#define OTP_STS_BUSY_Msk                 (0x1ul << OTP_STS_BUSY_Pos)                       /*!< OTP_T::STS: BUSY Mask                  */

#define OTP_STS_PFF_Pos                  (1)                                               /*!< OTP_T::STS: PFF Position               */
#define OTP_STS_PFF_Msk                  (0x1ul << OTP_STS_PFF_Pos)                        /*!< OTP_T::STS: PFF Mask                   */

#define OTP_STS_ADDRFF_Pos               (2)                                               /*!< OTP_T::STS: ADDRFF Position            */
#define OTP_STS_ADDRFF_Msk               (0x1ul << OTP_STS_ADDRFF_Pos)                     /*!< OTP_T::STS: ADDRFF Mask                */

#define OTP_STS_FTMFF_Pos                (3)                                               /*!< OTP_T::STS: FTMFF Position             */
#define OTP_STS_FTMFF_Msk                (0x1ul << OTP_STS_FTMFF_Pos)                      /*!< OTP_T::STS: FTMFF Mask                 */

#define OTP_STS_CMDFF_Pos                (4)                                               /*!< OTP_T::STS: CMDFF Position             */
#define OTP_STS_CMDFF_Msk                (0x1ul << OTP_STS_CMDFF_Pos)                      /*!< OTP_T::STS: CMDFF Mask                 */

#define OTP_ADDR_ADDR_Pos                (0)                                               /*!< OTP_T::ADDR: ADDR Position             */
#define OTP_ADDR_ADDR_Msk                (0xffful << OTP_ADDR_ADDR_Pos)                    /*!< OTP_T::ADDR: ADDR Mask                 */

#define OTP_DATA_DATA_Pos                (0)                                               /*!< OTP_T::DATA: DATA Position             */
#define OTP_DATA_DATA_Msk                (0xfffffffful << OTP_DATA_DATA_Pos)               /*!< OTP_T::DATA: DATA Mask                 */

#define OTP_USMSTS0_BLK1_Pos             (2)                                               /*!< OTP_T::USMSTS0: BLK1 Position          */
#define OTP_USMSTS0_BLK1_Msk             (0x3ul << OTP_USMSTS0_BLK1_Pos)                   /*!< OTP_T::USMSTS0: BLK1 Mask              */

#define OTP_USMSTS0_BLK2_Pos             (4)                                               /*!< OTP_T::USMSTS0: BLK2 Position          */
#define OTP_USMSTS0_BLK2_Msk             (0x3ul << OTP_USMSTS0_BLK2_Pos)                   /*!< OTP_T::USMSTS0: BLK2 Mask              */

#define OTP_USMSTS0_BLK3_Pos             (6)                                               /*!< OTP_T::USMSTS0: BLK3 Position          */
#define OTP_USMSTS0_BLK3_Msk             (0x3ul << OTP_USMSTS0_BLK3_Pos)                   /*!< OTP_T::USMSTS0: BLK3 Mask              */

#define OTP_USMSTS0_BLK4_Pos             (8)                                               /*!< OTP_T::USMSTS0: BLK4 Position          */
#define OTP_USMSTS0_BLK4_Msk             (0x3ul << OTP_USMSTS0_BLK4_Pos)                   /*!< OTP_T::USMSTS0: BLK4 Mask              */

#define OTP_USMSTS0_BLK5_Pos             (10)                                              /*!< OTP_T::USMSTS0: BLK5 Position          */
#define OTP_USMSTS0_BLK5_Msk             (0x3ul << OTP_USMSTS0_BLK5_Pos)                   /*!< OTP_T::USMSTS0: BLK5 Mask              */

#define OTP_USMSTS0_BLK6_Pos             (12)                                              /*!< OTP_T::USMSTS0: BLK6 Position          */
#define OTP_USMSTS0_BLK6_Msk             (0x3ul << OTP_USMSTS0_BLK6_Pos)                   /*!< OTP_T::USMSTS0: BLK6 Mask              */

#define OTP_USMSTS0_BLK7_Pos             (14)                                              /*!< OTP_T::USMSTS0: BLK7 Position          */
#define OTP_USMSTS0_BLK7_Msk             (0x3ul << OTP_USMSTS0_BLK7_Pos)                   /*!< OTP_T::USMSTS0: BLK7 Mask              */

#define OTP_USMSTS0_BLK8_Pos             (16)                                              /*!< OTP_T::USMSTS0: BLK8 Position          */
#define OTP_USMSTS0_BLK8_Msk             (0x3ul << OTP_USMSTS0_BLK8_Pos)                   /*!< OTP_T::USMSTS0: BLK8 Mask              */

#define OTP_USMSTS0_BLK9_Pos             (18)                                              /*!< OTP_T::USMSTS0: BLK9 Position          */
#define OTP_USMSTS0_BLK9_Msk             (0x3ul << OTP_USMSTS0_BLK9_Pos)                   /*!< OTP_T::USMSTS0: BLK9 Mask              */

#define OTP_USMSTS0_BLK10_Pos            (20)                                              /*!< OTP_T::USMSTS0: BLK10 Position         */
#define OTP_USMSTS0_BLK10_Msk            (0x3ul << OTP_USMSTS0_BLK10_Pos)                  /*!< OTP_T::USMSTS0: BLK10 Mask             */

#define OTP_USMSTS0_BLK11_Pos            (22)                                              /*!< OTP_T::USMSTS0: BLK11 Position         */
#define OTP_USMSTS0_BLK11_Msk            (0x3ul << OTP_USMSTS0_BLK11_Pos)                  /*!< OTP_T::USMSTS0: BLK11 Mask             */

#define OTP_USMSTS0_BLK12_Pos            (24)                                              /*!< OTP_T::USMSTS0: BLK12 Position         */
#define OTP_USMSTS0_BLK12_Msk            (0x3ul << OTP_USMSTS0_BLK12_Pos)                  /*!< OTP_T::USMSTS0: BLK12 Mask             */

#define OTP_USMSTS0_BLK13_Pos            (26)                                              /*!< OTP_T::USMSTS0: BLK13 Position         */
#define OTP_USMSTS0_BLK13_Msk            (0x3ul << OTP_USMSTS0_BLK13_Pos)                  /*!< OTP_T::USMSTS0: BLK13 Mask             */

#define OTP_USMSTS0_BLK14_Pos            (28)                                              /*!< OTP_T::USMSTS0: BLK14 Position         */
#define OTP_USMSTS0_BLK14_Msk            (0x3ul << OTP_USMSTS0_BLK14_Pos)                  /*!< OTP_T::USMSTS0: BLK14 Mask             */

#define OTP_USMSTS0_BLK15_Pos            (30)                                              /*!< OTP_T::USMSTS0: BLK15 Position         */
#define OTP_USMSTS0_BLK15_Msk            (0x3ul << OTP_USMSTS0_BLK15_Pos)                  /*!< OTP_T::USMSTS0: BLK15 Mask             */

#define OTP_USMSTS1_BLK16_Pos            (0)                                               /*!< OTP_T::USMSTS1: BLK16 Position         */
#define OTP_USMSTS1_BLK16_Msk            (0x3ul << OTP_USMSTS1_BLK16_Pos)                  /*!< OTP_T::USMSTS1: BLK16 Mask             */

#define OTP_OTP_CTL_START_Pos            (0)                                               /*!< OTP_T::OTP_CTL: START Position         */
#define OTP_OTP_CTL_START_Msk            (0x1ul << OTP_OTP_CTL_START_Pos)                  /*!< OTP_T::OTP_CTL: START Mask             */

#define OTP_OTP_CTL_CMD_Pos              (4)                                               /*!< OTP_T::OTP_CTL: CMD Position           */
#define OTP_OTP_CTL_CMD_Msk              (0x7ul << OTP_OTP_CTL_CMD_Pos)                    /*!< OTP_T::OTP_CTL: CMD Mask               */

#define OTP_OTP_STS_BUSY_Pos             (0)                                               /*!< OTP_T::OTP_STS: BUSY Position          */
#define OTP_OTP_STS_BUSY_Msk             (0x1ul << OTP_OTP_STS_BUSY_Pos)                   /*!< OTP_T::OTP_STS: BUSY Mask              */

#define OTP_OTP_STS_PFF_Pos              (1)                                               /*!< OTP_T::OTP_STS: PFF Position           */
#define OTP_OTP_STS_PFF_Msk              (0x1ul << OTP_OTP_STS_PFF_Pos)                    /*!< OTP_T::OTP_STS: PFF Mask               */

#define OTP_OTP_STS_ADDRFF_Pos           (2)                                               /*!< OTP_T::OTP_STS: ADDRFF Position        */
#define OTP_OTP_STS_ADDRFF_Msk           (0x1ul << OTP_OTP_STS_ADDRFF_Pos)                 /*!< OTP_T::OTP_STS: ADDRFF Mask            */

#define OTP_OTP_STS_FTMFF_Pos            (3)                                               /*!< OTP_T::OTP_STS: FTMFF Position         */
#define OTP_OTP_STS_FTMFF_Msk            (0x1ul << OTP_OTP_STS_FTMFF_Pos)                  /*!< OTP_T::OTP_STS: FTMFF Mask             */

#define OTP_OTP_STS_CMDFF_Pos            (4)                                               /*!< OTP_T::OTP_STS: CMDFF Position         */
#define OTP_OTP_STS_CMDFF_Msk            (0x1ul << OTP_OTP_STS_CMDFF_Pos)                  /*!< OTP_T::OTP_STS: CMDFF Mask             */

#define OTP_OTP_ADDR_ADDR_Pos            (0)                                               /*!< OTP_T::OTP_ADDR: ADDR Position         */
#define OTP_OTP_ADDR_ADDR_Msk            (0xffful << OTP_OTP_ADDR_ADDR_Pos)                /*!< OTP_T::OTP_ADDR: ADDR Mask             */

#define OTP_OTP_DATA_DATA_Pos            (0)                                               /*!< OTP_T::OTP_DATA: DATA Position         */
#define OTP_OTP_DATA_DATA_Msk            (0xfffffffful << OTP_OTP_DATA_DATA_Pos)           /*!< OTP_T::OTP_DATA: DATA Mask             */

#define OTP_OTP_USMSTS_BLK3_Pos          (6)                                               /*!< OTP_T::OTP_USMSTS: BLK3 Position       */
#define OTP_OTP_USMSTS_BLK3_Msk          (0x3ul << OTP_OTP_USMSTS_BLK3_Pos)                /*!< OTP_T::OTP_USMSTS: BLK3 Mask           */

#define OTP_OTP_USMSTS_BLK4_Pos          (8)                                               /*!< OTP_T::OTP_USMSTS: BLK4 Position       */
#define OTP_OTP_USMSTS_BLK4_Msk          (0x3ul << OTP_OTP_USMSTS_BLK4_Pos)                /*!< OTP_T::OTP_USMSTS: BLK4 Mask           */

#define OTP_OTP_USMSTS_BLK7_Pos          (14)                                              /*!< OTP_T::OTP_USMSTS: BLK7 Position       */
#define OTP_OTP_USMSTS_BLK7_Msk          (0x3ul << OTP_OTP_USMSTS_BLK7_Pos)                /*!< OTP_T::OTP_USMSTS: BLK7 Mask           */

/**@}*/ /* OTP_CONST */
/**@}*/ /* end of OTP register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif  //__OTP_REG_H__
