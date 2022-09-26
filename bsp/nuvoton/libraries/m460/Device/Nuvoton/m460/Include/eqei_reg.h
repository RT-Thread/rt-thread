/**************************************************************************//**
 * @file     qei_reg.h
 * @version  V1.00
 * @brief    EQEI register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EQEI_REG_H__
#define __EQEI_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup EQEI Quadrature Encoder Interface(EQEI)
    Memory Mapped Structure for EQEI Controller
@{ */

typedef struct
{


    /**
     * @var EQEI_T::CNT
     * Offset: 0x00  EQEI Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNT       |Quadrature Encoder Interface Counter
     * |        |          |A 32-bit up/down counter
     * |        |          |When an effective phase pulse is detected, this counter is increased by one if the bit DIRF (EQEI_STATUS[8]) is one or decreased by one if the bit DIRF(EQEI_STATUS[8]) is zero
     * |        |          |This register performs an integrator which count value is proportional to the encoder position
     * |        |          |The pulse counter may be initialized to a predetermined value by one of three events occurs:
     * |        |          |1. Software is written if EQEIEN (EQEI_CTL[29]) = 0.
     * |        |          |2. Compare-match event if EQEIEN(EQEI_CTL[29])=1 and EQEI is in compare-counting mode.
     * |        |          |3. Index signal change if EQEIEN(EQEI_CTL[29])=1 and IDXRLDEN (EQEI_CTL[27])=1.
     * @var EQEI_T::CNTHOLD
     * Offset: 0x04  EQEI Counter Hold Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNTHOLD   |Quadrature Encoder Interface Counter Hold
     * |        |          |When bit HOLDCNT (EQEI_CTL[24]) goes from low to high, the CNT(EQEI_CNT[31:0]) is copied into CNTHOLD (EQEI_CNTHOLD[31:0]) register.
     * @var EQEI_T::CNTLATCH
     * Offset: 0x08  EQEI Counter Index Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNTLATCH  |Quadrature Encoder Interface Counter Index Latch
     * |        |          |When the IDXF (EQEI_STATUS[0]) bit is set, the CNT(EQEI_CNT[31:0]) is copied into CNTLATCH (EQEI_CNTLATCH[31:0]) register.
     * @var EQEI_T::CNTCMP
     * Offset: 0x0C  EQEI Counter Compare Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNTCMP    |Quadrature Encoder Interface Counter Compare
     * |        |          |If the EQEI controller is in the compare-counting mode CMPEN (EQEI_CTL[28]) =1, when the value of CNT(EQEI_CNT[31:0]) matches CNTCMP(EQEI_CNTCMP[31:0]), CMPF will be set
     * |        |          |This register is software writable.
     * @var EQEI_T::CNTMAX
     * Offset: 0x14  EQEI Pre-set Maximum Count Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNTMAX    |Quadrature Encoder Interface Preset Maximum Count
     * |        |          |This register value determined by user stores the maximum value which may be the number of the EQEI counter for the EQEI controller compare-counting mode
     * @var EQEI_T::CTL
     * Offset: 0x18  EQEI Controller Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |NFCLKSEL  |Noise Filter Clock Pre-divide Selection
     * |        |          |To determine the sampling frequency of the Noise Filter clock .
     * |        |          |000 = EQEI_CLK.
     * |        |          |001 = EQEI_CLK/2.
     * |        |          |010 = EQEI_CLK/4.
     * |        |          |011 = EQEI_CLK/16.
     * |        |          |100 = EQEI_CLK/32.
     * |        |          |101 = EQEI_CLK/64.
     * |[3]     |NFDIS     |QEI Controller Input Noise Filter Disable Bit
     * |        |          |0 = The noise filter of EQEI controller Enabled.
     * |        |          |1 = The noise filter of EQEI controller Disabled.
     * |[4]     |CHAEN     |QEA Input to EQEI Controller Enable Bit
     * |        |          |0 = QEA input to EQEI Controller Disabled.
     * |        |          |1 = QEA input to EQEI Controller Enabled.
     * |[5]     |CHBEN     |QEB Input to EQEI Controller Enable Bit
     * |        |          |0 = QEB input to EQEI Controller Disabled.
     * |        |          |1 = QEB input to EQEI Controller Enabled.
     * |[6]     |IDXEN     |IDX Input to EQEI Controller Enable Bit
     * |        |          |0 = IDX input to EQEI Controller Disabled.
     * |        |          |1 = IDX input to EQEI Controller Enabled.
     * |[7]     |IDXRSTEN    |IDX Reset EQEI Position Counter Enable Bit
     * |        |          |0 = Reset EQEI position counter in every time IDX signal.
     * |        |          |1 = Reset EQEI position counter in first time IDX signal.
     * |        |          |Note: IDXRLDEN(EQEI_CTL[27]) should be set 1.
     * |[10:8]  |MODE      |QEI Counting Mode Selection
     * |        |          |There are seven quadrature encoder pulse counter operation modes.
     * |        |          |000 = X4 Free-counting Mode.
     * |        |          |001 = X2 Free-counting Mode.
     * |        |          |010 = X4 Compare-counting Mode.
     * |        |          |011 = X2 Compare-counting Mode.
     * |        |          |100 = Phase Counting Mode Type 1. (PCMT1).
     * |        |          |101 = Phase Counting Mode Type 2. (PCMT2).
     * |        |          |110 = Directional Counting Mode.
     * |        |          |111 = Reserved.
     * |        |          |Note: User needs to set DIRSRC(EQEI_CTL2[5:4]) when MODE(EQEI_CTL[10:8]) selects to directional counting mode.
     * |[12]    |CHAINV    |Inverse QEA Input Polarity
     * |        |          |0 = Not inverse QEA input polarity.
     * |        |          |1 = QEA input polarity is inversed to EQEI controller.
     * |[13]    |CHBINV    |Inverse QEB Input Polarity
     * |        |          |0 = Not inverse QEB input polarity.
     * |        |          |1 = QEB input polarity is inversed to EQEI controller.
     * |[14]    |IDXINV    |Inverse IDX Input Polarity
     * |        |          |0 = Not inverse IDX input polarity.
     * |        |          |1 = IDX input polarity is inversed to EQEI controller.
     * |[15]      |IDXRSTEV  |IDX Signal Resets Enable Bit in First IDX Reset Event (Write Only)
     * |        |          |0 = The next IDX level high signal reset function is disabled.
     * |        |          |1 = The next IDX level high signal reset function is enabled.
     * |        |          |Note: This bit only effective when IDXRSTEN (EQEI_CTL[7])=1 and IDXRLDEN (EQEI_CTL[27])=1.
     * |[16]    |OVUNIEN   |OVUNF Trigger EQEI Interrupt Enable Bit
     * |        |          |0 = OVUNF can trigger EQEI controller interrupt Disabled.
     * |        |          |1 = OVUNF can trigger EQEI controller interrupt Enabled.
     * |[17]    |DIRIEN    |DIRCHGF Trigger EQEI Interrupt Enable Bit
     * |        |          |0 = DIRCHGF can trigger EQEI controller interrupt Disabled.
     * |        |          |1 = DIRCHGF can trigger EQEI controller interrupt Enabled.
     * |[18]    |CMPIEN    |CMPF Trigger EQEI Interrupt Enable Bit
     * |        |          |0 = CMPF can trigger EQEI controller interrupt Disabled.
     * |        |          |1 = CMPF can trigger EQEI controller interrupt Enabled.
     * |[19]    |IDXIEN    |IDXF Trigger EQEI Interrupt Enable Bit
     * |        |          |0 = The IDXF can trigger EQEI interrupt Disabled.
     * |        |          |1 = The IDXF can trigger EQEI interrupt Enabled.
     * |[20]    |HOLDTMR0  |Hold EQEI_CNT by Timer 0
     * |        |          |0 = TIF (TIMER0_INTSTS[0]) has no effect on HOLDCNT.
     * |        |          |1 = A rising edge of bit TIF(TIMER0_INTSTS[0]) in timer 0 sets HOLDCNT to 1.
     * |[21]    |HOLDTMR1  |Hold EQEI_CNT by Timer 1
     * |        |          |0 = TIF(TIMER1_INTSTS[0]) has no effect on HOLDCNT.
     * |        |          |1 = A rising edge of bit TIF (TIMER1_INTSTS[0]) in timer 1 sets HOLDCNT to 1.
     * |[22]    |HOLDTMR2  |Hold EQEI_CNT by Timer 2
     * |        |          |0 = TIF(TIMER2_INTSTS[0]) has no effect on HOLDCNT.
     * |        |          |1 = A rising edge of bit TIF(TIMER2_INTSTS[0]) in timer 2 sets HOLDCNT to 1.
     * |[23]    |HOLDTMR3  |Hold EQEI_CNT by Timer 3
     * |        |          |0 = TIF (TIMER3_INTSTS[0]) has no effect on HOLDCNT.
     * |        |          |1 = A rising edge of bit TIF(TIMER3_INTSTS[0]) in timer 3 sets HOLDCNT to 1.
     * |[24]    |HOLDCNT   |Hold EQEI_CNT Control
     * |        |          |When this bit is set from low to high, the CNT(EQEI_CNT[31:0]) is copied into CNTHOLD(EQEI_CNTHOLD[31:0])
     * |        |          |This bit may be set by writing 1 to it or Timer0~Timer3 interrupt flag TIF (TIMERx_INTSTS[0]).
     * |        |          |0 = No operation.
     * |        |          |1 = EQEI_CNT content is captured and stored in CNTHOLD(EQEI_CNTHOLD[31:0]).
     * |        |          |Note: This bit is automatically cleared after EQEI_CNTHOLD holds EQEI_CNT value.
     * |[25]    |IDXLATEN  |Index Latch EQEI_CNT Enable Bit
     * |        |          |If this bit is set to high, the CNT(EQEI_CNT[31:0]) content will be latched into CNTLATCH (EQEI_CNTLATCH[31:0]) at every rising on signal CHX.
     * |        |          |0 = The index signal latch EQEI counter function Disabled.
     * |        |          |1 = The index signal latch EQEI counter function Enabled.
     * |[27]    |IDXRLDEN  |Index Trigger EQEI_CNT Reload Enable Bit
     * |        |          |When this bit is high and a rising edge comes on signal CHX, the CNT(EQEI_CNT[31:0]) will be reset to zero if the counter is in up-counting type (DIRF(EQEI_STATUS[8]) = 1); while the CNT(EQEI_CNT[31:0]) will be reloaded with CNTMAX (EQEI_CNTMAX[31:0]) content if the counter is in down-counting type (DIRF(EQEI_STATUS[8]) = 0).
     * |        |          |0 = Reload function Disabled.
     * |        |          |1 = EQEI_CNT re-initialized by Index signal Enabled.
     * |[28]    |CMPEN     |The Compare Function Enable Bit
     * |        |          |The compare function in EQEI controller is to compare the dynamic counting EQEI_CNT with the compare register CNTCMP( EQEI_CNTCMP[31:0]), if CNT(EQEI_CNT[31:0]) reaches CNTCMP( EQEI_CNTCMP[31:0]), the flag CMPF will be set.
     * |        |          |0 = Compare function Disabled.
     * |        |          |1 = Compare function Enabled.
     * |[29]    |EQEIEN    |Enhanced Quadrature Encoder Interface Controller Enable Bit
     * |        |          |0 = EQEI controller function Disabled.
     * |        |          |1 = EQEI controller function Enabled.
     * @var EQEI_T::CTL2
     * Offset: 0x1C  EQEI Controller Control Register2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SWAPEN    |Swap Function Enable Bit
     * |        |          |0 = EQEI swap function Disabled.
     * |        |          |1 = EQEI swap function Enabled.
     * |[2:1]     |CRS       |Clock Rate Setting without Quadrature Mode
     * |        |          |00 = EQEI counter only counts the falling edge.
     * |        |          |01 = EQEI counter only counts the rising edge.
     * |        |          |10 = EQEI counter counts the rising and falling edge.
     * |        |          |11 = reserved.
     * |[5:4]   |DIRSRC    |Direction Signal Source Select
     * |        |          |00 = Direction signal is determined from EQEI system calculation.
     * |        |          |01 = reserved.
     * |        |          |10 = Direction signal is tied 1 only for direction up count mode.
     * |        |          |11 = Direction signal is tied 0 only for down count mode.
     * |[8]     |UTEN        |Unit Timer Function Enable Bit
     * |        |          |0 = EQEI unit timer function is disable.
     * |        |          |1 = EQEI unit timer function is enable.
     * |[9]     |UTHOLDEN  |Unit Timer Counter Hold Enable Bit
     * |        |          |0 = No operation.
     * |        |          |1 = EQEI_CNT content is captured and stored in CNTHOLD(EQEI_CNTHOLD[31:0]) when UTCNT matches UTCMP(EQEI_UTCMP[31:0]).
     * |[10]      |UTEVTRST |Enable Bit to Reset EQEI Position Counter by Unit Timer Event
     * |        |          |0 = Disable to reset EQEI position counter feature when unit timer counter event occurs.
     * |        |          |1 = Enable to reset EQEI position counter feature when unit timer counter event occurs.
     * |[11]      |IDXRSTUTS |IDX Resets Unit Timer Select Bit
     * |        |          |0 = Unit timer will not be reset when IDX reset event happens.
     * |        |          |1 = Resets unit timer or not will follow EQEI_CNT when IDX reset event happens.
     * |[16]      |PHEIEN      |PHEF Trigger EQEI Interrupt Enable Bit
     * |        |          |0 = PHEF can trigger EQEI controller interrupt Disabled.
     * |        |          |1 = PHEF can trigger EQEI controller interrupt Enabled.
     * |[17]      |UTIEIEN   |UTIEF Trigger EQEI Interrupt Enable Bit
     * |        |          |0 = UTIEF can trigger EQEI controller interrupt Disabled.
     * |        |          |1 = UTIEF can trigger EQEI controller interrupt Enabled.
     * @var EQEI_T::UTCNT
     * Offset: 0x20  EQEI Unit Timer Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UTCNT     |Unit Timer Counter
     * |        |          |A 32-bit unit timer counter which may be reset to an initial value when any of the following events occur:
     * |        |          |1. Software is written if UTEN (EQEI_CTL2[8]) = 0.
     * |        |          |2. UT_EN (EQEI_CTL2[8]) =1, and the unit timer counter value matches UTCMP(EQEI_UTCMP[31:0]).
     * |        |          |3. IDXRLDEN(EQEI_CTL[27]) =1 and IDXRSTUTS(EQEI_CTL2[11]=1, determine the unit timer to be reset or not will follow EQEI_CNT when IDX reset event happens.
     * @var EQEI_T::UTCMP
     * Offset: 0x24  EQEI Unit Timer Compare Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |UTCMP     |Unit Timer Counter Compare
     * |        |          |If the EQEI unit timer is enable (EQEI_CTL2[8]) =1, and the unit timer counter value also matches UTCMP(EQEI_UTCMP[31:0]), then UTIEF (EQEI_STATUS[10]) will be set. This register is software writable.
     * @var EQEI_T::STATUS
     * Offset: 0x2C  EQEI Controller Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |IDXF      |IDX Detected Flag
     * |        |          |When the EQEI controller detects a rising edge on signal CHX it will set flag IDXF to high.
     * |        |          |0 = No rising edge detected on signal CHX.
     * |        |          |1 = A rising edge occurs on signal CHX.
     * |        |          |Note: This bit is only cleared by writing 1 to it.
     * |[1]     |CMPF      |Compare-match Flag
     * |        |          |If the EQEI compare function is enabled, the flag is set by hardware while EQEI counter up or down counts and reach to the CNTCMP(EQEI_CNTCMP[31:0]).
     * |        |          |0 = EQEI counter does not match with CNTCMP(EQEI_CNTCMP[31:0]).
     * |        |          |1 = EQEI counter counts to the same as CNTCMP(EQEI_CNTCMP[31:0]).
     * |        |          |Note: This bit is only cleared by writing 1 to it.
     * |[2]     |OVUNF     |QEI Counter Overflow or Underflow Flag
     * |        |          |Flag is set by hardware while CNT(EQEI_CNT[31:0]) overflows from 0xFFFF_FFFF to zero in free-counting mode or from the CNTMAX (EQEI_CNTMAX[31:0]) to zero in compare-counting mode
     * |        |          |Similarly, the flag is set while EQEI counter underflows from zero to 0xFFFF_FFFF or CNTMAX (EQEI_CNTMAX[31:0]).
     * |        |          |0 = No overflow or underflow occurs in EQEI counter.
     * |        |          |1 = EQEI counter occurs counting overflow or underflow.
     * |        |          |Note: This bit is only cleared by writing 1 to it.
     * |[3]     |DIRCHGF   |Direction Change Flag
     * |        |          |Flag is set by hardware while EQEI counter counting direction is changed.
     * |        |          |Software can clear this bit by writing 1 to it.
     * |        |          |0 = No change in EQEI counter counting direction.
     * |        |          |1 = EQEI counter counting direction is changed.
     * |        |          |Note: This bit is only cleared by writing 1 to it.
     * |[8]     |DIRF      |QEI Counter Counting Direction Indication
     * |        |          |0 = EQEI Counter is in down-counting.
     * |        |          |1 = EQEI Counter is in up-counting.
     * |        |          |Note: This bit is set/reset by hardware according to the phase detection between CHA and CHB.
     * |[9]     |FIDXEF    |First IDX Signal Reset Event Flag (Read Only)
     * |        |          |0 = The first IDX reset event has not happened yet.
     * |        |          |1 = The first IDX reset event has happened.
     * |        |          |Note: This bit only effective when IDXRSTEN (EQEI_CTL[7])=1 and IDXRLDEN (EQEI_CTL[27])=1.
     * |[16]      |PHEF EQEI |Phase Error Flag
     * |        |          |0 = No Phase error occurs in EQEI CHA and CHB.
     * |        |          |1 = Phase error occurs in EQEI CHA and CHB.
     * |        |          |Note: This bit is only cleared by writing 1 to it.
     * |[17]      |UTIEF       |EQEI Unit Timer Event Flag
     * |        |          |0 = No timer event occurs in EQEI unit timer counter.
     * |        |          |1 = Unit timer event occurs in EQEI unit timer counter.
     * |        |          |Note: This bit is only cleared by writing 1 to it.
    */
    __IO uint32_t CNT;                   /*!< [0x0000] EQEI Counter Register                                             */
    __IO uint32_t CNTHOLD;               /*!< [0x0004] EQEI Counter Hold Register                                        */
    __IO uint32_t CNTLATCH;              /*!< [0x0008] EQEI Counter Index Latch Register                                 */
    __IO uint32_t CNTCMP;                /*!< [0x000c] EQEI Counter Compare Register                                     */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CNTMAX;                /*!< [0x0014] EQEI Pre-set Maximum Count Register                               */
    __IO uint32_t CTL;                   /*!< [0x0018] EQEI Controller Control Register                                  */
    __IO uint32_t CTL2;                  /*!< [0x001C] EQEI Controller Control Register2                                 */
    __IO uint32_t UTCNT;                 /*!< [0x0020] EQEI Unit Timer Counter Register                                  */
    __IO uint32_t UTCMP;                 /*!< [0x0024] EQEI Unit Timer Compare Register                                  */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t STATUS;                /*!< [0x002c] EQEI Controller Status Register                                   */

} EQEI_T;

