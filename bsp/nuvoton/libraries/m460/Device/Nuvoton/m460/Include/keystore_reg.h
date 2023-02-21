/**************************************************************************//**
 * @file     keystore_reg.h
 * @version  V1.00
 * @brief    Key store register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __KEYSTORE_REG_H__
#define __KEYSTORE_REG_H__


/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Key Store -------------------------*/
/**
    @addtogroup KS Key Store(KS)
    Memory Mapped Structure for KS Controller
@{ */

typedef struct
{


    /**
     * @var KS_T::CTL
     * Offset: 0x00  Key Store Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |Key Store Start Control Bit
     * |        |          |0 = No operation.
     * |        |          |1 = Start the operation.
     * |[3:1]   |OPMODE    |Key Store Operation Mode
     * |        |          |000 = Read operation.
     * |        |          |001 = Create operation.
     * |        |          |010 = Erase one key operation (only for key is in SRAM and OTP).
     * |        |          |011 = Erase all keys operation (only for SRAM and Flash).
     * |        |          |100 = Revoke key operation.
     * |        |          |101 = Data Remanence prevention operation (only for SRAM).
     * |        |          |111 = Lock operation (only for OTP).
     * |        |          |Others = reserved.
     * |[7]     |CONT      |Read/Write Key Continue Bit
     * |        |          |0 = Read/Write key operation is not continuous to previous operation.
     * |        |          |1 = Read/Write key operation is continuous to previous operation.
     * |[8]     |INIT      |Key Store Initialization
     * |        |          |User should to check BUSY(KS_STS[2]) is 0, and then write 1 to this bit and START(KS_CTL[0[), the Key Store will start to be initializationed.
     * |        |          |After Key Store is initialized, INIT will be cleared.
     * |        |          |Note: Before executing INIT, user must to checks KS(SYS_SRAMPC1) is 00.
     * |[15]    |IEN       |Key Store Interrupt Enable Bit
     * |        |          |0 = Key Store Interrupt Disabled.
     * |        |          |1 = Key Store Interrupt Enabled.
     * @var KS_T::METADATA
     * Offset: 0x04  Key Store Metadata Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SEC       |Secure Key Selection Bit
     * |        |          |0 = Set key as the non-secure key.
     * |        |          |1 = Set key as the secure key.
     * |[1]     |PRIV      |Privilege Key Selection Bit
     * |        |          |0 = Set key as the non-privilege key.
     * |        |          |1 = Set key as the privilege key.
     * |[2]     |READABLE  |Key Readable Control Bit
     * |        |          |0 = key is un-readable.
     * |        |          |1 = key is readable.
     * |[4]     |BS        |Booting State Selection Bit
     * |        |          |0 = Set key used at all state.
     * |        |          |1 = Set key used at boot loader state 1 (BL1 state).
     * |[12:8]  |SIZE      |Key Size Selection Bits
     * |        |          |00000 = 128 bits.
     * |        |          |00001 = 163 bits.
     * |        |          |00010 = 192 bits.
     * |        |          |00011 = 224 bits.
     * |        |          |00100 = 233 bits.
     * |        |          |00101 = 255 bits.
     * |        |          |00110 = 256 bits.
     * |        |          |00111 = 283 bits.
     * |        |          |01000 = 384 bits.
     * |        |          |01001 = 409 bits.
     * |        |          |01010 = 512 bits.
     * |        |          |01011 = 521 bits.
     * |        |          |01100 = 571 bits.
     * |        |          |10000 = 1024 bits.
     * |        |          |10001 = 1536 bits.
     * |        |          |10010 = 2048 bits.
     * |        |          |10011 = 3072 bits.
     * |        |          |10100 = 4096 bits.
     * |        |          |Others = reserved.
     * |[18:16] |OWNER     |Key Owner Selection Bits
     * |        |          |000 = AES
     * |        |          |001 = HMAC
     * |        |          |010 = RSA exponent blind key for SCAP(CRYPTO_RSA_CTL[8]) = 1 and CRT(CRYPTO_RSA_CTL[2]) = 0
     * |        |          |011 = RSA middle data, p, q and private key.
     * |        |          |100 = ECC.
     * |        |          |101 = CPU.
     * |        |          |Others = reserved.
     * |[25:20] |NUMBER    |Key Number
     * |        |          |Before read or erase one key operation starts, user should write the key number to be operated
     * |        |          |When create operation is finished, user can read these bits to get its key number.
     * |[31:30] |DST       |Key Location Selection Bits
     * |        |          |00 = Key is in SRAM.
     * |        |          |01 = Key is in Flash.
     * |        |          |10 = Key is in OTP.
     * |        |          |Others = reserved.
     * @var KS_T::STS
     * Offset: 0x08  Key Store Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |IF        |Key Store Finish Interrupt Flag
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No Key Store interrupt.
     * |        |          |1 = Key Store operation done interrupt.
     * |[1]     |EIF       |Key Store Error Flag
     * |        |          |This bit is cleared by writing 1 and it has no effect by writing 0.
     * |        |          |0 = No Key Store error.
     * |        |          |1 = Key Store error interrupt.
     * |[2]     |BUSY      |Key Store Busy Flag (read only)
     * |        |          |0 = Key Store is idle or finished.
     * |        |          |1 = Key Store is busy.
     * |[3]     |SRAMFULL  |Key Storage at SRAM Full Status Bit (read only)
     * |        |          |0 = Key Storage at SRAM is not full.
     * |        |          |1 = Key Storage at SRAM is full.
     * |[4]     |FLASHFULL |Key Storage at Flash Full Status Bit (read only)
     * |        |          |0 = Key Storage at Flash is not full.
     * |        |          |1 = Key Storage at Flash is full.
     * |[7]     |INITDONE  |Key Store Initialization Done Status (read only)
     * |        |          |0 = Key Store is un-initialized.
     * |        |          |1 = Key Store is initialized.
     * |[8]     |RAMINV    |Key Store SRAM Invert Status (read only)
     * |        |          |0 = Key Store key in SRAM is normal.
     * |        |          |1 = Key Store key in SRAM is inverted.
     * @var KS_T::REMAIN
     * Offset: 0x0C  Key Store Remaining Space Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[12:0]  |RRMNG     |Key Store SRAM Remaining Space
     * |        |          |The RRMNG shows the remaining byte count space for SRAM.
     * |[28:16] |FRMNG     |Key Store Flash Remaining Space
     * |        |          |The FRMNG shows the remaining byte count space for Flash.
     * @var KS_T::KEY0
     * Offset: 0x20  Key Store Entry Key Word 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::KEY1
     * Offset: 0x24  Key Store Entry Key Word 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::KEY2
     * Offset: 0x28  Key Store Entry Key Word 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::KEY3
     * Offset: 0x2C  Key Store Entry Key Word 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::KEY4
     * Offset: 0x30  Key Store Entry Key Word 4 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::KEY5
     * Offset: 0x34  Key Store Entry Key Word 5 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::KEY6
     * Offset: 0x38  Key Store Entry Key Word 6 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::KEY7
     * Offset: 0x3C  Key Store Entry Key Word 7 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Key Data
     * |        |          |The register will be cleared if the Key Store executes the write operation or CPU completes the reading key.
     * @var KS_T::OTPSTS
     * Offset: 0x40  Key Store OTP Keys Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |KEY0      |OTP Key 0 Used Status
     * |        |          |0 = OTP key 0 is unused.
     * |        |          |1 = OTP key 0 is used.
     * |        |          |Note: If chip is in RMA stage, this bit will set to 1 and key is revoked after initialization if key is existed.Note: If chip is changed to RMA stage, the existing key will be revoked after initialization.
     * |[1]     |KEY1      |OTP Key 1 Used Status
     * |        |          |0 = OTP key 1 is unused.
     * |        |          |1 = OTP key 1 is used.
     * |        |          |Note: If chip is in RMA stage, this bit will set to 1 and key is revoked after initialization if key is existed.Note: If chip is changed to RMA stage, the existing key will be revoked after initialization.
     * |[2]     |KEY2      |OTP Key 2 Used Status
     * |        |          |0 = OTP key 2 is unused.
     * |        |          |1 = OTP key 2 is used.
     * |        |          |Note: If chip is in RMA stage, this bit will set to 1 and key is revoked after initialization if key is existed.Note: If chip is changed to RMA stage, the existing key will be revoked after initialization.
     * |[3]     |KEY3      |OTP Key 3 Used Status
     * |        |          |0 = OTP key 3 is unused.
     * |        |          |1 = OTP key 3 is used.
     * |        |          |Note: If chip is in RMA stage, this bit will set to 1 and key is revoked after initialization if key is existed.Note: If chip is changed to RMA stage, the existing key will be revoked after initialization.
     * |[4]     |KEY4      |OTP Key 4 Used Status
     * |        |          |0 = OTP key 4 is unused.
     * |        |          |1 = OTP key 4 is used.
     * |        |          |Note: If chip is in RMA stage, this bit will set to 1 and key is revoked after initialization if key is existed.Note: If chip is changed to RMA stage, existing key will be revoked after initialization.
     * |[5]     |KEY5      |OTP Key 5 Used Status
     * |        |          |0 = OTP key 5 is unused.
     * |        |          |1 = OTP key 5 is used.
     * |        |          |Note: If chip is in RMA stage, this bit will set to 1 and key is revoked after initialization if key is existed.Note: If chip is changed to RMA stage, the existing key will be revoked after initialization.
     * |[6]     |KEY6      |OTP Key 6 Used Status
     * |        |          |0 = OTP key 6 is unused.
     * |        |          |1 = OTP key 6 is used.
     * |        |          |Note: If chip is in RMA stage, this bit will set to 1 and key is revoked after initialization if key is existed.Note: If chip is changed to RMA stage, the existing key will be revoked after initialization.
     * |[7]     |KEY7      |OTP Key 7 Used Status
     * |        |          |0 = OTP key 7 is unused.
     * |        |          |1 = OTP key 7 is used.
     * |        |          |Note: If chip is inchanged to RMA stage, this bit will set to 1 and key is revoked after initialization if key is existedthe existing key will be revoked after initialization.
     * @var KS_T::REMKCNT
     * Offset: 0x44  Key Store Remaining Key Count Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |RRMKCNT   |Key Store SRAM Remaining Key Count
     * |        |          |The RRMKCNT shows the remaining key count for SRAM.
     * |[21:16] |FRMKCNT   |Key Store Flash Remaining Key Count
     * |        |          |The FRMKCNT shows the remaining key count for Flash.
     * @var KS_T::VERSION
     * Offset: 0xFFC  Key Store RTL Design Version Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MINOR     |RTL Design Minor Version Number
     * |        |          |Minor version number is dependent on moduleu2019s ECO version control.
     * |        |          |0x0000 (Current Minor Version Number)
     * |[23:16] |SUB       |RTL Design Sub Version Number
     * |        |          |Sub version number is correlated to moduleu2019s key feature.
     * |        |          |0x01 (Current Sub Version Number)
     * |[31:24] |MAJOR     |RTL Design Major Version Number
     * |        |          |Major version number is correlated to Product Line.
     * |        |          |0x021 (Current Major Version Number)
     */
    __IO uint32_t CTL;                   /*!< [0x0000] Key Store Control Register                                       */
    __IO uint32_t METADATA;              /*!< [0x0004] Key Store Metadata Register                                      */
    __IO uint32_t STS;                   /*!< [0x0008] Key Store Status Register                                        */
    __I  uint32_t REMAIN;                /*!< [0x000c] Key Store Remaining Space Register                               */
    __I  uint32_t RESERVE0[4];
    __IO uint32_t KEY[8];                /*!< [0x0020-0x003c] Key Store Entry Key Word 0 Register                              */
    __I  uint32_t OTPSTS;                /*!< [0x0040] Key Store OTP Keys Status Register                               */
    __I  uint32_t REMKCNT;               /*!< [0x0044] Key Store Remaining Key Count Register                           */
    __I  uint32_t RESERVE1[1005];
    __I  uint32_t VERSION;               /*!< [0x0ffc] Key Store RTL Design Version Register                            */

} KS_T;

