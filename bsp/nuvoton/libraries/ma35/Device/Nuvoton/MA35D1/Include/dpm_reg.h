/**************************************************************************//**
 * @file     dpm_reg.h
 * @brief    DPM register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __DPM_REG_H__
#define __DPM_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/*---------------------- Debug Protection Mechanism -------------------------*/
/**
    @addtogroup DPM Debug Protection Mechanism(DPM)
    Memory Mapped Structure for DPM Controller
@{ */

typedef struct
{


    /**
     * @var DPM_T::A35SDS
     * Offset: 0x10  DPM A35 Secure Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::A35SNDS
     * Offset: 0x14  DPM A35 Secure Non-invasive Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::A35NSDS
     * Offset: 0x18  DPM A35 Non-secure Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::A35NSNDS
     * Offset: 0x1C  DPM A35 Non-secure Non-invasive Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::M4DS
     * Offset: 0x20  DPM M4 Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::M4NDS
     * Offset: 0x24  DPM M4 Non-invasive Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::EXTDS
     * Offset: 0x30  DPM External Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     * @var DPM_T::EXTTDS
     * Offset: 0x34  DPM External Tracing Debug State Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGDEN    |Debug State Register Enable Bit
     * |        |          |0 = Set the debug state to CLOSE state when current state is OPEN state.
     * |        |          |1 = Set the debug state to OPEN state when current state is CLOSE state.
     * |        |          |Note: if SINFAEN.SSPCC is set to high. This bit becomes read-only by Non-Secure software
     * |[1]     |ODIS      |Debug State OTP Disable Bit (Read Only)
     * |        |          |Indicate the Disable bit stored in OTP.
     * |[2]     |OLOCK     |Debug State OTP Lock Bit (Read Only)
     * |        |          |Indicate the Lock bit stored in OTP.
     * |[31:24] |VCODE     |Write Verify Code and Read Verify Code
     * |        |          |Read operation:
     * |        |          |0xA5 = The read access for DPM_CTL is correct.
     * |        |          |Others = The read access for DPM_CTL is incorrect.
     * |        |          |Write operation:
     * |        |          |0x5A = The write verify code, which is needed to do a valid write to DPM_CA35SDS.
     * |        |          |Others = Invalid write verify code.
     */
    __I  uint32_t RESERVE0[4];
    __IO uint32_t A35SDS;                /*!< [0x0010] DPM A35 Secure Debug State Register                              */
    __IO uint32_t A35SNDS;               /*!< [0x0014] DPM A35 Secure Non-invasive Debug State Register                 */
    __IO uint32_t A35NSDS;               /*!< [0x0018] DPM A35 Non-secure Debug State Register                          */
    __IO uint32_t A35NSNDS;              /*!< [0x001c] DPM A35 Non-secure Non-invasive Debug State Register             */
    __IO uint32_t M4DS;                  /*!< [0x0020] DPM M4 Debug State Register                                      */
    __IO uint32_t M4NDS;                 /*!< [0x0024] DPM M4 Non-invasive Debug State Register                         */
    __I  uint32_t RESERVE1[2];
    __IO uint32_t EXTDS;                 /*!< [0x0030] DPM External Debug State Register                                */
    __IO uint32_t EXTTDS;                /*!< [0x0034] DPM External Tracing Debug State Register                        */

} DPM_T;

/**
    @addtogroup DPM_CONST DPM Bit Field Definition
    Constant Definitions for DPM Controller
@{ */

#define DPM_A35SDS_REGDEN_Pos            (0)                                               /*!< DPM_T::A35SDS: REGDEN Position         */
#define DPM_A35SDS_REGDEN_Msk            (0x1ul << DPM_A35SDS_REGDEN_Pos)                  /*!< DPM_T::A35SDS: REGDEN Mask             */

#define DPM_A35SDS_ODIS_Pos              (1)                                               /*!< DPM_T::A35SDS: ODIS Position           */
#define DPM_A35SDS_ODIS_Msk              (0x1ul << DPM_A35SDS_ODIS_Pos)                    /*!< DPM_T::A35SDS: ODIS Mask               */

#define DPM_A35SDS_OLOCK_Pos             (2)                                               /*!< DPM_T::A35SDS: OLOCK Position          */
#define DPM_A35SDS_OLOCK_Msk             (0x1ul << DPM_A35SDS_OLOCK_Pos)                   /*!< DPM_T::A35SDS: OLOCK Mask              */

#define DPM_A35SDS_VCODE_Pos             (24)                                              /*!< DPM_T::A35SDS: VCODE Position          */
#define DPM_A35SDS_VCODE_Msk             (0xfful << DPM_A35SDS_VCODE_Pos)                  /*!< DPM_T::A35SDS: VCODE Mask              */

