/**************************************************************************//**
 * @file     clk_reg.h
 * @version  V1.00
 * @brief    CLK register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __KEYPAD_REG_H__
#define __KEYPAD_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Keypad Control Interface -------------------------*/
/**
    @addtogroup KPI Keypad Control Interface (KPI)
    Memory Mapped Structure for KPI Controller
@{ */

typedef struct
{


    /**
     * @var KPI_T::CTL
     * Offset: 0x00  Keypad Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |KPEN      |Keypad Scan Enable Bit
     * |        |          |Setting this bit high enables the key scan function.
     * |        |          |0 = Keypad scan Disabled.
     * |        |          |1 = Keypad scan Enabled.
     * |[1]     |KPIEN     |Key Press Key Interrupt Enable Bit
     * |        |          |The keypad controller will generate an interrupt when the controller detects any effective key press.
     * |        |          |0 = Keypad press interrupt Disabled.
     * |        |          |1 = Keypad press interrupt Enabled.
     * |        |          |Note: The bit will be reset when KPI reset occurs.
     * |[2]     |KRIEN     |Key Release Key Interrupt Enable Bit
     * |        |          |The keypad controller will generate an interrupt when the controller detects keypad status changes from press to release.
     * |        |          |0 = Keypad release interrupt Disabled.
     * |        |          |1 = Keypad release interrupt Enabled.
     * |        |          |Note: The bit will be reset when KPI reset occurs.
     * |[3]     |KIEN      |Key Interrupt Enable Bit
     * |        |          |0 = Keypad interrupt Disabled.
     * |        |          |1 = Keypad interrupt Enabled.
     * |        |          |Note: The bit will be reset when KPI reset occurs.
     * |[5:4]   |DBCT      |De-bounce Cycle Time
     * |        |          |For keypad debounce, keypad will generate an interrupt when key press, key release or three key reset continued n * key array scan time.
     * |        |          |00 = n=1.
     * |        |          |01 = n=2.
     * |        |          |10 = n=3.
     * |        |          |11 = n=4.
     * |        |          |Note: It would need more time to indicate key press and release event when users selected more debounce cycle time.
     * |[15:8]  |PSC       |Row Scan Cycle Pre-scale Value
     * |        |          |This value is used to pre-scale row scan cycle.
     * |        |          |The pre-scale counter is clocked by the divided crystal clock, xCLOCK.
     * |        |          |The divided number is from 1 to 256.
     * |        |          |E.g.If the crystal clock is 1Mhz then the xCLOCK period is 1us.
     * |        |          |If the keypad matric is 3x3 then
     * |        |          |Each row scan time = xCLOCK x PRESCALE PSC x PrescaleDividerPSCDIV.
     * |        |          |Key array scan time = Each row scan time x ROWS.
     * |        |          |Example scan time for PRESCALE = 0x40, and PrescaleDividerPSCDIV = 0x1F.
     * |        |          |Each row scan time = 1us x 65 x 32 = 2.08ms.
     * |        |          |Scan time = 2.08 x 3 = 6.24ms.
     * |        |          |Note:
     * |        |          |When PRESCALEPSC is determined, De-bounce sampling cycle should not exceed the half of (PRESCALEPSC x PrescaleDividerPSCDIV),
     * |        |          |in the above example, and if scan row delay cycle is 4 xclock
     * |        |          |The maximum DBCLKSEL should be 10244*256 xCLOCK, bouncing time is 1ms.
     * |[19:16] |DBCLKSEL  |Scan in De-bounce Sampling Cycle Selection
     * |        |          |0000 = Reserved.
     * |        |          |0001 = Reserved.
     * |        |          |0010 = Reserved.
     * |        |          |0011 = Sample interrupt input once per 8 clocks.
     * |        |          |0100 = Sample interrupt input once per 16 clocks.
     * |        |          |0101 = Sample interrupt input once per 32 clocks.
     * |        |          |0110 = Sample interrupt input once per 64 clocks.
     * |        |          |0111 = Sample interrupt input once per 128 clocks.
     * |        |          |1000 = Sample interrupt input once per 256 clocks.
     * |        |          |1001 = Sample interrupt input once per 512 clocks.
     * |        |          |1010 = Sample interrupt input once per 1024 clocks.
     * |        |          |1011 = Sample interrupt input once per 2048 clocks.
     * |        |          |1100 = Sample interrupt input once per 4096 clocks.
     * |        |          |1101 = Sample interrupt input once per 8192 clocks.
     * |        |          |1110 = reserved.
     * |        |          |1111 = reserved.
     * |        |          |Note:
     * |        |          |scan row delay cycle < debounce sampling cycle.
     * |        |          |row scan time > scan row delay cycle + (2 * debounce sampling cycle) + 1 xclock cycle(change row) + 2 xclock cycle(cross clock domain).
     * |        |          |row scan time = xCLOCK x PRESCALEPSC x PrescaleDividerPSCDIVprescale * 32 (xclock).
     * |        |          |xclock = 1 MHz ~32 kHz.
     * |        |          |bouncing time last for 1ms
     * |        |          |For example, if xclock = 1 MHz,.
     * |        |          |debounce sampling cycle choose 1024 xclock,
     * |        |          |and scan row delay cycle choose 8 xclock,
     * |        |          |row scan time should choose larger than (8+2048+3) xclock,
     * |        |          |suppose PrescaleDividerPSCDIV = 0x1F, then prescale = 65 (20562059/32 = 64.2535).
     * |[23:22] |ROWDLY    |Scan Row Delay
     * |        |          |Setting delay cycle when row change, for avoid KPI from detecting wrong key..
     * |        |          |00 = 4 KPI engine clock cycle.
     * |        |          |01 = 8 KPI engine clock cycle.
     * |        |          |10 = 16 KPI engine clock cycle.
     * |        |          |11 = 32 KPI engine clock cycle.
     * |        |          |Note:
     * |        |          |scan row delay cycle < debounce sampling cycle.
     * |        |          |row scan time > scan row delay cycle + (2 * debounce sampling cycle) + 1 xclock cycle(change row) + 2 xclock cycle(cross clock domain).
     * |[26:24] |KCOL      |Keypad Matrix COL Number
     * |        |          |The keypad matrix is set by ROW x COL. The COL number can be set 1 to 8.
     * |        |          |000 = 1.
     * |        |          |001 = 2.
     * |        |          |010 = 3.
     * |        |          |011 = 4.
     * |        |          |100 = 5.
     * |        |          |101 = 6.
     * |        |          |110 = 7.
     * |        |          |111 = 8.
     * |[30:28] |KROW      |Keypad Matrix ROW Number
     * |        |          |The keypad matrix is set by ROW x COL. The ROW number can be set 2 to 6.
     * |        |          |000 = reserved.
     * |        |          |001 = 2.
     * |        |          |010 = 3.
     * |        |          |011 = 4.
     * |        |          |100 = 5.
     * |        |          |101 = 6.
     * |        |          |110 = Reserved.
     * |        |          |111 = Reserved.
     * @var KPI_T::STATUS
     * Offset: 0x08  Keypad Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |TKRIF     |3Three-keys Reset Interrupt Flag
     * |        |          |This bit will be set after 3Three-keys reset occurs.
     * |        |          |When READ:
     * |        |          |0 = No reset.
     * |        |          |1 = 3Three -keys reset interrupt occurred.
     * |        |          |When WRITE:
     * |        |          |0 = No operation.
     * |        |          |1 = Clear interrupt flag.
     * |[2]     |KIF       |Key Interrupt Flag
     * |        |          |This bit indicates the key scan interrupt is active when any key press or, key release or three key reset or wake up.
     * |        |          |When READ:
     * |        |          |0 = No reset.
     * |        |          |1 = Key press/Key release/3Three-key reset/wakeup interrupt occurred.
     * |        |          |To clear KIF, software must clear KPIF, KRIF and TKRIF
     * |        |          |(u9019u6BB5WSu81EAu5DF1u731Cu7684uFF0Cu5C0Du55CE?)
     * |[3]     |KRIF      |Release Key Release Interrupt Flag
     * |        |          |This bit indicates that some keys (one or multiple key) have been released.
     * |        |          |When READ:
     * |        |          |0 = No key release.
     * |        |          |1 = At least one key release.
     * |        |          |Note: To clear KRKEYINTIF, software must clear each releasing event flag that are shown on u201Ckey releasing eventu201D
     * |        |          |KPI_KRF0/1 registers.
     * |        |          |C code example:
     * |        |          |DWORD RKE0, RKE1
     * |        |          |PKE0 = reg_read(KPIKRE0); PKE1 = reg_read(KPIKRE1);.
     * |        |          |Reg_write(KPIKRE0, RKE0); Reg_write(KPIKRE1, RKE1)
     * |[4]     |KPIF      |Key Press Key Interrupt Flag
     * |        |          |This bit indicates that some keys (one or multiple key) have been pressed.
     * |        |          |When READ:
     * |        |          |0 = No key press.
     * |        |          |1 = At least one key press.
     * |        |          |Note: To clear KPIFPKEYINT, software must clear each pressing event flag that are shown on u201CKPIKPE1KPI_KPF0/1, KPIKPE0u201D
     * |        |          |registers.
     * |        |          |C code example:
     * |        |          |DWORD PKE0, PKE1
     * |        |          |PKE0 = reg_read(KPIKPE0); PKE1 = reg_read(KPIKPE1);.
     * |        |          |Reg_write(KPIKPE0, PKE0); Reg_write(KPIKPE1, PKE1)
     * @var KPI_T::KST0
     * Offset: 0x10  Keypad State Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KSTmn     |Key State
     * |        |          |KESTm,n: m is row number, n is column number.
     * |        |          |0 = Key m,n is pressing.
     * |        |          |1 = Key m,n is releasing.
     * @var KPI_T::KST1
     * Offset: 0x14  Keypad State Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |KESTmn    |Key State
     * |        |          |KESTm,n: m is row number, n is column number.
     * |        |          |0 = Key m,n is pressing.
     * |        |          |1 = Key m,n is releasing.
     * @var KPI_T::KPF0
     * Offset: 0x18  Lower 32 Key Press Flag Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KPFmn     |Lower 32 Key Press Event Change IndicatorFlag
     * |        |          |m is row number, n is column number.
     * |        |          |KPE mn[X] = 1, m=row, n=column:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a high to low event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear PKEYINT KPIF (KPI_STATUS[4]) by writing 1 bit by bit to this register.
     * @var KPI_T::KPF1
     * Offset: 0x1C  Upper 32 Key Press Flag Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |KPEmn     |Upper 32 Key Press Event Change IndicatorFlag
     * |        |          |KPE mn[X] = 1, m =is row number, n =is column number.:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a high to low event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear PKEYINT (KPISTATUS[4]) by writing 1 bit by bit to this register.
     * @var KPI_T::KRF0
     * Offset: 0x20  Lower 32 Key Release Flag Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KRFmn     |Lower 32 Key Release Event Change IndicatorFlag
     * |        |          |KRE mn[X] = 1, m= is row number, n= is column number.:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a low to high event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear RKEYINT (KPISTATUS[3]) by writing 1 bit by bit to this register.
     * @var KPI_T::KRF1
     * Offset: 0x24  Upper 32 Key Release Flag Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |KRFmn     |Upper 32 Key Release Event Change IndicatorFlag
     * |        |          |KRE mn[X] = 1, m =is row number, n =is column number.:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a low to high event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear RKEYINT (KPISTATUS[3]) by writing 1 bit by bit to this register.
     * @var KPI_T::DLYCTL
     * Offset: 0x28  Delay Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PSCDIV    |Pre-scale Divider
     * |        |          |This value is used to divide RESCALE that is set in KPICONFKPI_CTL[15:8]
     * |        |          |The prescale divider counter is clocked by the divided crystal clock, xCLOCK
     * |        |          |The number is from 1 to 256.
     * |        |          |E.g. If the crystal clock is 1Mhz then the xCLOCK period is 1us. If the keypad matrix is 3x3. Then,
     * |        |          |each row scan time = xCLOCK x PRESCALEPSC x PrescaleDividerPSCDIV.
     * |        |          |key array scan time = each row scan time x ROWS.
     * |        |          |example scan time for PRESCALEPSC = 0x40, and PrescaleDividerPSCDIV = 0x1F.
     * |        |          |each row scan time = 1us x 65 x 32 = 2.08ms.
     * |        |          |scan time = 2.08 x 3 = 6.24ms.
     * |        |          |Note:
     * |        |          |When PRESCALEPSC (KPICONFKPI_CTL[15:8]) is determined, De-bounce sampling cycle should not exceed the half of (PRESCALEPSC x PrescaleDividerPSCDIV),
     * |        |          |in the above example, and if scan row delay cycle is 4 xclock
     * |        |          |The maximum DBCLKSEL(KPICONFKPI_CTL[19:16]) should be 1024 x clock, bouncing time is 1ms.
     * |[17:8]  |SCANDLY   |Key Array Scan Delay
     * |        |          |This value is used to insert delay cycle between each key array scan.
     * |        |          |The key array scan delay counter is clocked by the divided crystal clock, xCLOCK.
     * |        |          |Key array scan delay time = xCLOCK x KASDSCANDLY.
     * |        |          |The number of key array scan delay cycle is 0 and from 2 to 1024.
     * |        |          |0 = No delay.
     * |        |          |Others = others + 1 cycles.
     * |        |          |Note:
     * |        |          |If the key array scan delay is set to 0, there are no delay between each key array scan.
     * |        |          |There are no delay 1 cycle situation.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] Keypad Control Register                                          */
    __IO uint32_t Reserved0;             /*!< [0x0004] Reserved                                                         */
    __IO uint32_t STATUS;                /*!< [0x0008] Keypad Status Register                                           */
    __IO uint32_t Reserved1;             /*!< [0x000c] Reserved                                                         */
    __I  uint32_t KST[2];                /*!< [0x0010-0x0014] Keypad State Register 0                                   */
    __IO uint32_t KPF[2];                /*!< [0x0018-0x001c] Lower 32 Key Press Flag Register 0                        */
    __IO uint32_t KRF[2];                /*!< [0x0020-0x0024] Lower 32 Key Release Flag Register 0                      */
    __IO uint32_t DLYCTL;                /*!< [0x0028] Delay Control Register                                           */

} KPI_T;