/**
    @addtogroup EQEI_CONST EQEI Bit Field Definition
    Constant Definitions for EQEI Controller
@{ */

#define EQEI_CNT_CNT_Pos                  (0)                                               /*!< EQEI_T::CNT: CNT Position               */
#define EQEI_CNT_CNT_Msk                  (0xfffffffful << EQEI_CNT_CNT_Pos)                /*!< EQEI_T::CNT: CNT Mask                   */

#define EQEI_CNTHOLD_CNTHOLD_Pos          (0)                                               /*!< EQEI_T::CNTHOLD: CNTHOLD Position       */
#define EQEI_CNTHOLD_CNTHOLD_Msk          (0xfffffffful << EQEI_CNTHOLD_CNTHOLD_Pos)        /*!< EQEI_T::CNTHOLD: CNTHOLD Mask           */

#define EQEI_CNTLATCH_CNTLATCH_Pos        (0)                                               /*!< EQEI_T::CNTLATCH: CNTLATCH Position     */
#define EQEI_CNTLATCH_CNTLATCH_Msk        (0xfffffffful << EQEI_CNTLATCH_CNTLATCH_Pos)      /*!< EQEI_T::CNTLATCH: CNTLATCH Mask         */

#define EQEI_CNTCMP_CNTCMP_Pos            (0)                                               /*!< EQEI_T::CNTCMP: CNTCMP Position         */
#define EQEI_CNTCMP_CNTCMP_Msk            (0xfffffffful << EQEI_CNTCMP_CNTCMP_Pos)          /*!< EQEI_T::CNTCMP: CNTCMP Mask             */