/**
    @addtogroup KS_CONST KS Bit Field Definition
    Constant Definitions for KS Controller
@{ */

#define KS_CTL_START_Pos                 (0)                                               /*!< KS_T::CTL: START Position              */
#define KS_CTL_START_Msk                 (0x1ul << KS_CTL_START_Pos)                       /*!< KS_T::CTL: START Mask                  */

#define KS_CTL_OPMODE_Pos                (1)                                               /*!< KS_T::CTL: OPMODE Position             */
#define KS_CTL_OPMODE_Msk                (0x7ul << KS_CTL_OPMODE_Pos)                      /*!< KS_T::CTL: OPMODE Mask                 */

#define KS_CTL_CONT_Pos                  (7)                                               /*!< KS_T::CTL: CONT Position               */
#define KS_CTL_CONT_Msk                  (0x1ul << KS_CTL_CONT_Pos)                        /*!< KS_T::CTL: CONT Mask                   */

#define KS_CTL_INIT_Pos                  (8)                                               /*!< KS_T::CTL: INIT Position               */
#define KS_CTL_INIT_Msk                  (0x1ul << KS_CTL_INIT_Pos)                        /*!< KS_T::CTL: INIT Mask                   */

#define KS_CTL_IEN_Pos                   (15)                                              /*!< KS_T::CTL: IEN Position                */
#define KS_CTL_IEN_Msk                   (0x1ul << KS_CTL_IEN_Pos)                         /*!< KS_T::CTL: IEN Mask                    */