/**
    @addtogroup KPI_CONST KPI Bit Field Definition
    Constant Definitions for KPI Controller
@{ */

#define KPI_CTL_KPEN_Pos                 (0)                                               /*!< KPI_T::CTL: KPEN Position              */
#define KPI_CTL_KPEN_Msk                 (0x1ul << KPI_CTL_KPEN_Pos)                       /*!< KPI_T::CTL: KPEN Mask                  */

#define KPI_CTL_KPIEN_Pos                (1)                                               /*!< KPI_T::CTL: KPIEN Position             */
#define KPI_CTL_KPIEN_Msk                (0x1ul << KPI_CTL_KPIEN_Pos)                      /*!< KPI_T::CTL: KPIEN Mask                 */

#define KPI_CTL_KRIEN_Pos                (2)                                               /*!< KPI_T::CTL: KRIEN Position             */
#define KPI_CTL_KRIEN_Msk                (0x1ul << KPI_CTL_KRIEN_Pos)                      /*!< KPI_T::CTL: KRIEN Mask                 */

#define KPI_CTL_KIEN_Pos                 (3)                                               /*!< KPI_T::CTL: KIEN Position              */
#define KPI_CTL_KIEN_Msk                 (0x1ul << KPI_CTL_KIEN_Pos)                       /*!< KPI_T::CTL: KIEN Mask                  */

