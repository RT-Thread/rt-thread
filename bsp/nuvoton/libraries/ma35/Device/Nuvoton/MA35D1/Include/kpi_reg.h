/**************************************************************************//**
 * @file     kpi_reg.h
 * @version  V1.00
 * @brief    KPI register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 20 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __KPI_REG_H__
#define __KPI_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup Keypad Interface (KPI)
    Memory Mapped Structure for KPI Controller
@{ */

typedef struct
{


    /**
     * @var KPI_T::KPICONF
     * Offset: 0x00  Keypad Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ENKP      |Keypad Scan Enable Bit
     * |        |          |Setting this bit high enables the key scan function.
     * |        |          |0 = Keypad scan Disabled.
     * |        |          |1 = Keypad scan Enabled.
     * |[1]     |PKINTEN   |Press Key Interrupt Enable Bit
     * |        |          |The keypad controller will generate an interrupt when the controller detects any effective key press.
     * |        |          |0 = Keypad press interrupt Disabled.
     * |        |          |1 = Keypad press interrupt Enabled.
     * |        |          |Note: The bit will be reset when KPI reset occurs.
     * |[2]     |RKINTEN   |Release Key Interrupt Enable Bit
     * |        |          |The keypad controller will generate an interrupt when the controller detects keypad status changes from press to release.
     * |        |          |0 = Keypad release interrupt Disabled.
     * |        |          |1 = Keypad release interrupt Enabled.
     * |        |          |Note: The bit will be reset when KPI reset occurs.
     * |[3]     |INTEN     |Key Interrupt Enable Bit
     * |        |          |0 = Keypad interrupt Disabled.
     * |        |          |1 = Keypad interrupt Enabled.
     * |        |          |Note: The bit will be reset when KPI reset occurs.
     * |[5]     |WAKEUP    |Lower Power Wakeup Enable Bit
     * |        |          |Setting this bit enables low power wakeup.
     * |        |          |0 = Wakeup Disabled.
     * |        |          |1 = Wakeup Enabled.
     * |        |          |Note: Setting the bit will force all KPI scan out to low.
     * |[15:8]  |PRESCALE  |Row Scan Cycle Pre-scale Value
     * |        |          |This value is used to pre-scale row scan cycle.
     * |        |          |The pre-scale counter is clocked by the divided crystal clock, xCLOCK.
     * |        |          |The divided number is from 1 to 256.
     * |        |          |E.g.If the crystal clock is 1Mhz then the xCLOCK period is 1us.
     * |        |          |If the keypad matric is 3x3 then
     * |        |          |Each row scan time = xCLOCK x PRESCALE x PrescaleDivider.
     * |        |          |Key array scan time = Each row scan time x ROWS.
     * |        |          |Example scan time for PRESCALE = 0x40, and PrescaleDivider = 0x1F.
     * |        |          |Each row scan time = 1us x 65 x 32 = 2.08ms.
     * |        |          |Scan time = 2.08 x 3 = 6.24ms.
     * |        |          |Note:
     * |        |          |When PRESCALE is determined, De-bounce sampling cycle should not exceed the half of (PRESCALE x PrescaleDivider),
     * |        |          |in the above example, and if scan row delay cycle is 4 xclock
     * |        |          |The maximum DBCLKSEL should be 4*256 xCLOCK, bouncing time is 1ms.
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
     * |        |          |row scan time > scan row delay cycle + (2 * debounce sampling cycle).
     * |        |          |row scan time = prescale * 32 (xclock).
     * |        |          |xclock = 1 MHz ~32 kHz.
     * |        |          |bouncing time last for 1ms
     * |        |          |For example, if xclock = 1 MHz,.
     * |        |          |debounce sampling cycle choose 1024 xclock,
     * |        |          |and scan row delay cycle choose 8 xclock,
     * |        |          |row scan time should choose larger than (8+2048) xclock,
     * |        |          |suppose PrescaleDivider = 0x1F, then prescale = 65 (2056/32 = 64.25).
     * |[23:22] |SCANROWD  |Scan Row Delay
     * |        |          |Setting delay cycle when row change.
     * |        |          |00 = 4 KPI engine clock cycle.
     * |        |          |01 = 8 KPI engine clock cycle.
     * |        |          |10 = 16 KPI engine clock cycle.
     * |        |          |11 = 32 KPI engine clock cycle.
     * |        |          |Note:
     * |        |          |scan row delay cycle < debounce sampling cycle.
     * |        |          |row scan time > scan row delay cycle + (2 * debounce sampling cycle).
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
     * @var KPI_T::KPI3KCONF
     * Offset: 0x04  Keypad 3-keys Configuration Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |K30C      |The #0 Key Column Address
     * |[5:3]   |K30R      |The #0 Key Row Address
     * |        |          |The #0 means the row address and the column address is the lowest of the specified 3-keys
     * |[10:8]  |K31C      |The #1 Key Column Address
     * |[13:11] |K31R      |The #1 Key Row Address
     * |        |          |The #1 means the row address and the column address is the 2nd of the specified 3-keys
     * |[18:16] |K32C      |The #2 Key Column Address
     * |[21:19] |K32R      |The #2 Key Row Address
     * |        |          |The #2 means the row address and the column address is the highest of the specified 3-keys
     * |[24]    |EN3KYRST  |Enable Three-key Reset
     * |        |          |Setting this bit enables hardware reset when three-key is detected
     * |        |          |0 = Three-key function Disabled.
     * |        |          |1 = Three-key function Enabled.
     * |        |          |Note: The bit will be reset when KPI reset occurs.
     * @var KPI_T::KPISTATUS
     * Offset: 0x08  Keypad Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PDWAKE    |Power Down Wakeup Flag
     * |        |          |This flag indicates the chip is woken up from power down by keypad.
     * |        |          |When READ:
     * |        |          |0 = No wakeup.
     * |        |          |1 = Wake-up by keypad.
     * |        |          |When WRITE:
     * |        |          |0 = No operation.
     * |        |          |1 = Clear interrupt flag.
     * |[1]     |RST3KEY   |3-keys Reset Flag
     * |        |          |This bit will be set after 3-keys reset occurs.
     * |        |          |When READ:
     * |        |          |0 = No reset.
     * |        |          |1 = 3 keys reset interrupt occurred.
     * |        |          |When WRITE:
     * |        |          |0 = No operation.
     * |        |          |1 = Clear interrupt flag.
     * |[2]     |KEYINT    |Key Interrupt
     * |        |          |This bit indicates the key scan interrupt is active when any key press or release or three key reset or wake up.
     * |        |          |When READ:
     * |        |          |0 = No reset.
     * |        |          |1 = Key press/release/3-key reset/wakeup interrupt occurred.
     * |[3]     |RKEYINT   |Release Key Interrupt
     * |        |          |This bit indicates that some keys (one or multiple key) have been released.
     * |        |          |When READ:
     * |        |          |0 = No key release.
     * |        |          |1 = At least one key release.
     * |        |          |Note: To clear RKEYINT, software must clear each releasing event that are shown on u201Ckey releasing eventu201D.
     * |        |          |C code example:
     * |        |          |DWORD RKE0, RKE1
     * |        |          |PKE0 = reg_read(KPIKRE0); PKE1 = reg_read(KPIKRE1);.
     * |        |          |Reg_write(KPIKRE0, RKE0); Reg_write(KPIKRE1, RKE1)
     * |[4]     |PKEYINT   |Press Key Interrupt
     * |        |          |This bit indicates that some keys (one or multiple key) have been pressed.
     * |        |          |When READ:
     * |        |          |0 = No key press.
     * |        |          |1 = At least one key press.
     * |        |          |Note: To clear PKEYINT, software must clear each pressing event that are shown on u201CKPIKPE1, KPIKPE0u201D.
     * |        |          |C code example:
     * |        |          |DWORD PKE0, PKE1
     * |        |          |PKE0 = reg_read(KPIKPE0); PKE1 = reg_read(KPIKPE1);.
     * |        |          |Reg_write(KPIKPE0, PKE0); Reg_write(KPIKPE1, PKE1)
     * @var KPI_T::KPIRSTC
     * Offset: 0x0C  Keypad Reset Period Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |RSTC      |3-key Reset Period Count
     * |        |          |The keypad controller generates a reset signal when it detects 3-key match condition, if the EN3KYRST (KPI3KCONF[24]) is set
     * |        |          |The RSTC is used to control the reset period.
     * |        |          |Reset period = 64 * RSTC XCLOCK.
     * @var KPI_T::KPIKEST0
     * Offset: 0x10  Keypad State Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KESTmn    |Key State
     * |        |          |KESTm,n: m is row number, n is column number
     * |        |          |0 = Key m,n is pressing.
     * |        |          |1 = Key m,n is releasing.
     * @var KPI_T::KPIKEST1
     * Offset: 0x14  Keypad State Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |KESTmn    |Key State
     * |        |          |KESTm,n: m is row number, n is column number
     * |        |          |0 = Key m,n is pressing.
     * |        |          |1 = Key m,n is releasing.
     * @var KPI_T::KPIKPE0
     * Offset: 0x18  Lower 32 Key Press Event Indicator
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KPEmn     |Lower 32 Key Press Event Change Indicator
     * |        |          |KPE mn[X] = 1, m=row, n=column:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a high to low event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear PKEYINT (KPISTATUS[4]) by writing 1 bit by bit to this register.
     * @var KPI_T::KPIKPE1
     * Offset: 0x1C  Upper 32 Key Press Event Indicator
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |KPEmn     |Upper 32 Key Press Event Change Indicator
     * |        |          |KPE mn[X] = 1, m=row, n=column:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a high to low event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear PKEYINT (KPISTATUS[4]) by writing 1 bit by bit to this register.
     * @var KPI_T::KPIKRE0
     * Offset: 0x20  Lower 32 Key Release Event Indicator
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KREmn     |Lower 32 Key Release Event Change Indicator
     * |        |          |KRE mn[X] = 1, m=row, n=column:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a low to high event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear RKEYINT (KPISTATUS[3]) by writing 1 bit by bit to this register.
     * @var KPI_T::KPIKRE1
     * Offset: 0x24  Upper 32 Key Release Event Indicator
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |KREmn     |Upper 32 Key Release Event Change Indicator
     * |        |          |KRE mn[X] = 1, m=row, n=column:.
     * |        |          |0 = No key event.
     * |        |          |1 = Corresponding key has a low to high event change.
     * |        |          |Note:
     * |        |          |Hardware will set this bit, and software should clear this bit by writing 1.
     * |        |          |Software can clear RKEYINT (KPISTATUS[3]) by writing 1 bit by bit to this register.
     * @var KPI_T::KPIPRESCALDIV
     * Offset: 0x28  Pre-scale Divider
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PRESCALDIV|Pre-scale Divider
     * |        |          |This value is used to divide RESCALE that is set in KPICONF[15:8]
     * |        |          |The prescale divider counter is clocked by the divided crystal clock, xCLOCK
     * |        |          |The number is from 1 to 256.
     * |        |          |E.g. If the crystal clock is 1Mhz then the xCLOCK period is 1us. If the keypad matrix is 3x3. Then,
     * |        |          |each row scan time = xCLOCK x PRESCALE x PrescaleDivider.
     * |        |          |key array scan time = each row scan time x ROWS.
     * |        |          |example scan time for PRESCALE = 0x40, and PrescaleDivider = 0x1F.
     * |        |          |each row scan time = 1us x 65 x 32 = 2.08ms.
     * |        |          |scan time = 2.08 x 3 = 6.24ms.
     * |        |          |Note:
     * |        |          |When PRESCALE (KPICONF[15:8]) is determined, De-bounce sampling cycle should not exceed the half of (PRESCALE x PrescaleDivider),
     * |        |          |in the above example, and if scan row delay cycle is 4 xclock
     * |        |          |The maximum DBCLKSEL(KPICONF[19:16]) should be 1024 x clock, bouncing time is 1ms.
     */
    __IO uint32_t KPICONF;               /*!< [0x0000] Keypad Configuration Register                                    */
    __IO uint32_t KPI3KCONF;             /*!< [0x0004] Keypad 3-keys Configuration Register                             */
    __IO uint32_t KPISTATUS;             /*!< [0x0008] Keypad Status Register                                           */
    __IO uint32_t KPIRSTC;               /*!< [0x000c] Keypad Reset Period Control Register                             */
    __I  uint32_t KPIKEST0;              /*!< [0x0010] Keypad State Register 0                                          */
    __I  uint32_t KPIKEST1;              /*!< [0x0014] Keypad State Register 1                                          */
    __IO uint32_t KPIKPE0;               /*!< [0x0018] Lower 32 Key Press Event Indicator                               */
    __IO uint32_t KPIKPE1;               /*!< [0x001c] Upper 32 Key Press Event Indicator                               */
    __IO uint32_t KPIKRE0;               /*!< [0x0020] Lower 32 Key Release Event Indicator                             */
    __IO uint32_t KPIKRE1;               /*!< [0x0024] Upper 32 Key Release Event Indicator                             */
    __IO uint32_t KPIPRESCALDIV;         /*!< [0x0028] Pre-scale Divider                                                */

} KPI_T;

