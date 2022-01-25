/**************************************************************************//**
 * @file     scu_reg.h
 * @version  V1.00
 * @brief    SCU register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SCU_REG_H__
#define __SCU_REG_H__

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Booting Flag -------------------------*/
/**
    @addtogroup BTF Booting Flag
    Memory Mapped Structure for BTF Controller
  @{
*/

typedef struct
{


    /**
     * @var BTF_T::BTF
     * Offset: 0x00  Booting Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BL2       |BL2 Flag
     * |        |          |Indicating the CPU is running at BL2
     */
    __IO uint32_t BTF;                   /*!< [0x0000] Booting Flag Register                                            */

} BTF_T;

/**
    @addtogroup BTF_CONST BTF Bit Field Definition
    Constant Definitions for BTF Controller
  @{
*/

#define BTF_BTF_BL2_Pos                  (0)                                               /*!< BTF_T::BTF: BL2 Position               */
#define BTF_BTF_BL2_Msk                  (0x1ul << BTF_BTF_BL2_Pos)                        /*!< BTF_T::BTF: BL2 Mask                   */

/**@}*/ /* BTF_CONST */
/**@}*/ /* end of BTF register group */


/*---------------------- Debug Protection Mechanism -------------------------*/
/**
    @addtogroup DPM Debug Protection Mechanism(DPM)
    Memory Mapped Structure for DPM Controller
  @{
*/

typedef struct
{


    /**
     * @var DPM_T::CTL
     * Offset: 0x00  Secure DPM Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DBGDIS    |Set Secure DPM Debug Disable Bit
     * |        |          |When this bit is read as zero, it can be write to one to configure the Secure DPM DBGDIS bit (DBGDISS).
     * |        |          |When write:
     * |        |          |0 = No operation.
     * |        |          |1 = Trigger the process to set DBGDISS configuration bit.
     * |        |          |Note: This bit can be set to 1 but cannot be cleared to 0.
     * |[1]     |LOCK      |Set Secure DPM Debug Lock Bit
     * |        |          |When this bit is read as zero, it can be write to one to configure the Secure DPM LOCK bit (LOCKS).
     * |        |          |When write:
     * |        |          |0 = No operation.
     * |        |          |1 = Trigger the process to set LOCKS configuration bit.
     * |        |          |Note: This bit can be set to 1 but cannot be cleared to 0.
     * |[2]     |PWCMP     |Secure DPM Password Compare Bit
     * |        |          |Set to enter the process of compare Secure DPM password.
     * |        |          |0 = No operation.
     * |        |          |1 = Compare Secure DPM password.
     * |        |          |Note: This bit will be cleared after the comparison process is finished.
     * |[3]     |PWUPD     |Secure DPM Password Update Bit
     * |        |          |Set to enter the process of updating Secure DPM password.
     * |        |          |0 = No operation.
     * |        |          |1 = Update Secure DPM password.
     * |        |          |Note 1: This bit should be set with PWCMP equal to 0.
     * |        |          |Note 2: This bit will be cleared after the update process is finished.
     * |[8]     |INTEN     |DPM Interrupt Enable Bit
     * |        |          |0 = DPM interrupt function Enabled.
     * |        |          |1 = DPM interrupt function Disabled.
     * |[12]    |DACCWDIS  |Secure DPM Debug Write Access Disable Bit
     * |        |          |This bit disables the writability of external debugger to Secure DPM registers for debug authentication.
     * |        |          |0 = External debugger can write Secure DPM registers.
     * |        |          |1 = External debugger cannot write Secure DPM registers.
     * |[13]    |DACCDIS   |Debug Access Disable Bit
     * |        |          |This bit disables the accessibility of external debugger to all DPM registers.
     * |        |          |0 = External debugger can read/write DPM registers.
     * |        |          |1 = External debugger cannot read/write DPM registers.
     * |[31:24] |WVCODE    |Write Verify Code and Read Verify Code
     * |        |RVCODE    |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, 0x5A, is needed to do a valid write to DPM_CTL.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::STS
     * Offset: 0x04  Secure DPM Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |DPM Busy Flag (Read Only)
     * |        |          |This bit indicates the DPM is busy.
     * |        |          |0 = DPM is not busy and writing to any register is accepted.
     * |        |          |1 = DPM is busy and other bits in DPM_STS register are not valid and writing to any register is ignored.
     * |[1]     |INT       |DPM Interrupt Flag (Read Only)
     * |        |          |This bit indicates the interrupt is triggered.
     * |        |          |0 = Interrupt is not enabled or no password comparison flag is set.
     * |        |          |1 = Interrupt is enabled and PWCERR flag in either DPM_STS or DPM_NSSTS register is not cleared.
     * |        |          |Note: This bit is cleared automatically when PWCERR flag in both DPM_STS and DPM_NSSTS are zero.
     * |[4]     |PWCERR    |Secure DPM Password Compared Error Flag
     * |        |          |This bit indicates the result of Secure DPM password comparison.
     * |        |          |When read:
     * |        |          |0 = The result of Secure DPM password is correct.
     * |        |          |1 = The result of Seucre DPM password is incorrect.
     * |        |          |Note: This flag is write-one-clear.
     * |[5]     |PWUOK     |Secure DPM Password Updated Flag
     * |        |          |This bit indicates Secure DPM password has been updated successfully.
     * |        |          |When read:
     * |        |          |0 = No successful updating process has happened.
     * |        |          |1 = There is at least one successful updating process since last clearing of this bit.
     * |        |          |Note: This flag is write-one-clear.
     * |[6]     |PWFMAX    |Secure DPM Password Fail Times Maximum Reached Flag (Read Only)
     * |        |          |This bit indicates if the fail times of comparing Secure DPM password reached max times.
     * |        |          |0 = Max time has not reached and Secure DPM password comparison can be triggered.
     * |        |          |1 = Max time reached and Secure DPM password comparison cannot be processed anymore.
     * |[10:8]  |PWUCNT    |Secure DPM Password Updated Times (Read Only)
     * |        |          |This bit indicates how many times of secure password has been updated.
     * |        |          |The max value is 7. If PWUCNT reached the max value, Secure DPM password cannot be updated anymore.
     * |[16]    |DBGDIS    |Secure Debug Disable Flag (Read Only)
     * |        |          |This bit indicates the current value of Secure DPM DBGDIS bit (DBGDISS).
     * |        |          |{PWOK, LOCK, DBGDIS} bits define the current state of DPM.
     * |        |          |x00 = DEFAULT state.
     * |        |          |x1x = LOCKED state.
     * |        |          |001 = CLOSE state.
     * |        |          |101 = OPEN state.
     * |        |          |Others = Unknown.
     * |[17]    |LOCK      |Secure Debug Lock Flag (Read Only)
     * |        |          |This bit indicates the current value of Secure DPM LOCK bit (LOCKS).
     * |[18]    |PWOK      |Secure Password OK Flag (Read Only)
     * |        |          |This bit indicates the Secure DPM password has been checked and is correct.
     * |        |          |0 = The Secure DPM password has not been checked pass, yet.
     * |        |          |1 = The Secure DPM password has been checked pass since last cold reset.
     * @var DPM_T::SPW
     * Offset: 0x10  Secure DPM Password 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[31:0] to this register to update or compare Secure DPM password.
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     * Offset: 0x14  Secure DPM Password 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[63:32] to this register to update or compare Secure DPM password
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     * Offset: 0x18  Secure DPM Password 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[95:64] to this register to update or compare Secure DPM password.
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     * Offset: 0x1C  Secure DPM Password 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[127:96] to this register to update or compare Secure DPM password.
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     * @var DPM_T::NSCTL
     * Offset: 0x50  Non-secure DPM Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DBGDIS    |Set Non-secure DPM Debug Disable Bit
     * |        |          |When this bit is read as zero, it can be write to one to configure the Non-secure DPM DBGDIS bit (DBGDISNS).
     * |        |          |When write:
     * |        |          |0 = No operation.
     * |        |          |1 = Trigger the process to set DBGDISNS configuration bit.
     * |        |          |Note: This bit can be set to 1 but cannot be cleared to 0.
     * |[1]     |LOCK      |Set Non-secure DPM Debug Lock Bit
     * |        |          |When this bit is read as zero, it can be write to one to configure the Non-secure DPM LOCK bit (LOCKNS).
     * |        |          |When write:
     * |        |          |0 = No operation.
     * |        |          |1 = Trigger the process to set LOCKNS configuration bit.
     * |        |          |Note: This bit can be set to 1 but cannot be cleared to 0.
     * |[2]     |PWCMP     |Non-secure DPM Password Compare Bit
     * |        |          |Set to enter the process of compare Non-secure DPM password.
     * |        |          |0 = No operation.
     * |        |          |1 = Compare Non-secure DPM password.
     * |        |          |Note: This bit will be cleared after the comparison process is finished.
     * |[3]     |PWUPD     |Non-secure DPM Password Update Bit
     * |        |          |Set to enter the process of updating Non-secure DPM password.
     * |        |          |0 = No operation.
     * |        |          |1 = Update Non-secure DPM password.
     * |        |          |Note 1: This bit should be set with PWCMP equal to 0.
     * |        |          |Note 2: This bit will be cleared after the update process is finished.
     * |[12]    |DACCWDIS  |Debug Write Access Disable Bit
     * |        |          |This bit disables the writability of external debugger to Non-secure DPM registers for debug authentication.
     * |        |          |0 = External debugger can write Non-secure DPM registers.
     * |        |          |1 = External debugger cannot write Non-secure DPM registers.
     * |[31:24] |WVCODE    |Write Verify Code and Read Verify Code
     * |        |RVCODE    |Read operation:
     * |        |          |0xA5 = The read access for DPM_NSCTL is correct.
     * |        |          |Others = The read access for DPM_NSCTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, 0x5A, is needed to do a valid write to DPM_NSCTL.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::NSSTS
     * Offset: 0x54  Non-secure DPM Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |DPM Busy Flag (Read Only)
     * |        |          |This bit indicates the DPM is busy.
     * |        |          |0 = DPM is not busy and writing to any register is accepted.
     * |        |          |1 = DPM is busy and other bits in DPM_NSSTS register are not valid and writing to any register is ignored.
     * |[4]     |PWCERR    |Non-secure DPM Password Compared Error Flag
     * |        |          |This bit indicates the result of Non-secure DPM password comparison.
     * |        |          |0 = The result of Non-secure DPM password is correct.
     * |        |          |1 = The result of Non-seucre DPM password is incorrect.
     * |        |          |Note: This flag is write-one-clear.
     * |[5]     |PWUOK     |Non-secure DPM Password Updated Flag
     * |        |          |This bit indicates Non-secure DPM password has been updated correctly.
     * |        |          |When read:
     * |        |          |0 = No successful updating process has happened.
     * |        |          |1 = There is at least one successful updating process since last clearing of this bit.
     * |        |          |Note: This flag is write-one-clear.
     * |[6]     |PWFMAX    |Non-secure DPM Password Fail Times Maximum Reached Flag (Read Only)
     * |        |          |This bit indicates if the fail times of comparing Non-secure DPM password reached max times.
     * |        |          |0 = Max time has not reached and Non-secure DPM password comparison can be triggered.
     * |        |          |1 = Max time reached and Non-secure DPM password comparison cannot be processed anymore.
     * |[10:8]  |PWUCNT    |Non-secure DPM Password Updated Times (Read Only)
     * |        |          |This bit indicates how many times of non-secure password has been updated.
     * |        |          |The max value is 7. If PWUCNT reached the max value, Non-secure DPM password cannot be updated anymore.
     * |[16]    |DBGDIS    |Non-secure Debug Disable Flag (Read Only)
     * |        |          |This bit indicates the current value of of Non-secure DPM DBGDIS bit (DBGDISNS).
     * |        |          |{PWOK, LOCK, DBGDIS} bits define the current state of DPM.
     * |        |          |x00 = DEFAULT state.
     * |        |          |x1x = LOCKED state.
     * |        |          |001 = CLOSE state.
     * |        |          |101 = OPEN state.
     * |        |          |Others = Unknown.
     * |[17]    |LOCK      |Non-secure Debug Lock Flag (Read Only)
     * |        |          |This bit indicates the current value of Non-secure DPM DBGDIS bit (LOCKNS).
     * |[18]    |PWOK      |Non-secure Password OK Flag (Read Only)
     * |        |          |This bit indicates the Non-secure DPM password has been checked and is correct.
     * |        |          |0 = The Non-secure DPM password has not been checked pass, yet.
     * |        |          |1 = The Non-secure DPM password has been checked pass since last cold reset.
     * @var DPM_T::NSPW
     * Offset: 0x60  Non-secure DPM Password 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[31:0] to this register to update or compare Non-secure DPM password.
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     * Offset: 0x64  Non-secure DPM Password 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[63:32] to this register to update or compare Non-secure DPM password.
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     * Offset: 0x68  Non-secure DPM Password 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[95:64] to this register to update or compare Non-secure DPM password.
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     * Offset: 0x6C  Non-secure DPM Password 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PW        |Password
     * |        |          |Write password[127:96] to this register to update or compare Non-secure DPM password.
     * |        |          |It is write-only and always read as 0xFFFFFFFF.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] Secure DPM Control Register                                      */
    __IO uint32_t STS;                   /*!< [0x0004] Secure DPM Status Register                                       */
    __I  uint32_t RESERVE0[2];
    __O  uint32_t SPW[4];                /*!< [0x0010/0x0014/0x0018/0x001c] Secure DPM Password 0/1/2/3                 */
    __I  uint32_t RESERVE1[12];
    __IO uint32_t NSCTL;                 /*!< [0x0050] Non-secure DPM Control Register                                  */
    __IO uint32_t NSSTS;                 /*!< [0x0054] Non-secure DPM Status Register                                   */
    __I  uint32_t RESERVE2[2];
    __O  uint32_t NSPW[4];               /*!< [0x00600/0x0064/0x0068/0x006c] Non-secure DPM Password 0/1/2/3            */


} DPM_T;

/**
    @addtogroup DPM_CONST DPM Bit Field Definition
    Constant Definitions for DPM Controller
  @{
*/

#define DPM_CTL_DBGDIS_Pos               (0)                                               /*!< DPM_T::CTL: DBGDIS Position            */
#define DPM_CTL_DBGDIS_Msk               (0x1ul << DPM_CTL_DBGDIS_Pos)                     /*!< DPM_T::CTL: DBGDIS Mask                */

#define DPM_CTL_LOCK_Pos                 (1)                                               /*!< DPM_T::CTL: LOCK Position              */
#define DPM_CTL_LOCK_Msk                 (0x1ul << DPM_CTL_LOCK_Pos)                       /*!< DPM_T::CTL: LOCK Mask                  */

#define DPM_CTL_PWCMP_Pos                (2)                                               /*!< DPM_T::CTL: PWCMP Position             */
#define DPM_CTL_PWCMP_Msk                (0x1ul << DPM_CTL_PWCMP_Pos)                      /*!< DPM_T::CTL: PWCMP Mask                 */

#define DPM_CTL_PWUPD_Pos                (3)                                               /*!< DPM_T::CTL: PWUPD Position             */
#define DPM_CTL_PWUPD_Msk                (0x1ul << DPM_CTL_PWUPD_Pos)                      /*!< DPM_T::CTL: PWUPD Mask                 */

#define DPM_CTL_INTEN_Pos                (8)                                               /*!< DPM_T::CTL: INTEN Position             */
#define DPM_CTL_INTEN_Msk                (0x1ul << DPM_CTL_INTEN_Pos)                      /*!< DPM_T::CTL: INTEN Mask                 */

#define DPM_CTL_DACCWDIS_Pos             (12)                                              /*!< DPM_T::CTL: DACCWDIS Position          */
#define DPM_CTL_DACCWDIS_Msk             (0x1ul << DPM_CTL_DACCWDIS_Pos)                   /*!< DPM_T::CTL: DACCWDIS Mask              */

#define DPM_CTL_DACCDIS_Pos              (13)                                              /*!< DPM_T::CTL: DACCDIS Position           */
#define DPM_CTL_DACCDIS_Msk              (0x1ul << DPM_CTL_DACCDIS_Pos)                    /*!< DPM_T::CTL: DACCDIS Mask               */

#define DPM_CTL_WVCODE_Pos               (24)                                              /*!< DPM_T::CTL: WVCODE Position            */
#define DPM_CTL_WVCODE_Msk               (0xfful << DPM_CTL_WVCODE_Pos)                    /*!< DPM_T::CTL: WVCODE Mask                */

#define DPM_CTL_RVCODE_Pos               (24)                                              /*!< DPM_T::CTL: RVCODE Position            */
#define DPM_CTL_RVCODE_Msk               (0xfful << DPM_CTL_RVCODE_Pos)                    /*!< DPM_T::CTL: RVCODE Mask                */

#define DPM_STS_BUSY_Pos                 (0)                                               /*!< DPM_T::STS: BUSY Position              */
#define DPM_STS_BUSY_Msk                 (0x1ul << DPM_STS_BUSY_Pos)                       /*!< DPM_T::STS: BUSY Mask                  */

#define DPM_STS_INT_Pos                  (1)                                               /*!< DPM_T::STS: INT Position               */
#define DPM_STS_INT_Msk                  (0x1ul << DPM_STS_INT_Pos)                        /*!< DPM_T::STS: INT Mask                   */

#define DPM_STS_PWCERR_Pos               (4)                                               /*!< DPM_T::STS: PWCERR Position            */
#define DPM_STS_PWCERR_Msk               (0x1ul << DPM_STS_PWCERR_Pos)                     /*!< DPM_T::STS: PWCERR Mask                */

#define DPM_STS_PWUOK_Pos                (5)                                               /*!< DPM_T::STS: PWUOK Position             */
#define DPM_STS_PWUOK_Msk                (0x1ul << DPM_STS_PWUOK_Pos)                      /*!< DPM_T::STS: PWUOK Mask                 */

#define DPM_STS_PWFMAX_Pos               (6)                                               /*!< DPM_T::STS: PWFMAX Position            */
#define DPM_STS_PWFMAX_Msk               (0x1ul << DPM_STS_PWFMAX_Pos)                     /*!< DPM_T::STS: PWFMAX Mask                */

#define DPM_STS_PWUCNT_Pos               (8)                                               /*!< DPM_T::STS: PWUCNT Position            */
#define DPM_STS_PWUCNT_Msk               (0x7ul << DPM_STS_PWUCNT_Pos)                     /*!< DPM_T::STS: PWUCNT Mask                */

#define DPM_STS_DBGDIS_Pos               (16)                                              /*!< DPM_T::STS: DBGDIS Position            */
#define DPM_STS_DBGDIS_Msk               (0x1ul << DPM_STS_DBGDIS_Pos)                     /*!< DPM_T::STS: DBGDIS Mask                */

#define DPM_STS_LOCK_Pos                 (17)                                              /*!< DPM_T::STS: LOCK Position              */
#define DPM_STS_LOCK_Msk                 (0x1ul << DPM_STS_LOCK_Pos)                       /*!< DPM_T::STS: LOCK Mask                  */

#define DPM_STS_PWOK_Pos                 (18)                                              /*!< DPM_T::STS: PWOK Position              */
#define DPM_STS_PWOK_Msk                 (0x1ul << DPM_STS_PWOK_Pos)                       /*!< DPM_T::STS: PWOK Mask                  */

#define DPM_SPW0_PW_Pos                  (0)                                               /*!< DPM_T::SPW0: PW Position               */
#define DPM_SPW0_PW_Msk                  (0xfffffffful << DPM_SPW0_PW_Pos)                 /*!< DPM_T::SPW0: PW Mask                   */

#define DPM_SPW1_PW_Pos                  (0)                                               /*!< DPM_T::SPW1: PW Position               */
#define DPM_SPW1_PW_Msk                  (0xfffffffful << DPM_SPW1_PW_Pos)                 /*!< DPM_T::SPW1: PW Mask                   */

#define DPM_SPW2_PW_Pos                  (0)                                               /*!< DPM_T::SPW2: PW Position               */
#define DPM_SPW2_PW_Msk                  (0xfffffffful << DPM_SPW2_PW_Pos)                 /*!< DPM_T::SPW2: PW Mask                   */

#define DPM_SPW3_PW_Pos                  (0)                                               /*!< DPM_T::SPW3: PW Position               */
#define DPM_SPW3_PW_Msk                  (0xfffffffful << DPM_SPW3_PW_Pos)                 /*!< DPM_T::SPW3: PW Mask                   */

#define DPM_NSCTL_DBGDIS_Pos             (0)                                               /*!< DPM_T::NSCTL: DBGDIS Position          */
#define DPM_NSCTL_DBGDIS_Msk             (0x1ul << DPM_NSCTL_DBGDIS_Pos)                   /*!< DPM_T::NSCTL: DBGDIS Mask              */

#define DPM_NSCTL_LOCK_Pos               (1)                                               /*!< DPM_T::NSCTL: LOCK Position            */
#define DPM_NSCTL_LOCK_Msk               (0x1ul << DPM_NSCTL_LOCK_Pos)                     /*!< DPM_T::NSCTL: LOCK Mask                */