#define EQEI_CNTMAX_CNTMAX_Pos            (0)                                               /*!< EQEI_T::CNTMAX: CNTMAX Position         */
#define EQEI_CNTMAX_CNTMAX_Msk            (0xfffffffful << EQEI_CNTMAX_CNTMAX_Pos)          /*!< EQEI_T::CNTMAX: CNTMAX Mask             */

#define EQEI_CTL_NFCLKSEL_Pos             (0)                                               /*!< EQEI_T::CTL: NFCLKSEL Position          */
#define EQEI_CTL_NFCLKSEL_Msk             (0x7ul << EQEI_CTL_NFCLKSEL_Pos)                  /*!< EQEI_T::CTL: NFCLKSEL Mask              */

#define EQEI_CTL_NFDIS_Pos                (3)                                               /*!< EQEI_T::CTL: NFDIS Position             */
#define EQEI_CTL_NFDIS_Msk                (0x1ul << EQEI_CTL_NFDIS_Pos)                     /*!< EQEI_T::CTL: NFDIS Mask                 */

#define EQEI_CTL_CHAEN_Pos                (4)                                               /*!< EQEI_T::CTL: CHAEN Position             */
#define EQEI_CTL_CHAEN_Msk                (0x1ul << EQEI_CTL_CHAEN_Pos)                     /*!< EQEI_T::CTL: CHAEN Mask                 */

