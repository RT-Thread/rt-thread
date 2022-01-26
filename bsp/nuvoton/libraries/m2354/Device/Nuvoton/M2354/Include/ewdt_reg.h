/**************************************************************************//**
 * @file     ewdt_reg.h
 * @version  V1.00
 * @brief    EWDT register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EWDT_REG_H__
#define __EWDT_REG_H__

/**
  @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Extra Watch Dog Timer Controller -------------------------*/
/**
  @addtogroup EWDT Extra Watch Dog Timer Controller(EWDT)
  Memory Mapped Structure for EWDT Controller
  @{
*/

typedef struct
{


    /**
     * @var EWDT_T::CTL
     * Offset: 0x00  EWDT Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |RSTEN     |EWDT Time-out Reset Enable Control (Write Protect)
     * |        |          |Setting this bit will enable the EWDT time-out reset system function If the EWDT up counter value has not been cleared after the specific EWDT reset delay period expires.
     * |        |          |0 = EWDT time-out reset system function Disabled.
     * |        |          |1 = EWDT time-out reset system function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |RSTF      |EWDT Time-out Reset Flag
     * |        |          |This bit indicates the system has been reset by EWDT time-out reset system event or not.
     * |        |          |0 = EWDT time-out reset system event did not occur.
     * |        |          |1 = EWDT time-out reset system event has been occurred.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * |[3]     |IF        |EWDT Time-out Interrupt Flag
     * |        |          |This bit will set to 1 while EWDT up counter value reaches the selected EWDT time-out interval
     * |        |          |0 = EWDT time-out interrupt event interrupt did not occur.
     * |        |          |1 = EWDT time-out interrupt interrupt event occurred.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * |[4]     |WKEN      |EWDT Time-out Wake-up Function Control (Write Protect)
     * |        |          |If this bit is set to 1, while EWDT time-out interrupt flag IF (EWDT_CTL[3]) is generated to 1 and interrupt enable bit INTEN (EWDT_CTL[6]) is enabled, the EWDT time-out interrupt signal will generate a event to trigger CPU wake-up trigger event to chip.
     * |        |          |0 = Trigger Wake-up trigger event function Disabled if EWDT time-out interrupt signal generated.
     * |        |          |1 = Trigger Wake-up trigger event function Enabled if EWDT time-out interrupt signal generated.
     * |        |          |Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note2: Chip can be woken-up by while EWDT time-out interrupt signal generated only if EWDT clock source is selected to LIRC or LXT (32 kHz).
     * |[5]     |WKF       |EWDT Time-out Wake-up Flag (Write Protect)
     * |        |          |This bit indicates the EWDT time-out event has triggered interrupt chip wake-up or not.flag status of EWDT
     * |        |          |0 = WDT does not cause chip wake-up.
     * |        |          |1 = Chip wake-up from Idle or Power-down mode if when WDT time-out interrupt signal is generated.
     * |        |          |Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note2: This bit is cleared by writing 1 to it.
     * |[6]     |INTEN     |WDT Time-out Interrupt Enable Control (Write Protect)
     * |        |          |If this bit is enabled, when WDT time-out event occurs, the IF (WDT_CTL[3]) will be set to 1 and the WDT time-out interrupt signal is generated and inform to CPU.
     * |        |          |0 = WDT time-out interrupt Disabled.
     * |        |          |1 = WDT time-out interrupt Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7]     |WDTEN     |WDT Enable Control (Write Protect)
     * |        |          |0 = Set WDT counter stop Disabled, and (This action will reset the internal up counter value will be reset also).
     * |        |          |1 = Set WDT counter start Enabled.
     * |        |          |Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note2: Perform enable or disable WDTEN bit needs 2 * WDT_CLK period to become active, user can read SYNC (WDT_CTL[30]) to check enable/disable command is completed or not.
     * |        |          |Note32: If CWDTEN[2:0] (combined by with Config0[31] and Config0[4:3]) bits is not configure to 0x111, this bit is forced as 1 and user cannot change this bit to 0.
     * |        |          |Note3: This bit disabled needs 2 * WDT_CLK.
     * |[11:8]  |TOUTSEL   |WDT Time-out Interval Selection (Write Protect)
     * |        |          |These three bits select the time-out interval period after for the WDT starts counting.
     * |        |          |000 = 2^4 * WDT_CLK.
     * |        |          |001 = 2^6 * WDT_CLK.
     * |        |          |010 = 2^8 * WDT_CLK.
     * |        |          |011 = 2^10 * WDT_CLK.
     * |        |          |100 = 2^12 * WDT_CLK.
     * |        |          |101 = 2^14 * WDT_CLK.
     * |        |          |110 = 2^16 * WDT_CLK.
     * |        |          |111 = 2^18 * WDT_CLK.
     * |        |          |111 = 2^20 * WDT_CLK.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[30]    |SYNC      |WDT Enable Control SYNC SYNC Flag Indicator (Read Only)
     * |        |          |If use to synchronization, software er can check execute enable/disable this flag after enable WDTEN (WDT_CTL[7]), this flag can be indicated enable/disable WDTEN function is become completed or not active or not..
     * |        |          |SYNC delay is
     * |        |          |0 = Set WDTEN bit is WDT enable control synccompletedhronizing is completion.
     * |        |          |1 = Set WDTEN bit WDT enable control is synchronizing and not become active yet..
     * |        |          |Note: Perform enable or disable WDTEN bit
     * |        |          |This bit enabled needs 2 * WDT_CLK period to become active.
     * |[31]    |ICEDEBUG  |ICE Debug Mode Acknowledge Disable Control (Write Protect)
     * |        |          |0 = ICE debug mode acknowledgment affects WDT counting.
     * |        |          |WDT up counter will be held while CPU is held by ICE.
     * |        |          |1 = ICE debug mode acknowledgment Disabled.
     * |        |          |WDT up counter will keep going no matter CPU is held by ICE or not.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var EWDT_T::ALTCTL
     * Offset: 0x04  EWDT Alternative Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |RSTDSEL   |WDT Reset Delay Period Selection (Write Protect)
     * |        |          |When WDT time-out event happened, user has a time named WDT Reset Delay Period to clear execute WDT counter by setting RSTCNT (WDT_CTL[0]) reset to prevent WDT time-out reset system occurred happened
     * |        |          |User can select a suitable setting of RSTDSEL for different application program WDT Reset Delay Period.
     * |        |          |00 = WDT Reset Delay Period is 1026 * WDT_CLK.
     * |        |          |01 = WDT Reset Delay Period is 130 * WDT_CLK.
     * |        |          |10 = WDT Reset Delay Period is 18 * WDT_CLK.
     * |        |          |11 = WDT Reset Delay Period is 3 * WDT_CLK.
     * |        |          |Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note2: This register will be reset to 0 if WDT time-out reset system event occurred happened.
     * @var EWDT_T::RSTCNT
     * Offset: 0x08  EWDT Reset Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RSTCNT    |WDT Reset Counter Register
     * |        |          |Writing 0x00005AA5 to this register field will reset the internal 18-bit WDT up counter value to 0.
     * |        |          |Note: This WDT_RSTCNT is not write protected, but this RSTCNT (WDT_CTL[0]) is write protected.
     * |        |          |Note: Perform RSTCNT to reset counter needs 2 * WDT_CLK period to become active.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] EWDT Control Register                                             */
    __IO uint32_t ALTCTL;                /*!< [0x0004] EWDT Alternative Control Register                                 */
    __O  uint32_t RSTCNT;                /*!< [0x0008] EWDT Reset Counter Register                                       */

} EWDT_T;