#define DPM_NSCTL_PWCMP_Pos              (2)                                               /*!< DPM_T::NSCTL: PWCMP Position           */
#define DPM_NSCTL_PWCMP_Msk              (0x1ul << DPM_NSCTL_PWCMP_Pos)                    /*!< DPM_T::NSCTL: PWCMP Mask               */

#define DPM_NSCTL_PWUPD_Pos              (3)                                               /*!< DPM_T::NSCTL: PWUPD Position           */
#define DPM_NSCTL_PWUPD_Msk              (0x1ul << DPM_NSCTL_PWUPD_Pos)                    /*!< DPM_T::NSCTL: PWUPD Mask               */

#define DPM_NSCTL_DACCWDIS_Pos           (12)                                              /*!< DPM_T::NSCTL: DACCWDIS Position        */
#define DPM_NSCTL_DACCWDIS_Msk           (0x1ul << DPM_NSCTL_DACCWDIS_Pos)                 /*!< DPM_T::NSCTL: DACCWDIS Mask            */

#define DPM_NSCTL_WVCODE_Pos             (24)                                              /*!< DPM_T::NSCTL: WVCODE Position          */
#define DPM_NSCTL_WVCODE_Msk             (0xfful << DPM_NSCTL_WVCODE_Pos)                  /*!< DPM_T::NSCTL: WVCODE Mask              */

#define DPM_NSCTL_RVCODE_Pos             (24)                                              /*!< DPM_T::NSCTL: RVCODE Position          */
#define DPM_NSCTL_RVCODE_Msk             (0xfful << DPM_NSCTL_RVCODE_Pos)                  /*!< DPM_T::NSCTL: RVCODE Mask              */

#define DPM_NSSTS_BUSY_Pos               (0)                                               /*!< DPM_T::NSSTS: BUSY Position            */
#define DPM_NSSTS_BUSY_Msk               (0x1ul << DPM_NSSTS_BUSY_Pos)                     /*!< DPM_T::NSSTS: BUSY Mask                */

#define DPM_NSSTS_PWCERR_Pos             (4)                                               /*!< DPM_T::NSSTS: PWCERR Position          */
#define DPM_NSSTS_PWCERR_Msk             (0x1ul << DPM_NSSTS_PWCERR_Pos)                   /*!< DPM_T::NSSTS: PWCERR Mask              */

#define DPM_NSSTS_PWUOK_Pos              (5)                                               /*!< DPM_T::NSSTS: PWUOK Position           */
#define DPM_NSSTS_PWUOK_Msk              (0x1ul << DPM_NSSTS_PWUOK_Pos)                    /*!< DPM_T::NSSTS: PWUOK Mask               */

#define DPM_NSSTS_PWFMAX_Pos             (6)                                               /*!< DPM_T::NSSTS: PWFMAX Position          */
#define DPM_NSSTS_PWFMAX_Msk             (0x1ul << DPM_NSSTS_PWFMAX_Pos)                   /*!< DPM_T::NSSTS: PWFMAX Mask              */

#define DPM_NSSTS_PWUCNT_Pos             (8)                                               /*!< DPM_T::NSSTS: PWUCNT Position          */
#define DPM_NSSTS_PWUCNT_Msk             (0x7ul << DPM_NSSTS_PWUCNT_Pos)                   /*!< DPM_T::NSSTS: PWUCNT Mask              */

#define DPM_NSSTS_DBGDIS_Pos             (16)                                              /*!< DPM_T::NSSTS: DBGDIS Position          */
#define DPM_NSSTS_DBGDIS_Msk             (0x1ul << DPM_NSSTS_DBGDIS_Pos)                   /*!< DPM_T::NSSTS: DBGDIS Mask              */

#define DPM_NSSTS_LOCK_Pos               (17)                                              /*!< DPM_T::NSSTS: LOCK Position            */
#define DPM_NSSTS_LOCK_Msk               (0x1ul << DPM_NSSTS_LOCK_Pos)                     /*!< DPM_T::NSSTS: LOCK Mask                */

#define DPM_NSSTS_PWOK_Pos               (18)                                              /*!< DPM_T::NSSTS: PWOK Position            */
#define DPM_NSSTS_PWOK_Msk               (0x1ul << DPM_NSSTS_PWOK_Pos)                     /*!< DPM_T::NSSTS: PWOK Mask                */

#define DPM_NSPW0_PW_Pos                 (0)                                               /*!< DPM_T::NSPW0: PW Position              */
#define DPM_NSPW0_PW_Msk                 (0xfffffffful << DPM_NSPW0_PW_Pos)                /*!< DPM_T::NSPW0: PW Mask                  */

#define DPM_NSPW1_PW_Pos                 (0)                                               /*!< DPM_T::NSPW1: PW Position              */
#define DPM_NSPW1_PW_Msk                 (0xfffffffful << DPM_NSPW1_PW_Pos)                /*!< DPM_T::NSPW1: PW Mask                  */

#define DPM_NSPW2_PW_Pos                 (0)                                               /*!< DPM_T::NSPW2: PW Position              */
#define DPM_NSPW2_PW_Msk                 (0xfffffffful << DPM_NSPW2_PW_Pos)                /*!< DPM_T::NSPW2: PW Mask                  */

#define DPM_NSPW3_PW_Pos                 (0)                                               /*!< DPM_T::NSPW3: PW Position              */
#define DPM_NSPW3_PW_Msk                 (0xfffffffful << DPM_NSPW3_PW_Pos)                /*!< DPM_T::NSPW3: PW Mask                  */


/**@}*/ /* DPM_CONST */
/**@}*/ /* end of DPM register group */



/*---------------------- Firmware Version Counter -------------------------*/
/**
    @addtogroup FVC Firmware Version Counter(FVC)
    Memory Mapped Structure for FVC Controller
@{ */

typedef struct
{


    /**
     * @var FVC_T::CTL
     * Offset: 0x00  FVC Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INIT      |FVC Init Bit
     * |        |          |Set to 1 to enable FVC
     * |        |          |This bit is writable when FVC is at Reset state.
     * |        |          |Note: After set to 1, this bit is cleared to 0 automatically when FVC is back to Reset state.
     * |[1]     |MONOEN    |Monotonic Enable Bit
     * |        |          |Set to 1 to enable the monotonic mechanism of FVC.
     * |        |          |Note: This bit can be set to1 but cannot be cleared to 0.
     * |[31:16] |WVCODE    |Verification Code
     * |        |          |When written, this field must be 0x7710
     * @var FVC_T::STS
     * Offset: 0x04  FVC Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |FVC Busy Bit
     * |        |          |Indicates the FVC is at busy state.
     * |[1]     |RDY       |FVC Ready Bit
     * |        |          |Indicates the FVC is ready after the initial process.
     * @var FVC_T::NVC0
     * Offset: 0x10  Non-volatile Version Counter Control Register0 BL2 Firmware
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FWVER     |Firmware Version
     * |        |          |Read: Indicates the current firmware version of FVC0.
     * |        |          |Write: Updates the firmware version of FVC0.
     * |        |          |The maximum value of this field is 63.
     * |        |          |Indicating number of 1 in Fuse OTP or number of 0 in Flash
     * |[31:16] |WVCODE    |Verification Code
     * |        |          |When written, this field must be the current firmware version number
     * @var FVC_T::NVC1
     * Offset: 0x14  Non-volatile Version Counter Control Register1 BL32 Firmware
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FWVER     |Firmware Version
     * |        |          |Read: Indicates the current firmware version of NVC1.
     * |        |          |Write: Updates the firmware version of NVC1.
     * |        |          |The maximum value of this field is 63.
     * |        |          |Indicating number of 1 in Fuse OTP or number of 0 in Flash
     * |[31:16] |WVCODE    |Verification Code
     * |        |          |When written, this field must be the current firmware version number
     * @var FVC_T::NVC4
     * Offset: 0x20  Non-volatile Version Counter Control Register4 BL33 Firmware
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FWVER     |Firmware Version
     * |        |          |Read: Indicates the current firmware version of NVC4.
     * |        |          |Write: Updates the firmware version of NVC4.
     * |        |          |The maximum value of this field is 255.
     * |        |          |Indicating number of 1 in Fuse OTP or number of 0 in Flash
     * |[31:16] |WVCODE    |Verification Code
     * |        |          |When written, this field must be the current firmware version number
     * @var FVC_T::NVC5
     * Offset: 0x24  Non-volatile Version Counter Control Register5 User-defined Firmware
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FWVER     |Firmware Version
     * |        |          |Read: Indicates the current firmware version of NVC5.
     * |        |          |Write: Updates the firmware version of NVC5.
     * |        |          |The maximum value of this field is 255.
     * |        |          |Indicating number of 1 in Fuse OTP or number of 0 in Flash
     * |[31:16] |WVCODE    |Verification Code
     * |        |          |When written, this field must be the current firmware version number
     */
    __IO uint32_t CTL;                   /*!< [0x0000] FVC Control Register                                           */
    __I  uint32_t STS;                   /*!< [0x0004] FVC Status Register                                            */
    __I  uint32_t RESERVE0[2];
    __IO uint32_t NVC[6];                /*!< [0x0010-0x24] Non-volatile Version Counter Control Register Firmware. NVC[2], NVC[3] is reserved    */
} FVC_T;

/**
    @addtogroup FVC_CONST FVC Bit Field Definition
    Constant Definitions for FVC Controller
@{ */

#define FVC_CTL_INIT_Pos                 (0)                                               /*!< FVC_T::CTL: INIT Position              */
#define FVC_CTL_INIT_Msk                 (0x1ul << FVC_CTL_INIT_Pos)                       /*!< FVC_T::CTL: INIT Mask                  */

#define FVC_CTL_MONOEN_Pos               (1)                                               /*!< FVC_T::CTL: MONOEN Position            */
#define FVC_CTL_MONOEN_Msk               (0x1ul << FVC_CTL_MONOEN_Pos)                     /*!< FVC_T::CTL: MONOEN Mask                */

#define FVC_CTL_WVCODE_Pos               (16)                                              /*!< FVC_T::CTL: WVCODE Position            */
#define FVC_CTL_WVCODE_Msk               (0xfffful << FVC_CTL_WVCODE_Pos)                  /*!< FVC_T::CTL: WVCODE Mask                */

#define FVC_STS_BUSY_Pos                 (0)                                               /*!< FVC_T::STS: BUSY Position              */
#define FVC_STS_BUSY_Msk                 (0x1ul << FVC_STS_BUSY_Pos)                       /*!< FVC_T::STS: BUSY Mask                  */

#define FVC_STS_RDY_Pos                  (1)                                               /*!< FVC_T::STS: RDY Position               */
#define FVC_STS_RDY_Msk                  (0x1ul << FVC_STS_RDY_Pos)                        /*!< FVC_T::STS: RDY Mask                   */

#define FVC_NVC_FWVER_Pos                (0)                                               /*!< FVC_T::NVC:  FWVER Position            */
#define FVC_NVC_FWVER_Msk                (0xfffful << FVC_NVC_FWVER_Pos)                   /*!< FVC_T::NVC:  FWVER Mask                */

/**@}*/ /* FVC_CONST */
/**@}*/ /* end of FVC register group */


/*---------------------- Product Life-cycle Manager -------------------------*/
/**
    @addtogroup PLM Product Life-cycle Manager(PLM)
    Memory Mapped Structure for PLM Controller
  @{
*/

typedef struct
{


    /**
     * @var PLM_T::CTL
     * Offset: 0x00  Product Life-cycle Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |STAGE     |Life-cycle Stage Update Bits
     * |        |          |Bits to update PLM stage. All bits can be set to one but cannot be cleared to zero.
     * |        |          |001 = progress to OEM stage.
     * |        |          |011 = progress to Deployed stage.
     * |        |          |111 = progress to RMA stage.
     * |        |          |Other value will be ignored.
     * |[31:16] |WVCODE    |Write Verify Code
     * |        |          |The code is 0x475A for a valid write to this register.
     * @var PLM_T::STS
     * Offset: 0x04  Product Life-cycle Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |STAGE     |Life-cycle Stage (Read Only)
     * |        |          |Indicates the current stage of PLM.
     * |        |          |000 = Vendor Stage.
     * |        |          |001 = OEM Stage.
     * |        |          |011 = Deployed Stage.
     * |        |          |111 = RMA Stage.
     * |        |          |Others = ERROR Stage.
     * |[8]     |DIRTY     |DIRTY Bit (Read Only)
     * |        |          |Indicate the life-cycle stage has been progressed after last cold-reset
     * |        |          |Value of STAGE bits is not Current stage of PLM
     * |        |          |It needs a cold reset to make it work.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] Product Life-cycle Control Register                              */
    __I  uint32_t STS;                   /*!< [0x0004] Product Life-cycle Status Register                               */

} PLM_T;

/**
    @addtogroup PLM_CONST PLM Bit Field Definition
    Constant Definitions for PLM Controller
  @{
*/

#define PLM_CTL_STAGE_Pos                (0)                                               /*!< PLM_T::CTL: STAGE Position             */
#define PLM_CTL_STAGE_Msk                (0x7ul << PLM_CTL_STAGE_Pos)                      /*!< PLM_T::CTL: STAGE Mask                 */

#define PLM_CTL_WVCODE_Pos               (16)                                              /*!< PLM_T::CTL: WVCODE Position            */
#define PLM_CTL_WVCODE_Msk               (0xfffful << PLM_CTL_WVCODE_Pos)                  /*!< PLM_T::CTL: WVCODE Mask                */

#define PLM_STS_STAGE_Pos                (0)                                               /*!< PLM_T::STS: STAGE Position             */
#define PLM_STS_STAGE_Msk                (0x7ul << PLM_STS_STAGE_Pos)                      /*!< PLM_T::STS: STAGE Mask                 */

#define PLM_STS_DIRTY_Pos                (8)                                               /*!< PLM_T::STS: DIRTY Position             */
#define PLM_STS_DIRTY_Msk                (0x1ul << PLM_STS_DIRTY_Pos)                      /*!< PLM_T::STS: DIRTY Mask                 */

/**@}*/ /* PLM_CONST */
/**@}*/ /* end of PLM register group */


/*---------------------- Secure configuration Unit -------------------------*/
/**
    @addtogroup SCU Secure configuration Unit(SCU)
    Memory Mapped Structure for SCU Controller
  @{
*/

