/**************************************************************************//**
 * @file     ewwdt_reg.h
 * @version  V1.00
 * @brief    EWWDT register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EWWDT_REG_H__
#define __EWWDT_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Extra Window Watchdog Timer -------------------------*/
/**
    @addtogroup EWWDT Extra Window Watchdog Timer(EWWDT)
    Memory Mapped Structure for EWWDT Controller
  @{
*/

typedef struct
{


    /**
     * @var EWWDT_T::RLDCNT
     * Offset: 0x00  WWDT Reload Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RLDCNT    |WWDT Reload Counter Register
     * |        |          |Writing only 0x00005AA5 to this register will reload the WWDT counter value to 0x3F.
     * |        |          |Note1: User can only write execute WWDT_RLDCNT register to the reload WWDT counter value command when current current WWDT counter value CNTDAT (WWDT_CNT[5:0]) is between 10 and CMPDAT (WWDT_CTL[21:16])
     * |        |          |If user writes 0x00005AA5 in WWDT_RLDCNT register when current current CNTDATWWDT counter value is larger than CMPDAT, WWDT reset signal system event will be generated immediately.
     * |        |          |Note2: Execute WWDT counter reload always needs (WWDT_CLK *3) period to reload CNTDAT to 0x3F and internal prescale counter will be reset also.
     * @var EWWDT_T::CTL
     * Offset: 0x04  WWDT Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WWDTEN    |WWDT Enable Control Bit
     * |        |          |Set this bit to enable start WWDT counter counting.
     * |        |          |0 = WWDT counter is stopped.
     * |        |          |1 = WWDT counter is starting counting.
     * |[1]     |INTEN     |WWDT Interrupt Enable Control Bit
     * |        |          |If this bit is enabled, when WWDTIF (WWDT_STATUS[0]) is set to 1, the WWDT counter compare match interrupt signal is generated and inform to CPU.
     * |        |          |0 = WWDT counter compare match interrupt Disabled.
     * |        |          |1 = WWDT counter compare match interrupt Enabled.
     * |[11:8]  |PSCSEL    |WWDT Counter Prescale Period Selection
     * |        |          |0000 = Pre-scale is 1; Max time-out period is 1 * 64 * WWDT_CLK.
     * |        |          |0001 = Pre-scale is 2; Max time-out period is 2 * 64 * WWDT_CLK.
     * |        |          |0010 = Pre-scale is 4; Max time-out period is 4 * 64 * WWDT_CLK.
     * |        |          |0011 = Pre-scale is 8; Max time-out period is 8 * 64 * WWDT_CLK.
     * |        |          |0100 = Pre-scale is 16; Max time-out period is 16 * 64 * WWDT_CLK.
     * |        |          |0101 = Pre-scale is 32; Max time-out period is 32 * 64 * WWDT_CLK.
     * |        |          |0110 = Pre-scale is 64; Max time-out period is 64 * 64 * WWDT_CLK.
     * |        |          |0111 = Pre-scale is 128; Max time-out period is 128 * 64 * WWDT_CLK.
     * |        |          |1000 = Pre-scale is 192; Max time-out period is 192 * 64 * WWDT_CLK.
     * |        |          |1001 = Pre-scale is 256; Max time-out period is 256 * 64 * WWDT_CLK.
     * |        |          |1010 = Pre-scale is 384; Max time-out period is 384 * 64 * WWDT_CLK.
     * |        |          |1011 = Pre-scale is 512; Max time-out period is 512 * 64 * WWDT_CLK.
     * |        |          |1100 = Pre-scale is 768; Max time-out period is 768 * 64 * WWDT_CLK.
     * |        |          |1101 = Pre-scale is 1024; Max time-out period is 1024 * 64 * WWDT_CLK.
     * |        |          |1110 = Pre-scale is 1536; Max time-out period is 1536 * 64 * WWDT_CLK.
     * |        |          |1111 = Pre-scale is 2048; Max time-out period is 2048 * 64 * WWDT_CLK.
     * |[21:16] |CMPDAT    |WWDT Window Compare Register Value
     * |        |          |Set this register field to adjust the valid reload window interval when WWDTIF (WWDT_STATUS[0]) is generated..
     * |        |          |Note: User can only write WWDT_RLDCNT register to reload WWDT counter value when current WWDT CNTDAT (WWDT_CNT[5:]) is counter value between 10 and CMPDAT
     * |        |          |If user writes 0x00005AA5 in WWDT_RLDCNT register when current WWDT counter value CNTDAT is larger than CMPDAT, WWDT reset system event signal will be generated immediately.
     * |[31]    |ICEDEBUG  |ICE Debug Mode Acknowledge Disable Control
     * |        |          |0 = ICE debug mode acknowledgment effects WWDT counter counting.
     * |        |          |WWDT down counter will be held while CPU is held by ICE.
     * |        |          |1 = ICE debug mode acknowledgment Disabled.
     * |        |          |WWDT down counter will keep going counting no matter CPU is held by ICE or not.
     * @var EWWDT_T::STATUS
     * Offset: 0x08  WWDT Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WWDTIF    |WWDT Compare Match Interrupt Flag
     * |        |          |This bit indicates the that current CNTDAT (WWDT_CNT[5:0]) matches the CMPDAT (WWDT_CTL[21:16])interrupt flag status of WWDT while WWDT counter value matches CMPDAT (WWDT_CTL[21:16]).
     * |        |          |0 = No effect.
     * |        |          |1 = WWDT WWDT CNTDAT counter value matches the CMPDAT.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * |[1]     |WWDTRF    |WWDT Timer-out Reset System Flag
     * |        |          |If this bit is set to 1, it This bit indicates the that system has been reset by WWDT counter time-out reset system event.or not.
     * |        |          |0 = WWDT time-out reset system event did not occur.
     * |        |          |1 = WWDT time-out reset system event occurred.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * @var EWWDT_T::CNT
     * Offset: 0x0C  WWDT Counter Value Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |CNTDAT    |WWDT Counter Value
     * |        |          |CNTDAT will be updated continuously to monitor 6-bit WWDT down counter value.
     */
    __O  uint32_t RLDCNT;                /*!< [0x0000] EWWDT Reload Counter Register                                     */
    __IO uint32_t CTL;                   /*!< [0x0004] EWWDT Control Register                                            */
    __IO uint32_t STATUS;                /*!< [0x0008] EWWDT Status Register                                             */
    __I  uint32_t CNT;                   /*!< [0x000c] EWWDT Counter Value Register                                      */

} EWWDT_T;