#define EQEI_CTL_CHBEN_Pos                (5)                                               /*!< EQEI_T::CTL: CHBEN Position             */
#define EQEI_CTL_CHBEN_Msk                (0x1ul << EQEI_CTL_CHBEN_Pos)                     /*!< EQEI_T::CTL: CHBEN Mask                 */

#define EQEI_CTL_IDXEN_Pos                (6)                                               /*!< EQEI_T::CTL: IDXEN Position             */
#define EQEI_CTL_IDXEN_Msk                (0x1ul << EQEI_CTL_IDXEN_Pos)                     /*!< EQEI_T::CTL: IDXEN Mask                 */

#define EQEI_CTL_IDXRSTEN_Pos             (7)                                               /*!< EQEI_T::CTL: IDXRSTEN Position          */
#define EQEI_CTL_IDXRSTEN_Msk             (0x1ul << EQEI_CTL_IDXRSTEN_Pos)                  /*!< EQEI_T::CTL: IDXRSTEN Mask              */

#define EQEI_CTL_MODE_Pos                 (8)                                               /*!< EQEI_T::CTL: MODE Position              */
#define EQEI_CTL_MODE_Msk                 (0x7ul << EQEI_CTL_MODE_Pos)                      /*!< EQEI_T::CTL: MODE Mask                  */