/**
  @addtogroup EWDT_CONST WDT Bit Field Definition
  Constant Definitions for EWDT Controller
  @{
*/

#define EWDT_CTL_RSTEN_Pos                (1)                                               /*!< EWDT_T::CTL: RSTEN Position             */
#define EWDT_CTL_RSTEN_Msk                (0x1ul << EWDT_CTL_RSTEN_Pos)                     /*!< EWDT_T::CTL: RSTEN Mask                 */

#define EWDT_CTL_RSTF_Pos                 (2)                                               /*!< EWDT_T::CTL: RSTF Position              */
#define EWDT_CTL_RSTF_Msk                 (0x1ul << EWDT_CTL_RSTF_Pos)                      /*!< EWDT_T::CTL: RSTF Mask                  */

#define EWDT_CTL_IF_Pos                   (3)                                               /*!< EWDT_T::CTL: IF Position                */
#define EWDT_CTL_IF_Msk                   (0x1ul << EWDT_CTL_IF_Pos)                        /*!< EWDT_T::CTL: IF Mask                    */

#define EWDT_CTL_WKEN_Pos                 (4)                                               /*!< EWDT_T::CTL: WKEN Position              */
#define EWDT_CTL_WKEN_Msk                 (0x1ul << EWDT_CTL_WKEN_Pos)                      /*!< EWDT_T::CTL: WKEN Mask                  */