typedef struct
{


    /**
     * @var SCU_T::PNSSET
     * Offset: 0x00  Peripheral Non-secure Attribution Set Register0 (0x4000_0000~0x4001_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9]     |USBH      |Set USBH to Non-secure State
     * |        |          |Write 1 to set USBH to non-secure state. Write 0 has no effect.
     * |        |          |0 = USBH is a secure module (default).
     * |        |          |1 = USBH is a non-secure module.
     * |[13]    |SDH0      |Set SDH0 to Non-secure State
     * |        |          |Write 1 to set SDH0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SDH0 is a secure module (default).
     * |        |          |1 = SDH0 is a non-secure module.
     * |[16]    |EBI       |Set EBI to Non-secure State
     * |        |          |Write 1 to set EBI to non-secure state. Write 0 has no effect.
     * |        |          |0 = EBI is a secure module (default).
     * |        |          |1 = EBI is a non-secure module.
     * |[24]    |PDMA1     |Set PDMA1 to Non-secure State
     * |        |          |Write 1 to set PDMA1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = PDMA1 is a secure module (default).
     * |        |          |1 = PDMA1 is a non-secure module.
     * Offset: 0x04  Peripheral Non-secure Attribution Set Register1 (0x4002_0000~0x4003_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17]    |CRC       |Set CRC to Non-secure State
     * |        |          |Write 1 to set CRC to non-secure state. Write 0 has no effect.
     * |        |          |0 = CRC is a secure module (default).
     * |        |          |1 = CRC is a non-secure module.
     * |[18]    |CRPT      |Set CRPT to Non-secure State
     * |        |          |0 = CRPT is a secure module (default).
     * |        |          |1 = CRPT is a non-secure module.
     * Offset: 0x08  Peripheral Non-secure Attribution Set Register2 (0x4004_0000~0x4005_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |EWDT      |Set EWDT to Non-secure State
     * |        |          |Write 1 to set EWDT to non-secure state. Write 0 has no effect.
     * |        |          |0 = EWDT is a secure module (default).
     * |        |          |1 = EWDT is a non-secure module.
     * |[3]     |EADC      |Set EADC to Non-secure State
     * |        |          |Write 1 to set EADC to non-secure state. Write 0 has no effect.
     * |        |          |0 = EADC is a secure module (default).
     * |        |          |1 = EADC is a non-secure module.
     * |[5]     |ACMP01    |Set ACMP01 to Non-secure State
     * |        |          |Write 1 to set ACMP0, ACMP1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = ACMP0, ACMP1 are secure modules (default).
     * |        |          |1 = ACMP0, ACMP1 are non-secure modules.
     * |[7]     |DAC       |Set DAC to Non-secure State
     * |        |          |Write 1 to set DAC to non-secure state. Write 0 has no effect.
     * |        |          |0 = DAC is a secure module (default).
     * |        |          |1 = DAC is a non-secure module.
     * |[8]     |I2S0      |Set I2S0 to Non-secure State
     * |        |          |Write 1 to set I2S0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = I2S0 is a secure module (default).
     * |        |          |1 = I2S0 is a non-secure module.
     * |[13]    |OTG       |Set OTG to Non-secure State
     * |        |          |Write 1 to set OTG to non-secure state. Write 0 has no effect.
     * |        |          |0 = OTG is a secure module (default).
     * |        |          |1 = OTG is a non-secure module.
     * |[17]    |TMR23     |Set TMR23 to Non-secure State
     * |        |          |Write 1 to set TMR23 to non-secure state. Write 0 has no effect.
     * |        |          |0 = TMR23 is a secure module (default).
     * |        |          |1 = TMR23 is a non-secure module.
     * |[24]    |EPWM0     |Set EPWM0 to Non-secure State
     * |        |          |Write 1 to set EPWM0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = EPWM0 is a secure module (default).
     * |        |          |1 = EPWM0 is a non-secure module.
     * |[25]    |EPWM1     |Set EPWM1 to Non-secure State
     * |        |          |Write 1 to set EPWM1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = EPWM1 is a secure module (default).
     * |        |          |1 = EPWM1 is a non-secure module.
     * |[26]    |BPWM0     |Set BPWM0 to Non-secure State
     * |        |          |Write 1 to set BPWM0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = BPWM0 is a secure module (default).
     * |        |          |1 = BPWM0 is a non-secure module.
     * |[27]    |BPWM1     |Set BPWM1 to Non-secure State
     * |        |          |Write 1 to set BPWM1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = BPWM1 is a secure module (default).
     * |        |          |1 = BPWM1 is a non-secure module.
     * Offset: 0x0C  Peripheral Non-secure Attribution Set Register3 (0x4006_0000~0x4007_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |QSPI0     |Set QSPI0 to Non-secure State
     * |        |          |Write 1 to set QSPI0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = QSPI0 is a secure module (default).
     * |        |          |1 = QSPI0 is a non-secure module.
     * |[1]     |SPI0      |Set SPI0 to Non-secure State
     * |        |          |Write 1 to set SPI0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SPI0 is a secure module (default).
     * |        |          |1 = SPI0 is a non-secure module.
     * |[2]     |SPI1      |Set SPI1 to Non-secure State
     * |        |          |Write 1 to set SPI1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SPI1 is a secure module (default).
     * |        |          |1 = SPI1 is a non-secure module.
     * |[3]     |SPI2      |Set SPI2 to Non-secure State
     * |        |          |Write 1 to set SPI2 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SPI2 is a secure module (default).
     * |        |          |1 = SPI2 is a non-secure module.
     * |[4]     |SPI3      |Set SPI3 to Non-secure State
     * |        |          |Write 1 to set SPI3 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SPI3 is a secure module (default).
     * |        |          |1 = SPI3 is a non-secure module.
     * |[16]    |UART0     |Set UART0 to Non-secure State
     * |        |          |Write 1 to set UART0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = UART0 is a secure module (default).
     * |        |          |1 = UART0 is a non-secure module.
     * |[17]    |UART1     |Set UART1 to Non-secure State
     * |        |          |Write 1 to set UART1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = UART1 is a secure module (default).
     * |        |          |1 = UART1 is a non-secure module.
     * |[18]    |UART2     |Set UART2 to Non-secure State
     * |        |          |Write 1 to set UART2 to non-secure state. Write 0 has no effect.
     * |        |          |0 = UART2 is a secure module (default).
     * |        |          |1 = UART2 is a non-secure module.
     * |[19]    |UART3     |Set UART3 to Non-secure State
     * |        |          |Write 1 to set UART3 to non-secure state. Write 0 has no effect.
     * |        |          |0 = UART3 is a secure module (default).
     * |        |          |1 = UART3 is a non-secure module.
     * |[20]    |UART4     |Set UART4 to Non-secure State
     * |        |          |Write 1 to set UART4 to non-secure state. Write 0 has no effect.
     * |        |          |0 = UART4 is a secure module (default).
     * |        |          |1 = UART4 is a non-secure module.
     * |[21]    |UART5     |Set UART5 to Non-secure State
     * |        |          |Write 1 to set UART5 to non-secure state. Write 0 has no effect.
     * |        |          |0 = UART5 is a secure module (default).
     * |        |          |1 = UART5 is a non-secure module.
     * Offset: 0x10  Peripheral Non-secure Attribution Set Register4 (0x4008_0000~0x4009_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |I2C0      |Set I2C0 to Non-secure State
     * |        |          |Write 1 to set I2C0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = I2C0 is a secure module (default).
     * |        |          |1 = I2C0 is a non-secure module.
     * |[1]     |I2C1      |Set I2C1 to Non-secure State
     * |        |          |Write 1 to set I2C1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = I2C1 is a secure module (default).
     * |        |          |1 = I2C1 is a non-secure module.
     * |[2]     |I2C2      |Set I2C2 to Non-secure State
     * |        |          |Write 1 to set I2C2 to non-secure state. Write 0 has no effect.
     * |        |          |0 = I2C2 is a secure module (default).
     * |        |          |1 = I2C2 is a non-secure module.
     * |[16]    |SC0       |Set SC0 to Non-secure State
     * |        |          |Write 1 to set SC0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SC0 is a secure module (default).
     * |        |          |1 = SC0 is a non-secure module.
     * |[17]    |SC1       |Set SC1 to Non-secure State
     * |        |          |Write 1 to set SC1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SC1 is a secure module (default).
     * |        |          |1 = SC1 is a non-secure module.
     * |[18]    |SC2       |Set SC2 to Non-secure State
     * |        |          |Write 1 to set SC2 to non-secure state. Write 0 has no effect.
     * |        |          |0 = SC2 is a secure module (default).
     * |        |          |1 = SC2 is a non-secure module.
     * Offset: 0x14  Peripheral Non-secure Attribution Set Register5 (0x400A_0000~0x400B_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CAN0      |Set CAN0 to Non-secure State
     * |        |          |Write 1 to set CAN0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = CAN0 is a secure module (default).
     * |        |          |1 = CAN0 is a non-secure module.
     * |[16]    |QEI0      |Set QEI0 to Non-secure State
     * |        |          |Write 1 to set QEI0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = QEI0 is a secure module (default).
     * |        |          |1 = QEI0 is a non-secure module.
     * |[17]    |QEI1      |Set QEI1 to Non-secure State
     * |        |          |Write 1 to set QEI1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = QEI1 is a secure module (default).
     * |        |          |1 = QEI1 is a non-secure module.
     * |[20]    |ECAP0     |Set ECAP0 to Non-secure State
     * |        |          |Write 1 to set ECAP0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = ECAP0 is a secure module (default).
     * |        |          |1 = ECAP0 is a non-secure module.
     * |[21]    |ECAP1     |Set ECAP1 to Non-secure State
     * |        |          |Write 1 to set ECAP1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = ECAP1 is a secure module (default).
     * |        |          |1 = ECAP1 is a non-secure module.
     * |[25]    |TRNG      |Set TRNG to Non-secure State
     * |        |          |Write 1 to set TRNG to non-secure state. Write 0 has no effect.
     * |        |          |0 = TRNG is a secure module (default).
     * |        |          |1 = TRNG is a non-secure module.
     * |[27]    |LCD       |Set LCD to Non-secure State
     * |        |          |Write 1 to set LCD to non-secure state. Write 0 has no effect.
     * |        |          |0 = LCD is a secure module (default).
     * |        |          |1 = LCD is a non-secure module.
     * Offset: 0x18  Peripheral Non-secure Attribution Set Register6 (0x400C_0000~0x400D_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |USBD      |Set USBD to Non-secure State
     * |        |          |Write 1 to set USBD to non-secure state. Write 0 has no effect.
     * |        |          |0 = USBD is a secure module (default).
     * |        |          |1 = USBD is a non-secure module.
     * |[16]    |USCI0     |Set USCI0 to Non-secure State
     * |        |          |Write 1 to set USCI0 to non-secure state. Write 0 has no effect.
     * |        |          |0 = USCI0 is a secure module (default).
     * |        |          |1 = USCI0 is a non-secure module.
     * |[17]    |USCI1     |Set USCI1 to Non-secure State
     * |        |          |Write 1 to set USCI1 to non-secure state. Write 0 has no effect.
     * |        |          |0 = USCI1 is a secure module (default).
     * |        |          |1 = USCI1 is a non-secure module.
     * @var SCU_T::IONSSET
     * Offset: 0x20  IO Non-secure Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PA        |Set GPIO Port a to Non-scecure State
     * |        |          |Write 1 to set PA to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port A is secure (default).
     * |        |          |1 = GPIO port A is non-secure.
     * |[1]     |PB        |Set GPIO Port B to Non-scecure State
     * |        |          |Write 1 to set PB to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port B is secure (default).
     * |        |          |1 = GPIO port B is non-secure.
     * |[2]     |PC        |Set GPIO Port C to Non-scecure State
     * |        |          |Write 1 to set PC to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port C is secure (default).
     * |        |          |1 = GPIO port C is non-secure.
     * |[3]     |PD        |Set GPIO Port D to Non-scecure State
     * |        |          |Write 1 to set PD to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port D is secure (default).
     * |        |          |1 = GPIO port D is non-secure.
     * |[4]     |PE        |Set GPIO Port E to Non-scecure State
     * |        |          |Write 1 to set PE to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port E is secure (default).
     * |        |          |1 = GPIO port E is non-secure.
     * |[5]     |PF        |Set GPIO Port F to Non-scecure State
     * |        |          |Write 1 to set PF to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port F is secure (default).
     * |        |          |1 = GPIO port F is non-secure.
     * |[6]     |PG        |Set GPIO Port G to Non-scecure State
     * |        |          |Write 1 to set PG to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port G is secure (default).
     * |        |          |1 = GPIO port G is non-secure.
     * |[7]     |PH        |Set GPIO Port H to Non-scecure State
     * |        |          |Write 1 to set PH to non-secure state. Write 0 has no effect.
     * |        |          |0 = GPIO port H is secure (default).
     * |        |          |1 = GPIO port H is non-secure.
     * @var SCU_T::SRAMNSSET
     * Offset: 0x24  SRAM Non-secure Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |SECn      |Set SRAM Section n to Non-scecure State
     * |        |          |Write 1 to set SRAM section n to non-secure state. Write 0 is ignored.
     * |        |          |0 = SRAM Section n is secure (default).
     * |        |          |1 = SRAM Section n is non-secure.
     * |        |          |Size per section is 16 Kbytes.
     * |        |          |Secure SRAM section n is 0x2000_0000+0x4000*n to 0x2000_0000+0x4000*(n+1)-0x1
     * |        |          |Non-secure SRAM section n is 0x3000_0000+0x4000*n to 0x3000_0000+0x4000*(n+1)-0x1
     * @var SCU_T::FNSADDR
     * Offset: 0x28  Flash Non-secure Boundary Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FNSADDR   |Flash Non-secure Boundary Address
     * |        |          |Indicate the base address of Non-secure region set in user configuration
     * |        |          |Refer to FMC section for more details.
     * @var SCU_T::SVIOIEN
     * Offset: 0x2C  Security Violation Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |APB0IEN   |APB0 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of APB0 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of APB0 Enabled.
     * |[1]     |APB1IEN   |APB1 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of APB1 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of APB1 Enabled.
     * |[4]     |GPIOIEN   |GPIO Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of GPIO Disabled.
     * |        |          |1 = Interrupt triggered from security violation of GPIO Enabled.
     * |[5]     |EBIIEN    |EBI Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of EBI Disabled.
     * |        |          |1 = Interrupt triggered from security violation of EBI Enabled.
     * |[6]     |USBHIEN   |USBH Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of USB host Disabled.
     * |        |          |1 = Interrupt triggered from security violation of USB host Enabled.
     * |[7]     |CRCIEN    |CRC Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of CRC Disabled.
     * |        |          |1 = Interrupt triggered from security violation of CRC Enabled.
     * |[8]     |SDH0IEN   |SDH0 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of SD host 0 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of SD host 0 Enabled.
     * |[10]    |PDMA0IEN  |PDMA0 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of PDMA0 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of PDMA0 Enabled.
     * |[11]    |PDMA1IEN  |PDMA1 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of PDMA1 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of PDMA1 Enabled.
     * |[12]    |SRAM0IEN  |SRAM Bank 0 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of SRAM bank0 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of SRAM bank0 Enabled.
     * |[13]    |SRAM1IEN  |SRAM Bank 1 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of SRAM bank1 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of SRAM bank1 Enabled.
     * |[14]    |FMCIEN    |FMC Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of FMC Disabled.
     * |        |          |1 = Interrupt triggered from security violation of FMC Enabled.
     * |[15]    |FLASHIEN  |FLASH Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of Flash data Disabled.
     * |        |          |1 = Interrupt triggered from security violation of Flash data Enabled.
     * |[16]    |SCUIEN    |SCU Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of SCU Disabled.
     * |        |          |1 = Interrupt triggered from security violation of SCU Enabled.
     * |[17]    |SYSIEN    |SYS Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of system manager Disabled.
     * |        |          |1 = Interrupt triggered from security violation of system manager Enabled.
     * |[18]    |CRPTIEN   |CRPT Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of crypto Disabled.
     * |        |          |1 = Interrupt triggered from security violation of crypto Enabled.
     * |[19]    |KSIEN     |KS Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of keystore Disabled.
     * |        |          |1 = Interrupt triggered from security violation of keystore Enabled.
     * @var SCU_T::SVINTSTS
     * Offset: 0x30  Security Violation Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |APB0IF    |APB0 Security Violation Interrupt Status
     * |        |          |0 = No APB0 violation interrupt event.
     * |        |          |1 = There is APB0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[1]     |APB1IF    |APB1 Security Violation Interrupt Status
     * |        |          |0 = No APB1 violation interrupt event.
     * |        |          |1 = There is APB1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[4]     |GPIOIF    |GPIO Security Violation Interrupt Status
     * |        |          |0 = No GPIO violation interrupt event.
     * |        |          |1 = There is GPIO violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[5]     |EBIIF     |EBI Security Violation Interrupt Status
     * |        |          |0 = No EBI violation interrupt event.
     * |        |          |1 = There is EBI violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[6]     |USBHIF    |USBH Security Violation Interrupt Status
     * |        |          |0 = No USBH violation interrupt event.
     * |        |          |1 = There is USBH violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[7]     |CRCIF     |CRC Security Violation Interrupt Status
     * |        |          |0 = No CRC violation interrupt event.
     * |        |          |1 = There is CRC violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[8]     |SDH0IF    |SDH0 Security Violation Interrupt Status
     * |        |          |0 = No SDH0 violation interrupt event.
     * |        |          |1 = There is SDH0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[10]    |PDMA0IF   |PDMA0 Security Violation Interrupt Status
     * |        |          |0 = No PDMA0 violation interrupt event.
     * |        |          |1 = There is PDMA0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[11]    |PDMA1IF   |PDMA1 Security Violation Interrupt Status
     * |        |          |0 = No PDMA1 violation interrupt event.
     * |        |          |1 = There is PDMA1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[12]    |SRAM0IF   |SRAM0 Security Violation Interrupt Status
     * |        |          |0 = No SRAM0 violation interrupt event.
     * |        |          |1 = There is SRAM0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[13]    |SRAM1IF   |SRAM Bank 1 Security Violation Interrupt Status
     * |        |          |0 = No SRAM1 violation interrupt event.
     * |        |          |1 = There is SRAM1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[14]    |FMCIF     |FMC Security Violation Interrupt Status
     * |        |          |0 = No FMC violation interrupt event.
     * |        |          |1 = There is FMC violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[15]    |FLASHIF   |FLASH Security Violation Interrupt Status
     * |        |          |0 = No FLASH violation interrupt event.
     * |        |          |1 = There is FLASH violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[16]    |SCUIF     |SCU Security Violation Interrupt Status
     * |        |          |0 = No SCU violation interrupt event.
     * |        |          |1 = There is SCU violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[17]    |SYSIF     |SYS Security Violation Interrupt Status
     * |        |          |0 = No SYS violation interrupt event.
     * |        |          |1 = There is SYS violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[18]    |CRPTIF    |CRPT Security Violation Interrupt Status
     * |        |          |0 = No CRPT violation interrupt event.
     * |        |          |1 = There is CRPT violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[19]    |KSIF      |KS Security Violation Interrupt Status
     * |        |          |0 = No KS violation interrupt event.
     * |        |          |1 = There is KS violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * @var SCU_T::APB0VSRC
     * Offset: 0x34  APB0 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::APB0VA
     * Offset: 0x38  APB0 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::APB1VSRC
     * Offset: 0x3C  APB1 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::APB1VA
     * Offset: 0x40  APB1 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::GPIOVSRC
     * Offset: 0x44  GPIO Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::GPIOVA
     * Offset: 0x48  GPIO Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::EBIVSRC
     * Offset: 0x4C  EBI Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::EBIVA
     * Offset: 0x50  EBI Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::USBHVSRC
     * Offset: 0x54  USBH Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::USBHVA
     * Offset: 0x58  USBH Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::CRCVSRC
     * Offset: 0x5C  CRC Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::CRCVA
     * Offset: 0x60  CRC Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::SD0VSRC
     * Offset: 0x64  SDH0 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::SD0VA
     * Offset: 0x68  SDH0 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::PDMA0VSRC
     * Offset: 0x74  PDMA0 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::PDMA0VA
     * Offset: 0x78  PDMA0 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::PDMA1VSRC
     * Offset: 0x7C  PDMA1 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::PDMA1VA
     * Offset: 0x80  PDMA1 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::SRAM0VSRC
     * Offset: 0x84  SRAM0 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::SRAM0VA
     * Offset: 0x88  SRAM0 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::SRAM1VSRC
     * Offset: 0x8C  SRAM1 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::SRAM1VA
     * Offset: 0x90  SRAM1 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::FMCVSRC
     * Offset: 0x94  FMC Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::FMCVA
     * Offset: 0x98  FMC Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::FLASHVSRC
     * Offset: 0x9C  Flash Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::FLASHVA
     * Offset: 0xA0  Flash Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::SCUVSRC
     * Offset: 0xA4  SCU Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::SCUVA
     * Offset: 0xA8  SCU Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::SYSVSRC
     * Offset: 0xAC  System(GMISC) Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::SYSVA
     * Offset: 0xB0  System(GMISC) Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::CRPTVSRC
     * Offset: 0xB4  Crypto Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::CRPTVA
     * Offset: 0xB8  Crypto Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::KSVSRC
     * Offset: 0xBC  KS Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::KSVA
     * Offset: 0xC0  KS Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::SRAM2VSRC
     * Offset: 0xC4  SRAM2 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = core processor.
     * |        |          |0x3 = PDMA0.
     * |        |          |0x4 = SDH0.
     * |        |          |0x5 = CRYPTO.
     * |        |          |0x6 = USH.
     * |        |          |0xB = PDMA1.
     * |        |          |Others is undefined.
     * @var SCU_T::SRAM2VA
     * Offset: 0xC8  SRAM2 Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SCU_T::SINFAEN
     * Offset: 0xF0  Shared Information Access Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SCUSIAEN  |SCU Shared Information Access Enable Bit
     * |        |          |0 = Non-secure CPU access SCU Shared information Disabled.
     * |        |          |1 = Non-secure CPU access SCU Shared information Enabled.
     * |[1]     |SYSSIAEN  |SYS Shared Information Access Enable Bit
     * |        |          |0 = Non-secure CPU access SYS Shared information Disabled.
     * |        |          |1 = Non-secure CPU access SYS Shared information Enabled.
     * |        |          |Note:Include clock information.
     * |[2]     |FMCSIAEN  |FMC Shared Information Access Enable Bit
     * |        |          |0 = Non-secure CPU access FMC Shared information Disabled.
     * |        |          |1 = Non-secure CPU access FMC Shared information Enabled.
     * @var SCU_T::PNPSET
     * Offset: 0x100  Peripheral Non-privileged Attribution Set Register0 (0x4000_0000~0x4001_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SYS       |Set SYS to Non-privileged State
     * |        |          |0 = SYS is a privileged module (default).
     * |        |          |1 = SYS is a non-privileged module.
     * |[8]     |PDMA0     |Set PDMA0 to Non-privileged State
     * |        |          |0 = PDMA0 is a privileged module (default).
     * |        |          |1 = PDMA0 is a non-privileged module.
     * |[9]     |USBH      |Set USBH to Non-privileged State
     * |        |          |0 = USBH is a privileged module (default).
     * |        |          |1 = USBH is a non-privileged module.
     * |[12]    |FMC       |Set FMC to Non-privileged State
     * |        |          |0 = FMC is a privileged module (default).
     * |        |          |1 = FMC is a non-privileged module.
     * |[13]    |SDH0      |Set SDH0 to Non-privileged State
     * |        |          |0 = SDH0 is a privileged module (default).
     * |        |          |1 = SDH0 is a non-privileged module.
     * |[16]    |EBI       |Set EBI to Non-privileged State
     * |        |          |0 = EBI is a privileged module (default).
     * |        |          |1 = EBI is a non-privileged module.
     * |[24]    |PDMA1     |Set PDMA1 to Non-privileged State
     * |        |          |0 = PDMA1 is a privileged module (default).
     * |        |          |1 = PDMA1 is a non-privileged module.
     * Offset: 0x104  Peripheral Non-privileged Attribution Set Register1 (0x4002_0000~0x4003_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15]    |SCU       |Set SCU to Non-privileged State
     * |        |          |0 = SCU is a privileged module (default).
     * |        |          |1 = SCU is a non-privileged module.
     * |[17]    |CRC       |Set CRC to Non-privileged State
     * |        |          |0 = CRC is a privileged module (default).
     * |        |          |1 = CRC is a non-privileged module.
     * |[18]    |CRPT      |Set CRPT to Non-privileged State
     * |        |          |0 = CRPT is a privileged module (default).
     * |        |          |1 = CRPT is a non-privileged module.
     * |[21]    |KS        |Set KS to Non-privileged State
     * |        |          |0 = KS is a privileged module (default).
     * |        |          |1 = KS is a non-privileged module.
     * Offset: 0x108  Peripheral Non-privileged Attribution Set Register2 (0x4004_0000~0x4005_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDT       |Set WDT to Non-privileged State
     * |        |          |0 = WDT is a privileged module (default).
     * |        |          |1 = WDT is a non-privileged module.
     * |[1]     |RTC       |Set RTC to Non-privileged State
     * |        |          |0 = RTC is a privileged module (default).
     * |        |          |1 = RTC is a non-privileged module.
     * |[2]     |EWDT      |Set EWDT to Non-privileged State
     * |        |          |0 = EWDT is a privileged module (default).
     * |        |          |1 = EWDT is a non-privileged module.
     * |[3]     |EADC      |Set EADC to Non-privileged State
     * |        |          |0 = EADC is a privileged module (default).
     * |        |          |1 = EADC is a non-privileged module.
     * |[5]     |ACMP01    |Set ACMP01 to Non-privileged State
     * |        |          |0 = ACMP0, ACMP1 are privileged modules (default).
     * |        |          |1 = ACMP0, ACMP1 are non-privileged modules.
     * |[7]     |DAC       |Set DAC to Non-privileged State
     * |        |          |0 = DAC is a privileged module (default).
     * |        |          |1 = DAC is a non-privileged module.
     * |[8]     |I2S0      |Set I2S0 to Non-privileged State
     * |        |          |0 = I2S0 is a privileged module (default).
     * |        |          |1 = I2S0 is a non-privileged module.
     * |[13]    |OTG       |Set OTG to Non-privileged State
     * |        |          |0 = OTG is a privileged module (default).
     * |        |          |1 = OTG is a non-privileged module.
     * |[16:14] |TMR01     |Set TMR01 to Non-privileged State
     * |        |          |0 = TMR01 is a privileged module (default).
     * |        |          |1 = TMR01 is a non-privileged module.
     * |[17]    |TMR23     |Set TMR23 to Non-privileged State
     * |        |          |0 = TMR23 is a privileged module (default).
     * |        |          |1 = TMR23 is a non-privileged module.
     * |[24]    |EPWM0     |Set EPWM0 to Non-privileged State
     * |        |          |0 = EPWM0 is a privileged module (default).
     * |        |          |1 = EPWM0 is a non-privileged module.
     * |[25]    |EPWM1     |Set EPWM1 to Non-privileged State
     * |        |          |0 = EPWM1 is a privileged module (default).
     * |        |          |1 = EPWM1 is a non-privileged module.
     * |[26]    |BPWM0     |Set BPWM0 to Non-privileged State
     * |        |          |0 = BPWM0 is a privileged module (default).
     * |        |          |1 = BPWM0 is a non-privileged module.
     * |[27]    |BPWM1     |Set BPWM1 to Non-privileged State
     * |        |          |0 = BPWM1 is a privileged module (default).
     * |        |          |1 = BPWM1 is a non-privileged module.
     * Offset: 0x10C  Peripheral Non-privileged Attribution Set Register3 (0x4006_0000~0x4007_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |QSPI0     |Set QSPI0 to Non-privileged State
     * |        |          |0 = QSPI0 is a privileged module (default).
     * |        |          |1 = QSPI0 is a non-privileged module.
     * |[1]     |SPI0      |Set SPI0 to Non-privileged State
     * |        |          |0 = SPI0 is a privileged module (default).
     * |        |          |1 = SPI0 is a non-privileged module.
     * |[2]     |SPI1      |Set SPI1 to Non-privileged State
     * |        |          |0 = SPI1 is a privileged module (default).
     * |        |          |1 = SPI1 is a non-privileged module.
     * |[3]     |SPI2      |Set SPI2 to Non-privileged State
     * |        |          |0 = SPI2 is a privileged module (default).
     * |        |          |1 = SPI2 is a non-privileged module.
     * |[4]     |SPI3      |Set SPI3 to Non-privileged State
     * |        |          |0 = SPI3 is a privileged module (default).
     * |        |          |1 = SPI3 is a non-privileged module.
     * |[16]    |UART0     |Set UART0 to Non-privileged State
     * |        |          |0 = UART0 is a privileged module (default).
     * |        |          |1 = UART0 is a non-privileged module.
     * |[17]    |UART1     |Set UART1 to Non-privileged State
     * |        |          |0 = UART1 is a privileged module (default).
     * |        |          |1 = UART1 is a non-privileged module.
     * |[18]    |UART2     |Set UART2 to Non-privileged State
     * |        |          |0 = UART2 is a privileged module (default).
     * |        |          |1 = UART2 is a non-privileged module.
     * |[19]    |UART3     |Set UART3 to Non-privileged State
     * |        |          |0 = UART3 is a privileged module (default).
     * |        |          |1 = UART3 is a non-privileged module.
     * |[20]    |UART4     |Set UART4 to Non-privileged State
     * |        |          |0 = UART4 is a privileged module (default).
     * |        |          |1 = UART4 is a non-privileged module.
     * |[21]    |UART5     |Set UART5 to Non-privileged State
     * |        |          |0 = UART5 is a privileged module (default).
     * |        |          |1 = UART5 is a non-privileged module.
     * Offset: 0x110  Peripheral Non-privileged Attribution Set Register4 (0x4008_0000~0x4009_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |I2C0      |Set I2C0 to Non-privileged State
     * |        |          |0 = I2C0 is a privileged module (default).
     * |        |          |1 = I2C0 is a non-privileged module.
     * |[1]     |I2C1      |Set I2C1 to Non-privileged State
     * |        |          |0 = I2C1 is a privileged module (default).
     * |        |          |1 = I2C1 is a non-privileged module.
     * |[2]     |I2C2      |Set I2C2 to Non-privileged State
     * |        |          |0 = I2C2 is a privileged module (default).
     * |        |          |1 = I2C2 is a non-privileged module.
     * |[16]    |SC0       |Set SC0 to Non-privileged State
     * |        |          |0 = SC0 is a privileged module (default).
     * |        |          |1 = SC0 is a non-privileged module.
     * |[17]    |SC1       |Set SC1 to Non-privileged State
     * |        |          |0 = SC1 is a privileged module (default).
     * |        |          |1 = SC1 is a non-privileged module.
     * |[18]    |SC2       |Set SC2 to Non-privileged State
     * |        |          |0 = SC2 is a privileged module (default).
     * |        |          |1 = SC2 is a non-privileged module.
     * Offset: 0x114  Peripheral Non-privileged Attribution Set Register5 (0x400A_0000~0x400B_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CAN0      |Set CAN0 to Non-privileged State
     * |        |          |0 = CAN0 is a privileged module (default).
     * |        |          |1 = CAN0 is a non-privileged module.
     * |[16]    |QEI0      |Set QEI0 to Non-privileged State
     * |        |          |0 = QEI0 is a privileged module (default).
     * |        |          |1 = QEI0 is a non-privileged module.
     * |[17]    |QEI1      |Set QEI1 to Non-privileged State
     * |        |          |0 = QEI1 is a privileged module (default).
     * |        |          |1 = QEI1 is a non-privileged module.
     * |[20]    |ECAP0     |Set ECAP0 to Non-privileged State
     * |        |          |0 = ECAP0 is a privileged module (default).
     * |        |          |1 = ECAP0 is a non-privileged module.
     * |[21]    |ECAP1     |Set ECAP1 to Non-privileged State
     * |        |          |0 = ECAP1 is a privileged module (default).
     * |        |          |1 = ECAP1 is a non-privileged module.
     * |[25]    |TRNG      |Set TRNG to Non-privileged State
     * |        |          |0 = TRNG is a privileged module (default).
     * |        |          |1 = TRNG is a non-privileged module.
     * |[27]    |LCD       |Set LCD to Non-privileged State
     * |        |          |0 = LCD is a privileged module (default).
     * |        |          |1 = LCD is a non-privileged module.
     * |[29]    |TAMPER    |Set TAMPER to Non-privileged State
     * |        |          |0 = TAMPER is a privileged module (default).
     * |        |          |1 = TAMPER is a non-privileged module.
     * Offset: 0x118  Peripheral Non-privileged Attribution Set Register6 (0x400C_0000~0x400D_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |USBD      |Set USBD to Non-privileged State
     * |        |          |0 = USBD is a privileged module (default).
     * |        |          |1 = USBD is a non-privileged module.
     * |[16]    |USCI0     |Set USCI0 to Non-privileged State
     * |        |          |0 = USCI0 is a privileged module (default).
     * |        |          |1 = USCI0 is a non-privileged module.
     * |[17]    |USCI1     |Set USCI1 to Non-privileged State
     * |        |          |0 = USCI1 is a privileged module (default).
     * |        |          |1 = USCI1 is a non-privileged module.
     * @var SCU_T::IONPSET
     * Offset: 0x120  IO Non-privileged Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PA        |Set GPIO Port a to Non-privileged State
     * |        |          |0 = GPIO port A is privileged (default).
     * |        |          |1 = GPIO port A is non-privileged.
     * |[1]     |PB        |Set GPIO Port B to Non-privileged State
     * |        |          |0 = GPIO port B is privileged (default).
     * |        |          |1 = GPIO port B is non-privileged.
     * |[2]     |PC        |Set GPIO Port C to Non-privileged State
     * |        |          |0 = GPIO port C is privileged (default).
     * |        |          |1 = GPIO port C is non-privileged.
     * |[3]     |PD        |Set GPIO Port D to Non-privileged State
     * |        |          |0 = GPIO port D is privileged (default).
     * |        |          |1 = GPIO port D is non-privileged.
     * |[4]     |PE        |Set GPIO Port E to Nonj-privileged State
     * |        |          |0 = GPIO port E is privileged (default).
     * |        |          |1 = GPIO port E is non-privileged.
     * |[5]     |PF        |Set GPIO Port F to Non-privileged State
     * |        |          |0 = GPIO port F is privileged (default).
     * |        |          |1 = GPIO port F is non-privileged.
     * |[6]     |PG        |Set GPIO Port G to Non-privileged State
     * |        |          |0 = GPIO port G is privileged (default).
     * |        |          |1 = GPIO port G is non-privileged.
     * |[7]     |PH        |Set GPIO Port H to Non-privileged State
     * |        |          |0 = GPIO port H is privileged (default).
     * |        |          |1 = GPIO port H is non-privileged.
     * @var SCU_T::SRAMNPSET
     * Offset: 0x124  SRAM Non-privileged Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[19:0]  |SECn      |Set SRAM Section n to Non-privileged State
     * |        |          |0 = SRAM Section n is privileged (default).
     * |        |          |1 = SRAM Section n is non-privileged.
     * |        |          |Size per section is 16 Kbytes.
     * |        |          |Secure SRAM section n is 0x2000_0000+0x4000*n to 0x2000_0000+0x4000*(n+1)-0x1
     * |        |          |Non-secure SRAM section n is 0x3000_0000+0x4000*n to 0x3000_0000+0x4000*(n+1)-0x1
     * @var SCU_T::MEMNPSET
     * Offset: 0x128  Other Memory Non-privileged Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FLASH     |Set Flash to Non-privileged State
     * |        |          |Set the privileged state of memory ranging from 0x0000_0000 to 0x1FFF_FFFF.
     * |        |          |0 = Flash is setting to privileged (default).
     * |        |          |1 = Flash is setting to non-privileged.
     * |[1]     |EXTMEM    |Set External Memory (EBI Memory) to Non-privileged State
     * |        |          |Set the privileged state of memory ranging from 0x6000_0000 to 0x7FFF_FFFF.
     * |        |          |0 = External Memory is setting to privileged (default).
     * |        |          |1 = External Memory is setting to non-privileged.
     * @var SCU_T::PVIOIEN
     * Offset: 0x12C  Privileged Violation Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |APB0IEN   |APB0 Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of APB0 Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of APB0 Enabled.
     * |[1]     |APB1IEN   |APB1 Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of APB1 Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of APB1 Enabled.
     * |[4]     |GPIOIEN   |GPIO Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of GPIO Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of GPIO Enabled.
     * |[5]     |EBIIEN    |EBI Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of EBI Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of EBI Enabled.
     * |[6]     |USBHIEN   |USBH Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of USB host Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of USB host Enabled.
     * |[7]     |CRCIEN    |CRC Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of CRC Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of CRC Enabled.
     * |[8]     |SDH0IEN   |SDH0 Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of SD host 0 Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of SD host 0 Enabled.
     * |[10]    |PDMA0IEN  |PDMA0 Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of PDMA0 Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of PDMA0 Enabled.
     * |[11]    |PDMA1IEN  |PDMA1 Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of PDMA1 Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of PDMA1 Enabled.
     * |[12]    |SRAM0IEN  |SRAM Bank 0 Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of SRAM bank0 Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of SRAM bank0 Enabled.
     * |[13]    |SRAM1IEN  |SRAM Bank 1 Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of SRAM bank1 Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of SRAM bank1 Enabled.
     * |[14]    |FMCIEN    |FMC Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of FMC Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of FMC Enabled.
     * |[15]    |FLASHIEN  |FLASH Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of Flash data Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of Flash data Enabled.
     * |[16]    |SCUIEN    |SCU Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of SCU Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of SCU Enabled.
     * |[17]    |SYSIEN    |SYS Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of system manager Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of system manager Enabled.
     * |[18]    |CRPTIEN   |CRPT Privileged Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from privileged violation of crypto Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of crypto Enabled.
     * |[19]    |KSIEN     |KS Privileged Violation Interrupt Enale Bit
     * |        |          |0 = Interrupt triggered from privileged violation of keystore Disabled.
     * |        |          |1 = Interrupt triggered from privileged violation of keystore Enabled.
     * @var SCU_T::PVINTSTS
     * Offset: 0x130  Privileged Violation Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |APB0IF    |APB0 Privileged Violation Interrupt Status
     * |        |          |0 = No APB0 violation interrupt event.
     * |        |          |1 = There is APB0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[1]     |APB1IF    |APB1 Privileged Violation Interrupt Status
     * |        |          |0 = No APB1 violation interrupt event.
     * |        |          |1 = There is APB1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[4]     |GPIOIF    |GPIO Privileged Violation Interrupt Status
     * |        |          |0 = No GPIO violation interrupt event.
     * |        |          |1 = There is GPIO violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[5]     |EBIIF     |EBI Privileged Violation Interrupt Status
     * |        |          |0 = No EBI violation interrupt event.
     * |        |          |1 = There is EBI violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[6]     |USBHIF    |USBH Privileged Violation Interrupt Status
     * |        |          |0 = No USBH violation interrupt event.
     * |        |          |1 = There is USBH violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[7]     |CRCIF     |CRC Privileged Violation Interrupt Status
     * |        |          |0 = No CRC violation interrupt event.
     * |        |          |1 = There is CRC violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[8]     |SDH0IF    |SDH0 Privileged Violation Interrupt Status
     * |        |          |0 = No SDH0 violation interrupt event.
     * |        |          |1 = There is SDH0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[10]    |PDMA0IF   |PDMA0 Privileged Violation Interrupt Status
     * |        |          |0 = No PDMA0 violation interrupt event.
     * |        |          |1 = There is PDMA0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[11]    |PDMA1IF   |PDMA1 Privileged Violation Interrupt Status
     * |        |          |0 = No PDMA1 violation interrupt event.
     * |        |          |1 = There is PDMA1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[12]    |SRAM0IF   |SRAM0 Privileged Violation Interrupt Status
     * |        |          |0 = No SRAM0 violation interrupt event.
     * |        |          |1 = There is SRAM0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[13]    |SRAM1IF   |SRAM Bank 1 Privileged Violation Interrupt Status
     * |        |          |0 = No SRAM1 violation interrupt event.
     * |        |          |1 = There is SRAM1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[14]    |FMCIF     |FMC Privileged Violation Interrupt Status
     * |        |          |0 = No FMC violation interrupt event.
     * |        |          |1 = There is FMC violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[15]    |FLASHIF   |FLASH Privileged Violation Interrupt Status
     * |        |          |0 = No FLASH violation interrupt event.
     * |        |          |1 = There is FLASH violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[16]    |SCUIF     |SCU Privileged Violation Interrupt Status
     * |        |          |0 = No SCU violation interrupt event.
     * |        |          |1 = There is SCU violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[17]    |SYSIF     |SYS Privileged Violation Interrupt Status
     * |        |          |0 = No SYS violation interrupt event.
     * |        |          |1 = There is SYS violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[18]    |CRPTIF    |CRPT Privileged Violation Interrupt Status
     * |        |          |0 = No CRPT violation interrupt event.
     * |        |          |1 = There is CRPT violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[19]    |KSIF      |KS Privileged Violation Interrupt Status
     * |        |          |0 = No KS violation interrupt event.
     * |        |          |1 = There is KS violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * @var SCU_T::NSMCTL
     * Offset: 0x200  Non-secure State Monitor Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PRESCALE  |Pre-scale Value of Non-secure State Monitor Counter
     * |        |          |0 = Counter Disabled.
     * |        |          |Others = Counter Enabled and the counter clock source = HCLK/PRESCALE.
     * |[8]     |NSMIEN    |Non-secure State Monitor Interrupt Enable Bit
     * |        |          |0 = Non-secure state monitor interrupt Disabled.
     * |        |          |1 = Non-secure state monitor interrupt Enabled.
     * |[9]     |AUTORLD   |Auto Reload Non-secure State Monitor Counter When CURRNS Changing to 1
     * |        |          |0 = Disable clearing non-secure state monitor counter automtically (default).
     * |        |          |1 = Enable clearing non-secure state monitor counter automatically when the core processor changes from secure state to non-secure state
     * |        |          |(i.e.when CURRNS chagned from 0 to 1).
     * |[10]    |TMRMOD    |Non-secure Monitor Mode Enable Bit
     * |        |          |0 = Monitor mode. The counter will count down when the core processor is in non-secure state. (default)
     * |        |          |1 = Free-counting mode
     * |        |          |The counter will keep counting no mater the core processor is in secure or non-secure state.
     * |[12]    |IDLEON    |Monitor Counter Keep Counting When the Chip Is in Idle Mode Enable Bit
     * |        |          |0 = The counter will be halted when the chip is in idle mode.
     * |        |          |1 = The counter will keep counting when the chip is in idle mode. (default)
     * |        |          |Note: In monitor mode, the counter is always halted when the core processor is in secure state.
     * |[13]    |DBGON     |Monitor Counter Keep Counting When the Chip Is in Debug Mode Enable Bit
     * |        |          |0 = The counter will be halted when the core processor is halted by ICE. (default)
     * |        |          |1 = The counter will keep counting when the core processor is halted by ICE.
     * @var SCU_T::NSMLOAD
     * Offset: 0x204  Non-secure State Monitor Reload Value Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |RELOAD    |Reload Value for Non-secure State Monitor Counter
     * |        |          |The RELOAD value will be reloaded to the counter whenever the counter counts down to 0.
     * @var SCU_T::NSMVAL
     * Offset: 0x208  Non-secure State Monitor Counter Value Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |VALUE     |Counter Value of Non-secure State Monitor Counter
     * |        |          |Current value of non-secure state monitor counter
     * |        |          |This is down counter and counts down only when CURRNS = 1
     * |        |          |When counting down to 0, VALUE will automatically be reloaded from NSMLOAD register.
     * |        |          |A write of any value clears the VALUE to 0 and also clears NSMIF.
     * @var SCU_T::NSMSTS
     * Offset: 0x20C  Non-secure State Monitor Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CURRNS    |Current Core Processor Secure/Non-secure State (Read Only)
     * |        |          |0 = Core processor is in secure state.
     * |        |          |1 = Core processor is in non-secure state.
     * |        |          |Note: This bit can be used to monitor the current secure/non-secure state of the core processor, even if the non-secure state monitor counter is disabled.
     * |[1]     |NSMIF     |Non-secure State Monitor Interrupt Flag
     * |        |          |0 = Counter doesnu2019t count down to 0 since the last NSMIF has been cleared.
     * |        |          |1 = Counter counts down to 0.
     * |        |          |Note: This bit is cleared by writing 1.
     * @var SCU_T::BBE
     * Offset: 0x300  Block Bus Error Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BBEEN     |Block Bus-error Enable Bit
     * |        |          |0 = Disable Blocking Bus Error to the core processor.
     * |        |          |1 = Enable Blocking Bus Error to the core processor.
     * |        |          |This bit is double write-protected, WRVERY and SYS_REGLCTL register.
     * |[31:8]  |WVERY     |Write Verify Code
     * |        |          |In order to write BBEEN bit, the code should be set as 0x59475A.
     * |        |          |When read access, the return value of this field is always 0.
     * @var SCU_T::IDAUANS
     * Offset: 0x304  IDAU All Non-secure Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |IDAUANSEN |IDAU All Non-secure Enable Bit
     * |        |          |0 = Disable IDAU sets all region Non-secure.
     * |        |          |1 = Enable IDAU sets all region Non-secure.
     * |        |          |This bit is double write-protected, WRVERY and SYS_REGLCTL register.
     * |[31:8]  |WVERY     |Write Verify Code
     * |        |          |In order to write BBEEN bit, the code should be set as 0x59475A.
     * |        |          |When read access, the return value of this field is always 0.
     * @var SCU_T::VERSION
     * Offset: 0xFFC  SCU RTL Design Version Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MINOR     |SCU RTL Design Minor Version
     * |        |          |Minor version number is dependent on ECO version control.
     * |[23:16] |SUB       |SCU RTL Design Sub Version Number
     * |        |          |Major version number is correlated to product line.
     * |[31:24] |MAJOR     |SCU RTL Design Major Version Number
     * |        |          |Major version number is correlated to product line.
     */
    __IO uint32_t PNSSET[7];             /*!< [0x0000:0x0018] Peripheral Non-secure Attribution Set Register0 (0x4000_0000~0x400D_FFFF) */
    __I  uint32_t RESERVE0[2];
    __IO uint32_t SRAMNSSET;             /*!< [0x0024] SRAM Non-secure Attribution Set Register                         */
    __I  uint32_t FNSADDR;               /*!< [0x0028] Flash Non-secure Boundary Address Register                       */
    __IO uint32_t SVIOIEN;               /*!< [0x002c] Security Violation Interrupt Enable Register                     */
    __IO uint32_t SVINTSTS;              /*!< [0x0030] Security Violation Interrupt Status Register                     */
    __I  uint32_t APB0VSRC;              /*!< [0x0034] APB0 Security Policy Violation Source                            */
    __I  uint32_t APB0VA;                /*!< [0x0038] APB0 Violation Address                                           */
    __I  uint32_t APB1VSRC;              /*!< [0x003c] APB1 Security Policy Violation Source                            */
    __I  uint32_t APB1VA;                /*!< [0x0040] APB1 Violation Address                                           */
    __I  uint32_t GPIOVSRC;              /*!< [0x0044] GPIO Security Policy Violation Source                            */
    __I  uint32_t GPIOVA;                /*!< [0x0048] GPIO Violation Address                                           */
    __I  uint32_t EBIVSRC;               /*!< [0x004c] EBI Security Policy Violation Source                             */
    __I  uint32_t EBIVA;                 /*!< [0x0050] EBI Violation Address                                            */
    __I  uint32_t USBHVSRC;              /*!< [0x0054] USBH Security Policy Violation Source                            */
    __I  uint32_t USBHVA;                /*!< [0x0058] USBH Violation Address                                           */
    __I  uint32_t CRCVSRC;               /*!< [0x005c] CRC Security Policy Violation Source                             */
    __I  uint32_t CRCVA;                 /*!< [0x0060] CRC Violation Address                                            */
    __I  uint32_t SD0VSRC;               /*!< [0x0064] SDH0 Security Policy Violation Source                            */
    __I  uint32_t SD0VA;                 /*!< [0x0068] SDH0 Violation Address                                           */
    __I  uint32_t RESERVE1[2];
    __I  uint32_t PDMA0VSRC;             /*!< [0x0074] PDMA0 Security Policy Violation Source                           */
    __I  uint32_t PDMA0VA;               /*!< [0x0078] PDMA0 Violation Address                                          */
    __I  uint32_t PDMA1VSRC;             /*!< [0x007c] PDMA1 Security Policy Violation Source                           */
    __I  uint32_t PDMA1VA;               /*!< [0x0080] PDMA1 Violation Address                                          */
    __I  uint32_t SRAM0VSRC;             /*!< [0x0084] SRAM0 Security Policy Violation Source                           */
    __I  uint32_t SRAM0VA;               /*!< [0x0088] SRAM0 Violation Address                                          */
    __I  uint32_t SRAM1VSRC;             /*!< [0x008c] SRAM1 Security Policy Violation Source                           */
    __I  uint32_t SRAM1VA;               /*!< [0x0090] SRAM1 Violation Address                                          */
    __I  uint32_t FMCVSRC;               /*!< [0x0094] FMC Security Policy Violation Source                             */
    __I  uint32_t FMCVA;                 /*!< [0x0098] FMC Violation Address                                            */
    __I  uint32_t FLASHVSRC;             /*!< [0x009c] Flash Security Policy Violation Source                           */
    __I  uint32_t FLASHVA;               /*!< [0x00a0] Flash Violation Address                                          */
    __I  uint32_t SCUVSRC;               /*!< [0x00a4] SCU Security Policy Violation Source                             */
    __I  uint32_t SCUVA;                 /*!< [0x00a8] SCU Violation Address                                            */
    __I  uint32_t SYSVSRC;               /*!< [0x00ac] System(GMISC) Security Policy Violation Source                   */
    __I  uint32_t SYSVA;                 /*!< [0x00b0] System(GMISC) Violation Address                                  */
    __I  uint32_t CRPTVSRC;              /*!< [0x00b4] Crypto Security Policy Violation Source                          */
    __I  uint32_t CRPTVA;                /*!< [0x00b8] Crypto Violation Address                                         */
    __I  uint32_t KSVSRC;                /*!< [0x00bc] KS Security Policy Violation Source                              */
    __I  uint32_t KSVA;                  /*!< [0x00c0] KS Violation Address                                             */
    __I  uint32_t SRAM2VSRC;             /*!< [0x00c4] SRAM2 Security Policy Violation Source                           */
    __I  uint32_t SRAM2VA;               /*!< [0x00c8] SRAM2 Violation Address                                          */
    __I  uint32_t RESERVE2[9];
    __IO uint32_t SINFAEN;               /*!< [0x00f0] Shared Information Access Enable Register                        */
    __I  uint32_t RESERVE3[3];
    __IO uint32_t PNPSET[7];             /*!< [0x0100:0x0118] Peripheral Non-privileged Attribution Set Register0 (0x4000_0000~0x400D_FFFF) */
    __I  uint32_t RESERVE4[1];
    __IO uint32_t IONPSET;               /*!< [0x0120] IO Non-privileged Attribution Set Register                       */
    __IO uint32_t SRAMNPSET;             /*!< [0x0124] SRAM Non-privileged Attribution Set Register                     */
    __IO uint32_t MEMNPSET;              /*!< [0x0128] Other Memory Non-privileged Attribution Set Register             */
    __IO uint32_t PVIOIEN;               /*!< [0x012c] Privileged Violation Interrupt Enable Register                   */
    __IO uint32_t PVINTSTS;              /*!< [0x0130] Privileged Violation Interrupt Status Register                   */
    __I  uint32_t RESERVE5[3];
    __IO uint32_t IONSSET[8];            /*!< [0x0140:0x015C] IO Non-secure Attribution Set Register                    */
    __I  uint32_t RESERVE6[40];
    __IO uint32_t NSMCTL;                /*!< [0x0200] Non-secure State Monitor Control Register                        */
    __IO uint32_t NSMLOAD;               /*!< [0x0204] Non-secure State Monitor Reload Value Register                   */
    __IO uint32_t NSMVAL;                /*!< [0x0208] Non-secure State Monitor Counter Value Register                  */
    __IO uint32_t NSMSTS;                /*!< [0x020c] Non-secure State Monitor Status Register                         */
    __I  uint32_t RESERVE7[60];
    __IO uint32_t BBE;                   /*!< [0x0300] Block Bus Error Register                                         */
    __IO uint32_t IDAUANS;               /*!< [0x0304] IDAU All Non-secure Set Register                                 */
    __I  uint32_t RESERVE8[829];
    __I  uint32_t VERSION;               /*!< [0x0ffc] SCU RTL Design Version Register                                  */

} SCU_T;

