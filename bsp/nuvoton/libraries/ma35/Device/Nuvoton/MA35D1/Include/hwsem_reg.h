/**************************************************************************//**
 * @file     hwsem_reg.h
 * @brief    HWSEM register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020~2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HWSEM_REG_H__
#define __HWSEM_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup HWSEM Hardware Semaphore (HWSEM)
    Memory Mapped Structure for HWSEM Controller
@{ */

typedef struct
{


    /**
     * @var HWSEM_T::CTL
     * Offset: 0x00  HWSEM Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SEM0RST   |Reset Semaphore 0
     * |        |          |Set this bit to reset semaphore 0
     * |        |          |After reset, SEM_SEM0 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * |[1]     |SEM1RST   |Reset Semaphore 1
     * |        |          |Set this bit to reset semaphore 1
     * |        |          |After reset, SEM_SEM1 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * |[2]     |SEM2RST   |Reset Semaphore 2
     * |        |          |Set this bit to reset semaphore 2
     * |        |          |After reset, SEM_SEM2 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * |[3]     |SEM3RST   |Reset Semaphore 3
     * |        |          |Set this bit to reset semaphore 3
     * |        |          |After reset, SEM_SEM3 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * |[4]     |SEM4RST   |Reset Semaphore 4
     * |        |          |Set this bit to reset semaphore 4
     * |        |          |After reset, SEM_SEM4 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * |[5]     |SEM5RST   |Reset Semaphore 5
     * |        |          |Set this bit to reset semaphore 5
     * |        |          |After reset, SEM_SEM5 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * |[6]     |SEM6RST   |Reset Semaphore 6
     * |        |          |Set this bit to reset semaphore 6
     * |        |          |After reset, SEM_SEM6 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * |[7]     |SEM7RST   |Reset Semaphore 7
     * |        |          |Set this bit to reset semaphore 7
     * |        |          |After reset, SEM_SEM7 will reset to 0
     * |        |          |This bit automatically clears to 0 after reset complete.
     * @var HWSEM_T::INTENA35
     * Offset: 0x04  HWSEM Interrupt Enable Register (A35 Can Read/Write ,M4 Can Only Read)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SEM0IEN   |Semaphore 0 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 0 unlock interrupt Disabled
     * |        |          |1 = Semaphore 0 unlock interrupt Enabled.
     * |[1]     |SEM1IEN   |Semaphore 1 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 1 unlock interrupt Disabled
     * |        |          |1 = Semaphore 1 unlock interrupt Enabled.
     * |[2]     |SEM2IEN   |Semaphore 2 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 2 unlock interrupt Disabled
     * |        |          |1 = Semaphore 2 unlock interrupt Enabled.
     * |[3]     |SEM3IEN   |Semaphore 3 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 3 unlock interrupt Disabled
     * |        |          |1 = Semaphore 3 unlock interrupt Enabled.
     * |[4]     |SEM4IEN   |Semaphore 4 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 4 unlock interrupt Disabled
     * |        |          |1 = Semaphore 4 unlock interrupt Enabled.
     * |[5]     |SEM5IEN   |Semaphore 5 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 5 unlock interrupt Disabled
     * |        |          |1 = Semaphore 5 unlock interrupt Enabled.
     * |[6]     |SEM6IEN   |Semaphore 6 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 6 unlock interrupt Disabled
     * |        |          |1 = Semaphore 6 unlock interrupt Enabled.
     * |[7]     |SEM7IEN   |Semaphore 7 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 7 unlock interrupt Disabled
     * |        |          |1 = Semaphore 7 unlock interrupt Enabled.
     * @var HWSEM_T::INTENM4
     * Offset: 0x08  HWSEM Interrupt Enable Register (M4 Can Read/Write , A35 Can Only Read)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SEM0IEN   |Semaphore 0 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 0 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 0 unlock interrupt Enabled.
     * |[1]     |SEM1IEN   |Semaphore 1 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 1 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 1 unlock interrupt Enabled.
     * |[2]     |SEM2IEN   |Semaphore 2 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 2 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 2 unlock interrupt Enabled.
     * |[3]     |SEM3IEN   |Semaphore 3 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 3 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 3 unlock interrupt Enabled.
     * |[4]     |SEM4IEN   |Semaphore 4 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 4 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 4 unlock interrupt Enabled.
     * |[5]     |SEM5IEN   |Semaphore 5 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 5 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 5 unlock interrupt Enabled.
     * |[6]     |SEM6IEN   |Semaphore 6 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 6 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 6 unlock interrupt Enabled.
     * |[7]     |SEM7IEN   |Semaphore 7 Unlock Interrupt Enable Bit
     * |        |          |0 = Semaphore 7 unlock interrupt Disabled.
     * |        |          |1 = Semaphore 7 unlock interrupt Enabled.
     * @var HWSEM_T::INTSTSA35
     * Offset: 0x0C  HWSEM Interrupt Status Register (A35 Can Read/Write ,M4 Can Only Read) (Write 1 to Clear)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SEM0IF    |Semaphore 0 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 0 unlock interrupt generated.
     * |        |          |1 = Semaphore 0 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[1]     |SEM1IF    |Semaphore 1 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 1 unlock interrupt generated.
     * |        |          |1 = Semaphore 1 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[2]     |SEM2IF    |Semaphore 2 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 2 unlock interrupt generated.
     * |        |          |1 = Semaphore 2 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[3]     |SEM3IF    |Semaphore 3 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 3 unlock interrupt generated.
     * |        |          |1 = Semaphore 3 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[4]     |SEM4IF    |Semaphore 4 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 4 unlock interrupt generated.
     * |        |          |1 = Semaphore 4 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[5]     |SEM5IF    |Semaphore 5 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 5 unlock interrupt generated.
     * |        |          |1 = Semaphore 5 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[6]     |SEM6IF    |Semaphore 6 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 6 unlock interrupt generated.
     * |        |          |1 = Semaphore 6 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[7]     |SEM7IF    |Semaphore 7 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 7 unlock interrupt generated.
     * |        |          |1 = Semaphore 7 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * @var HWSEM_T::INTSTSM4
     * Offset: 0x10  HWSEM Interrupt Status Register (M4 Can Read/Write , A35 Can Only Read) (Write 1 to Clear)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SEM0IF    |Semaphore 0 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 0 unlock interrupt generated.
     * |        |          |1 = Semaphore 0 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[1]     |SEM1IF    |Semaphore 1 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 1 unlock interrupt generated.
     * |        |          |1 = Semaphore 1 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[2]     |SEM2IF    |Semaphore 2 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 2 unlock interrupt generated.
     * |        |          |1 = Semaphore 2 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[3]     |SEM3IF    |Semaphore 3 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 3 unlock interrupt generated.
     * |        |          |1 = Semaphore 3 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[4]     |SEM4IF    |Semaphore 4 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 4 unlock interrupt generated.
     * |        |          |1 = Semaphore 4 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[5]     |SEM5IF    |Semaphore 5 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 5 unlock interrupt generated.
     * |        |          |1 = Semaphore 5 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[6]     |SEM6IF    |Semaphore 6 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 6 unlock interrupt generated.
     * |        |          |1 = Semaphore 6 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[7]     |SEM7IF    |Semaphore 7 Unlock Interrupt Flag
     * |        |          |0 = No semaphore 7 unlock interrupt generated.
     * |        |          |1 = Semaphore 7 unlock interrupt generated.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * @var HWSEM_T::SEM0
     * Offset: 0x20  HWSEM Semaphore 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     * @var HWSEM_T::SEM1
     * Offset: 0x24  HWSEM Semaphore 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     * @var HWSEM_T::SEM2
     * Offset: 0x28  HWSEM Semaphore 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     * @var HWSEM_T::SEM3
     * Offset: 0x2C  HWSEM Semaphore 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     * @var HWSEM_T::SEM4
     * Offset: 0x30  HWSEM Semaphore 4 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     * @var HWSEM_T::SEM5
     * Offset: 0x34  HWSEM Semaphore 5 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     * @var HWSEM_T::SEM6
     * Offset: 0x38  HWSEM Semaphore 6 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     * @var HWSEM_T::SEM7
     * Offset: 0x3C  HWSEM Semaphore 7 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |ID        |Processor ID (Read Only)
     * |        |          |This field holds the ID of Processor which lock this semaphore.
     * |        |          |0000 = Semaphore is unlocked.
     * |        |          |0001 = This semaphore is locked by Cortex-A.
     * |        |          |0010 = This semaphore is locked by Cortex-M.
     * |        |          |Others = Reserved.
     * |[15:8]  |KEY       |Key for Lock/Unlock Semaphore
     * |        |          |This field holds the key to lock/unlock this semaphore.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] HWSEM Control Register                                           */
    __IO uint32_t INTENA35;              /*!< [0x0004] HWSEM Interrupt Enable Register                                  */
    __IO uint32_t INTENM4;               /*!< [0x0008] HWSEM Interrupt Enable Register                                  */
    __IO uint32_t INTSTSA35;             /*!< [0x000c] HWSEM Interrupt Status Register                                  */
    __IO uint32_t INTSTSM4;              /*!< [0x0010] HWSEM Interrupt Status Register                                  */
    __I  uint32_t RESERVE0[3];
    __IO uint32_t SEM[8];                /*!< [0x0020~0x003C] HWSEM Semaphore 0~8 Register                              */
} HWSEM_T;