/**
    @addtogroup KPI_CONST KPI Bit Field Definition
    Constant Definitions for KPI Controller
@{ */

#define KPI_KPICONF_ENKP_Pos             (0)                                               /*!< KPI_T::KPICONF: ENKP Position          */
#define KPI_KPICONF_ENKP_Msk             (0x1ul << KPI_KPICONF_ENKP_Pos)                   /*!< KPI_T::KPICONF: ENKP Mask              */

#define KPI_KPICONF_PKINTEN_Pos          (1)                                               /*!< KPI_T::KPICONF: PKINTEN Position       */
#define KPI_KPICONF_PKINTEN_Msk          (0x1ul << KPI_KPICONF_PKINTEN_Pos)                /*!< KPI_T::KPICONF: PKINTEN Mask           */

#define KPI_KPICONF_RKINTEN_Pos          (2)                                               /*!< KPI_T::KPICONF: RKINTEN Position       */
#define KPI_KPICONF_RKINTEN_Msk          (0x1ul << KPI_KPICONF_RKINTEN_Pos)                /*!< KPI_T::KPICONF: RKINTEN Mask           */

#define KPI_KPICONF_INTEN_Pos            (3)                                               /*!< KPI_T::KPICONF: INTEN Position         */
#define KPI_KPICONF_INTEN_Msk            (0x1ul << KPI_KPICONF_INTEN_Pos)                  /*!< KPI_T::KPICONF: INTEN Mask             */