#define EQEI_CTL_CHAINV_Pos               (12)                                              /*!< EQEI_T::CTL: CHAINV Position            */
#define EQEI_CTL_CHAINV_Msk               (0x1ul << EQEI_CTL_CHAINV_Pos)                    /*!< EQEI_T::CTL: CHAINV Mask                */

#define EQEI_CTL_CHBINV_Pos               (13)                                              /*!< EQEI_T::CTL: CHBINV Position            */
#define EQEI_CTL_CHBINV_Msk               (0x1ul << EQEI_CTL_CHBINV_Pos)                    /*!< EQEI_T::CTL: CHBINV Mask                */

#define EQEI_CTL_IDXINV_Pos               (14)                                              /*!< EQEI_T::CTL: IDXINV Position            */
#define EQEI_CTL_IDXINV_Msk               (0x1ul << EQEI_CTL_IDXINV_Pos)                    /*!< EQEI_T::CTL: IDXINV Mask                */

#define EQEI_CTL_IDXRSTEV_Pos             (15)                                              /*!< EQEI_T::CTL: IDXRSTEV Position          */
#define EQEI_CTL_IDXRSTEV_Msk             (0x1ul << EQEI_CTL_IDXRSTEV_Pos)                  /*!< EQEI_T::CTL: IDXRSTEV Mask              */