/**
    @addtogroup SCU_CONST SCU Bit Field Definition
    Constant Definitions for SCU Controller
  @{
*/

#define SCU_PNSSET0_USBH_Pos             (9)                                               /*!< SCU_T::PNSSET0: USBH Position          */
#define SCU_PNSSET0_USBH_Msk             (0x1ul << SCU_PNSSET0_USBH_Pos)                   /*!< SCU_T::PNSSET0: USBH Mask              */

#define SCU_PNSSET0_SDH0_Pos             (13)                                              /*!< SCU_T::PNSSET0: SDH0 Position          */
#define SCU_PNSSET0_SDH0_Msk             (0x1ul << SCU_PNSSET0_SDH0_Pos)                   /*!< SCU_T::PNSSET0: SDH0 Mask              */

#define SCU_PNSSET0_EBI_Pos              (16)                                              /*!< SCU_T::PNSSET0: EBI Position           */
#define SCU_PNSSET0_EBI_Msk              (0x1ul << SCU_PNSSET0_EBI_Pos)                    /*!< SCU_T::PNSSET0: EBI Mask               */

#define SCU_PNSSET0_PDMA1_Pos            (24)                                              /*!< SCU_T::PNSSET0: PDMA1 Position         */
#define SCU_PNSSET0_PDMA1_Msk            (0x1ul << SCU_PNSSET0_PDMA1_Pos)                  /*!< SCU_T::PNSSET0: PDMA1 Mask             */