#define KPI_KPICONF_WAKEUP_Pos           (5)                                               /*!< KPI_T::KPICONF: WAKEUP Position        */
#define KPI_KPICONF_WAKEUP_Msk           (0x1ul << KPI_KPICONF_WAKEUP_Pos)                 /*!< KPI_T::KPICONF: WAKEUP Mask            */

#define KPI_KPICONF_PRESCALE_Pos         (8)                                               /*!< KPI_T::KPICONF: PRESCALE Position      */
#define KPI_KPICONF_PRESCALE_Msk         (0xfful << KPI_KPICONF_PRESCALE_Pos)              /*!< KPI_T::KPICONF: PRESCALE Mask          */

#define KPI_KPICONF_DBCLKSEL_Pos         (16)                                              /*!< KPI_T::KPICONF: DBCLKSEL Position      */
#define KPI_KPICONF_DBCLKSEL_Msk         (0xful << KPI_KPICONF_DBCLKSEL_Pos)               /*!< KPI_T::KPICONF: DBCLKSEL Mask          */

#define KPI_KPICONF_SCANROWD_Pos         (22)                                              /*!< KPI_T::KPICONF: SCANROWD Position      */
#define KPI_KPICONF_SCANROWD_Msk         (0x3ul << KPI_KPICONF_SCANROWD_Pos)               /*!< KPI_T::KPICONF: SCANROWD Mask          */