#define EQEI_CTL_OVUNIEN_Pos              (16)                                              /*!< EQEI_T::CTL: OVUNIEN Position           */
#define EQEI_CTL_OVUNIEN_Msk              (0x1ul << EQEI_CTL_OVUNIEN_Pos)                   /*!< EQEI_T::CTL: OVUNIEN Mask               */

#define EQEI_CTL_DIRIEN_Pos               (17)                                              /*!< EQEI_T::CTL: DIRIEN Position            */
#define EQEI_CTL_DIRIEN_Msk               (0x1ul << EQEI_CTL_DIRIEN_Pos)                    /*!< EQEI_T::CTL: DIRIEN Mask                */

#define EQEI_CTL_CMPIEN_Pos               (18)                                              /*!< EQEI_T::CTL: CMPIEN Position            */
#define EQEI_CTL_CMPIEN_Msk               (0x1ul << EQEI_CTL_CMPIEN_Pos)                    /*!< EQEI_T::CTL: CMPIEN Mask                */

#define EQEI_CTL_IDXIEN_Pos               (19)                                              /*!< EQEI_T::CTL: IDXIEN Position            */
#define EQEI_CTL_IDXIEN_Msk               (0x1ul << EQEI_CTL_IDXIEN_Pos)                    /*!< EQEI_T::CTL: IDXIEN Mask                */

#define EQEI_CTL_HOLDTMR0_Pos             (20)                                              /*!< EQEI_T::CTL: HOLDTMR0 Position          */
#define EQEI_CTL_HOLDTMR0_Msk             (0x1ul << EQEI_CTL_HOLDTMR0_Pos)                  /*!< EQEI_T::CTL: HOLDTMR0 Mask              */

#define EQEI_CTL_HOLDTMR1_Pos             (21)                                              /*!< EQEI_T::CTL: HOLDTMR1 Position          */
#define EQEI_CTL_HOLDTMR1_Msk             (0x1ul << EQEI_CTL_HOLDTMR1_Pos)                  /*!< EQEI_T::CTL: HOLDTMR1 Mask              */