#define KS_METADATA_SEC_Pos              (0)                                               /*!< KS_T::METADATA: SEC Position           */
#define KS_METADATA_SEC_Msk              (0x1ul << KS_METADATA_SEC_Pos)                    /*!< KS_T::METADATA: SEC Mask               */

#define KS_METADATA_PRIV_Pos             (1)                                               /*!< KS_T::METADATA: PRIV Position          */
#define KS_METADATA_PRIV_Msk             (0x1ul << KS_METADATA_PRIV_Pos)                   /*!< KS_T::METADATA: PRIV Mask              */

#define KS_METADATA_READABLE_Pos         (2)                                               /*!< KS_T::METADATA: READABLE Position      */
#define KS_METADATA_READABLE_Msk         (0x1ul << KS_METADATA_READABLE_Pos)               /*!< KS_T::METADATA: READABLE Mask          */

#define KS_METADATA_BS_Pos               (4)                                               /*!< KS_T::METADATA: BS Position            */
#define KS_METADATA_BS_Msk               (0x1ul << KS_METADATA_BS_Pos)                     /*!< KS_T::METADATA: BS Mask                */

#define KS_METADATA_SIZE_Pos             (8)                                               /*!< KS_T::METADATA: SIZE Position          */
#define KS_METADATA_SIZE_Msk             (0x1ful << KS_METADATA_SIZE_Pos)                  /*!< KS_T::METADATA: SIZE Mask              */