/**
    @addtogroup HWSEM_CONST HWSEM Bit Field Definition
    Constant Definitions for HWSEM Controller
@{ */

#define HWSEM_CTL_SEM0RST_Pos            (0)                                               /*!< HWSEM_T::CTL: SEM0RST Position         */
#define HWSEM_CTL_SEM0RST_Msk            (0x1ul << HWSEM_CTL_SEM0RST_Pos)                  /*!< HWSEM_T::CTL: SEM0RST Mask             */

#define HWSEM_CTL_SEM1RST_Pos            (1)                                               /*!< HWSEM_T::CTL: SEM1RST Position         */
#define HWSEM_CTL_SEM1RST_Msk            (0x1ul << HWSEM_CTL_SEM1RST_Pos)                  /*!< HWSEM_T::CTL: SEM1RST Mask             */

#define HWSEM_CTL_SEM2RST_Pos            (2)                                               /*!< HWSEM_T::CTL: SEM2RST Position         */
#define HWSEM_CTL_SEM2RST_Msk            (0x1ul << HWSEM_CTL_SEM2RST_Pos)                  /*!< HWSEM_T::CTL: SEM2RST Mask             */

#define HWSEM_CTL_SEM3RST_Pos            (3)                                               /*!< HWSEM_T::CTL: SEM3RST Position         */
#define HWSEM_CTL_SEM3RST_Msk            (0x1ul << HWSEM_CTL_SEM3RST_Pos)                  /*!< HWSEM_T::CTL: SEM3RST Mask             */