#define EQEI_CTL_HOLDTMR2_Pos             (22)                                              /*!< EQEI_T::CTL: HOLDTMR2 Position          */
#define EQEI_CTL_HOLDTMR2_Msk             (0x1ul << EQEI_CTL_HOLDTMR2_Pos)                  /*!< EQEI_T::CTL: HOLDTMR2 Mask              */

#define EQEI_CTL_HOLDTMR3_Pos             (23)                                              /*!< EQEI_T::CTL: HOLDTMR3 Position          */
#define EQEI_CTL_HOLDTMR3_Msk             (0x1ul << EQEI_CTL_HOLDTMR3_Pos)                  /*!< EQEI_T::CTL: HOLDTMR3 Mask              */

#define EQEI_CTL_HOLDCNT_Pos              (24)                                              /*!< EQEI_T::CTL: HOLDCNT Position           */
#define EQEI_CTL_HOLDCNT_Msk              (0x1ul << EQEI_CTL_HOLDCNT_Pos)                   /*!< EQEI_T::CTL: HOLDCNT Mask               */

#define EQEI_CTL_IDXLATEN_Pos             (25)                                              /*!< EQEI_T::CTL: IDXLATEN Position          */
#define EQEI_CTL_IDXLATEN_Msk             (0x1ul << EQEI_CTL_IDXLATEN_Pos)                  /*!< EQEI_T::CTL: IDXLATEN Mask              */

#define EQEI_CTL_IDXRLDEN_Pos             (27)                                              /*!< EQEI_T::CTL: IDXRLDEN Position          */
#define EQEI_CTL_IDXRLDEN_Msk             (0x1ul << EQEI_CTL_IDXRLDEN_Pos)                  /*!< EQEI_T::CTL: IDXRLDEN Mask              */

#define EQEI_CTL_CMPEN_Pos                (28)                                              /*!< EQEI_T::CTL: CMPEN Position             */
#define EQEI_CTL_CMPEN_Msk                (0x1ul << EQEI_CTL_CMPEN_Pos)                     /*!< EQEI_T::CTL: CMPEN Mask                 */

#define EQEI_CTL_QEIEN_Pos                (29)                                              /*!< EQEI_T::CTL: EQEIEN Position            */
#define EQEI_CTL_QEIEN_Msk                (0x1ul << EQEI_CTL_QEIEN_Pos)                     /*!< EQEI_T::CTL: EQEIEN Mask                */

#define EQEI_CTL2_SWAPEN_Pos              (0)                                              /*!< EQEI_T::CTL2: SWAPEN Position            */
#define EQEI_CTL2_SWAPEN_Msk              (0x1ul << EQEI_CTL2_SWAPEN_Pos)                  /*!< EQEI_T::CTL2: SWAPEN Mask                */

#define EQEI_CTL2_CRS_Pos                 (1)                                              /*!< EQEI_T::CTL2: CRS Position               */
#define EQEI_CTL2_CRS_Msk                 (0x3ul << EQEI_CTL2_CRS_Pos)                     /*!< EQEI_T::CTL2: CRS Mask                   */

#define EQEI_CTL2_DIRSRC_Pos              (4)                                              /*!< EQEI_T::CTL2: DIRSRC Position            */
#define EQEI_CTL2_DIRSRC_Msk              (0x3ul << EQEI_CTL2_DIRSRC_Pos)                  /*!< EQEI_T::CTL2: DIRSRC Mask                */

#define EQEI_CTL2_UTEN_Pos                (8)                                              /*!< EQEI_T::CTL2: UTEN Position              */
#define EQEI_CTL2_UTEN_Msk                (0x1ul << EQEI_CTL2_UTEN_Pos)                    /*!< EQEI_T::CTL2: UTEN Mask                  */

#define EQEI_CTL2_UTHOLDEN_Pos            (9)                                              /*!< EQEI_T::CTL2: UTHOLDEN Position          */
#define EQEI_CTL2_UTHOLDEN_Msk            (0x1ul << EQEI_CTL2_UTHOLDEN_Pos)                /*!< EQEI_T::CTL2: UTHOLDEN Mask              */

#define EQEI_CTL2_UTEVTRST_Pos            (10)                                             /*!< EQEI_T::CTL2: UTEVTRST Position          */
#define EQEI_CTL2_UTEVTRST_Msk            (0x1ul << EQEI_CTL2_UTEVTRST_Pos)                /*!< EQEI_T::CTL2: UTEVTRST Mask              */

