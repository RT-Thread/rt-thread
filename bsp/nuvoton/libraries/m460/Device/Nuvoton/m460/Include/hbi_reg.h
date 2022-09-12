/**************************************************************************//**
 * @file     hbi_reg.h
 * @version  V1.00
 * @brief    HBI register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HBI_REG_H__
#define __HBI_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup  Hyper Bus Interface Controller (HBI)
    Memory Mapped Structure for HBI Controller
@{ */
typedef struct
{


    /**
     * @var HBI_T::CMD
     * Offset: 0x00  HyperBus Command and Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |HYPCMD    |HyperBus Command and Status
     * |        |          |Write
     * |        |          |0001 = Reset HyperRAM.
     * |        |          |0010 = Read HyperRAM regsiter (16-Bit, Read Data[15:0].
     * |        |          |0101 = Exit From Hybrid Sleep and deep power down.
     * |        |          |0111 = Write HyperRAM regsiter (16-Bit, Write Data[15:0].
     * |        |          |1000 = Read 1 word (Read Data[15:0]) from HyperRAM.
     * |        |          |1001 = Read 2 word (Read Data[31:0]) from HyperRAM.
     * |        |          |1100 = Write 1 Byte (Write Data[7:0]) to HyperRAM.
     * |        |          |1101 = Write 2 Bytes (Write Data[15:0]) to HyperRAM.
     * |        |          |1110 = Write 3 Byte (Write Data[23:0]) to HyperRAM.
     * |        |          |1111 = Write 4 Byte (Write Data[31:0]) to HyperRAM.
     * |        |          |Other value = reserved.
     * |        |          |Read
     * |        |          |0000 = HyperBus interface is Idle.
     * |        |          |Other value = HyperBus interface is busy.
     * |        |          |Note: When an operation is Done, the read value automatically return to 4'b0000.
     * @var HBI_T::CONFIG
     * Offset: 0x04  HyperBus Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |CSST      |Chip Select Setup Time to Next CK Rising Edge
     * |        |          |This field indicates the setup time between the chip select and the next CK rising edge
     * |        |          |00 = 1.5 HCLK cycles.
     * |        |          |01 = 2.5 HCLK cycles.
     * |        |          |10 = 3.5 HCLK cycles.
     * |        |          |11 = 4.5 HCLK cycles.
     * |[5:2]   |ACCT      |Initial Access Time
     * |        |          |This field indicates the initial access cycles of the Hyper Bus transaction
     * |        |          |0000 = 5 CK cycles.
     * |        |          |0001 = 6 CK cycles.
     * |        |          |0010 = 7 CK cycles.
     * |        |          |1110 = 3 CK cycles.
     * |        |          |1111 = 4 CK cycles.
     * |        |          |Others = Reserved.
     * |        |          |Note: This field must be set to the same value as
     * |        |          |initial Latency in HyperRAM Configuration Register 0.
     * |[7:6]   |CSH       |Chip Select Hold Time After CK Falling Edge
     * |        |          |This field indicates the hold time between the last CK falling edge and chip select
     * |        |          |00 = 0.5 HCLK cycles.
     * |        |          |01 = 1.5 HCLK cycles.
     * |        |          |10 = 2.5 HCLK cycles.
     * |        |          |11 = 3.5 HCLK cycles.
     * |[11:8]  |CSHI      |Chip Select High between Transaction
     * |        |          |This field indicates the inactive period between two Hyper Bus transactions
     * |        |          |0000 = 1 HCLK cycle.
     * |        |          |0001 = 2 HCLK cycles.
     * |        |          |0010 = 3 HCLK cycles.
     * |        |          |0011 = 4 HCLK cycles.
     * |        |          |...
     * |        |          |1111 = 16 HCLK cycles.
     * |        |          |Note : This field must meet the HyperRAM device specification of tCSHI.
     * |[13:12] |BGSIZE    |Burst Group Size
     * |        |          |This field indicates the burst length on the Hyper Bus transaction
     * |        |          |00 = 128 Bytes.
     * |        |          |01 = 64 Bytes.
     * |        |          |10 = 16 Bytes.
     * |        |          |11 = 32 Bytes.
     * |        |          |Note : This field must be set to the same value as burst Length in HyperRAM Configuration Regsiter 0.
     * |[14]      |ENDIAN      |Endian Condition on the Hyper Bus Data Pipe
     * |        |          |0 = Little-Endian.
     * |        |          |   Byte A = Bits[7:0] of a 16-Bit  ..........word
     * |        |          |   Byte B = Bits[15:8] of a 16-Bit ..........word
     * |        |          |1 = Big-Endia.
     * |        |          |   Byte A = Bits[15:8] of a 16-Bit ..........word
     * |        |          |   Byte B = Bits[7:0] of a 16-Bit  ..........word
     * |[15]    |CKDIV     |Hyper Bus Clock Divider
     * |        |          | 0 = Hyper Bus Clock rate is HCLK/2.
     * |        |          | 1 = Hyper Bus Clock rate is HCLK/4.
     * |[26:16] |CSMAXLT     |Chip Select Maximum Low Time
     * |        |          | This field indicates the maximum Low period of the  chip select (CS#) in one transaction
     * |        |          | 00000000000 = 1 HCLK cycle.
     * |        |          | 00000000001 = 2 HCLK cycles.
     * |        |          | 00000000010 = 3 HCLK cycles.
     * |        |          | 00000000011 = 4 HCLK cycles.
     * |        |          | ...
     * |        |          | 01011101100 = 749 HCLK cycles (3.9us @192 MHz).
     * |        |          | ...
     * |        |          | 11111111110 = 2047 HCLK cycles.
     * |        |          | 11111111111 = 2048 HCLK cycles.
     * |        |          | Note: This field inidcates the timing of HyperRAM Chip Select specification so that it has to relative the frequency of HCLK and the CLKDIV (HBI_CONFIG[15]).
     * @var HBI_T::ADR
     * Offset: 0x08  HyperBus Byte Address access Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |HBI_ADR   |HyperBus Byte Address
     * |        |          |Memory Space Range:
     * |        |          |   0x0000_0000 ~ 0x01FF_FFFF
     * |        |          |Register Space Range:
     * |        |          |   0X0000_0000 = Identification Register 0
     * |        |          |   0X0000_0002 = Identification Register 1
     * |        |          |   0X0000_1000 = Configuration Register 0
     * |        |          |   0X0000_1002 = Configuration Register 1
     * |        |          |Note:
     * |        |          |1.  It is "Byte" address, not "word" address
     * |        |          |2.  Up to 32M Bytes of memory space is supported.
     * @var HBI_T::WDATA
     * Offset: 0x0C  HyperBus 32-Bits Write Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |WDATA     |HyperBus 32-Bits Write Data
     * |        |          |To write 1 Byte to HyperRAM, Byte 0 (Data[7:0]) is used
     * |        |          |To write 2 Bytes to HyperRAM, Byte 1~0 (Data[15:0]) is used
     * |        |          |To write 3 Bytes to HyperRAM, Byte 2~0 (Data[23:0]) is used
     * |        |          |To write 4 Bytes to HyperRAM, Byte 3~ (Data[31:0]) is used
     * @var HBI_T::RDATA
     * Offset: 0x10  HyperBus 32-Bits Read Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RDATA     |HyperBus 32-Bits Read Data
     * |        |          |32-Bits Data for HyperBus Read
     * |        |          |Note: The data order is depened on the ENDIAN (HBI_CONFIG[14]). Refer to 1.1.5.4 for detail information.
     * @var HBI_T::INTEN
     * Offset: 0x14  HyperBus Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]   |OPINTEN   |HyperBus Operation Done Interrupt Enable
     * |        |          |0 = Operation done interrupt is Disab led.
     * |        |          |1 = Operation done interrupt is Enabled.
     * @var HBI_T::INTSTS
     * Offset: 0x18  HyperBus Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |OPDONE    |HyperBus Operation Done Interrupt
     * |        |          |0 = HyperBus operation is busy.
     * |        |          |1 = HyperBus operation is done.
     */
    __IO uint32_t CMD ;               /*!< [0x0000] HyperBus Command and Status Register         */
    __IO uint32_t CONFIG;             /*!< [0x0004] HyperBus Configuration Register              */
    __IO uint32_t ADR;                /*!< [0x0008] HyperBus Byte Address access Register        */
    __IO uint32_t WDATA;              /*!< [0x000C] HyperBus 32-Bits Write Data Register         */
    __IO uint32_t RDATA;              /*!< [0x0010] HyperBus 32-Bits Read Data Register          */
    __IO uint32_t INTEN;              /*!< [0x0014] HyperBus Interrupt Enable Register           */
    __IO uint32_t INTSTS;             /*!< [0x0018] HyperBus Interrupt Status Register           */
} HBI_T;