#define HWSEM_CTL_SEM4RST_Pos            (4)                                               /*!< HWSEM_T::CTL: SEM4RST Position         */
#define HWSEM_CTL_SEM4RST_Msk            (0x1ul << HWSEM_CTL_SEM4RST_Pos)                  /*!< HWSEM_T::CTL: SEM4RST Mask             */

#define HWSEM_CTL_SEM5RST_Pos            (5)                                               /*!< HWSEM_T::CTL: SEM5RST Position         */
#define HWSEM_CTL_SEM5RST_Msk            (0x1ul << HWSEM_CTL_SEM5RST_Pos)                  /*!< HWSEM_T::CTL: SEM5RST Mask             */

#define HWSEM_CTL_SEM6RST_Pos            (6)                                               /*!< HWSEM_T::CTL: SEM6RST Position         */
#define HWSEM_CTL_SEM6RST_Msk            (0x1ul << HWSEM_CTL_SEM6RST_Pos)                  /*!< HWSEM_T::CTL: SEM6RST Mask             */

#define HWSEM_CTL_SEM7RST_Pos            (7)                                               /*!< HWSEM_T::CTL: SEM7RST Position         */
#define HWSEM_CTL_SEM7RST_Msk            (0x1ul << HWSEM_CTL_SEM7RST_Pos)                  /*!< HWSEM_T::CTL: SEM7RST Mask             */

#define HWSEM_INTENA35_SEM0IEN_Pos       (0)                                               /*!< HWSEM_T::INTENA35: SEM0IEN Position    */
#define HWSEM_INTENA35_SEM0IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM0IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM0IEN Mask        */

#define HWSEM_INTENA35_SEM1IEN_Pos       (1)                                               /*!< HWSEM_T::INTENA35: SEM1IEN Position    */
#define HWSEM_INTENA35_SEM1IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM1IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM1IEN Mask        */