#define SCU_PNSSET1_CRC_Pos              (17)                                              /*!< SCU_T::PNSSET1: CRC Position           */
#define SCU_PNSSET1_CRC_Msk              (0x1ul << SCU_PNSSET1_CRC_Pos)                    /*!< SCU_T::PNSSET1: CRC Mask               */

#define SCU_PNSSET1_CRPT_Pos             (18)                                              /*!< SCU_T::PNSSET1: CRPT Position          */
#define SCU_PNSSET1_CRPT_Msk             (0x1ul << SCU_PNSSET1_CRPT_Pos)                   /*!< SCU_T::PNSSET1: CRPT Mask              */

#define SCU_PNSSET2_EWDT_Pos             (2)                                               /*!< SCU_T::PNSSET2: EWDT Position          */
#define SCU_PNSSET2_EWDT_Msk             (0x1ul << SCU_PNSSET2_EWDT_Pos)                   /*!< SCU_T::PNSSET2: EWDT Mask              */

#define SCU_PNSSET2_EADC_Pos             (3)                                               /*!< SCU_T::PNSSET2: EADC Position          */
#define SCU_PNSSET2_EADC_Msk             (0x1ul << SCU_PNSSET2_EADC_Pos)                   /*!< SCU_T::PNSSET2: EADC Mask              */

#define SCU_PNSSET2_ACMP01_Pos           (5)                                               /*!< SCU_T::PNSSET2: ACMP01 Position        */
#define SCU_PNSSET2_ACMP01_Msk           (0x1ul << SCU_PNSSET2_ACMP01_Pos)                 /*!< SCU_T::PNSSET2: ACMP01 Mask            */

#define SCU_PNSSET2_DAC_Pos              (7)                                               /*!< SCU_T::PNSSET2: DAC Position           */
#define SCU_PNSSET2_DAC_Msk              (0x1ul << SCU_PNSSET2_DAC_Pos)                    /*!< SCU_T::PNSSET2: DAC Mask               */

#define SCU_PNSSET2_I2S0_Pos             (8)                                               /*!< SCU_T::PNSSET2: I2S0 Position          */
#define SCU_PNSSET2_I2S0_Msk             (0x1ul << SCU_PNSSET2_I2S0_Pos)                   /*!< SCU_T::PNSSET2: I2S0 Mask              */

#define SCU_PNSSET2_OTG_Pos              (13)                                              /*!< SCU_T::PNSSET2: OTG Position           */
#define SCU_PNSSET2_OTG_Msk              (0x1ul << SCU_PNSSET2_OTG_Pos)                    /*!< SCU_T::PNSSET2: OTG Mask               */

#define SCU_PNSSET2_TMR23_Pos            (17)                                              /*!< SCU_T::PNSSET2: TMR23 Position         */
#define SCU_PNSSET2_TMR23_Msk            (0x1ul << SCU_PNSSET2_TMR23_Pos)                  /*!< SCU_T::PNSSET2: TMR23 Mask             */

#define SCU_PNSSET2_EPWM0_Pos            (24)                                              /*!< SCU_T::PNSSET2: EPWM0 Position         */
#define SCU_PNSSET2_EPWM0_Msk            (0x1ul << SCU_PNSSET2_EPWM0_Pos)                  /*!< SCU_T::PNSSET2: EPWM0 Mask             */

#define SCU_PNSSET2_EPWM1_Pos            (25)                                              /*!< SCU_T::PNSSET2: EPWM1 Position         */
#define SCU_PNSSET2_EPWM1_Msk            (0x1ul << SCU_PNSSET2_EPWM1_Pos)                  /*!< SCU_T::PNSSET2: EPWM1 Mask             */

#define SCU_PNSSET2_BPWM0_Pos            (26)                                              /*!< SCU_T::PNSSET2: BPWM0 Position         */
#define SCU_PNSSET2_BPWM0_Msk            (0x1ul << SCU_PNSSET2_BPWM0_Pos)                  /*!< SCU_T::PNSSET2: BPWM0 Mask             */

#define SCU_PNSSET2_BPWM1_Pos            (27)                                              /*!< SCU_T::PNSSET2: BPWM1 Position         */
#define SCU_PNSSET2_BPWM1_Msk            (0x1ul << SCU_PNSSET2_BPWM1_Pos)                  /*!< SCU_T::PNSSET2: BPWM1 Mask             */

#define SCU_PNSSET3_QSPI0_Pos            (0)                                               /*!< SCU_T::PNSSET3: QSPI0 Position         */
#define SCU_PNSSET3_QSPI0_Msk            (0x1ul << SCU_PNSSET3_QSPI0_Pos)                  /*!< SCU_T::PNSSET3: QSPI0 Mask             */

#define SCU_PNSSET3_SPI0_Pos             (1)                                               /*!< SCU_T::PNSSET3: SPI0 Position          */
#define SCU_PNSSET3_SPI0_Msk             (0x1ul << SCU_PNSSET3_SPI0_Pos)                   /*!< SCU_T::PNSSET3: SPI0 Mask              */

#define SCU_PNSSET3_SPI1_Pos             (2)                                               /*!< SCU_T::PNSSET3: SPI1 Position          */
#define SCU_PNSSET3_SPI1_Msk             (0x1ul << SCU_PNSSET3_SPI1_Pos)                   /*!< SCU_T::PNSSET3: SPI1 Mask              */

#define SCU_PNSSET3_SPI2_Pos             (3)                                               /*!< SCU_T::PNSSET3: SPI2 Position          */
#define SCU_PNSSET3_SPI2_Msk             (0x1ul << SCU_PNSSET3_SPI2_Pos)                   /*!< SCU_T::PNSSET3: SPI2 Mask              */

#define SCU_PNSSET3_SPI3_Pos             (4)                                               /*!< SCU_T::PNSSET3: SPI3 Position          */
#define SCU_PNSSET3_SPI3_Msk             (0x1ul << SCU_PNSSET3_SPI3_Pos)                   /*!< SCU_T::PNSSET3: SPI3 Mask              */

#define SCU_PNSSET3_UART0_Pos            (16)                                              /*!< SCU_T::PNSSET3: UART0 Position         */
#define SCU_PNSSET3_UART0_Msk            (0x1ul << SCU_PNSSET3_UART0_Pos)                  /*!< SCU_T::PNSSET3: UART0 Mask             */

#define SCU_PNSSET3_UART1_Pos            (17)                                              /*!< SCU_T::PNSSET3: UART1 Position         */
#define SCU_PNSSET3_UART1_Msk            (0x1ul << SCU_PNSSET3_UART1_Pos)                  /*!< SCU_T::PNSSET3: UART1 Mask             */

#define SCU_PNSSET3_UART2_Pos            (18)                                              /*!< SCU_T::PNSSET3: UART2 Position         */
#define SCU_PNSSET3_UART2_Msk            (0x1ul << SCU_PNSSET3_UART2_Pos)                  /*!< SCU_T::PNSSET3: UART2 Mask             */

#define SCU_PNSSET3_UART3_Pos            (19)                                              /*!< SCU_T::PNSSET3: UART3 Position         */
#define SCU_PNSSET3_UART3_Msk            (0x1ul << SCU_PNSSET3_UART3_Pos)                  /*!< SCU_T::PNSSET3: UART3 Mask             */

#define SCU_PNSSET3_UART4_Pos            (20)                                              /*!< SCU_T::PNSSET3: UART4 Position         */
#define SCU_PNSSET3_UART4_Msk            (0x1ul << SCU_PNSSET3_UART4_Pos)                  /*!< SCU_T::PNSSET3: UART4 Mask             */

#define SCU_PNSSET3_UART5_Pos            (21)                                              /*!< SCU_T::PNSSET3: UART5 Position         */
#define SCU_PNSSET3_UART5_Msk            (0x1ul << SCU_PNSSET3_UART5_Pos)                  /*!< SCU_T::PNSSET3: UART5 Mask             */

#define SCU_PNSSET4_I2C0_Pos             (0)                                               /*!< SCU_T::PNSSET4: I2C0 Position          */
#define SCU_PNSSET4_I2C0_Msk             (0x1ul << SCU_PNSSET4_I2C0_Pos)                   /*!< SCU_T::PNSSET4: I2C0 Mask              */

#define SCU_PNSSET4_I2C1_Pos             (1)                                               /*!< SCU_T::PNSSET4: I2C1 Position          */
#define SCU_PNSSET4_I2C1_Msk             (0x1ul << SCU_PNSSET4_I2C1_Pos)                   /*!< SCU_T::PNSSET4: I2C1 Mask              */

#define SCU_PNSSET4_I2C2_Pos             (2)                                               /*!< SCU_T::PNSSET4: I2C2 Position          */
#define SCU_PNSSET4_I2C2_Msk             (0x1ul << SCU_PNSSET4_I2C2_Pos)                   /*!< SCU_T::PNSSET4: I2C2 Mask              */

#define SCU_PNSSET4_SC0_Pos              (16)                                              /*!< SCU_T::PNSSET4: SC0 Position           */
#define SCU_PNSSET4_SC0_Msk              (0x1ul << SCU_PNSSET4_SC0_Pos)                    /*!< SCU_T::PNSSET4: SC0 Mask               */

#define SCU_PNSSET4_SC1_Pos              (17)                                              /*!< SCU_T::PNSSET4: SC1 Position           */
#define SCU_PNSSET4_SC1_Msk              (0x1ul << SCU_PNSSET4_SC1_Pos)                    /*!< SCU_T::PNSSET4: SC1 Mask               */

#define SCU_PNSSET4_SC2_Pos              (18)                                              /*!< SCU_T::PNSSET4: SC2 Position           */
#define SCU_PNSSET4_SC2_Msk              (0x1ul << SCU_PNSSET4_SC2_Pos)                    /*!< SCU_T::PNSSET4: SC2 Mask               */

#define SCU_PNSSET5_CAN0_Pos             (0)                                               /*!< SCU_T::PNSSET5: CAN0 Position          */
#define SCU_PNSSET5_CAN0_Msk             (0x1ul << SCU_PNSSET5_CAN0_Pos)                   /*!< SCU_T::PNSSET5: CAN0 Mask              */

#define SCU_PNSSET5_QEI0_Pos             (16)                                              /*!< SCU_T::PNSSET5: QEI0 Position          */
#define SCU_PNSSET5_QEI0_Msk             (0x1ul << SCU_PNSSET5_QEI0_Pos)                   /*!< SCU_T::PNSSET5: QEI0 Mask              */

#define SCU_PNSSET5_QEI1_Pos             (17)                                              /*!< SCU_T::PNSSET5: QEI1 Position          */
#define SCU_PNSSET5_QEI1_Msk             (0x1ul << SCU_PNSSET5_QEI1_Pos)                   /*!< SCU_T::PNSSET5: QEI1 Mask              */

#define SCU_PNSSET5_ECAP0_Pos            (20)                                              /*!< SCU_T::PNSSET5: ECAP0 Position         */
#define SCU_PNSSET5_ECAP0_Msk            (0x1ul << SCU_PNSSET5_ECAP0_Pos)                  /*!< SCU_T::PNSSET5: ECAP0 Mask             */

#define SCU_PNSSET5_ECAP1_Pos            (21)                                              /*!< SCU_T::PNSSET5: ECAP1 Position         */
#define SCU_PNSSET5_ECAP1_Msk            (0x1ul << SCU_PNSSET5_ECAP1_Pos)                  /*!< SCU_T::PNSSET5: ECAP1 Mask             */

#define SCU_PNSSET5_TRNG_Pos             (25)                                              /*!< SCU_T::PNSSET5: TRNG Position          */
#define SCU_PNSSET5_TRNG_Msk             (0x1ul << SCU_PNSSET5_TRNG_Pos)                   /*!< SCU_T::PNSSET5: TRNG Mask              */

#define SCU_PNSSET5_LCD_Pos              (27)                                              /*!< SCU_T::PNSSET5: LCD Position           */
#define SCU_PNSSET5_LCD_Msk              (0x1ul << SCU_PNSSET5_LCD_Pos)                    /*!< SCU_T::PNSSET5: LCD Mask               */

#define SCU_PNSSET6_USBD_Pos             (0)                                               /*!< SCU_T::PNSSET6: USBD Position          */
#define SCU_PNSSET6_USBD_Msk             (0x1ul << SCU_PNSSET6_USBD_Pos)                   /*!< SCU_T::PNSSET6: USBD Mask              */

#define SCU_PNSSET6_USCI0_Pos            (16)                                              /*!< SCU_T::PNSSET6: USCI0 Position         */
#define SCU_PNSSET6_USCI0_Msk            (0x1ul << SCU_PNSSET6_USCI0_Pos)                  /*!< SCU_T::PNSSET6: USCI0 Mask             */

#define SCU_PNSSET6_USCI1_Pos            (17)                                              /*!< SCU_T::PNSSET6: USCI1 Position         */
#define SCU_PNSSET6_USCI1_Msk            (0x1ul << SCU_PNSSET6_USCI1_Pos)                  /*!< SCU_T::PNSSET6: USCI1 Mask             */

#define SCU_IONSSET_PA_Pos               (0)                                               /*!< SCU_T::IONSSET: PA Position            */
#define SCU_IONSSET_PA_Msk               (0x1ul << SCU_IONSSET_PA_Pos)                     /*!< SCU_T::IONSSET: PA Mask                */

#define SCU_IONSSET_PB_Pos               (1)                                               /*!< SCU_T::IONSSET: PB Position            */
#define SCU_IONSSET_PB_Msk               (0x1ul << SCU_IONSSET_PB_Pos)                     /*!< SCU_T::IONSSET: PB Mask                */

#define SCU_IONSSET_PC_Pos               (2)                                               /*!< SCU_T::IONSSET: PC Position            */
#define SCU_IONSSET_PC_Msk               (0x1ul << SCU_IONSSET_PC_Pos)                     /*!< SCU_T::IONSSET: PC Mask                */

#define SCU_IONSSET_PD_Pos               (3)                                               /*!< SCU_T::IONSSET: PD Position            */
#define SCU_IONSSET_PD_Msk               (0x1ul << SCU_IONSSET_PD_Pos)                     /*!< SCU_T::IONSSET: PD Mask                */

#define SCU_IONSSET_PE_Pos               (4)                                               /*!< SCU_T::IONSSET: PE Position            */
#define SCU_IONSSET_PE_Msk               (0x1ul << SCU_IONSSET_PE_Pos)                     /*!< SCU_T::IONSSET: PE Mask                */

#define SCU_IONSSET_PF_Pos               (5)                                               /*!< SCU_T::IONSSET: PF Position            */
#define SCU_IONSSET_PF_Msk               (0x1ul << SCU_IONSSET_PF_Pos)                     /*!< SCU_T::IONSSET: PF Mask                */

#define SCU_IONSSET_PG_Pos               (6)                                               /*!< SCU_T::IONSSET: PG Position            */
#define SCU_IONSSET_PG_Msk               (0x1ul << SCU_IONSSET_PG_Pos)                     /*!< SCU_T::IONSSET: PG Mask                */

#define SCU_IONSSET_PH_Pos               (7)                                               /*!< SCU_T::IONSSET: PH Position            */
#define SCU_IONSSET_PH_Msk               (0x1ul << SCU_IONSSET_PH_Pos)                     /*!< SCU_T::IONSSET: PH Mask                */

#define SCU_SRAMNSSET_SECn_Pos           (0)                                               /*!< SCU_T::SRAMNSSET: SECn Position        */
#define SCU_SRAMNSSET_SECn_Msk           (0xffful << SCU_SRAMNSSET_SECn_Pos)               /*!< SCU_T::SRAMNSSET: SECn Mask            */

#define SCU_FNSADDR_FNSADDR_Pos          (0)                                               /*!< SCU_T::FNSADDR: FNSADDR Position       */
#define SCU_FNSADDR_FNSADDR_Msk          (0xfffffffful << SCU_FNSADDR_FNSADDR_Pos)         /*!< SCU_T::FNSADDR: FNSADDR Mask           */

#define SCU_SVIOIEN_APB0IEN_Pos          (0)                                               /*!< SCU_T::SVIOIEN: APB0IEN Position       */
#define SCU_SVIOIEN_APB0IEN_Msk          (0x1ul << SCU_SVIOIEN_APB0IEN_Pos)                /*!< SCU_T::SVIOIEN: APB0IEN Mask           */