#define KPI_CTL_DBCT_Pos                 (4)                                               /*!< KPI_T::CTL: DBCT Position              */
#define KPI_CTL_DBCT_Msk                 (0x3ul << KPI_CTL_DBCT_Pos)                       /*!< KPI_T::CTL: DBCT Mask                  */

#define KPI_CTL_PSC_Pos                  (8)                                               /*!< KPI_T::CTL: PSC Position               */
#define KPI_CTL_PSC_Msk                  (0xfful << KPI_CTL_PSC_Pos)                       /*!< KPI_T::CTL: PSC Mask                   */

#define KPI_CTL_DBCLKSEL_Pos             (16)                                              /*!< KPI_T::CTL: DBCLKSEL Position          */
#define KPI_CTL_DBCLKSEL_Msk             (0xful << KPI_CTL_DBCLKSEL_Pos)                   /*!< KPI_T::CTL: DBCLKSEL Mask              */

#define KPI_CTL_ROWDLY_Pos               (22)                                              /*!< KPI_T::CTL: ROWDLY Position            */
#define KPI_CTL_ROWDLY_Msk               (0x3ul << KPI_CTL_ROWDLY_Pos)                     /*!< KPI_T::CTL: ROWDLY Mask                */

#define KPI_CTL_KCOL_Pos                 (24)                                              /*!< KPI_T::CTL: KCOL Position              */
#define KPI_CTL_KCOL_Msk                 (0x7ul << KPI_CTL_KCOL_Pos)                       /*!< KPI_T::CTL: KCOL Mask                  */