#define HWSEM_INTENA35_SEM2IEN_Pos       (2)                                               /*!< HWSEM_T::INTENA35: SEM2IEN Position    */
#define HWSEM_INTENA35_SEM2IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM2IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM2IEN Mask        */

#define HWSEM_INTENA35_SEM3IEN_Pos       (3)                                               /*!< HWSEM_T::INTENA35: SEM3IEN Position    */
#define HWSEM_INTENA35_SEM3IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM3IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM3IEN Mask        */

#define HWSEM_INTENA35_SEM4IEN_Pos       (4)                                               /*!< HWSEM_T::INTENA35: SEM4IEN Position    */
#define HWSEM_INTENA35_SEM4IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM4IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM4IEN Mask        */

#define HWSEM_INTENA35_SEM5IEN_Pos       (5)                                               /*!< HWSEM_T::INTENA35: SEM5IEN Position    */
#define HWSEM_INTENA35_SEM5IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM5IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM5IEN Mask        */

#define HWSEM_INTENA35_SEM6IEN_Pos       (6)                                               /*!< HWSEM_T::INTENA35: SEM6IEN Position    */
#define HWSEM_INTENA35_SEM6IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM6IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM6IEN Mask        */

#define HWSEM_INTENA35_SEM7IEN_Pos       (7)                                               /*!< HWSEM_T::INTENA35: SEM7IEN Position    */
#define HWSEM_INTENA35_SEM7IEN_Msk       (0x1ul << HWSEM_INTENA35_SEM7IEN_Pos)             /*!< HWSEM_T::INTENA35: SEM7IEN Mask        */

#define HWSEM_INTENM4_SEM0IEN_Pos        (0)                                               /*!< HWSEM_T::INTENM4: SEM0IEN Position     */
#define HWSEM_INTENM4_SEM0IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM0IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM0IEN Mask         */

#define HWSEM_INTENM4_SEM1IEN_Pos        (1)                                               /*!< HWSEM_T::INTENM4: SEM1IEN Position     */
#define HWSEM_INTENM4_SEM1IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM1IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM1IEN Mask         */

#define HWSEM_INTENM4_SEM2IEN_Pos        (2)                                               /*!< HWSEM_T::INTENM4: SEM2IEN Position     */
#define HWSEM_INTENM4_SEM2IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM2IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM2IEN Mask         */

#define HWSEM_INTENM4_SEM3IEN_Pos        (3)                                               /*!< HWSEM_T::INTENM4: SEM3IEN Position     */
#define HWSEM_INTENM4_SEM3IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM3IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM3IEN Mask         */

#define HWSEM_INTENM4_SEM4IEN_Pos        (4)                                               /*!< HWSEM_T::INTENM4: SEM4IEN Position     */
#define HWSEM_INTENM4_SEM4IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM4IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM4IEN Mask         */

#define HWSEM_INTENM4_SEM5IEN_Pos        (5)                                               /*!< HWSEM_T::INTENM4: SEM5IEN Position     */
#define HWSEM_INTENM4_SEM5IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM5IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM5IEN Mask         */

#define HWSEM_INTENM4_SEM6IEN_Pos        (6)                                               /*!< HWSEM_T::INTENM4: SEM6IEN Position     */
#define HWSEM_INTENM4_SEM6IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM6IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM6IEN Mask         */

#define HWSEM_INTENM4_SEM7IEN_Pos        (7)                                               /*!< HWSEM_T::INTENM4: SEM7IEN Position     */
#define HWSEM_INTENM4_SEM7IEN_Msk        (0x1ul << HWSEM_INTENM4_SEM7IEN_Pos)              /*!< HWSEM_T::INTENM4: SEM7IEN Mask         */

#define HWSEM_INTSTSA35_SEM0IF_Pos       (0)                                               /*!< HWSEM_T::INTSTSA35: SEM0IF Position    */
#define HWSEM_INTSTSA35_SEM0IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM0IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM0IF Mask        */

#define HWSEM_INTSTSA35_SEM1IF_Pos       (1)                                               /*!< HWSEM_T::INTSTSA35: SEM1IF Position    */
#define HWSEM_INTSTSA35_SEM1IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM1IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM1IF Mask        */