#define KS_METADATA_OWNER_Pos            (16)                                              /*!< KS_T::METADATA: OWNER Position         */
#define KS_METADATA_OWNER_Msk            (0x7ul << KS_METADATA_OWNER_Pos)                  /*!< KS_T::METADATA: OWNER Mask             */

#define KS_METADATA_NUMBER_Pos           (20)                                              /*!< KS_T::METADATA: NUMBER Position        */
#define KS_METADATA_NUMBER_Msk           (0x3ful << KS_METADATA_NUMBER_Pos)                /*!< KS_T::METADATA: NUMBER Mask            */

#define KS_METADATA_DST_Pos              (30)                                              /*!< KS_T::METADATA: DST Position           */
#define KS_METADATA_DST_Msk              (0x3ul << KS_METADATA_DST_Pos)                    /*!< KS_T::METADATA: DST Mask               */

#define KS_STS_IF_Pos                    (0)                                               /*!< KS_T::STS: IF Position                 */
#define KS_STS_IF_Msk                    (0x1ul << KS_STS_IF_Pos)                          /*!< KS_T::STS: IF Mask                     */

#define KS_STS_EIF_Pos                   (1)                                               /*!< KS_T::STS: EIF Position                */
#define KS_STS_EIF_Msk                   (0x1ul << KS_STS_EIF_Pos)                         /*!< KS_T::STS: EIF Mask                    */