#define KPI_KPICONF_KCOL_Pos             (24)                                              /*!< KPI_T::KPICONF: KCOL Position          */
#define KPI_KPICONF_KCOL_Msk             (0x7ul << KPI_KPICONF_KCOL_Pos)                   /*!< KPI_T::KPICONF: KCOL Mask              */

#define KPI_KPICONF_KROW_Pos             (28)                                              /*!< KPI_T::KPICONF: KROW Position          */
#define KPI_KPICONF_KROW_Msk             (0x7ul << KPI_KPICONF_KROW_Pos)                   /*!< KPI_T::KPICONF: KROW Mask              */

#define KPI_KPI3KCONF_K30C_Pos           (0)                                               /*!< KPI_T::KPI3KCONF: K30C Position        */
#define KPI_KPI3KCONF_K30C_Msk           (0x7ul << KPI_KPI3KCONF_K30C_Pos)                 /*!< KPI_T::KPI3KCONF: K30C Mask            */

#define KPI_KPI3KCONF_K30R_Pos           (3)                                               /*!< KPI_T::KPI3KCONF: K30R Position        */
#define KPI_KPI3KCONF_K30R_Msk           (0x7ul << KPI_KPI3KCONF_K30R_Pos)                 /*!< KPI_T::KPI3KCONF: K30R Mask            */