#define EWDT_CTL_WKF_Pos                  (5)                                               /*!< EWDT_T::CTL: WKF Position               */
#define EWDT_CTL_WKF_Msk                  (0x1ul << EWDT_CTL_WKF_Pos)                       /*!< EWDT_T::CTL: WKF Mask                   */

#define EWDT_CTL_INTEN_Pos                (6)                                               /*!< EWDT_T::CTL: INTEN Position             */
#define EWDT_CTL_INTEN_Msk                (0x1ul << EWDT_CTL_INTEN_Pos)                     /*!< EWDT_T::CTL: INTEN Mask                 */

#define EWDT_CTL_WDTEN_Pos                (7)                                               /*!< EWDT_T::CTL: WDTEN Position             */
#define EWDT_CTL_WDTEN_Msk                (0x1ul << EWDT_CTL_WDTEN_Pos)                     /*!< EWDT_T::CTL: WDTEN Mask                 */

#define EWDT_CTL_TOUTSEL_Pos              (8)                                               /*!< EWDT_T::CTL: TOUTSEL Position           */
#define EWDT_CTL_TOUTSEL_Msk              (0xful << EWDT_CTL_TOUTSEL_Pos)                   /*!< EWDT_T::CTL: TOUTSEL Mask               */

#define EWDT_CTL_SYNC_Pos                 (30)                                              /*!< EWDT_T::CTL: SYNC Position              */
#define EWDT_CTL_SYNC_Msk                 (0x1ul << EWDT_CTL_SYNC_Pos)                      /*!< EWDT_T::CTL: SYNC Mask                  */

#define EWDT_CTL_ICEDEBUG_Pos             (31)                                              /*!< EWDT_T::CTL: ICEDEBUG Position          */
#define EWDT_CTL_ICEDEBUG_Msk             (0x1ul << EWDT_CTL_ICEDEBUG_Pos)                  /*!< EWDT_T::CTL: ICEDEBUG Mask              */

#define EWDT_ALTCTL_RSTDSEL_Pos           (0)                                               /*!< EWDT_T::ALTCTL: RSTDSEL Position        */
#define EWDT_ALTCTL_RSTDSEL_Msk           (0x3ul << EWDT_ALTCTL_RSTDSEL_Pos)                /*!< EWDT_T::ALTCTL: RSTDSEL Mask            */

#define EWDT_RSTCNT_RSTCNT_Pos            (0)                                               /*!< EWDT_T::RSTCNT: RSTCNT Position         */
#define EWDT_RSTCNT_RSTCNT_Msk            (0xfffffffful << EWDT_RSTCNT_RSTCNT_Pos)          /*!< EWDT_T::RSTCNT: RSTCNT Mask             */


/**@}*/ /* EWDT_CONST */
/**@}*/ /* end of EWDT register group */
/**@}*/ /* end of REGISTER group */

#endif /* __EWDT_REG_H__ */