/**
    @addtogroup HBI_CONST HBI Bit Field Definition
    Constant Definitions for HBI Controller
@{ */

#define HBI_CMD_HYPCMD_Pos               (0)                                            /*!< HBI_T::CMD: HYPCMD Position         */
#define HBI_CMD_HYPCMD_Msk               (0xful << HBI_CMD_HYPCMD_Pos)                  /*!< HBI_T::CMD: HYPCMD Mask             */

#define HBI_CONFIG_CSST_Pos              (0)                                            /*!< HBI_T::CONFIG: CSST Position        */
#define HBI_CONFIG_CSST_Msk              (0x3ul << HBI_CONFIG_CSST_Pos)                 /*!< HBI_T::CONFIG: CSST Mask            */

#define HBI_CONFIG_ACCT_Pos              (2)                                            /*!< HBI_T::CONFIG: ACCT Position        */
#define HBI_CONFIG_ACCT_Msk              (0xful << HBI_CONFIG_ACCT_Pos)                 /*!< HBI_T::CONFIG: ACCT Mask            */

#define HBI_CONFIG_CSH_Pos               (6)                                            /*!< HBI_T::CONFIG: CSH Position         */
#define HBI_CONFIG_CSH_Msk               (0x3ul << HBI_CONFIG_CSH_Pos)                  /*!< HBI_T::CONFIG: CSH Mask             */