#define KS_STS_BUSY_Pos                  (2)                                               /*!< KS_T::STS: BUSY Position               */
#define KS_STS_BUSY_Msk                  (0x1ul << KS_STS_BUSY_Pos)                        /*!< KS_T::STS: BUSY Mask                   */

#define KS_STS_SRAMFULL_Pos              (3)                                               /*!< KS_T::STS: SRAMFULL Position           */
#define KS_STS_SRAMFULL_Msk              (0x1ul << KS_STS_SRAMFULL_Pos)                    /*!< KS_T::STS: SRAMFULL Mask               */

#define KS_STS_FLASHFULL_Pos             (4)                                               /*!< KS_T::STS: FLASHFULL Position          */
#define KS_STS_FLASHFULL_Msk             (0x1ul << KS_STS_FLASHFULL_Pos)                   /*!< KS_T::STS: FLASHFULL Mask              */

#define KS_STS_INITDONE_Pos              (7)                                               /*!< KS_T::STS: INITDONE Position           */
#define KS_STS_INITDONE_Msk              (0x1ul << KS_STS_INITDONE_Pos)                    /*!< KS_T::STS: INITDONE Mask               */

#define KS_STS_RAMINV_Pos                (8)                                               /*!< KS_T::STS: RAMINV Position             */
#define KS_STS_RAMINV_Msk                (0x1ul << KS_STS_RAMINV_Pos)                      /*!< KS_T::STS: RAMINV Mask                 */

#define KS_STS_KRVKF_Pos                 (9)                                               /*!< KS_T::STS: KRVKF Position             */
#define KS_STS_KRVKF_Msk                 (0x1ul << KS_STS_KRVKF_Pos)                      /*!< KS_T::STS: KRVKF Mask                 */

#define KS_REMAIN_RRMNG_Pos              (0)                                               /*!< KS_T::REMAIN: RRMNG Position           */
#define KS_REMAIN_RRMNG_Msk              (0x1ffful << KS_REMAIN_RRMNG_Pos)                 /*!< KS_T::REMAIN: RRMNG Mask               */

#define KS_REMAIN_FRMNG_Pos              (16)                                              /*!< KS_T::REMAIN: FRMNG Position           */
#define KS_REMAIN_FRMNG_Msk              (0x1ffful << KS_REMAIN_FRMNG_Pos)                 /*!< KS_T::REMAIN: FRMNG Mask               */

#define KS_KEY_KEY_Pos                   (0)                                               /*!< KS_T::KEY: KEY Position                */
#define KS_KEY_KEY_Msk                   (0xfffffffful << KS_KEY0_KEY_Pos)                 /*!< KS_T::KEY: KEY Mask                    */

#define KS_OTPSTS_KEY0_Pos               (0)                                               /*!< KS_T::OTPSTS: KEY0 Position            */
#define KS_OTPSTS_KEY0_Msk               (0x1ul << KS_OTPSTS_KEY0_Pos)                     /*!< KS_T::OTPSTS: KEY0 Mask                */