#define DPM_A35SNDS_REGDEN_Pos           (0)                                               /*!< DPM_T::A35SNDS: REGDEN Position        */
#define DPM_A35SNDS_REGDEN_Msk           (0x1ul << DPM_A35SNDS_REGDEN_Pos)                 /*!< DPM_T::A35SNDS: REGDEN Mask            */

#define DPM_A35SNDS_ODIS_Pos             (1)                                               /*!< DPM_T::A35SNDS: ODIS Position          */
#define DPM_A35SNDS_ODIS_Msk             (0x1ul << DPM_A35SNDS_ODIS_Pos)                   /*!< DPM_T::A35SNDS: ODIS Mask              */

#define DPM_A35SNDS_OLOCK_Pos            (2)                                               /*!< DPM_T::A35SNDS: OLOCK Position         */
#define DPM_A35SNDS_OLOCK_Msk            (0x1ul << DPM_A35SNDS_OLOCK_Pos)                  /*!< DPM_T::A35SNDS: OLOCK Mask             */

#define DPM_A35SNDS_VCODE_Pos            (24)                                              /*!< DPM_T::A35SNDS: VCODE Position         */
#define DPM_A35SNDS_VCODE_Msk            (0xfful << DPM_A35SNDS_VCODE_Pos)                 /*!< DPM_T::A35SNDS: VCODE Mask             */

#define DPM_A35NSDS_REGDEN_Pos           (0)                                               /*!< DPM_T::A35NSDS: REGDEN Position        */
#define DPM_A35NSDS_REGDEN_Msk           (0x1ul << DPM_A35NSDS_REGDEN_Pos)                 /*!< DPM_T::A35NSDS: REGDEN Mask            */

#define DPM_A35NSDS_ODIS_Pos             (1)                                               /*!< DPM_T::A35NSDS: ODIS Position          */
#define DPM_A35NSDS_ODIS_Msk             (0x1ul << DPM_A35NSDS_ODIS_Pos)                   /*!< DPM_T::A35NSDS: ODIS Mask              */

#define DPM_A35NSDS_OLOCK_Pos            (2)                                               /*!< DPM_T::A35NSDS: OLOCK Position         */
#define DPM_A35NSDS_OLOCK_Msk            (0x1ul << DPM_A35NSDS_OLOCK_Pos)                  /*!< DPM_T::A35NSDS: OLOCK Mask             */

#define DPM_A35NSDS_VCODE_Pos            (24)                                              /*!< DPM_T::A35NSDS: VCODE Position         */
#define DPM_A35NSDS_VCODE_Msk            (0xfful << DPM_A35NSDS_VCODE_Pos)                 /*!< DPM_T::A35NSDS: VCODE Mask             */

#define DPM_A35NSNDS_REGDEN_Pos          (0)                                               /*!< DPM_T::A35NSNDS: REGDEN Position       */
#define DPM_A35NSNDS_REGDEN_Msk          (0x1ul << DPM_A35NSNDS_REGDEN_Pos)                /*!< DPM_T::A35NSNDS: REGDEN Mask           */

#define DPM_A35NSNDS_ODIS_Pos            (1)                                               /*!< DPM_T::A35NSNDS: ODIS Position         */
#define DPM_A35NSNDS_ODIS_Msk            (0x1ul << DPM_A35NSNDS_ODIS_Pos)                  /*!< DPM_T::A35NSNDS: ODIS Mask             */

#define DPM_A35NSNDS_OLOCK_Pos           (2)                                               /*!< DPM_T::A35NSNDS: OLOCK Position        */
#define DPM_A35NSNDS_OLOCK_Msk           (0x1ul << DPM_A35NSNDS_OLOCK_Pos)                 /*!< DPM_T::A35NSNDS: OLOCK Mask            */

#define DPM_A35NSNDS_VCODE_Pos           (24)                                              /*!< DPM_T::A35NSNDS: VCODE Position        */
#define DPM_A35NSNDS_VCODE_Msk           (0xfful << DPM_A35NSNDS_VCODE_Pos)                /*!< DPM_T::A35NSNDS: VCODE Mask            */

#define DPM_M4DS_REGDEN_Pos              (0)                                               /*!< DPM_T::M4DS: REGDEN Position           */
#define DPM_M4DS_REGDEN_Msk              (0x1ul << DPM_M4DS_REGDEN_Pos)                    /*!< DPM_T::M4DS: REGDEN Mask               */

#define DPM_M4DS_ODIS_Pos                (1)                                               /*!< DPM_T::M4DS: ODIS Position             */
#define DPM_M4DS_ODIS_Msk                (0x1ul << DPM_M4DS_ODIS_Pos)                      /*!< DPM_T::M4DS: ODIS Mask                 */