#define HBI_CONFIG_CSHI_Pos              (8)                                            /*!< HBI_T::CONFIG: CSHI Position        */
#define HBI_CONFIG_CSHI_Msk              (0xful << HBI_CONFIG_CSHI_Pos)                 /*!< HBI_T::CONFIG: CSHI Mask            */

#define HBI_CONFIG_BGSIZE_Pos            (12)                                           /*!< HBI_T::CONFIG: BGSIZE Position      */
#define HBI_CONFIG_BGSIZE_Msk            (0x3ul << HBI_CONFIG_BGSIZE_Pos)               /*!< HBI_T::CONFIG: BGSIZE Mask          */

#define HBI_CONFIG_ENDIAN_Pos            (14)                                           /*!< HBI_T::CONFIG: ENDIAN Position      */
#define HBI_CONFIG_ENDIAN_Msk            (0x1ul << HBI_CONFIG_ENDIAN_Pos)               /*!< HBI_T::CONFIG: ENDIAN Mask          */

#define HBI_CONFIG_CKDIV_Pos             (15)                                           /*!< HBI_T::CONFIG: CKDIV Position       */
#define HBI_CONFIG_CKDIV_Msk             (0x1ul << HBI_CONFIG_CKDIV_Pos)                /*!< HBI_T::CONFIG: CKDIV Mask           */

#define HBI_CONFIG_CSMAXLT_Pos           (16)                                           /*!< HBI_T::CONFIG: CSMAXLT Position     */
#define HBI_CONFIG_CSMAXLT_Msk           (0x7fful << HBI_CONFIG_CSMAXLT_Pos)            /*!< HBI_T::CONFIG: CSMAXLT Mask         */

#define HBI_ADR_ADR_Pos                  (0)                                            /*!< HBI_T::ADR: ADR Position            */
#define HBI_ADR_ADR_Msk                  (0xfffffffful << HBI_ADR_ADR_Pos)                  /*!< HBI_T::ADR: ADR Mask                */

#define HBI_WDATA_WDATA_Pos              (0)                                            /*!< HBI_T::WDATA: WDATA Position        */
#define HBI_WDATA_WDATA_Msk              (0xfffffffful << HBI_WDATA_WDATA_Pos)              /*!< HBI_T::WDATA: WDATA Mask            */

#define HBI_RDATA_RDATA_Pos              (0)                                            /*!< HBI_T::RDATA: RDATA Position        */
#define HBI_RDATA_RDATA_Msk              (0xfffffffful << HBI_RDATA_RDATA_Pos)              /*!< HBI_T::RDATA: RDATA Mask            */

#define HBI_INTEN_OPINTEN_Pos            (0)                                            /*!< HBI_T::INTEN: OPINTEN Position      */
#define HBI_INTEN_OPINTEN_Msk            (0x1ul << HBI_INTEN_OPINTEN_Pos)               /*!< HBI_T::INTEN: OPINTEN Mask          */

#define HBI_INTSTS_OPDONE_Pos            (0)                                            /*!< HBI_T::INTSTS: OPDONE Position      */
#define HBI_INTSTS_OPDONE_Msk            (0x1ul << HBI_INTSTS_OPDONE_Pos)               /*!< HBI_T::INTSTS: OPDONE Mask          */


/**@}*/ /* HBI_CONST */
/**@}*/ /* end of HBI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __HBI_REG_H__ */