#define KS_OTPSTS_KEY1_Pos               (1)                                               /*!< KS_T::OTPSTS: KEY1 Position            */
#define KS_OTPSTS_KEY1_Msk               (0x1ul << KS_OTPSTS_KEY1_Pos)                     /*!< KS_T::OTPSTS: KEY1 Mask                */

#define KS_OTPSTS_KEY2_Pos               (2)                                               /*!< KS_T::OTPSTS: KEY2 Position            */
#define KS_OTPSTS_KEY2_Msk               (0x1ul << KS_OTPSTS_KEY2_Pos)                     /*!< KS_T::OTPSTS: KEY2 Mask                */

#define KS_OTPSTS_KEY3_Pos               (3)                                               /*!< KS_T::OTPSTS: KEY3 Position            */
#define KS_OTPSTS_KEY3_Msk               (0x1ul << KS_OTPSTS_KEY3_Pos)                     /*!< KS_T::OTPSTS: KEY3 Mask                */

#define KS_OTPSTS_KEY4_Pos               (4)                                               /*!< KS_T::OTPSTS: KEY4 Position            */
#define KS_OTPSTS_KEY4_Msk               (0x1ul << KS_OTPSTS_KEY4_Pos)                     /*!< KS_T::OTPSTS: KEY4 Mask                */

#define KS_OTPSTS_KEY5_Pos               (5)                                               /*!< KS_T::OTPSTS: KEY5 Position            */
#define KS_OTPSTS_KEY5_Msk               (0x1ul << KS_OTPSTS_KEY5_Pos)                     /*!< KS_T::OTPSTS: KEY5 Mask                */

#define KS_OTPSTS_KEY6_Pos               (6)                                               /*!< KS_T::OTPSTS: KEY6 Position            */
#define KS_OTPSTS_KEY6_Msk               (0x1ul << KS_OTPSTS_KEY6_Pos)                     /*!< KS_T::OTPSTS: KEY6 Mask                */

#define KS_OTPSTS_KEY7_Pos               (7)                                               /*!< KS_T::OTPSTS: KEY7 Position            */
#define KS_OTPSTS_KEY7_Msk               (0x1ul << KS_OTPSTS_KEY7_Pos)                     /*!< KS_T::OTPSTS: KEY7 Mask                */

#define KS_REMKCNT_RRMKCNT_Pos           (0)                                               /*!< KS_T::REMKCNT: RRMKCNT Position        */
#define KS_REMKCNT_RRMKCNT_Msk           (0x3ful << KS_REMKCNT_RRMKCNT_Pos)                /*!< KS_T::REMKCNT: RRMKCNT Mask            */

#define KS_REMKCNT_FRMKCNT_Pos           (16)                                              /*!< KS_T::REMKCNT: FRMKCNT Position        */
#define KS_REMKCNT_FRMKCNT_Msk           (0x3ful << KS_REMKCNT_FRMKCNT_Pos)                /*!< KS_T::REMKCNT: FRMKCNT Mask            */

#define KS_VERSION_MINOR_Pos             (0)                                               /*!< KS_T::VERSION: MINOR Position          */
#define KS_VERSION_MINOR_Msk             (0xfffful << KS_VERSION_MINOR_Pos)                /*!< KS_T::VERSION: MINOR Mask              */

#define KS_VERSION_SUB_Pos               (16)                                              /*!< KS_T::VERSION: SUB Position            */
#define KS_VERSION_SUB_Msk               (0xfful << KS_VERSION_SUB_Pos)                    /*!< KS_T::VERSION: SUB Mask                */

#define KS_VERSION_MAJOR_Pos             (24)                                              /*!< KS_T::VERSION: MAJOR Position          */
#define KS_VERSION_MAJOR_Msk             (0xfful << KS_VERSION_MAJOR_Pos)                  /*!< KS_T::VERSION: MAJOR Mask              */

/**@}*/ /* KS_CONST */
/**@}*/ /* end of KS register group */
/**@}*/ /* end of REGISTER group */

#endif /* __KEYSTORE_REG_H__ */