#define SCU_SVIOIEN_APB1IEN_Pos          (1)                                               /*!< SCU_T::SVIOIEN: APB1IEN Position       */
#define SCU_SVIOIEN_APB1IEN_Msk          (0x1ul << SCU_SVIOIEN_APB1IEN_Pos)                /*!< SCU_T::SVIOIEN: APB1IEN Mask           */

#define SCU_SVIOIEN_GPIOIEN_Pos          (4)                                               /*!< SCU_T::SVIOIEN: GPIOIEN Position       */
#define SCU_SVIOIEN_GPIOIEN_Msk          (0x1ul << SCU_SVIOIEN_GPIOIEN_Pos)                /*!< SCU_T::SVIOIEN: GPIOIEN Mask           */

#define SCU_SVIOIEN_EBIIEN_Pos           (5)                                               /*!< SCU_T::SVIOIEN: EBIIEN Position        */
#define SCU_SVIOIEN_EBIIEN_Msk           (0x1ul << SCU_SVIOIEN_EBIIEN_Pos)                 /*!< SCU_T::SVIOIEN: EBIIEN Mask            */

#define SCU_SVIOIEN_USBHIEN_Pos          (6)                                               /*!< SCU_T::SVIOIEN: USBHIEN Position       */
#define SCU_SVIOIEN_USBHIEN_Msk          (0x1ul << SCU_SVIOIEN_USBHIEN_Pos)                /*!< SCU_T::SVIOIEN: USBHIEN Mask           */

#define SCU_SVIOIEN_CRCIEN_Pos           (7)                                               /*!< SCU_T::SVIOIEN: CRCIEN Position        */
#define SCU_SVIOIEN_CRCIEN_Msk           (0x1ul << SCU_SVIOIEN_CRCIEN_Pos)                 /*!< SCU_T::SVIOIEN: CRCIEN Mask            */

#define SCU_SVIOIEN_SDH0IEN_Pos          (8)                                               /*!< SCU_T::SVIOIEN: SDH0IEN Position       */
#define SCU_SVIOIEN_SDH0IEN_Msk          (0x1ul << SCU_SVIOIEN_SDH0IEN_Pos)                /*!< SCU_T::SVIOIEN: SDH0IEN Mask           */

#define SCU_SVIOIEN_PDMA0IEN_Pos         (10)                                              /*!< SCU_T::SVIOIEN: PDMA0IEN Position      */
#define SCU_SVIOIEN_PDMA0IEN_Msk         (0x1ul << SCU_SVIOIEN_PDMA0IEN_Pos)               /*!< SCU_T::SVIOIEN: PDMA0IEN Mask          */

#define SCU_SVIOIEN_PDMA1IEN_Pos         (11)                                              /*!< SCU_T::SVIOIEN: PDMA1IEN Position      */
#define SCU_SVIOIEN_PDMA1IEN_Msk         (0x1ul << SCU_SVIOIEN_PDMA1IEN_Pos)               /*!< SCU_T::SVIOIEN: PDMA1IEN Mask          */

#define SCU_SVIOIEN_SRAM0IEN_Pos         (12)                                              /*!< SCU_T::SVIOIEN: SRAM0IEN Position      */
#define SCU_SVIOIEN_SRAM0IEN_Msk         (0x1ul << SCU_SVIOIEN_SRAM0IEN_Pos)               /*!< SCU_T::SVIOIEN: SRAM0IEN Mask          */

#define SCU_SVIOIEN_SRAM1IEN_Pos         (13)                                              /*!< SCU_T::SVIOIEN: SRAM1IEN Position      */
#define SCU_SVIOIEN_SRAM1IEN_Msk         (0x1ul << SCU_SVIOIEN_SRAM1IEN_Pos)               /*!< SCU_T::SVIOIEN: SRAM1IEN Mask          */

#define SCU_SVIOIEN_FMCIEN_Pos           (14)                                              /*!< SCU_T::SVIOIEN: FMCIEN Position        */
#define SCU_SVIOIEN_FMCIEN_Msk           (0x1ul << SCU_SVIOIEN_FMCIEN_Pos)                 /*!< SCU_T::SVIOIEN: FMCIEN Mask            */

#define SCU_SVIOIEN_FLASHIEN_Pos         (15)                                              /*!< SCU_T::SVIOIEN: FLASHIEN Position      */
#define SCU_SVIOIEN_FLASHIEN_Msk         (0x1ul << SCU_SVIOIEN_FLASHIEN_Pos)               /*!< SCU_T::SVIOIEN: FLASHIEN Mask          */

#define SCU_SVIOIEN_SCUIEN_Pos           (16)                                              /*!< SCU_T::SVIOIEN: SCUIEN Position        */
#define SCU_SVIOIEN_SCUIEN_Msk           (0x1ul << SCU_SVIOIEN_SCUIEN_Pos)                 /*!< SCU_T::SVIOIEN: SCUIEN Mask            */

#define SCU_SVIOIEN_SYSIEN_Pos           (17)                                              /*!< SCU_T::SVIOIEN: SYSIEN Position        */
#define SCU_SVIOIEN_SYSIEN_Msk           (0x1ul << SCU_SVIOIEN_SYSIEN_Pos)                 /*!< SCU_T::SVIOIEN: SYSIEN Mask            */

#define SCU_SVIOIEN_CRPTIEN_Pos          (18)                                              /*!< SCU_T::SVIOIEN: CRPTIEN Position       */
#define SCU_SVIOIEN_CRPTIEN_Msk          (0x1ul << SCU_SVIOIEN_CRPTIEN_Pos)                /*!< SCU_T::SVIOIEN: CRPTIEN Mask           */

#define SCU_SVIOIEN_KSIEN_Pos            (19)                                              /*!< SCU_T::SVIOIEN: KSIEN Position         */
#define SCU_SVIOIEN_KSIEN_Msk            (0x1ul << SCU_SVIOIEN_KSIEN_Pos)                  /*!< SCU_T::SVIOIEN: KSIEN Mask             */

#define SCU_SVINTSTS_APB0IF_Pos          (0)                                               /*!< SCU_T::SVINTSTS: APB0IF Position       */
#define SCU_SVINTSTS_APB0IF_Msk          (0x1ul << SCU_SVINTSTS_APB0IF_Pos)                /*!< SCU_T::SVINTSTS: APB0IF Mask           */

#define SCU_SVINTSTS_APB1IF_Pos          (1)                                               /*!< SCU_T::SVINTSTS: APB1IF Position       */
#define SCU_SVINTSTS_APB1IF_Msk          (0x1ul << SCU_SVINTSTS_APB1IF_Pos)                /*!< SCU_T::SVINTSTS: APB1IF Mask           */

#define SCU_SVINTSTS_GPIOIF_Pos          (4)                                               /*!< SCU_T::SVINTSTS: GPIOIF Position       */
#define SCU_SVINTSTS_GPIOIF_Msk          (0x1ul << SCU_SVINTSTS_GPIOIF_Pos)                /*!< SCU_T::SVINTSTS: GPIOIF Mask           */

#define SCU_SVINTSTS_EBIIF_Pos           (5)                                               /*!< SCU_T::SVINTSTS: EBIIF Position        */
#define SCU_SVINTSTS_EBIIF_Msk           (0x1ul << SCU_SVINTSTS_EBIIF_Pos)                 /*!< SCU_T::SVINTSTS: EBIIF Mask            */

#define SCU_SVINTSTS_USBHIF_Pos          (6)                                               /*!< SCU_T::SVINTSTS: USBHIF Position       */
#define SCU_SVINTSTS_USBHIF_Msk          (0x1ul << SCU_SVINTSTS_USBHIF_Pos)                /*!< SCU_T::SVINTSTS: USBHIF Mask           */

#define SCU_SVINTSTS_CRCIF_Pos           (7)                                               /*!< SCU_T::SVINTSTS: CRCIF Position        */
#define SCU_SVINTSTS_CRCIF_Msk           (0x1ul << SCU_SVINTSTS_CRCIF_Pos)                 /*!< SCU_T::SVINTSTS: CRCIF Mask            */

#define SCU_SVINTSTS_SDH0IF_Pos          (8)                                               /*!< SCU_T::SVINTSTS: SDH0IF Position       */
#define SCU_SVINTSTS_SDH0IF_Msk          (0x1ul << SCU_SVINTSTS_SDH0IF_Pos)                /*!< SCU_T::SVINTSTS: SDH0IF Mask           */

#define SCU_SVINTSTS_PDMA0IF_Pos         (10)                                              /*!< SCU_T::SVINTSTS: PDMA0IF Position      */
#define SCU_SVINTSTS_PDMA0IF_Msk         (0x1ul << SCU_SVINTSTS_PDMA0IF_Pos)               /*!< SCU_T::SVINTSTS: PDMA0IF Mask          */

#define SCU_SVINTSTS_PDMA1IF_Pos         (11)                                              /*!< SCU_T::SVINTSTS: PDMA1IF Position      */
#define SCU_SVINTSTS_PDMA1IF_Msk         (0x1ul << SCU_SVINTSTS_PDMA1IF_Pos)               /*!< SCU_T::SVINTSTS: PDMA1IF Mask          */

#define SCU_SVINTSTS_SRAM0IF_Pos         (12)                                              /*!< SCU_T::SVINTSTS: SRAM0IF Position      */
#define SCU_SVINTSTS_SRAM0IF_Msk         (0x1ul << SCU_SVINTSTS_SRAM0IF_Pos)               /*!< SCU_T::SVINTSTS: SRAM0IF Mask          */

#define SCU_SVINTSTS_SRAM1IF_Pos         (13)                                              /*!< SCU_T::SVINTSTS: SRAM1IF Position      */
#define SCU_SVINTSTS_SRAM1IF_Msk         (0x1ul << SCU_SVINTSTS_SRAM1IF_Pos)               /*!< SCU_T::SVINTSTS: SRAM1IF Mask          */

#define SCU_SVINTSTS_FMCIF_Pos           (14)                                              /*!< SCU_T::SVINTSTS: FMCIF Position        */
#define SCU_SVINTSTS_FMCIF_Msk           (0x1ul << SCU_SVINTSTS_FMCIF_Pos)                 /*!< SCU_T::SVINTSTS: FMCIF Mask            */

#define SCU_SVINTSTS_FLASHIF_Pos         (15)                                              /*!< SCU_T::SVINTSTS: FLASHIF Position      */
#define SCU_SVINTSTS_FLASHIF_Msk         (0x1ul << SCU_SVINTSTS_FLASHIF_Pos)               /*!< SCU_T::SVINTSTS: FLASHIF Mask          */

#define SCU_SVINTSTS_SCUIF_Pos           (16)                                              /*!< SCU_T::SVINTSTS: SCUIF Position        */
#define SCU_SVINTSTS_SCUIF_Msk           (0x1ul << SCU_SVINTSTS_SCUIF_Pos)                 /*!< SCU_T::SVINTSTS: SCUIF Mask            */

#define SCU_SVINTSTS_SYSIF_Pos           (17)                                              /*!< SCU_T::SVINTSTS: SYSIF Position        */
#define SCU_SVINTSTS_SYSIF_Msk           (0x1ul << SCU_SVINTSTS_SYSIF_Pos)                 /*!< SCU_T::SVINTSTS: SYSIF Mask            */

#define SCU_SVINTSTS_CRPTIF_Pos          (18)                                              /*!< SCU_T::SVINTSTS: CRPTIF Position       */
#define SCU_SVINTSTS_CRPTIF_Msk          (0x1ul << SCU_SVINTSTS_CRPTIF_Pos)                /*!< SCU_T::SVINTSTS: CRPTIF Mask           */

#define SCU_SVINTSTS_KSIF_Pos            (19)                                              /*!< SCU_T::SVINTSTS: KSIF Position         */
#define SCU_SVINTSTS_KSIF_Msk            (0x1ul << SCU_SVINTSTS_KSIF_Pos)                  /*!< SCU_T::SVINTSTS: KSIF Mask             */

#define SCU_APB0VSRC_MASTER_Pos          (0)                                               /*!< SCU_T::APB0VSRC: MASTER Position       */
#define SCU_APB0VSRC_MASTER_Msk          (0xful << SCU_APB0VSRC_MASTER_Pos)                /*!< SCU_T::APB0VSRC: MASTER Mask           */

#define SCU_APB0VA_VIOADDR_Pos           (0)                                               /*!< SCU_T::APB0VA: VIOADDR Position        */
#define SCU_APB0VA_VIOADDR_Msk           (0xfffffffful << SCU_APB0VA_VIOADDR_Pos)          /*!< SCU_T::APB0VA: VIOADDR Mask            */

#define SCU_APB1VSRC_MASTER_Pos          (0)                                               /*!< SCU_T::APB1VSRC: MASTER Position       */
#define SCU_APB1VSRC_MASTER_Msk          (0xful << SCU_APB1VSRC_MASTER_Pos)                /*!< SCU_T::APB1VSRC: MASTER Mask           */

#define SCU_APB1VA_VIOADDR_Pos           (0)                                               /*!< SCU_T::APB1VA: VIOADDR Position        */
#define SCU_APB1VA_VIOADDR_Msk           (0xfffffffful << SCU_APB1VA_VIOADDR_Pos)          /*!< SCU_T::APB1VA: VIOADDR Mask            */

#define SCU_GPIOVSRC_MASTER_Pos          (0)                                               /*!< SCU_T::GPIOVSRC: MASTER Position       */
#define SCU_GPIOVSRC_MASTER_Msk          (0xful << SCU_GPIOVSRC_MASTER_Pos)                /*!< SCU_T::GPIOVSRC: MASTER Mask           */

#define SCU_GPIOVA_VIOADDR_Pos           (0)                                               /*!< SCU_T::GPIOVA: VIOADDR Position        */
#define SCU_GPIOVA_VIOADDR_Msk           (0xfffffffful << SCU_GPIOVA_VIOADDR_Pos)          /*!< SCU_T::GPIOVA: VIOADDR Mask            */

#define SCU_EBIVSRC_MASTER_Pos           (0)                                               /*!< SCU_T::EBIVSRC: MASTER Position        */
#define SCU_EBIVSRC_MASTER_Msk           (0xful << SCU_EBIVSRC_MASTER_Pos)                 /*!< SCU_T::EBIVSRC: MASTER Mask            */

#define SCU_EBIVA_VIOADDR_Pos            (0)                                               /*!< SCU_T::EBIVA: VIOADDR Position         */
#define SCU_EBIVA_VIOADDR_Msk            (0xfffffffful << SCU_EBIVA_VIOADDR_Pos)           /*!< SCU_T::EBIVA: VIOADDR Mask             */

#define SCU_USBHVSRC_MASTER_Pos          (0)                                               /*!< SCU_T::USBHVSRC: MASTER Position       */
#define SCU_USBHVSRC_MASTER_Msk          (0xful << SCU_USBHVSRC_MASTER_Pos)                /*!< SCU_T::USBHVSRC: MASTER Mask           */

#define SCU_USBHVA_VIOADDR_Pos           (0)                                               /*!< SCU_T::USBHVA: VIOADDR Position        */
#define SCU_USBHVA_VIOADDR_Msk           (0xfffffffful << SCU_USBHVA_VIOADDR_Pos)          /*!< SCU_T::USBHVA: VIOADDR Mask            */

#define SCU_CRCVSRC_MASTER_Pos           (0)                                               /*!< SCU_T::CRCVSRC: MASTER Position        */
#define SCU_CRCVSRC_MASTER_Msk           (0xful << SCU_CRCVSRC_MASTER_Pos)                 /*!< SCU_T::CRCVSRC: MASTER Mask            */

#define SCU_CRCVA_VIOADDR_Pos            (0)                                               /*!< SCU_T::CRCVA: VIOADDR Position         */
#define SCU_CRCVA_VIOADDR_Msk            (0xfffffffful << SCU_CRCVA_VIOADDR_Pos)           /*!< SCU_T::CRCVA: VIOADDR Mask             */

#define SCU_SD0VSRC_MASTER_Pos           (0)                                               /*!< SCU_T::SD0VSRC: MASTER Position        */
#define SCU_SD0VSRC_MASTER_Msk           (0xful << SCU_SD0VSRC_MASTER_Pos)                 /*!< SCU_T::SD0VSRC: MASTER Mask            */

#define SCU_SD0VA_VIOADDR_Pos            (0)                                               /*!< SCU_T::SD0VA: VIOADDR Position         */
#define SCU_SD0VA_VIOADDR_Msk            (0xfffffffful << SCU_SD0VA_VIOADDR_Pos)           /*!< SCU_T::SD0VA: VIOADDR Mask             */

#define SCU_PDMA0VSRC_MASTER_Pos         (0)                                               /*!< SCU_T::PDMA0VSRC: MASTER Position      */
#define SCU_PDMA0VSRC_MASTER_Msk         (0xful << SCU_PDMA0VSRC_MASTER_Pos)               /*!< SCU_T::PDMA0VSRC: MASTER Mask          */

#define SCU_PDMA0VA_VIOADDR_Pos          (0)                                               /*!< SCU_T::PDMA0VA: VIOADDR Position       */
#define SCU_PDMA0VA_VIOADDR_Msk          (0xfffffffful << SCU_PDMA0VA_VIOADDR_Pos)         /*!< SCU_T::PDMA0VA: VIOADDR Mask           */

#define SCU_PDMA1VSRC_MASTER_Pos         (0)                                               /*!< SCU_T::PDMA1VSRC: MASTER Position      */
#define SCU_PDMA1VSRC_MASTER_Msk         (0xful << SCU_PDMA1VSRC_MASTER_Pos)               /*!< SCU_T::PDMA1VSRC: MASTER Mask          */

#define SCU_PDMA1VA_VIOADDR_Pos          (0)                                               /*!< SCU_T::PDMA1VA: VIOADDR Position       */
#define SCU_PDMA1VA_VIOADDR_Msk          (0xfffffffful << SCU_PDMA1VA_VIOADDR_Pos)         /*!< SCU_T::PDMA1VA: VIOADDR Mask           */

#define SCU_SRAM0VSRC_MASTER_Pos         (0)                                               /*!< SCU_T::SRAM0VSRC: MASTER Position      */
#define SCU_SRAM0VSRC_MASTER_Msk         (0xful << SCU_SRAM0VSRC_MASTER_Pos)               /*!< SCU_T::SRAM0VSRC: MASTER Mask          */

#define SCU_SRAM0VA_VIOADDR_Pos          (0)                                               /*!< SCU_T::SRAM0VA: VIOADDR Position       */
#define SCU_SRAM0VA_VIOADDR_Msk          (0xfffffffful << SCU_SRAM0VA_VIOADDR_Pos)         /*!< SCU_T::SRAM0VA: VIOADDR Mask           */

#define SCU_SRAM1VSRC_MASTER_Pos         (0)                                               /*!< SCU_T::SRAM1VSRC: MASTER Position      */
#define SCU_SRAM1VSRC_MASTER_Msk         (0xful << SCU_SRAM1VSRC_MASTER_Pos)               /*!< SCU_T::SRAM1VSRC: MASTER Mask          */

#define SCU_SRAM1VA_VIOADDR_Pos          (0)                                               /*!< SCU_T::SRAM1VA: VIOADDR Position       */
#define SCU_SRAM1VA_VIOADDR_Msk          (0xfffffffful << SCU_SRAM1VA_VIOADDR_Pos)         /*!< SCU_T::SRAM1VA: VIOADDR Mask           */

#define SCU_FMCVSRC_MASTER_Pos           (0)                                               /*!< SCU_T::FMCVSRC: MASTER Position        */
#define SCU_FMCVSRC_MASTER_Msk           (0xful << SCU_FMCVSRC_MASTER_Pos)                 /*!< SCU_T::FMCVSRC: MASTER Mask            */

#define SCU_FMCVA_VIOADDR_Pos            (0)                                               /*!< SCU_T::FMCVA: VIOADDR Position         */
#define SCU_FMCVA_VIOADDR_Msk            (0xfffffffful << SCU_FMCVA_VIOADDR_Pos)           /*!< SCU_T::FMCVA: VIOADDR Mask             */

#define SCU_FLASHVSRC_MASTER_Pos         (0)                                               /*!< SCU_T::FLASHVSRC: MASTER Position      */
#define SCU_FLASHVSRC_MASTER_Msk         (0xful << SCU_FLASHVSRC_MASTER_Pos)               /*!< SCU_T::FLASHVSRC: MASTER Mask          */

#define SCU_FLASHVA_VIOADDR_Pos          (0)                                               /*!< SCU_T::FLASHVA: VIOADDR Position       */
#define SCU_FLASHVA_VIOADDR_Msk          (0xfffffffful << SCU_FLASHVA_VIOADDR_Pos)         /*!< SCU_T::FLASHVA: VIOADDR Mask           */

#define SCU_SCUVSRC_MASTER_Pos           (0)                                               /*!< SCU_T::SCUVSRC: MASTER Position        */
#define SCU_SCUVSRC_MASTER_Msk           (0xful << SCU_SCUVSRC_MASTER_Pos)                 /*!< SCU_T::SCUVSRC: MASTER Mask            */