/**
    @addtogroup WWDT_CONST WWDT Bit Field Definition
    Constant Definitions for WWDT Controller
  @{
*/

#define EWWDT_RLDCNT_RLDCNT_Pos           (0)                                               /*!< EWWDT_T::RLDCNT: RLDCNT Position        */
#define EWWDT_RLDCNT_RLDCNT_Msk           (0xfffffffful << EWWDT_RLDCNT_RLDCNT_Pos)         /*!< EWWDT_T::RLDCNT: RLDCNT Mask            */

#define EWWDT_CTL_WWDTEN_Pos              (0)                                               /*!< EWWDT_T::CTL: WWDTEN Position           */
#define EWWDT_CTL_WWDTEN_Msk              (0x1ul << EWWDT_CTL_WWDTEN_Pos)                   /*!< EWWDT_T::CTL: WWDTEN Mask               */

#define EWWDT_CTL_INTEN_Pos               (1)                                               /*!< EWWDT_T::CTL: INTEN Position            */
#define EWWDT_CTL_INTEN_Msk               (0x1ul << EWWDT_CTL_INTEN_Pos)                    /*!< EWWDT_T::CTL: INTEN Mask                */

#define EWWDT_CTL_PSCSEL_Pos              (8)                                               /*!< EWWDT_T::CTL: PSCSEL Position           */
#define EWWDT_CTL_PSCSEL_Msk              (0xful << EWWDT_CTL_PSCSEL_Pos)                   /*!< EWWDT_T::CTL: PSCSEL Mask               */

#define EWWDT_CTL_CMPDAT_Pos              (16)                                              /*!< EWWDT_T::CTL: CMPDAT Position           */
#define EWWDT_CTL_CMPDAT_Msk              (0x3ful << EWWDT_CTL_CMPDAT_Pos)                  /*!< EWWDT_T::CTL: CMPDAT Mask               */

#define EWWDT_CTL_ICEDEBUG_Pos            (31)                                              /*!< EWWDT_T::CTL: ICEDEBUG Position         */
#define EWWDT_CTL_ICEDEBUG_Msk            (0x1ul << EWWDT_CTL_ICEDEBUG_Pos)                 /*!< EWWDT_T::CTL: ICEDEBUG Mask             */

#define EWWDT_STATUS_WWDTIF_Pos           (0)                                               /*!< EWWDT_T::STATUS: WWDTIF Position        */
#define EWWDT_STATUS_WWDTIF_Msk           (0x1ul << EWWDT_STATUS_WWDTIF_Pos)                /*!< EWWDT_T::STATUS: WWDTIF Mask            */

#define EWWDT_STATUS_WWDTRF_Pos           (1)                                               /*!< EWWDT_T::STATUS: WWDTRF Position        */
#define EWWDT_STATUS_WWDTRF_Msk           (0x1ul << EWWDT_STATUS_WWDTRF_Pos)                /*!< EWWDT_T::STATUS: WWDTRF Mask            */

#define EWWDT_CNT_CNTDAT_Pos              (0)                                               /*!< EWWDT_T::CNT: CNTDAT Position           */
#define EWWDT_CNT_CNTDAT_Msk              (0x3ful << EWWDT_CNT_CNTDAT_Pos)                  /*!< EWWDT_T::CNT: CNTDAT Mask               */

/**@}*/ /* EWWDT_CONST */
/**@}*/ /* end of EWWDT register group */
/**@}*/ /* end of REGISTER group */

#endif /* __EWWDT_REG_H__ */