#define KPI_KPI3KCONF_K31C_Pos           (8)                                               /*!< KPI_T::KPI3KCONF: K31C Position        */
#define KPI_KPI3KCONF_K31C_Msk           (0x7ul << KPI_KPI3KCONF_K31C_Pos)                 /*!< KPI_T::KPI3KCONF: K31C Mask            */

#define KPI_KPI3KCONF_K31R_Pos           (11)                                              /*!< KPI_T::KPI3KCONF: K31R Position        */
#define KPI_KPI3KCONF_K31R_Msk           (0x7ul << KPI_KPI3KCONF_K31R_Pos)                 /*!< KPI_T::KPI3KCONF: K31R Mask            */

#define KPI_KPI3KCONF_K32C_Pos           (16)                                              /*!< KPI_T::KPI3KCONF: K32C Position        */
#define KPI_KPI3KCONF_K32C_Msk           (0x7ul << KPI_KPI3KCONF_K32C_Pos)                 /*!< KPI_T::KPI3KCONF: K32C Mask            */

#define KPI_KPI3KCONF_K32R_Pos           (19)                                              /*!< KPI_T::KPI3KCONF: K32R Position        */
#define KPI_KPI3KCONF_K32R_Msk           (0x7ul << KPI_KPI3KCONF_K32R_Pos)                 /*!< KPI_T::KPI3KCONF: K32R Mask            */

#define KPI_KPI3KCONF_EN3KYRST_Pos       (24)                                              /*!< KPI_T::KPI3KCONF: EN3KYRST Position    */
#define KPI_KPI3KCONF_EN3KYRST_Msk       (0x1ul << KPI_KPI3KCONF_EN3KYRST_Pos)             /*!< KPI_T::KPI3KCONF: EN3KYRST Mask        */

#define KPI_KPISTATUS_PDWAKE_Pos         (0)                                               /*!< KPI_T::KPISTATUS: PDWAKE Position      */
#define KPI_KPISTATUS_PDWAKE_Msk         (0x1ul << KPI_KPISTATUS_PDWAKE_Pos)               /*!< KPI_T::KPISTATUS: PDWAKE Mask          */

#define KPI_KPISTATUS_RST3KEY_Pos        (1)                                               /*!< KPI_T::KPISTATUS: RST3KEY Position     */
#define KPI_KPISTATUS_RST3KEY_Msk        (0x1ul << KPI_KPISTATUS_RST3KEY_Pos)              /*!< KPI_T::KPISTATUS: RST3KEY Mask         */