#define HWSEM_INTSTSA35_SEM2IF_Pos       (2)                                               /*!< HWSEM_T::INTSTSA35: SEM2IF Position    */
#define HWSEM_INTSTSA35_SEM2IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM2IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM2IF Mask        */

#define HWSEM_INTSTSA35_SEM3IF_Pos       (3)                                               /*!< HWSEM_T::INTSTSA35: SEM3IF Position    */
#define HWSEM_INTSTSA35_SEM3IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM3IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM3IF Mask        */

#define HWSEM_INTSTSA35_SEM4IF_Pos       (4)                                               /*!< HWSEM_T::INTSTSA35: SEM4IF Position    */
#define HWSEM_INTSTSA35_SEM4IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM4IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM4IF Mask        */

#define HWSEM_INTSTSA35_SEM5IF_Pos       (5)                                               /*!< HWSEM_T::INTSTSA35: SEM5IF Position    */
#define HWSEM_INTSTSA35_SEM5IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM5IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM5IF Mask        */

#define HWSEM_INTSTSA35_SEM6IF_Pos       (6)                                               /*!< HWSEM_T::INTSTSA35: SEM6IF Position    */
#define HWSEM_INTSTSA35_SEM6IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM6IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM6IF Mask        */

#define HWSEM_INTSTSA35_SEM7IF_Pos       (7)                                               /*!< HWSEM_T::INTSTSA35: SEM7IF Position    */
#define HWSEM_INTSTSA35_SEM7IF_Msk       (0x1ul << HWSEM_INTSTSA35_SEM7IF_Pos)             /*!< HWSEM_T::INTSTSA35: SEM7IF Mask        */

#define HWSEM_INTSTSM4_SEM0IF_Pos        (0)                                               /*!< HWSEM_T::INTSTSM4: SEM0IF Position     */
#define HWSEM_INTSTSM4_SEM0IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM0IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM0IF Mask         */

#define HWSEM_INTSTSM4_SEM1IF_Pos        (1)                                               /*!< HWSEM_T::INTSTSM4: SEM1IF Position     */
#define HWSEM_INTSTSM4_SEM1IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM1IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM1IF Mask         */

#define HWSEM_INTSTSM4_SEM2IF_Pos        (2)                                               /*!< HWSEM_T::INTSTSM4: SEM2IF Position     */
#define HWSEM_INTSTSM4_SEM2IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM2IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM2IF Mask         */

#define HWSEM_INTSTSM4_SEM3IF_Pos        (3)                                               /*!< HWSEM_T::INTSTSM4: SEM3IF Position     */
#define HWSEM_INTSTSM4_SEM3IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM3IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM3IF Mask         */

#define HWSEM_INTSTSM4_SEM4IF_Pos        (4)                                               /*!< HWSEM_T::INTSTSM4: SEM4IF Position     */
#define HWSEM_INTSTSM4_SEM4IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM4IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM4IF Mask         */

#define HWSEM_INTSTSM4_SEM5IF_Pos        (5)                                               /*!< HWSEM_T::INTSTSM4: SEM5IF Position     */
#define HWSEM_INTSTSM4_SEM5IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM5IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM5IF Mask         */

#define HWSEM_INTSTSM4_SEM6IF_Pos        (6)                                               /*!< HWSEM_T::INTSTSM4: SEM6IF Position     */
#define HWSEM_INTSTSM4_SEM6IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM6IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM6IF Mask         */

#define HWSEM_INTSTSM4_SEM7IF_Pos        (7)                                               /*!< HWSEM_T::INTSTSM4: SEM7IF Position     */
#define HWSEM_INTSTSM4_SEM7IF_Msk        (0x1ul << HWSEM_INTSTSM4_SEM7IF_Pos)              /*!< HWSEM_T::INTSTSM4: SEM7IF Mask         */

#define HWSEM_SEM_ID_Pos                 (0)
#define HWSEM_SEM_ID_Msk                 (0xful << HWSEM_SEM_ID_Pos)

#define HWSEM_SEM_KEY_Pos                (8)                                               /*!< HWSEM_T::SEM: ID Position              */
#define HWSEM_SEM_KEY_Msk                (0xfful << HWSEM_SEM_KEY_Pos)                     /*!< HWSEM_T::SEM: ID Mask                  */

/**@}*/ /* HWSEM_CONST */
/**@}*/ /* end of HWSEM register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __HWSEM_REG_H__ */