#define EQEI_CTL2_IDXRSTUTS_Pos           (11)                                             /*!< EQEI_T::CTL2: IDXRSTUTS Position         */
#define EQEI_CTL2_IDXRSTUTS_Msk           (0x1ul << EQEI_CTL2_IDXRSTUTS_Pos)               /*!< EQEI_T::CTL2: IDXRSTUTS Mask             */

#define EQEI_CTL2_PHEIEN_Pos              (16)                                             /*!< EQEI_T::CTL2: PHEIEN Position            */
#define EQEI_CTL2_PHEIEN_Msk              (0x1ul << EQEI_CTL2_PHEIEN_Pos)                  /*!< EQEI_T::CTL2: PHEIEN Mask                */

#define EQEI_CTL2_UTIEIEN_Pos             (17)                                             /*!< EQEI_T::CTL2: UTIEIEN Position           */
#define EQEI_CTL2_UTIEIEN_Msk             (0x1ul << EQEI_CTL2_UTIEIEN_Pos)                 /*!< EQEI_T::CTL2: UTIEIEN Mask               */

#define EQEI_UTCNT_UTCNT_Pos              (0)                                              /*!< EQEI_T::UTCNT: UTCNT Position            */
#define EQEI_UTCNT_UTCNT_Msk              (0xfffffffful << EQEI_UTCNT_UTCNT_Pos)           /*!< EQEI_T::UTCNT: UTCNT Mask                */

#define EQEI_UTCMP_UTCMP_Pos              (0)                                              /*!< EQEI_T::UTCMP: UTCMP Position            */
#define EQEI_UTCMP_UTCMP_Msk              (0xfffffffful << EQEI_UTCMP_UTCMP_Pos)           /*!< EQEI_T::UTCMP: UTCMP Mask                */

#define EQEI_STATUS_IDXF_Pos              (0)                                              /*!< EQEI_T::STATUS: IDXF Position            */
#define EQEI_STATUS_IDXF_Msk              (0x1ul << EQEI_STATUS_IDXF_Pos)                  /*!< EQEI_T::STATUS: IDXF Mask                */

#define EQEI_STATUS_CMPF_Pos              (1)                                              /*!< EQEI_T::STATUS: CMPF Position            */
#define EQEI_STATUS_CMPF_Msk              (0x1ul << EQEI_STATUS_CMPF_Pos)                  /*!< EQEI_T::STATUS: CMPF Mask                */

#define EQEI_STATUS_OVUNF_Pos             (2)                                              /*!< EQEI_T::STATUS: OVUNF Position           */
#define EQEI_STATUS_OVUNF_Msk             (0x1ul << EQEI_STATUS_OVUNF_Pos)                 /*!< EQEI_T::STATUS: OVUNF Mask               */

#define EQEI_STATUS_DIRCHGF_Pos           (3)                                              /*!< EQEI_T::STATUS: DIRCHGF Position         */
#define EQEI_STATUS_DIRCHGF_Msk           (0x1ul << EQEI_STATUS_DIRCHGF_Pos)               /*!< EQEI_T::STATUS: DIRCHGF Mask             */

#define EQEI_STATUS_DIRF_Pos              (8)                                              /*!< EQEI_T::STATUS: DIRF Position            */
#define EQEI_STATUS_DIRF_Msk              (0x1ul << EQEI_STATUS_DIRF_Pos)                  /*!< EQEI_T::STATUS: DIRF Mask                */

#define EQEI_STATUS_FIDXEF_Pos            (9)                                              /*!< EQEI_T::STATUS: FIDXEF Position          */
#define EQEI_STATUS_FIDXEF_Msk            (0x1ul << EQEI_STATUS_FIDXEF_Pos)                /*!< EQEI_T::STATUS: FIDXEF Mask              */

#define EQEI_STATUS_PHEF_Pos              (16)                                             /*!< EQEI_T::STATUS: PHEF Position            */
#define EQEI_STATUS_PHEF_Msk              (0x1ul << EQEI_STATUS_PHEF_Pos)                  /*!< EQEI_T::STATUS: PHEF Mask                */

#define EQEI_STATUS_UTIEF_Pos             (17)                                             /*!< EQEI_T::STATUS: UTIEF Position           */
#define EQEI_STATUS_UTIEF_Msk             (0x1ul << EQEI_STATUS_UTIEF_Pos)                 /*!< EQEI_T::STATUS: UTIEF Mask               */


/**@}*/ /* EQEI_CONST */
/**@}*/ /* end of EQEI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __EQEI_REG_H__ */