#define SCU_SCUVA_VIOADDR_Pos            (0)                                               /*!< SCU_T::SCUVA: VIOADDR Position         */
#define SCU_SCUVA_VIOADDR_Msk            (0xfffffffful << SCU_SCUVA_VIOADDR_Pos)           /*!< SCU_T::SCUVA: VIOADDR Mask             */

#define SCU_SYSVSRC_MASTER_Pos           (0)                                               /*!< SCU_T::SYSVSRC: MASTER Position        */
#define SCU_SYSVSRC_MASTER_Msk           (0xful << SCU_SYSVSRC_MASTER_Pos)                 /*!< SCU_T::SYSVSRC: MASTER Mask            */

#define SCU_SYSVA_VIOADDR_Pos            (0)                                               /*!< SCU_T::SYSVA: VIOADDR Position         */
#define SCU_SYSVA_VIOADDR_Msk            (0xfffffffful << SCU_SYSVA_VIOADDR_Pos)           /*!< SCU_T::SYSVA: VIOADDR Mask             */

#define SCU_CRPTVSRC_MASTER_Pos          (0)                                               /*!< SCU_T::CRPTVSRC: MASTER Position       */
#define SCU_CRPTVSRC_MASTER_Msk          (0xful << SCU_CRPTVSRC_MASTER_Pos)                /*!< SCU_T::CRPTVSRC: MASTER Mask           */

#define SCU_CRPTVA_VIOADDR_Pos           (0)                                               /*!< SCU_T::CRPTVA: VIOADDR Position        */
#define SCU_CRPTVA_VIOADDR_Msk           (0xfffffffful << SCU_CRPTVA_VIOADDR_Pos)          /*!< SCU_T::CRPTVA: VIOADDR Mask            */

#define SCU_KSVSRC_MASTER_Pos            (0)                                               /*!< SCU_T::KSVSRC: MASTER Position         */
#define SCU_KSVSRC_MASTER_Msk            (0xful << SCU_KSVSRC_MASTER_Pos)                  /*!< SCU_T::KSVSRC: MASTER Mask             */

#define SCU_KSVA_VIOADDR_Pos             (0)                                               /*!< SCU_T::KSVA: VIOADDR Position          */
#define SCU_KSVA_VIOADDR_Msk             (0xfffffffful << SCU_KSVA_VIOADDR_Pos)            /*!< SCU_T::KSVA: VIOADDR Mask              */

#define SCU_SRAM2VSRC_MASTER_Pos         (0)                                               /*!< SCU_T::SRAM2VSRC: MASTER Position      */
#define SCU_SRAM2VSRC_MASTER_Msk         (0xful << SCU_SRAM2VSRC_MASTER_Pos)               /*!< SCU_T::SRAM2VSRC: MASTER Mask          */

#define SCU_SRAM2VA_VIOADDR_Pos          (0)                                               /*!< SCU_T::SRAM2VA: VIOADDR Position       */
#define SCU_SRAM2VA_VIOADDR_Msk          (0xfffffffful << SCU_SRAM2VA_VIOADDR_Pos)         /*!< SCU_T::SRAM2VA: VIOADDR Mask           */

#define SCU_SINFAEN_SCUSIAEN_Pos         (0)                                               /*!< SCU_T::SINFAEN: SCUSIAEN Position      */
#define SCU_SINFAEN_SCUSIAEN_Msk         (0x1ul << SCU_SINFAEN_SCUSIAEN_Pos)               /*!< SCU_T::SINFAEN: SCUSIAEN Mask          */

#define SCU_SINFAEN_SYSSIAEN_Pos         (1)                                               /*!< SCU_T::SINFAEN: SYSSIAEN Position      */
#define SCU_SINFAEN_SYSSIAEN_Msk         (0x1ul << SCU_SINFAEN_SYSSIAEN_Pos)               /*!< SCU_T::SINFAEN: SYSSIAEN Mask          */

#define SCU_SINFAEN_FMCSIAEN_Pos         (2)                                               /*!< SCU_T::SINFAEN: FMCSIAEN Position      */
#define SCU_SINFAEN_FMCSIAEN_Msk         (0x1ul << SCU_SINFAEN_FMCSIAEN_Pos)               /*!< SCU_T::SINFAEN: FMCSIAEN Mask          */

#define SCU_PNPSET0_SYS_Pos              (0)                                               /*!< SCU_T::PNPSET0: SYS Position           */
#define SCU_PNPSET0_SYS_Msk              (0x1ul << SCU_PNPSET0_SYS_Pos)                    /*!< SCU_T::PNPSET0: SYS Mask               */

#define SCU_PNPSET0_PDMA0_Pos            (8)                                               /*!< SCU_T::PNPSET0: PDMA0 Position         */
#define SCU_PNPSET0_PDMA0_Msk            (0x1ul << SCU_PNPSET0_PDMA0_Pos)                  /*!< SCU_T::PNPSET0: PDMA0 Mask             */

#define SCU_PNPSET0_USBH_Pos             (9)                                               /*!< SCU_T::PNPSET0: USBH Position          */
#define SCU_PNPSET0_USBH_Msk             (0x1ul << SCU_PNPSET0_USBH_Pos)                   /*!< SCU_T::PNPSET0: USBH Mask              */

#define SCU_PNPSET0_FMC_Pos              (12)                                              /*!< SCU_T::PNPSET0: FMC Position           */
#define SCU_PNPSET0_FMC_Msk              (0x1ul << SCU_PNPSET0_FMC_Pos)                    /*!< SCU_T::PNPSET0: FMC Mask               */

#define SCU_PNPSET0_SDH0_Pos             (13)                                              /*!< SCU_T::PNPSET0: SDH0 Position          */
#define SCU_PNPSET0_SDH0_Msk             (0x1ul << SCU_PNPSET0_SDH0_Pos)                   /*!< SCU_T::PNPSET0: SDH0 Mask              */

#define SCU_PNPSET0_EBI_Pos              (16)                                              /*!< SCU_T::PNPSET0: EBI Position           */
#define SCU_PNPSET0_EBI_Msk              (0x1ul << SCU_PNPSET0_EBI_Pos)                    /*!< SCU_T::PNPSET0: EBI Mask               */

#define SCU_PNPSET0_PDMA1_Pos            (24)                                              /*!< SCU_T::PNPSET0: PDMA1 Position         */
#define SCU_PNPSET0_PDMA1_Msk            (0x1ul << SCU_PNPSET0_PDMA1_Pos)                  /*!< SCU_T::PNPSET0: PDMA1 Mask             */

#define SCU_PNPSET1_SCU_Pos              (15)                                              /*!< SCU_T::PNPSET1: SCU Position           */
#define SCU_PNPSET1_SCU_Msk              (0x1ul << SCU_PNPSET1_SCU_Pos)                    /*!< SCU_T::PNPSET1: SCU Mask               */

#define SCU_PNPSET1_CRC_Pos              (17)                                              /*!< SCU_T::PNPSET1: CRC Position           */
#define SCU_PNPSET1_CRC_Msk              (0x1ul << SCU_PNPSET1_CRC_Pos)                    /*!< SCU_T::PNPSET1: CRC Mask               */

#define SCU_PNPSET1_CRPT_Pos             (18)                                              /*!< SCU_T::PNPSET1: CRPT Position          */
#define SCU_PNPSET1_CRPT_Msk             (0x1ul << SCU_PNPSET1_CRPT_Pos)                   /*!< SCU_T::PNPSET1: CRPT Mask              */

#define SCU_PNPSET1_KS_Pos               (21)                                              /*!< SCU_T::PNPSET1: KS Position            */
#define SCU_PNPSET1_KS_Msk               (0x1ul << SCU_PNPSET1_KS_Pos)                     /*!< SCU_T::PNPSET1: KS Mask                */

#define SCU_PNPSET2_WDT_Pos              (0)                                               /*!< SCU_T::PNPSET2: WDT Position           */
#define SCU_PNPSET2_WDT_Msk              (0x1ul << SCU_PNPSET2_WDT_Pos)                    /*!< SCU_T::PNPSET2: WDT Mask               */

#define SCU_PNPSET2_RTC_Pos              (1)                                               /*!< SCU_T::PNPSET2: RTC Position           */
#define SCU_PNPSET2_RTC_Msk              (0x1ul << SCU_PNPSET2_RTC_Pos)                    /*!< SCU_T::PNPSET2: RTC Mask               */

#define SCU_PNPSET2_EWDT_Pos             (2)                                               /*!< SCU_T::PNPSET2: EWDT Position          */
#define SCU_PNPSET2_EWDT_Msk             (0x1ul << SCU_PNPSET2_EWDT_Pos)                   /*!< SCU_T::PNPSET2: EWDT Mask              */

#define SCU_PNPSET2_EADC_Pos             (3)                                               /*!< SCU_T::PNPSET2: EADC Position          */
#define SCU_PNPSET2_EADC_Msk             (0x1ul << SCU_PNPSET2_EADC_Pos)                   /*!< SCU_T::PNPSET2: EADC Mask              */

#define SCU_PNPSET2_ACMP01_Pos           (5)                                               /*!< SCU_T::PNPSET2: ACMP01 Position        */
#define SCU_PNPSET2_ACMP01_Msk           (0x1ul << SCU_PNPSET2_ACMP01_Pos)                 /*!< SCU_T::PNPSET2: ACMP01 Mask            */

#define SCU_PNPSET2_DAC_Pos              (7)                                               /*!< SCU_T::PNPSET2: DAC Position           */
#define SCU_PNPSET2_DAC_Msk              (0x1ul << SCU_PNPSET2_DAC_Pos)                    /*!< SCU_T::PNPSET2: DAC Mask               */

#define SCU_PNPSET2_I2S0_Pos             (8)                                               /*!< SCU_T::PNPSET2: I2S0 Position          */
#define SCU_PNPSET2_I2S0_Msk             (0x1ul << SCU_PNPSET2_I2S0_Pos)                   /*!< SCU_T::PNPSET2: I2S0 Mask              */

#define SCU_PNPSET2_OTG_Pos              (13)                                              /*!< SCU_T::PNPSET2: OTG Position           */
#define SCU_PNPSET2_OTG_Msk              (0x1ul << SCU_PNPSET2_OTG_Pos)                    /*!< SCU_T::PNPSET2: OTG Mask               */

#define SCU_PNPSET2_TMR01_Pos            (14)                                              /*!< SCU_T::PNPSET2: TMR01 Position         */
#define SCU_PNPSET2_TMR01_Msk            (0x7ul << SCU_PNPSET2_TMR01_Pos)                  /*!< SCU_T::PNPSET2: TMR01 Mask             */

#define SCU_PNPSET2_TMR23_Pos            (17)                                              /*!< SCU_T::PNPSET2: TMR23 Position         */
#define SCU_PNPSET2_TMR23_Msk            (0x1ul << SCU_PNPSET2_TMR23_Pos)                  /*!< SCU_T::PNPSET2: TMR23 Mask             */

#define SCU_PNPSET2_EPWM0_Pos            (24)                                              /*!< SCU_T::PNPSET2: EPWM0 Position         */
#define SCU_PNPSET2_EPWM0_Msk            (0x1ul << SCU_PNPSET2_EPWM0_Pos)                  /*!< SCU_T::PNPSET2: EPWM0 Mask             */

#define SCU_PNPSET2_EPWM1_Pos            (25)                                              /*!< SCU_T::PNPSET2: EPWM1 Position         */
#define SCU_PNPSET2_EPWM1_Msk            (0x1ul << SCU_PNPSET2_EPWM1_Pos)                  /*!< SCU_T::PNPSET2: EPWM1 Mask             */

#define SCU_PNPSET2_BPWM0_Pos            (26)                                              /*!< SCU_T::PNPSET2: BPWM0 Position         */
#define SCU_PNPSET2_BPWM0_Msk            (0x1ul << SCU_PNPSET2_BPWM0_Pos)                  /*!< SCU_T::PNPSET2: BPWM0 Mask             */

#define SCU_PNPSET2_BPWM1_Pos            (27)                                              /*!< SCU_T::PNPSET2: BPWM1 Position         */
#define SCU_PNPSET2_BPWM1_Msk            (0x1ul << SCU_PNPSET2_BPWM1_Pos)                  /*!< SCU_T::PNPSET2: BPWM1 Mask             */

#define SCU_PNPSET3_QSPI0_Pos            (0)                                               /*!< SCU_T::PNPSET3: QSPI0 Position         */
#define SCU_PNPSET3_QSPI0_Msk            (0x1ul << SCU_PNPSET3_QSPI0_Pos)                  /*!< SCU_T::PNPSET3: QSPI0 Mask             */

#define SCU_PNPSET3_SPI0_Pos             (1)                                               /*!< SCU_T::PNPSET3: SPI0 Position          */
#define SCU_PNPSET3_SPI0_Msk             (0x1ul << SCU_PNPSET3_SPI0_Pos)                   /*!< SCU_T::PNPSET3: SPI0 Mask              */

#define SCU_PNPSET3_SPI1_Pos             (2)                                               /*!< SCU_T::PNPSET3: SPI1 Position          */
#define SCU_PNPSET3_SPI1_Msk             (0x1ul << SCU_PNPSET3_SPI1_Pos)                   /*!< SCU_T::PNPSET3: SPI1 Mask              */

#define SCU_PNPSET3_SPI2_Pos             (3)                                               /*!< SCU_T::PNPSET3: SPI2 Position          */
#define SCU_PNPSET3_SPI2_Msk             (0x1ul << SCU_PNPSET3_SPI2_Pos)                   /*!< SCU_T::PNPSET3: SPI2 Mask              */

#define SCU_PNPSET3_SPI3_Pos             (4)                                               /*!< SCU_T::PNPSET3: SPI3 Position          */
#define SCU_PNPSET3_SPI3_Msk             (0x1ul << SCU_PNPSET3_SPI3_Pos)                   /*!< SCU_T::PNPSET3: SPI3 Mask              */

#define SCU_PNPSET3_UART0_Pos            (16)                                              /*!< SCU_T::PNPSET3: UART0 Position         */
#define SCU_PNPSET3_UART0_Msk            (0x1ul << SCU_PNPSET3_UART0_Pos)                  /*!< SCU_T::PNPSET3: UART0 Mask             */

#define SCU_PNPSET3_UART1_Pos            (17)                                              /*!< SCU_T::PNPSET3: UART1 Position         */
#define SCU_PNPSET3_UART1_Msk            (0x1ul << SCU_PNPSET3_UART1_Pos)                  /*!< SCU_T::PNPSET3: UART1 Mask             */

#define SCU_PNPSET3_UART2_Pos            (18)                                              /*!< SCU_T::PNPSET3: UART2 Position         */
#define SCU_PNPSET3_UART2_Msk            (0x1ul << SCU_PNPSET3_UART2_Pos)                  /*!< SCU_T::PNPSET3: UART2 Mask             */

#define SCU_PNPSET3_UART3_Pos            (19)                                              /*!< SCU_T::PNPSET3: UART3 Position         */
#define SCU_PNPSET3_UART3_Msk            (0x1ul << SCU_PNPSET3_UART3_Pos)                  /*!< SCU_T::PNPSET3: UART3 Mask             */

#define SCU_PNPSET3_UART4_Pos            (20)                                              /*!< SCU_T::PNPSET3: UART4 Position         */
#define SCU_PNPSET3_UART4_Msk            (0x1ul << SCU_PNPSET3_UART4_Pos)                  /*!< SCU_T::PNPSET3: UART4 Mask             */

#define SCU_PNPSET3_UART5_Pos            (21)                                              /*!< SCU_T::PNPSET3: UART5 Position         */
#define SCU_PNPSET3_UART5_Msk            (0x1ul << SCU_PNPSET3_UART5_Pos)                  /*!< SCU_T::PNPSET3: UART5 Mask             */

#define SCU_PNPSET4_I2C0_Pos             (0)                                               /*!< SCU_T::PNPSET4: I2C0 Position          */
#define SCU_PNPSET4_I2C0_Msk             (0x1ul << SCU_PNPSET4_I2C0_Pos)                   /*!< SCU_T::PNPSET4: I2C0 Mask              */

#define SCU_PNPSET4_I2C1_Pos             (1)                                               /*!< SCU_T::PNPSET4: I2C1 Position          */
#define SCU_PNPSET4_I2C1_Msk             (0x1ul << SCU_PNPSET4_I2C1_Pos)                   /*!< SCU_T::PNPSET4: I2C1 Mask              */

#define SCU_PNPSET4_I2C2_Pos             (2)                                               /*!< SCU_T::PNPSET4: I2C2 Position          */
#define SCU_PNPSET4_I2C2_Msk             (0x1ul << SCU_PNPSET4_I2C2_Pos)                   /*!< SCU_T::PNPSET4: I2C2 Mask              */

#define SCU_PNPSET4_SC0_Pos              (16)                                              /*!< SCU_T::PNPSET4: SC0 Position           */
#define SCU_PNPSET4_SC0_Msk              (0x1ul << SCU_PNPSET4_SC0_Pos)                    /*!< SCU_T::PNPSET4: SC0 Mask               */

#define SCU_PNPSET4_SC1_Pos              (17)                                              /*!< SCU_T::PNPSET4: SC1 Position           */
#define SCU_PNPSET4_SC1_Msk              (0x1ul << SCU_PNPSET4_SC1_Pos)                    /*!< SCU_T::PNPSET4: SC1 Mask               */

#define SCU_PNPSET4_SC2_Pos              (18)                                              /*!< SCU_T::PNPSET4: SC2 Position           */
#define SCU_PNPSET4_SC2_Msk              (0x1ul << SCU_PNPSET4_SC2_Pos)                    /*!< SCU_T::PNPSET4: SC2 Mask               */

#define SCU_PNPSET5_CAN0_Pos             (0)                                               /*!< SCU_T::PNPSET5: CAN0 Position          */
#define SCU_PNPSET5_CAN0_Msk             (0x1ul << SCU_PNPSET5_CAN0_Pos)                   /*!< SCU_T::PNPSET5: CAN0 Mask              */

#define SCU_PNPSET5_QEI0_Pos             (16)                                              /*!< SCU_T::PNPSET5: QEI0 Position          */
#define SCU_PNPSET5_QEI0_Msk             (0x1ul << SCU_PNPSET5_QEI0_Pos)                   /*!< SCU_T::PNPSET5: QEI0 Mask              */

#define SCU_PNPSET5_QEI1_Pos             (17)                                              /*!< SCU_T::PNPSET5: QEI1 Position          */
#define SCU_PNPSET5_QEI1_Msk             (0x1ul << SCU_PNPSET5_QEI1_Pos)                   /*!< SCU_T::PNPSET5: QEI1 Mask              */

#define SCU_PNPSET5_ECAP0_Pos            (20)                                              /*!< SCU_T::PNPSET5: ECAP0 Position         */
#define SCU_PNPSET5_ECAP0_Msk            (0x1ul << SCU_PNPSET5_ECAP0_Pos)                  /*!< SCU_T::PNPSET5: ECAP0 Mask             */

#define SCU_PNPSET5_ECAP1_Pos            (21)                                              /*!< SCU_T::PNPSET5: ECAP1 Position         */
#define SCU_PNPSET5_ECAP1_Msk            (0x1ul << SCU_PNPSET5_ECAP1_Pos)                  /*!< SCU_T::PNPSET5: ECAP1 Mask             */

#define SCU_PNPSET5_TRNG_Pos             (25)                                              /*!< SCU_T::PNPSET5: TRNG Position          */
#define SCU_PNPSET5_TRNG_Msk             (0x1ul << SCU_PNPSET5_TRNG_Pos)                   /*!< SCU_T::PNPSET5: TRNG Mask              */

#define SCU_PNPSET5_LCD_Pos              (27)                                              /*!< SCU_T::PNPSET5: LCD Position           */
#define SCU_PNPSET5_LCD_Msk              (0x1ul << SCU_PNPSET5_LCD_Pos)                    /*!< SCU_T::PNPSET5: LCD Mask               */

#define SCU_PNPSET5_TAMPER_Pos           (29)                                              /*!< SCU_T::PNPSET5: TAMPER Position        */
#define SCU_PNPSET5_TAMPER_Msk           (0x1ul << SCU_PNPSET5_TAMPER_Pos)                 /*!< SCU_T::PNPSET5: TAMPER Mask            */

#define SCU_PNPSET6_USBD_Pos             (0)                                               /*!< SCU_T::PNPSET6: USBD Position          */
#define SCU_PNPSET6_USBD_Msk             (0x1ul << SCU_PNPSET6_USBD_Pos)                   /*!< SCU_T::PNPSET6: USBD Mask              */

#define SCU_PNPSET6_USCI0_Pos            (16)                                              /*!< SCU_T::PNPSET6: USCI0 Position         */
#define SCU_PNPSET6_USCI0_Msk            (0x1ul << SCU_PNPSET6_USCI0_Pos)                  /*!< SCU_T::PNPSET6: USCI0 Mask             */

#define SCU_PNPSET6_USCI1_Pos            (17)                                              /*!< SCU_T::PNPSET6: USCI1 Position         */
#define SCU_PNPSET6_USCI1_Msk            (0x1ul << SCU_PNPSET6_USCI1_Pos)                  /*!< SCU_T::PNPSET6: USCI1 Mask             */