#define KPI_CTL_KROW_Pos                 (28)                                              /*!< KPI_T::CTL: KROW Position              */
#define KPI_CTL_KROW_Msk                 (0x7ul << KPI_CTL_KROW_Pos)                       /*!< KPI_T::CTL: KROW Mask                  */

#define KPI_STATUS_TKRIF_Pos             (1)                                               /*!< KPI_T::STATUS: TKRIF Position          */
#define KPI_STATUS_TKRIF_Msk             (0x1ul << KPI_STATUS_TKRIF_Pos)                   /*!< KPI_T::STATUS: TKRIF Mask              */

#define KPI_STATUS_KIF_Pos               (2)                                               /*!< KPI_T::STATUS: KIF Position            */
#define KPI_STATUS_KIF_Msk               (0x1ul << KPI_STATUS_KIF_Pos)                     /*!< KPI_T::STATUS: KIF Mask                */

#define KPI_STATUS_KRIF_Pos              (3)                                               /*!< KPI_T::STATUS: KRIF Position           */
#define KPI_STATUS_KRIF_Msk              (0x1ul << KPI_STATUS_KRIF_Pos)                    /*!< KPI_T::STATUS: KRIF Mask               */

#define KPI_STATUS_KPIF_Pos              (4)                                               /*!< KPI_T::STATUS: KPIF Position           */
#define KPI_STATUS_KPIF_Msk              (0x1ul << KPI_STATUS_KPIF_Pos)                    /*!< KPI_T::STATUS: KPIF Mask               */