#define KPI_KPISTATUS_KEYINT_Pos         (2)                                               /*!< KPI_T::KPISTATUS: KEYINT Position      */
#define KPI_KPISTATUS_KEYINT_Msk         (0x1ul << KPI_KPISTATUS_KEYINT_Pos)               /*!< KPI_T::KPISTATUS: KEYINT Mask          */

#define KPI_KPISTATUS_RKEYINT_Pos        (3)                                               /*!< KPI_T::KPISTATUS: RKEYINT Position     */
#define KPI_KPISTATUS_RKEYINT_Msk        (0x1ul << KPI_KPISTATUS_RKEYINT_Pos)              /*!< KPI_T::KPISTATUS: RKEYINT Mask         */

#define KPI_KPISTATUS_PKEYINT_Pos        (4)                                               /*!< KPI_T::KPISTATUS: PKEYINT Position     */
#define KPI_KPISTATUS_PKEYINT_Msk        (0x1ul << KPI_KPISTATUS_PKEYINT_Pos)              /*!< KPI_T::KPISTATUS: PKEYINT Mask         */

#define KPI_KPIRSTC_RSTC_Pos             (0)                                               /*!< KPI_T::KPIRSTC: RSTC Position          */
#define KPI_KPIRSTC_RSTC_Msk             (0xfful << KPI_KPIRSTC_RSTC_Pos)                  /*!< KPI_T::KPIRSTC: RSTC Mask              */

#define KPI_KPIKEST0_KESTmn_Pos          (0)                                               /*!< KPI_T::KPIKEST0: KESTmn Position       */
#define KPI_KPIKEST0_KESTmn_Msk          (0xfffffffful << KPI_KPIKEST0_KESTmn_Pos)         /*!< KPI_T::KPIKEST0: KESTmn Mask           */

#define KPI_KPIKEST1_KESTmn_Pos          (0)                                               /*!< KPI_T::KPIKEST1: KESTmn Position       */
#define KPI_KPIKEST1_KESTmn_Msk          (0xfffful << KPI_KPIKEST1_KESTmn_Pos)             /*!< KPI_T::KPIKEST1: KESTmn Mask           */

#define KPI_KPIKPE0_KPEmn_Pos            (0)                                               /*!< KPI_T::KPIKPE0: KPEmn Position         */
#define KPI_KPIKPE0_KPEmn_Msk            (0xfffffffful << KPI_KPIKPE0_KPEmn_Pos)           /*!< KPI_T::KPIKPE0: KPEmn Mask             */

#define KPI_KPIKPE1_KPEmn_Pos            (0)                                               /*!< KPI_T::KPIKPE1: KPEmn Position         */
#define KPI_KPIKPE1_KPEmn_Msk            (0xfffful << KPI_KPIKPE1_KPEmn_Pos)               /*!< KPI_T::KPIKPE1: KPEmn Mask             */

#define KPI_KPIKRE0_KREmn_Pos            (0)                                               /*!< KPI_T::KPIKRE0: KREmn Position         */
#define KPI_KPIKRE0_KREmn_Msk            (0xfffffffful << KPI_KPIKRE0_KREmn_Pos)           /*!< KPI_T::KPIKRE0: KREmn Mask             */

#define KPI_KPIKRE1_KREmn_Pos            (0)                                               /*!< KPI_T::KPIKRE1: KREmn Position         */
#define KPI_KPIKRE1_KREmn_Msk            (0xfffful << KPI_KPIKRE1_KREmn_Pos)               /*!< KPI_T::KPIKRE1: KREmn Mask             */

#define KPI_KPIPRESCALDIV_PRESCALDIV_Pos (0)                                               /*!< KPI_T::KPIPRESCALDIV: PRESCALDIV Position*/
#define KPI_KPIPRESCALDIV_PRESCALDIV_Msk (0xfful << KPI_KPIPRESCALDIV_PRESCALDIV_Pos)      /*!< KPI_T::KPIPRESCALDIV: PRESCALDIV Mask  */

/**@}*/ /* KPI_CONST */
/**@}*/ /* end of KPI register group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __KPI_REG_H__ */