#define DPM_M4DS_OLOCK_Pos               (2)                                               /*!< DPM_T::M4DS: OLOCK Position            */
#define DPM_M4DS_OLOCK_Msk               (0x1ul << DPM_M4DS_OLOCK_Pos)                     /*!< DPM_T::M4DS: OLOCK Mask                */

#define DPM_M4DS_VCODE_Pos               (24)                                              /*!< DPM_T::M4DS: VCODE Position            */
#define DPM_M4DS_VCODE_Msk               (0xfful << DPM_M4DS_VCODE_Pos)                    /*!< DPM_T::M4DS: VCODE Mask                */

#define DPM_M4NDS_REGDEN_Pos             (0)                                               /*!< DPM_T::M4NDS: REGDEN Position          */
#define DPM_M4NDS_REGDEN_Msk             (0x1ul << DPM_M4NDS_REGDEN_Pos)                   /*!< DPM_T::M4NDS: REGDEN Mask              */

#define DPM_M4NDS_ODIS_Pos               (1)                                               /*!< DPM_T::M4NDS: ODIS Position            */
#define DPM_M4NDS_ODIS_Msk               (0x1ul << DPM_M4NDS_ODIS_Pos)                     /*!< DPM_T::M4NDS: ODIS Mask                */

#define DPM_M4NDS_OLOCK_Pos              (2)                                               /*!< DPM_T::M4NDS: OLOCK Position           */
#define DPM_M4NDS_OLOCK_Msk              (0x1ul << DPM_M4NDS_OLOCK_Pos)                    /*!< DPM_T::M4NDS: OLOCK Mask               */

#define DPM_M4NDS_VCODE_Pos              (24)                                              /*!< DPM_T::M4NDS: VCODE Position           */
#define DPM_M4NDS_VCODE_Msk              (0xfful << DPM_M4NDS_VCODE_Pos)                   /*!< DPM_T::M4NDS: VCODE Mask               */

#define DPM_EXTDS_REGDEN_Pos             (0)                                               /*!< DPM_T::EXTDS: REGDEN Position          */
#define DPM_EXTDS_REGDEN_Msk             (0x1ul << DPM_EXTDS_REGDEN_Pos)                   /*!< DPM_T::EXTDS: REGDEN Mask              */

#define DPM_EXTDS_ODIS_Pos               (1)                                               /*!< DPM_T::EXTDS: ODIS Position            */
#define DPM_EXTDS_ODIS_Msk               (0x1ul << DPM_EXTDS_ODIS_Pos)                     /*!< DPM_T::EXTDS: ODIS Mask                */

#define DPM_EXTDS_OLOCK_Pos              (2)                                               /*!< DPM_T::EXTDS: OLOCK Position           */
#define DPM_EXTDS_OLOCK_Msk              (0x1ul << DPM_EXTDS_OLOCK_Pos)                    /*!< DPM_T::EXTDS: OLOCK Mask               */

#define DPM_EXTDS_VCODE_Pos              (24)                                              /*!< DPM_T::EXTDS: VCODE Position           */
#define DPM_EXTDS_VCODE_Msk              (0xfful << DPM_EXTDS_VCODE_Pos)                   /*!< DPM_T::EXTDS: VCODE Mask               */

#define DPM_EXTTDS_REGDEN_Pos            (0)                                               /*!< DPM_T::EXTTDS: REGDEN Position         */
#define DPM_EXTTDS_REGDEN_Msk            (0x1ul << DPM_EXTTDS_REGDEN_Pos)                  /*!< DPM_T::EXTTDS: REGDEN Mask             */

#define DPM_EXTTDS_ODIS_Pos              (1)                                               /*!< DPM_T::EXTTDS: ODIS Position           */
#define DPM_EXTTDS_ODIS_Msk              (0x1ul << DPM_EXTTDS_ODIS_Pos)                    /*!< DPM_T::EXTTDS: ODIS Mask               */

#define DPM_EXTTDS_OLOCK_Pos             (2)                                               /*!< DPM_T::EXTTDS: OLOCK Position          */
#define DPM_EXTTDS_OLOCK_Msk             (0x1ul << DPM_EXTTDS_OLOCK_Pos)                   /*!< DPM_T::EXTTDS: OLOCK Mask              */

#define DPM_EXTTDS_VCODE_Pos             (24)                                              /*!< DPM_T::EXTTDS: VCODE Position          */
#define DPM_EXTTDS_VCODE_Msk             (0xfful << DPM_EXTTDS_VCODE_Pos)                  /*!< DPM_T::EXTTDS: VCODE Mask              */

/**@}*/ /* DPM_CONST */
/**@}*/ /* end of DPM register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __DPM_REG_H__ */