#define KPI_KST0_KSTmn_Pos               (0)                                               /*!< KPI_T::KST0: KSTmn Position            */
#define KPI_KST0_KSTmn_Msk               (0xfffffffful << KPI_KST0_KSTmn_Pos)              /*!< KPI_T::KST0: KSTmn Mask                */

#define KPI_KST1_KESTmn_Pos              (0)                                               /*!< KPI_T::KST1: KESTmn Position           */
#define KPI_KST1_KESTmn_Msk              (0xfffful << KPI_KST1_KESTmn_Pos)                 /*!< KPI_T::KST1: KESTmn Mask               */

#define KPI_KPF0_KPFmn_Pos               (0)                                               /*!< KPI_T::KPF0: KPFmn Position            */
#define KPI_KPF0_KPFmn_Msk               (0xfffffffful << KPI_KPF0_KPFmn_Pos)              /*!< KPI_T::KPF0: KPFmn Mask                */

#define KPI_KPF1_KPEmn_Pos               (0)                                               /*!< KPI_T::KPF1: KPEmn Position            */
#define KPI_KPF1_KPEmn_Msk               (0xfffful << KPI_KPF1_KPEmn_Pos)                  /*!< KPI_T::KPF1: KPEmn Mask                */

#define KPI_KRF0_KRFmn_Pos               (0)                                               /*!< KPI_T::KRF0: KRFmn Position            */
#define KPI_KRF0_KRFmn_Msk               (0xfffffffful << KPI_KRF0_KRFmn_Pos)              /*!< KPI_T::KRF0: KRFmn Mask                */

#define KPI_KRF1_KRFmn_Pos               (0)                                               /*!< KPI_T::KRF1: KRFmn Position            */
#define KPI_KRF1_KRFmn_Msk               (0xfffful << KPI_KRF1_KRFmn_Pos)                  /*!< KPI_T::KRF1: KRFmn Mask                */

#define KPI_DLYCTL_PSCDIV_Pos            (0)                                               /*!< KPI_T::DLYCTL: PSCDIV Position         */
#define KPI_DLYCTL_PSCDIV_Msk            (0xfful << KPI_DLYCTL_PSCDIV_Pos)                 /*!< KPI_T::DLYCTL: PSCDIV Mask             */

#define KPI_DLYCTL_SCANDLY_Pos           (8)                                               /*!< KPI_T::DLYCTL: SCANDLY Position        */
#define KPI_DLYCTL_SCANDLY_Msk           (0x3fful << KPI_DLYCTL_SCANDLY_Pos)               /*!< KPI_T::DLYCTL: SCANDLY Mask            */

/**@}*/ /* KPI_CONST */
/**@}*/ /* end of KPI register group */


/**@}*/ /* end of REGISTER group */
#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __KEYPAD_REG_H__ */