#define SCU_IONPSET_PA_Pos               (0)                                               /*!< SCU_T::IONPSET: PA Position            */
#define SCU_IONPSET_PA_Msk               (0x1ul << SCU_IONPSET_PA_Pos)                     /*!< SCU_T::IONPSET: PA Mask                */

#define SCU_IONPSET_PB_Pos               (1)                                               /*!< SCU_T::IONPSET: PB Position            */
#define SCU_IONPSET_PB_Msk               (0x1ul << SCU_IONPSET_PB_Pos)                     /*!< SCU_T::IONPSET: PB Mask                */

#define SCU_IONPSET_PC_Pos               (2)                                               /*!< SCU_T::IONPSET: PC Position            */
#define SCU_IONPSET_PC_Msk               (0x1ul << SCU_IONPSET_PC_Pos)                     /*!< SCU_T::IONPSET: PC Mask                */

#define SCU_IONPSET_PD_Pos               (3)                                               /*!< SCU_T::IONPSET: PD Position            */
#define SCU_IONPSET_PD_Msk               (0x1ul << SCU_IONPSET_PD_Pos)                     /*!< SCU_T::IONPSET: PD Mask                */

#define SCU_IONPSET_PE_Pos               (4)                                               /*!< SCU_T::IONPSET: PE Position            */
#define SCU_IONPSET_PE_Msk               (0x1ul << SCU_IONPSET_PE_Pos)                     /*!< SCU_T::IONPSET: PE Mask                */

#define SCU_IONPSET_PF_Pos               (5)                                               /*!< SCU_T::IONPSET: PF Position            */
#define SCU_IONPSET_PF_Msk               (0x1ul << SCU_IONPSET_PF_Pos)                     /*!< SCU_T::IONPSET: PF Mask                */

#define SCU_IONPSET_PG_Pos               (6)                                               /*!< SCU_T::IONPSET: PG Position            */
#define SCU_IONPSET_PG_Msk               (0x1ul << SCU_IONPSET_PG_Pos)                     /*!< SCU_T::IONPSET: PG Mask                */

#define SCU_IONPSET_PH_Pos               (7)                                               /*!< SCU_T::IONPSET: PH Position            */
#define SCU_IONPSET_PH_Msk               (0x1ul << SCU_IONPSET_PH_Pos)                     /*!< SCU_T::IONPSET: PH Mask                */

#define SCU_SRAMNPSET_SECn_Pos           (0)                                               /*!< SCU_T::SRAMNPSET: SECn Position        */
#define SCU_SRAMNPSET_SECn_Msk           (0xffffful << SCU_SRAMNPSET_SECn_Pos)             /*!< SCU_T::SRAMNPSET: SECn Mask            */

#define SCU_MEMNPSET_FLASH_Pos           (0)                                               /*!< SCU_T::MEMNPSET: FLASH Position        */
#define SCU_MEMNPSET_FLASH_Msk           (0x1ul << SCU_MEMNPSET_FLASH_Pos)                 /*!< SCU_T::MEMNPSET: FLASH Mask            */

#define SCU_MEMNPSET_EXTMEM_Pos          (1)                                               /*!< SCU_T::MEMNPSET: EXTMEM Position       */
#define SCU_MEMNPSET_EXTMEM_Msk          (0x1ul << SCU_MEMNPSET_EXTMEM_Pos)                /*!< SCU_T::MEMNPSET: EXTMEM Mask           */

#define SCU_PVIOIEN_APB0IEN_Pos          (0)                                               /*!< SCU_T::PVIOIEN: APB0IEN Position       */
#define SCU_PVIOIEN_APB0IEN_Msk          (0x1ul << SCU_PVIOIEN_APB0IEN_Pos)                /*!< SCU_T::PVIOIEN: APB0IEN Mask           */

#define SCU_PVIOIEN_APB1IEN_Pos          (1)                                               /*!< SCU_T::PVIOIEN: APB1IEN Position       */
#define SCU_PVIOIEN_APB1IEN_Msk          (0x1ul << SCU_PVIOIEN_APB1IEN_Pos)                /*!< SCU_T::PVIOIEN: APB1IEN Mask           */

#define SCU_PVIOIEN_GPIOIEN_Pos          (4)                                               /*!< SCU_T::PVIOIEN: GPIOIEN Position       */
#define SCU_PVIOIEN_GPIOIEN_Msk          (0x1ul << SCU_PVIOIEN_GPIOIEN_Pos)                /*!< SCU_T::PVIOIEN: GPIOIEN Mask           */

#define SCU_PVIOIEN_EBIIEN_Pos           (5)                                               /*!< SCU_T::PVIOIEN: EBIIEN Position        */
#define SCU_PVIOIEN_EBIIEN_Msk           (0x1ul << SCU_PVIOIEN_EBIIEN_Pos)                 /*!< SCU_T::PVIOIEN: EBIIEN Mask            */

#define SCU_PVIOIEN_USBHIEN_Pos          (6)                                               /*!< SCU_T::PVIOIEN: USBHIEN Position       */
#define SCU_PVIOIEN_USBHIEN_Msk          (0x1ul << SCU_PVIOIEN_USBHIEN_Pos)                /*!< SCU_T::PVIOIEN: USBHIEN Mask           */

#define SCU_PVIOIEN_CRCIEN_Pos           (7)                                               /*!< SCU_T::PVIOIEN: CRCIEN Position        */
#define SCU_PVIOIEN_CRCIEN_Msk           (0x1ul << SCU_PVIOIEN_CRCIEN_Pos)                 /*!< SCU_T::PVIOIEN: CRCIEN Mask            */

#define SCU_PVIOIEN_SDH0IEN_Pos          (8)                                               /*!< SCU_T::PVIOIEN: SDH0IEN Position       */
#define SCU_PVIOIEN_SDH0IEN_Msk          (0x1ul << SCU_PVIOIEN_SDH0IEN_Pos)                /*!< SCU_T::PVIOIEN: SDH0IEN Mask           */

#define SCU_PVIOIEN_PDMA0IEN_Pos         (10)                                              /*!< SCU_T::PVIOIEN: PDMA0IEN Position      */
#define SCU_PVIOIEN_PDMA0IEN_Msk         (0x1ul << SCU_PVIOIEN_PDMA0IEN_Pos)               /*!< SCU_T::PVIOIEN: PDMA0IEN Mask          */

#define SCU_PVIOIEN_PDMA1IEN_Pos         (11)                                              /*!< SCU_T::PVIOIEN: PDMA1IEN Position      */
#define SCU_PVIOIEN_PDMA1IEN_Msk         (0x1ul << SCU_PVIOIEN_PDMA1IEN_Pos)               /*!< SCU_T::PVIOIEN: PDMA1IEN Mask          */

#define SCU_PVIOIEN_SRAM0IEN_Pos         (12)                                              /*!< SCU_T::PVIOIEN: SRAM0IEN Position      */
#define SCU_PVIOIEN_SRAM0IEN_Msk         (0x1ul << SCU_PVIOIEN_SRAM0IEN_Pos)               /*!< SCU_T::PVIOIEN: SRAM0IEN Mask          */

#define SCU_PVIOIEN_SRAM1IEN_Pos         (13)                                              /*!< SCU_T::PVIOIEN: SRAM1IEN Position      */
#define SCU_PVIOIEN_SRAM1IEN_Msk         (0x1ul << SCU_PVIOIEN_SRAM1IEN_Pos)               /*!< SCU_T::PVIOIEN: SRAM1IEN Mask          */

#define SCU_PVIOIEN_FMCIEN_Pos           (14)                                              /*!< SCU_T::PVIOIEN: FMCIEN Position        */
#define SCU_PVIOIEN_FMCIEN_Msk           (0x1ul << SCU_PVIOIEN_FMCIEN_Pos)                 /*!< SCU_T::PVIOIEN: FMCIEN Mask            */

#define SCU_PVIOIEN_FLASHIEN_Pos         (15)                                              /*!< SCU_T::PVIOIEN: FLASHIEN Position      */
#define SCU_PVIOIEN_FLASHIEN_Msk         (0x1ul << SCU_PVIOIEN_FLASHIEN_Pos)               /*!< SCU_T::PVIOIEN: FLASHIEN Mask          */

#define SCU_PVIOIEN_SCUIEN_Pos           (16)                                              /*!< SCU_T::PVIOIEN: SCUIEN Position        */
#define SCU_PVIOIEN_SCUIEN_Msk           (0x1ul << SCU_PVIOIEN_SCUIEN_Pos)                 /*!< SCU_T::PVIOIEN: SCUIEN Mask            */

#define SCU_PVIOIEN_SYSIEN_Pos           (17)                                              /*!< SCU_T::PVIOIEN: SYSIEN Position        */
#define SCU_PVIOIEN_SYSIEN_Msk           (0x1ul << SCU_PVIOIEN_SYSIEN_Pos)                 /*!< SCU_T::PVIOIEN: SYSIEN Mask            */

#define SCU_PVIOIEN_CRPTIEN_Pos          (18)                                              /*!< SCU_T::PVIOIEN: CRPTIEN Position       */
#define SCU_PVIOIEN_CRPTIEN_Msk          (0x1ul << SCU_PVIOIEN_CRPTIEN_Pos)                /*!< SCU_T::PVIOIEN: CRPTIEN Mask           */

#define SCU_PVIOIEN_KSIEN_Pos            (19)                                              /*!< SCU_T::PVIOIEN: KSIEN Position         */
#define SCU_PVIOIEN_KSIEN_Msk            (0x1ul << SCU_PVIOIEN_KSIEN_Pos)                  /*!< SCU_T::PVIOIEN: KSIEN Mask             */

#define SCU_PVINTSTS_APB0IF_Pos          (0)                                               /*!< SCU_T::PVINTSTS: APB0IF Position       */
#define SCU_PVINTSTS_APB0IF_Msk          (0x1ul << SCU_PVINTSTS_APB0IF_Pos)                /*!< SCU_T::PVINTSTS: APB0IF Mask           */

#define SCU_PVINTSTS_APB1IF_Pos          (1)                                               /*!< SCU_T::PVINTSTS: APB1IF Position       */
#define SCU_PVINTSTS_APB1IF_Msk          (0x1ul << SCU_PVINTSTS_APB1IF_Pos)                /*!< SCU_T::PVINTSTS: APB1IF Mask           */

#define SCU_PVINTSTS_GPIOIF_Pos          (4)                                               /*!< SCU_T::PVINTSTS: GPIOIF Position       */
#define SCU_PVINTSTS_GPIOIF_Msk          (0x1ul << SCU_PVINTSTS_GPIOIF_Pos)                /*!< SCU_T::PVINTSTS: GPIOIF Mask           */

#define SCU_PVINTSTS_EBIIF_Pos           (5)                                               /*!< SCU_T::PVINTSTS: EBIIF Position        */
#define SCU_PVINTSTS_EBIIF_Msk           (0x1ul << SCU_PVINTSTS_EBIIF_Pos)                 /*!< SCU_T::PVINTSTS: EBIIF Mask            */

#define SCU_PVINTSTS_USBHIF_Pos          (6)                                               /*!< SCU_T::PVINTSTS: USBHIF Position       */
#define SCU_PVINTSTS_USBHIF_Msk          (0x1ul << SCU_PVINTSTS_USBHIF_Pos)                /*!< SCU_T::PVINTSTS: USBHIF Mask           */

#define SCU_PVINTSTS_CRCIF_Pos           (7)                                               /*!< SCU_T::PVINTSTS: CRCIF Position        */
#define SCU_PVINTSTS_CRCIF_Msk           (0x1ul << SCU_PVINTSTS_CRCIF_Pos)                 /*!< SCU_T::PVINTSTS: CRCIF Mask            */

#define SCU_PVINTSTS_SDH0IF_Pos          (8)                                               /*!< SCU_T::PVINTSTS: SDH0IF Position       */
#define SCU_PVINTSTS_SDH0IF_Msk          (0x1ul << SCU_PVINTSTS_SDH0IF_Pos)                /*!< SCU_T::PVINTSTS: SDH0IF Mask           */

#define SCU_PVINTSTS_PDMA0IF_Pos         (10)                                              /*!< SCU_T::PVINTSTS: PDMA0IF Position      */
#define SCU_PVINTSTS_PDMA0IF_Msk         (0x1ul << SCU_PVINTSTS_PDMA0IF_Pos)               /*!< SCU_T::PVINTSTS: PDMA0IF Mask          */

#define SCU_PVINTSTS_PDMA1IF_Pos         (11)                                              /*!< SCU_T::PVINTSTS: PDMA1IF Position      */
#define SCU_PVINTSTS_PDMA1IF_Msk         (0x1ul << SCU_PVINTSTS_PDMA1IF_Pos)               /*!< SCU_T::PVINTSTS: PDMA1IF Mask          */

#define SCU_PVINTSTS_SRAM0IF_Pos         (12)                                              /*!< SCU_T::PVINTSTS: SRAM0IF Position      */
#define SCU_PVINTSTS_SRAM0IF_Msk         (0x1ul << SCU_PVINTSTS_SRAM0IF_Pos)               /*!< SCU_T::PVINTSTS: SRAM0IF Mask          */

#define SCU_PVINTSTS_SRAM1IF_Pos         (13)                                              /*!< SCU_T::PVINTSTS: SRAM1IF Position      */
#define SCU_PVINTSTS_SRAM1IF_Msk         (0x1ul << SCU_PVINTSTS_SRAM1IF_Pos)               /*!< SCU_T::PVINTSTS: SRAM1IF Mask          */

#define SCU_PVINTSTS_FMCIF_Pos           (14)                                              /*!< SCU_T::PVINTSTS: FMCIF Position        */
#define SCU_PVINTSTS_FMCIF_Msk           (0x1ul << SCU_PVINTSTS_FMCIF_Pos)                 /*!< SCU_T::PVINTSTS: FMCIF Mask            */

#define SCU_PVINTSTS_FLASHIF_Pos         (15)                                              /*!< SCU_T::PVINTSTS: FLASHIF Position      */
#define SCU_PVINTSTS_FLASHIF_Msk         (0x1ul << SCU_PVINTSTS_FLASHIF_Pos)               /*!< SCU_T::PVINTSTS: FLASHIF Mask          */

#define SCU_PVINTSTS_SCUIF_Pos           (16)                                              /*!< SCU_T::PVINTSTS: SCUIF Position        */
#define SCU_PVINTSTS_SCUIF_Msk           (0x1ul << SCU_PVINTSTS_SCUIF_Pos)                 /*!< SCU_T::PVINTSTS: SCUIF Mask            */

#define SCU_PVINTSTS_SYSIF_Pos           (17)                                              /*!< SCU_T::PVINTSTS: SYSIF Position        */
#define SCU_PVINTSTS_SYSIF_Msk           (0x1ul << SCU_PVINTSTS_SYSIF_Pos)                 /*!< SCU_T::PVINTSTS: SYSIF Mask            */

#define SCU_PVINTSTS_CRPTIF_Pos          (18)                                              /*!< SCU_T::PVINTSTS: CRPTIF Position       */
#define SCU_PVINTSTS_CRPTIF_Msk          (0x1ul << SCU_PVINTSTS_CRPTIF_Pos)                /*!< SCU_T::PVINTSTS: CRPTIF Mask           */

#define SCU_PVINTSTS_KSIF_Pos            (19)                                              /*!< SCU_T::PVINTSTS: KSIF Position         */
#define SCU_PVINTSTS_KSIF_Msk            (0x1ul << SCU_PVINTSTS_KSIF_Pos)                  /*!< SCU_T::PVINTSTS: KSIF Mask             */

#define SCU_NSMCTL_PRESCALE_Pos          (0)                                               /*!< SCU_T::NSMCTL: PRESCALE Position       */
#define SCU_NSMCTL_PRESCALE_Msk          (0xfful << SCU_NSMCTL_PRESCALE_Pos)               /*!< SCU_T::NSMCTL: PRESCALE Mask           */

#define SCU_NSMCTL_NSMIEN_Pos            (8)                                               /*!< SCU_T::NSMCTL: NSMIEN Position         */
#define SCU_NSMCTL_NSMIEN_Msk            (0x1ul << SCU_NSMCTL_NSMIEN_Pos)                  /*!< SCU_T::NSMCTL: NSMIEN Mask             */

#define SCU_NSMCTL_AUTORLD_Pos           (9)                                               /*!< SCU_T::NSMCTL: AUTORLD Position        */
#define SCU_NSMCTL_AUTORLD_Msk           (0x1ul << SCU_NSMCTL_AUTORLD_Pos)                 /*!< SCU_T::NSMCTL: AUTORLD Mask            */

#define SCU_NSMCTL_TMRMOD_Pos            (10)                                              /*!< SCU_T::NSMCTL: TMRMOD Position         */
#define SCU_NSMCTL_TMRMOD_Msk            (0x1ul << SCU_NSMCTL_TMRMOD_Pos)                  /*!< SCU_T::NSMCTL: TMRMOD Mask             */

#define SCU_NSMCTL_IDLEON_Pos            (12)                                              /*!< SCU_T::NSMCTL: IDLEON Position         */
#define SCU_NSMCTL_IDLEON_Msk            (0x1ul << SCU_NSMCTL_IDLEON_Pos)                  /*!< SCU_T::NSMCTL: IDLEON Mask             */

#define SCU_NSMCTL_DBGON_Pos             (13)                                              /*!< SCU_T::NSMCTL: DBGON Position          */
#define SCU_NSMCTL_DBGON_Msk             (0x1ul << SCU_NSMCTL_DBGON_Pos)                   /*!< SCU_T::NSMCTL: DBGON Mask              */

#define SCU_NSMLOAD_RELOAD_Pos           (0)                                               /*!< SCU_T::NSMLOAD: RELOAD Position        */
#define SCU_NSMLOAD_RELOAD_Msk           (0xfffffful << SCU_NSMLOAD_RELOAD_Pos)            /*!< SCU_T::NSMLOAD: RELOAD Mask            */

#define SCU_NSMVAL_VALUE_Pos             (0)                                               /*!< SCU_T::NSMVAL: VALUE Position          */
#define SCU_NSMVAL_VALUE_Msk             (0xfffffful << SCU_NSMVAL_VALUE_Pos)              /*!< SCU_T::NSMVAL: VALUE Mask              */

#define SCU_NSMSTS_CURRNS_Pos            (0)                                               /*!< SCU_T::NSMSTS: CURRNS Position         */
#define SCU_NSMSTS_CURRNS_Msk            (0x1ul << SCU_NSMSTS_CURRNS_Pos)                  /*!< SCU_T::NSMSTS: CURRNS Mask             */

#define SCU_NSMSTS_NSMIF_Pos             (1)                                               /*!< SCU_T::NSMSTS: NSMIF Position          */
#define SCU_NSMSTS_NSMIF_Msk             (0x1ul << SCU_NSMSTS_NSMIF_Pos)                   /*!< SCU_T::NSMSTS: NSMIF Mask              */

#define SCU_BBE_BBEEN_Pos                (0)                                               /*!< SCU_T::BBE: BBEEN Position             */
#define SCU_BBE_BBEEN_Msk                (0x1ul << SCU_BBE_BBEEN_Pos)                      /*!< SCU_T::BBE: BBEEN Mask                 */

#define SCU_BBE_WVERY_Pos                (8)                                               /*!< SCU_T::BBE: WVERY Position             */
#define SCU_BBE_WVERY_Msk                (0xfffffful << SCU_BBE_WVERY_Pos)                 /*!< SCU_T::BBE: WVERY Mask                 */

#define SCU_IDAUANS_IDAUANSEN_Pos        (0)                                               /*!< SCU_T::IDAUANS: IDAUANSEN Position     */
#define SCU_IDAUANS_IDAUANSEN_Msk        (0x1ul << SCU_IDAUANS_IDAUANSEN_Pos)              /*!< SCU_T::IDAUANS: IDAUANSEN Mask         */

#define SCU_IDAUANS_WVERY_Pos            (8)                                               /*!< SCU_T::IDAUANS: WVERY Position         */
#define SCU_IDAUANS_WVERY_Msk            (0xfffffful << SCU_IDAUANS_WVERY_Pos)             /*!< SCU_T::IDAUANS: WVERY Mask             */

#define SCU_VERSION_MINOR_Pos            (0)                                               /*!< SCU_T::VERSION: MINOR Position         */
#define SCU_VERSION_MINOR_Msk            (0xfffful << SCU_VERSION_MINOR_Pos)               /*!< SCU_T::VERSION: MINOR Mask             */

#define SCU_VERSION_SUB_Pos              (16)                                              /*!< SCU_T::VERSION: SUB Position           */
#define SCU_VERSION_SUB_Msk              (0xfful << SCU_VERSION_SUB_Pos)                   /*!< SCU_T::VERSION: SUB Mask               */

#define SCU_VERSION_MAJOR_Pos            (24)                                              /*!< SCU_T::VERSION: MAJOR Position         */
#define SCU_VERSION_MAJOR_Msk            (0xfful << SCU_VERSION_MAJOR_Pos)                 /*!< SCU_T::VERSION: MAJOR Mask             */

/**@}*/ /* SCU_CONST */
/**@}*/ /* end of SCU register group */


/**@}*/ /* end of REGISTER group */
#endif /* __SCU_REG_H__ */
