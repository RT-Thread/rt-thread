/**************************************************************************//**
 * @file     crypto_reg.h
 * @version  V1.00
 * @brief    CRYPTO register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CRYPTO_REG_H__
#define __CRYPTO_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/


/*---------------------- Cryptographic Accelerator -------------------------*/
/**
    @addtogroup CRPT Cryptographic Accelerator(CRPT)
    Memory Mapped Structure for CRPT Controller
@{ */

typedef struct
{


    /**
     * @var CRPT_T::INTEN
     * Offset: 0x00  Crypto Interrupt Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |AESIEN    |AES Interrupt Enable Bit
     * |        |          |0 = AES interrupt Disabled.
     * |        |          |1 = AES interrupt Enabled.
     * |        |          |Note: In DMA mode, an interrupt will be triggered when an amount of data set in AES_DMA_CNT is fed into the AES engine.
     * |        |          |In Non-DMA mode, an interrupt will be triggered when the AES engine finishes the operation.
     * |[1]     |AESEIEN   |AES Error Flag Enable Bit
     * |        |          |0 = AES error interrupt flag Disabled.
     * |        |          |1 = AES error interrupt flag Enabled.
     * |[16]    |PRNGIEN   |PRNG Interrupt Enable Bit
     * |        |          |0 = PRNG interrupt Disabled.
     * |        |          |1 = PRNG interrupt Enabled.
     * |[17]    |PRNGEIEN  |PRNG Error Flag Enable Bit
     * |        |          |0 = PRNG error interrupt flag Disabled.
     * |        |          |1 = PRNG error interrupt flag Enabled.
     * |[22]    |ECCIEN    |ECC Interrupt Enable Bit
     * |        |          |0 = ECC interrupt Disabled.
     * |        |          |1 = ECC interrupt Enabled.
     * |        |          |Note: In DMA mode, an interrupt will be triggered when an amount of data set in ECC_DMA_CNT is fed into the ECC engine
     * |        |          |In Non-DMA mode, an interrupt will be triggered when the ECC engine finishes the operation.
     * |[23]    |ECCEIEN   |ECC Error Interrupt Enable Bit
     * |        |          |0 = ECC error interrupt flag Disabled.
     * |        |          |1 = ECC error interrupt flag Enabled.
     * |[24]    |HMACIEN   |SHA/HMAC Interrupt Enable Bit
     * |        |          |0 = SHA/HMAC interrupt Disabled.
     * |        |          |1 = SHA/HMAC interrupt Enabled.
     * |        |          |Note: In DMA mode, an interrupt will be triggered when an amount of data set in HMAC_DMA_CNT is fed into the SHA/HMAC engine
     * |        |          |In Non-DMA mode, an interrupt will be triggered when the SHA/HMAC engine finishes the operation.
     * |[25]    |HMACEIEN  |SHA/HMAC Error Interrupt Enable Bit
     * |        |          |0 = SHA/HMAC error interrupt flag Disabled.
     * |        |          |1 = HMAC error interrupt flag Enabled.
     * |[30]    |RSAIEN    |RSA Interrupt Enable Bit
     * |        |          |0 = RSA interrupt Disabled.
     * |        |          |1 = RSA interrupt Enabled.
     * |[31]    |RSAEIEN   |RSA Error Interrupt Enable Bit
     * |        |          |0 = RSA error interrupt flag Disabled.
     * |        |          |1 = RSA error interrupt flag Enabled.
     * @var CRPT_T::INTSTS
     * Offset: 0x04  Crypto Interrupt Flag
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |AESIF     |AES Finish Interrupt Flag
     * |        |          |0 = No AES interrupt.
     * |        |          |1 = AES encryption/decryption done interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[1]     |AESEIF    |AES Error Flag
     * |        |          |0 = No AES error.
     * |        |          |1 = AES encryption/decryption error interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[16]    |PRNGIF    |PRNG Finish Interrupt Flag
     * |        |          |0 = No PRNG interrupt.
     * |        |          |1 = PRNG key generation done interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[17]    |PRNGEIF   |PRNG Error Flag
     * |        |          |0 = No PRNG error.
     * |        |          |1 = PRNG key generation error interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[22]    |ECCIF     |ECC Finish Interrupt Flag
     * |        |          |0 = No ECC interrupt.
     * |        |          |1 = ECC operation done interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[23]    |ECCEIF    |ECC Error Flag
     * |        |          |This register includes operating and setting error. The detail flag is shown in CRPT_ECC_STS register.
     * |        |          |0 = No ECC error.
     * |        |          |1 = ECC error interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[24]    |HMACIF    |SHA/HMAC Finish Interrupt Flag
     * |        |          |0 = No SHA/HMAC interrupt.
     * |        |          |1 = SHA/HMAC operation done interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[25]    |HMACEIF   |SHA/HMAC Error Flag
     * |        |          |This register includes operating and setting error. The detail flag is shown in CRPT_HMAC_STS register.
     * |        |          |0 = No SHA/HMAC error.
     * |        |          |1 = SHA/HMAC error interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[30]    |RSAIF     |RSA Finish Interrupt Flag
     * |        |          |0 = No RSA interrupt.
     * |        |          |1 = RSA operation done interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * |[31]    |RSAEIF    |RSA Error Interrupt Flag
     * |        |          |This register includes operating and setting error. The detail flag is shown in CRPT_RSA_STS register.
     * |        |          |0 = No RSA error.
     * |        |          |1 = RSA error interrupt.
     * |        |          |Note: This bit is cleared by writing 1, and it has no effect by writing 0.
     * @var CRPT_T::PRNG_CTL
     * Offset: 0x08  PRNG Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |Start PRNG Engine
     * |        |          |0 = Stop PRNG engine.
     * |        |          |1 = Generate new key and store the new key to register CRPT_PRNG_KEYx, which will be cleared when the new key is generated.
     * |[1]     |SEEDRLD   |Reload New Seed for PRNG Engine
     * |        |          |0 = Generating key based on the current seed.
     * |        |          |1 = Reload new seed.
     * |[5:2]   |KEYSZ     |PRNG Generate Key Size
     * |        |          |0000 = 128 bits.
     * |        |          |0001 = 163 bits.
     * |        |          |0010 = 192 bits.
     * |        |          |0011 = 224 bits.
     * |        |          |0100 = 233 bits.
     * |        |          |0101 = 255 bits.
     * |        |          |0110 = 256 bits.
     * |        |          |0111 = 283 bits (only for KS).
     * |        |          |1000 = 384 bits (only for KS).
     * |        |          |1001 = 409 bits (only for KS).
     * |        |          |1010 = 512 bits (only for KS).
     * |        |          |1011 = 521 bits (only for KS).
     * |        |          |1100 = 571 bits (only for KS).
     * |        |          |1101 = Reserved.
     * |        |          |1110 = Reserved.
     * |        |          |1111 = Reserved.
     * |        |          |Note: 283~571 bits are only generated for key store.
     * |[8]     |BUSY      |PRNG Busy (Read Only)
     * |        |          |0 = PRNG engine is idle.
     * |        |          |1 = PRNG engine is generating CRPT_PRNG_KEYx.
     * |[16]    |SEEDSRC   |Seed Source
     * |        |          |0 = Seed is from TRNG.
     * |        |          |1 = Seed is from PRNG seed register.
     * |        |          |Note: When SEEDRLD is set to 0, this bit (SEEDSRC) is meaningless.
     * @var CRPT_T::PRNG_SEED
     * Offset: 0x0C  Seed for PRNG
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |Seed for PRNG (Write Only)
     * |        |          |The bits store the seed for PRNG engine.
     * |        |          |Note: In TRNG+PRNG mode, the seed is from TRNG engine, and it will not be stored in this register.
     * @var CRPT_T::PRNG_KEY0
     * Offset: 0x10  PRNG Generated Key0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_KEY1
     * Offset: 0x14  PRNG Generated Key1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_KEY2
     * Offset: 0x18  PRNG Generated Key2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_KEY3
     * Offset: 0x1C  PRNG Generated Key3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_KEY4
     * Offset: 0x20  PRNG Generated Key4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_KEY5
     * Offset: 0x24  PRNG Generated Key5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_KEY6
     * Offset: 0x28  PRNG Generated Key6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_KEY7
     * Offset: 0x2C  PRNG Generated Key7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |Store PRNG Generated Key (Read Only)
     * |        |          |The bits store the key that is generated by PRNG.
     * @var CRPT_T::PRNG_STS
     * Offset: 0x30  PRNG Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |PRNG Busy Flag
     * |        |          |0 = PRNG engine is idle.
     * |        |          |1 = PRNG engine is generating CRPT_PRNG_KEYx.
     * |[16]    |KCTLERR   |PRNG Key Control Register Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = PRNG key control error
     * |        |          |When PRNG execute ECDSA or ECDH, but PRNG seed not from TRNG or key is not written to the SRAM of key store (WSDST, CRPT_PRNG_KSCTL[23:22] is not equal to u201900u2019).
     * |[17]    |KSERR     |PRNG Access Key Store Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Access key store failed.
     * @var CRPT_T::AES_FDBCK0
     * Offset: 0x50  AES Engine Output Feedback Data After Cryptographic Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |AES Feedback Information
     * |        |          |The feedback value is 128 bits in size.
     * |        |          |The AES engine uses the data from CRPT_AES_FDBCKx as the data inputted to CRPT_AES_IVx for the next block in DMA cascade mode.
     * |        |          |The AES engine outputs feedback information for IV in the next blocku2019s operation
     * |        |          |Software can use this feedback information to implement more than four DMA channels
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_AES_IVx in the same channel operation, and then continue the operation with the original setting.
     * @var CRPT_T::AES_FDBCK1
     * Offset: 0x54  AES Engine Output Feedback Data After Cryptographic Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |AES Feedback Information
     * |        |          |The feedback value is 128 bits in size.
     * |        |          |The AES engine uses the data from CRPT_AES_FDBCKx as the data inputted to CRPT_AES_IVx for the next block in DMA cascade mode.
     * |        |          |The AES engine outputs feedback information for IV in the next blocku2019s operation
     * |        |          |Software can use this feedback information to implement more than four DMA channels
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_AES_IVx in the same channel operation, and then continue the operation with the original setting.
     * @var CRPT_T::AES_FDBCK2
     * Offset: 0x58  AES Engine Output Feedback Data After Cryptographic Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |AES Feedback Information
     * |        |          |The feedback value is 128 bits in size.
     * |        |          |The AES engine uses the data from CRPT_AES_FDBCKx as the data inputted to CRPT_AES_IVx for the next block in DMA cascade mode.
     * |        |          |The AES engine outputs feedback information for IV in the next blocku2019s operation
     * |        |          |Software can use this feedback information to implement more than four DMA channels
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_AES_IVx in the same channel operation, and then continue the operation with the original setting.
     * @var CRPT_T::AES_FDBCK3
     * Offset: 0x5C  AES Engine Output Feedback Data After Cryptographic Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |AES Feedback Information
     * |        |          |The feedback value is 128 bits in size.
     * |        |          |The AES engine uses the data from CRPT_AES_FDBCKx as the data inputted to CRPT_AES_IVx for the next block in DMA cascade mode.
     * |        |          |The AES engine outputs feedback information for IV in the next blocku2019s operation
     * |        |          |Software can use this feedback information to implement more than four DMA channels
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_AES_IVx in the same channel operation, and then continue the operation with the original setting.
     * @var CRPT_T::AES_GCM_IVCNT0
     * Offset: 0x80  AES GCM IV Byte Count Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNT       |AES GCM IV   Byte Count
     * |        |          |The bit   length of IV is 64 bits for AES GCM mode
     * |        |          |The CRPT_AES_GCM_IVCNT0 keeps the   low weight byte count of initial vector (i.e., len(IV)[34:3]) of AES GCM mode   and can be read and written.
     * @var CRPT_T::AES_GCM_IVCNT1
     * Offset: 0x84  AES GCM IV Byte Count Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[28:0]  |CNT       |AES GCM IV   Byte Count
     * |        |          |The bit   length of IV is 64 bits for AES GCM mode
     * |        |          |The CRPT_AES_GCM_IVCNT1 keeps the   high weight byte count of initial vector (i.e., len(IV)[64:35]) of AES GCM   mode and can be read and written.
     * @var CRPT_T::AES_GCM_ACNT0
     * Offset: 0x88  AES GCM A Byte Count Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNT       |AES GCM a Byte   Count
     * |        |          |The bit   length of A is 64 bits for AES GCM mode
     * |        |          |The CRPT_AES_GCM_ACNT0 keeps the low   weight byte count of the additional authenticated data (i.e., len(A)[34:3]) of   AES GCM mode and can be read and written.
     * @var CRPT_T::AES_GCM_ACNT1
     * Offset: 0x8C  AES GCM A Byte Count Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[28:0]  |CNT       |AES GCM a Byte   Count
     * |        |          |The bit   length of A is 64 bits for AES GCM mode
     * |        |          |The CRPT_AES_GCM_ACNT0 keeps the high   weight byte count of the additional authenticated data (i.e., len(A)[63:35]) of   AES GCM mode and can be read and written.
     * @var CRPT_T::AES_GCM_PCNT0
     * Offset: 0x90  AES GCM P Byte Count Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNT       |AES GCM P Byte   Count
     * |        |          |The bit   length of Por C is 39 bits for AES GCM mode
     * |        |          |The CRPT_AES_GCM_PCNT0 keeps   the low weight byte count of the plaintext or ciphertext (i.e., len(P)[34:3]   or len(C)[34:3]) of AES GCM mode and can be read and written.
     * @var CRPT_T::AES_GCM_PCNT1
     * Offset: 0x94  AES GCM P Byte Count Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[28:0]  |CNT       |AES GCM P Byte   Count
     * |        |          |The bit   length of Por C is 39 bits for AES GCM mode
     * |        |          |The CRPT_AES_GCM_PCNT1 keeps   the high weight byte count of the plaintext or ciphertext (i.e., len(P)[38:35]   or len(C)[38:35]) of AES GCM mode and can be read and written.
     * |        |          |The bit   length of Por C is 64 bits for AES CCM mode
     * |        |          |The CRPT_AES_GCM_PCNT1 keeps   the high weight byte count of the plaintext or ciphertext (i.e., len(P)[63:35]   or len(C)[63:35]) of AES CCM mode and can be read and written.
     * @var CRPT_T::AES_FBADDR
     * Offset: 0xA0  AES DMA Feedback Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FBADDR    |AES DMA Feedback Address
     * |        |          |In DMA cascade mode, software can update DMA feedback address register for automatically reading and writing feedback values via DMA
     * |        |          |The FBADDR keeps the feedback address of the feedback data for the next cascade operation
     * |        |          |Based on the feedback address, the AES accelerator can read the feedback data of the last cascade operation from SRAM memory space and write the feedback data of the current cascade operation to SRAM memory space
     * |        |          |The start of feedback address should be located at word boundary
     * |        |          |In other words, bit 1 and 0 of FBADDR are ignored.
     * |        |          |FBADDR can be read and written.
     * |        |          |In DMA mode, software can update the next CRPT_AES_FBADDR before triggering START.
     * @var CRPT_T::AES_CTL
     * Offset: 0x100  AES Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |AES Engine Start
     * |        |          |0 = No effect.
     * |        |          |1 = Start AES engine. BUSY flag will be set.
     * |        |          |Note: This bit is always 0 when it is read back.
     * |[1]     |STOP      |AES Engine Stop
     * |        |          |0 = No effect.
     * |        |          |1 = Stop AES engine.
     * |        |          |Note: This bit is always 0 when it is read back.
     * |[3:2]   |KEYSZ     |AES Key Size
     * |        |          |This bit defines three different key size for AES operation.
     * |        |          |2u2019b00 = 128 bits key.
     * |        |          |2u2019b01 = 192 bits key.
     * |        |          |2u2019b10 = 256 bits key.
     * |        |          |2u2019b11 = Reserved.
     * |        |          |If the AES accelerator is operating and the corresponding flag BUSY is 1, updating this register has no effect.
     * |[5]     |DMALAST   |AES Last Block
     * |        |          |In DMA mode, this bit must be set as beginning the last DMA cascade round.
     * |        |          |In Non-DMA mode, this bit must be set when feeding in the last block of data in ECB, CBC, CTR, OFB, and CFB mode, and feeding in the (last-1) block of data at CBC-CS1, CBC-CS2, and CBC-CS3 mode.
     * |        |          |This bit is always 0 when it is read back, and must be written again once START is triggered.
     * |[6]     |DMACSCAD  |AES Engine DMA with Cascade Mode
     * |        |          |0 = DMA cascade function Disabled.
     * |        |          |1 = In DMA cascade mode, software can update DMA source address register, destination address register, and byte count register during a cascade operation, without finishing the accelerator operation.
     * |        |          |Note: The last two blocks of AES-CBC-CS1/2/3 must be in the last cascade operation.
     * |[7]     |DMAEN     |AES Engine DMA Enable Bit
     * |        |          |0 = AES DMA engine Disabled.
     * |        |          |The AES engine operates in Non-DMA mode. The data need to be written in CRPT_AES_DATIN.
     * |        |          |1 = AES_DMA engine Enabled.
     * |        |          |The AES engine operates in DMA mode, and data movement from/to the engine is done by DMA logic.
     * |[15:8]  |OPMODE    |AES Engine Operation Modes
     * |        |          |0x00 = ECB (Electronic Codebook Mode)  0x01 = CBC (Cipher Block Chaining Mode).
     * |        |          |0x02 = CFB (Cipher Feedback Mode).
     * |        |          |0x03 = OFB (Output Feedback Mode).
     * |        |          |0x04 = CTR (Counter Mode).
     * |        |          |0x10 = CBC-CS1 (CBC Ciphertext-Stealing 1 Mode).
     * |        |          |0x11 = CBC-CS2 (CBC Ciphertext-Stealing 2 Mode).
     * |        |          |0x12 = CBC-CS3 (CBC Ciphertext-Stealing 3 Mode).
     * |        |          |0x20 = GCM (Galois/Counter Mode).
     * |        |          |0x21 = GHASH (Galois Hash Function).
     * |        |          |0x22 = CCM (Counter with CBC-MAC Mode).
     * |[16]    |ENCRYPTO  |AES Encryption/Decryption
     * |        |          |0 = AES engine executes decryption operation.
     * |        |          |1 = AES engine executes encryption operation.
     * |[20]    |FBIN      |Feedback Input to AES Via DMA Automatically
     * |        |          |0 = DMA automatic feedback input function Disabled.
     * |        |          |1 = DMA automatic feedback input function Enabled when DMAEN = 1.
     * |[21]    |FBOUT     |Feedback Output From AES Via DMA Automatically
     * |        |          |0 = DMA automatic feedback output function Disabled.
     * |        |          |1 = DMA automatic feedback output function Enabled when DMAEN = 1.
     * |[22]    |OUTSWAP   |AES Engine Output Data Swap
     * |        |          |0 = Keep the original order.
     * |        |          |1 = The order that CPU reads data from the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
     * |[23]    |INSWAP    |AES Engine Input Data Swap
     * |        |          |0 = Keep the original order.
     * |        |          |1 = The order that CPU feeds data to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
     * |[24]    |KOUTSWAP  |AES Engine Output Key, Initial Vector and Feedback Swap
     * |        |          |0 = Keep the original order.
     * |        |          |1 = The order that CPU reads key, initial vector and feedback from the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
     * |[25]    |KINSWAP   |AES Engine Input Key and Initial Vector Swap
     * |        |          |0 = Keep the original order.
     * |        |          |1 = The order that CPU feeds key and initial vector to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
     * |[30:26] |KEYUNPRT  |Unprotect Key
     * |        |          |Writing 0 to CRPT_AES_CTL[31] and u201C10110u201D to CRPT_AES_CTL[30:26] is to unprotect the AES key.
     * |        |          |The KEYUNPRT can be read and written
     * |        |          |When it is written as the AES engine is operating, BUSY flag is 1, there would be no effect on KEYUNPRT.
     * |[31]    |KEYPRT    |Protect Key
     * |        |          |Read as a flag to reflect KEYPRT.
     * |        |          |0 = No effect.
     * |        |          |1 = Protect the content of the AES key from reading
     * |        |          |The return value for reading CRPT_AES_KEYx is not the content of the registers CRPT_AES_KEYx
     * |        |          |Once it is set, it can be cleared by asserting KEYUNPRT
     * |        |          |The key content would be cleared as well.
     * @var CRPT_T::AES_STS
     * Offset: 0x104  AES Engine Flag
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |AES Engine Busy
     * |        |          |0 = The AES engine is idle or finished.
     * |        |          |1 = The AES engine is under processing.
     * |[8]     |INBUFEMPTY|AES Input Buffer Empty
     * |        |          |0 = There are some data in input buffer waiting for the AES engine to process.
     * |        |          |1 = AES input buffer is empty
     * |        |          |Software needs to feed data to the AES engine
     * |        |          |Otherwise, the AES engine will be pending to wait for input data.
     * |[9]     |INBUFFULL |AES Input Buffer Full Flag
     * |        |          |0 = AES input buffer is not full. Software can feed the data into the AES engine.
     * |        |          |1 = AES input buffer is full
     * |        |          |Software cannot feed data to the AES engine
     * |        |          |Otherwise, the flag INBUFERR will be set to 1.
     * |[10]    |INBUFERR  |AES Input Buffer Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Error happened during feeding data to the AES engine.
     * |[12]    |CNTERR    |CRPT_AES_CNT Setting Error
     * |        |          |0 = No error in CRPT_AES_CNT setting.
     * |        |          |1 = CRPT_AES_CNT is 0 if DMAEN (CRPT_AES_CTL[7]) is enabled.
     * |[16]    |OUTBUFEMPTY|AES Out Buffer Empty
     * |        |          |0 = AES output buffer is not empty. There are some valid data kept in output buffer.
     * |        |          |1 = AES output buffer is empty
     * |        |          |Software cannot get data from CRPT_AES_DATOUT
     * |        |          |Otherwise, the flag OUTBUFERR will be set to 1 since the output buffer is empty.
     * |[17]    |OUTBUFFULL|AES Out Buffer Full Flag
     * |        |          |0 = AES output buffer is not full.
     * |        |          |1 = AES output buffer is full, and software needs to get data from CRPT_AES_DATOUT
     * |        |          |Otherwise, the AES engine will be pending since the output buffer is full.
     * |[18]    |OUTBUFERR |AES Out Buffer Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Error happened during getting the result from AES engine.
     * |[20]    |BUSERR    |AES DMA Access Bus Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Bus error will stop DMA operation and AES engine.
     * |[21]    |KSERR     |AES Engine Access Key Store Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Key store access error will stop AES engine.
     * @var CRPT_T::AES_DATIN
     * Offset: 0x108  AES Engine Data Input Port Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATIN     |AES Engine Input Port
     * |        |          |CPU feeds data to AES engine through this port by checking CRPT_AES_STS. Feed data as INBUFFULL is 0.
     * @var CRPT_T::AES_DATOUT
     * Offset: 0x10C  AES Engine Data Output Port Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATOUT    |AES Engine Output Port
     * |        |          |CPU gets results from the AES engine through this port by checking CRPT_AES_STS
     * |        |          |Get data as OUTBUFEMPTY is 0.
     * @var CRPT_T::AES_KEY0
     * Offset: 0x110  AES Key Word 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_KEY1
     * Offset: 0x114  AES Key Word 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_KEY2
     * Offset: 0x118  AES Key Word 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_KEY3
     * Offset: 0x11C  AES Key Word 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_KEY4
     * Offset: 0x120  AES Key Word 4 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_KEY5
     * Offset: 0x124  AES Key Word 5 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_KEY6
     * Offset: 0x128  AES Key Word 6 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_KEY7
     * Offset: 0x12C  AES Key Word 7 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEY       |CRPT_AES_KEYx
     * |        |          |The KEY keeps the security key for AES operation.
     * |        |          |x = 0, 1..7.
     * |        |          |The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key.
     * |        |          |{CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 128-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 192-bit security key for AES operation.
     * |        |          |{CRPT_AES_KEY7, CRPT_AES_KEY6, CRPT_AES_KEY5, CRPT_AES_KEY4, CRPT_AES_KEY3, CRPT_AES_KEY2, CRPT_AES_KEY1, CRPT_AES_KEY0} stores the 256-bit security key for AES operation.
     * @var CRPT_T::AES_IV0
     * Offset: 0x130  AES Initial Vector Word 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |IV        |AES Initial Vectors
     * |        |          |x = 0, 1..3.
     * |        |          |Four initial vectors (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) are for AES operating in CBC, CFB, and OFB mode
     * |        |          |Four registers (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
     * @var CRPT_T::AES_IV1
     * Offset: 0x134  AES Initial Vector Word 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |IV        |AES Initial Vectors
     * |        |          |x = 0, 1..3.
     * |        |          |Four initial vectors (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) are for AES operating in CBC, CFB, and OFB mode
     * |        |          |Four registers (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
     * @var CRPT_T::AES_IV2
     * Offset: 0x138  AES Initial Vector Word 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |IV        |AES Initial Vectors
     * |        |          |x = 0, 1..3.
     * |        |          |Four initial vectors (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) are for AES operating in CBC, CFB, and OFB mode
     * |        |          |Four registers (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
     * @var CRPT_T::AES_IV3
     * Offset: 0x13C  AES Initial Vector Word 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |IV        |AES Initial Vectors
     * |        |          |x = 0, 1..3.
     * |        |          |Four initial vectors (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) are for AES operating in CBC, CFB, and OFB mode
     * |        |          |Four registers (CRPT_AES_IV0, CRPT_AES_IV1, CRPT_AES_IV2, and CRPT_AES_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
     * @var CRPT_T::AES_SADDR
     * Offset: 0x140  AES DMA Source Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SADDR     |AES DMA Source Address
     * |        |          |The AES accelerator supports DMA function to transfer the plain text between SRAM memory space and embedded FIFO
     * |        |          |The SADDR keeps the source address of the data buffer where the source text is stored
     * |        |          |Based on the source address, the AES accelerator can read the plain text (encryption) / cipher text (decryption) from SRAM memory space and do AES operation
     * |        |          |The start of source address should be located at word boundary
     * |        |          |In other words, bit 1 and 0 of SADDR are ignored.
     * |        |          |SADDR can be read and written
     * |        |          |Writing to SADDR while the AES accelerator is operating doesnu2019t affect the current AES operation
     * |        |          |But the value of SADDR will be updated later on
     * |        |          |Consequently, software can prepare the DMA source address for the next AES operation.
     * |        |          |In DMA mode, software can update the next CRPT_AES_SADDR before triggering START.
     * |        |          |The value of CRPT_AES_SADDR and CRPT_AES_DADDR can be the same.
     * @var CRPT_T::AES_DADDR
     * Offset: 0x144  AES DMA Destination Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DADDR     |AES DMA Destination Address
     * |        |          |The AES accelerator supports DMA function to transfer the cipher text between SRAM memory space and embedded FIFO
     * |        |          |The DADDR keeps the destination address of the data buffer where the engine outputu2019s text will be stored
     * |        |          |Based on the destination address, the AES accelerator can write the cipher text (encryption) / plain text (decryption) back to SRAM memory space after the AES operation is finished
     * |        |          |The start of destination address should be located at word boundary
     * |        |          |In other words, bit 1 and 0 of DADDR are ignored.
     * |        |          |DADDR can be read and written
     * |        |          |Writing to DADDR while the AES accelerator is operating doesnu2019t affect the current AES operation
     * |        |          |But the value of DADDR will be updated later on
     * |        |          |Consequently, software can prepare the destination address for the next AES operation.
     * |        |          |In DMA mode, software can update the next CRPT_AES_DADDR before triggering START.
     * |        |          |The value of CRPT_AES_SADDR and CRPT_AES_DADDR can be the same.
     * @var CRPT_T::AES_CNT
     * Offset: 0x148  AES Byte Count Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CNT       |AES Byte Count
     * |        |          |The   CRPT_AES_CNT keeps the byte count of source text that is for the AES engine   operating in DMA mode
     * |        |          |The CRPT_AES_CNT is 32-bit and the maximum of byte   count is 4G bytes.
     * |        |          |CRPT_AES_CNT   can be read and written
     * |        |          |Writing to CRPT_AES_CNT while the AES accelerator   is operating doesnu2019t affect the current AES operation
     * |        |          |But the value of   CRPT_AES_CNT will be updated later on
     * |        |          |Consequently, software can prepare   the byte count of data for the next AES operation.
     * |        |          |According to   CBC-CS1, CBC-CS2, and CBC-CS3 standard, the count of operation data must be more   than 16 bytes
     * |        |          |Operations that are qual or less than one block will output   unexpected result.
     * |        |          |In Non-DMA   ECB, CBC, CFB, OFB, CTR, CCM and GCM mode, CRPT_AES_CNT must be set as byte   count for the last block of data before feeding in the last block of data
     * |        |          |In   Non-DMA CBC-CS1, CBC-CS2, and CBC-CS3 mode, CRPT_AES_CNT must be set as   byte count for the last two blocks of data before feeding in the last two   blocks of data.
     * |        |          |In AES GCM   mode without DMA cascade function, the value of CRPT_AES_CNT is equal to   the total value of {CRPT_AES_GCM_IVCNT1, CRPT_AES_GCM_IVCNT0}, {CRPT_AES_GCM_ACNT1,   CRPT_AES_GCM_ACNT0} and {CRPT_AES_GCM_PCNT1, CRPT_AES_GCM_PCNT0}.
     * |        |          |In AES GCM   mode with DMA cascade function, the value of CRPT_AES_CNT represents the byte   count of source text in this cascade function
     * |        |          |Thus, the value of   CRPT_AES_CNT is less than or equal to the total value of {CRPT_AES_GCM_IVCNT1,   CRPT_AES_GCM_IVCNT0}, {CRPT_AES_GCM_ACNT1, CRPT_AES_GCM_ACNT0} and {CRPT_AES_GCM_PCNT1,   CRPT_AES_GCM_PCNT0} and must be block alignment.
     * |        |          |In AES CCM   mode without DMA cascade function, the value of CRPT_AES_CNT is equal to   the total value of {CRPT_AES_GCM_ACNT1, CRPT_AES_GCM_ACNT0} and {CRPT_AES_GCM_PCNT1,   CRPT_AES_GCM_PCNT0}.
     * |        |          |In AES CCM   mode with DMA cascade function, the value of CRPT_AES_CNT represents the byte   count of source text in this cascade function
     * |        |          |Thus, the value of   CRPT_AES_CNT is less than or equal to the total value of {CRPT_AES_GCM_ACNT1,   CRPT_AES_GCM_ACNT0} and {CRPT_AES_GCM_PCNT1, CRPT_AES_GCM_PCNT0} and   must be block alignment, except for the last block of plaintext or   ciphertext.
     * @var CRPT_T::HMAC_CTL
     * Offset: 0x300  SHA/HMAC Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |SHA/HMAC Engine Start
     * |        |          |0 = No effect.
     * |        |          |1 = Start SHA/HMAC engine. BUSY flag will be set.
     * |        |          |Note: This bit is always 0 when it is read back.
     * |[1]     |STOP      |SHA/HMAC Engine Stop
     * |        |          |0 = No effect.
     * |        |          |1 = Stop SHA/HMAC engine.
     * |        |          |Note: This bit is always 0 when it is read back.
     * |[4]     |DMAFIRST  |SHA/HMAC First Block in Cascade function
     * |        |          |This bit must be set as feeding in first byte of data.
     * |[5]     |DMALAST   |SHA/HMAC Last Block
     * |        |          |This bit must be set as feeding in last byte of data.
     * |[6]     |DMACSCAD  |SHA/HMAC Engine DMA with Cascade Mode
     * |        |          |0 = DMA cascade function Disabled.
     * |        |          |1 = In DMA cascade mode, software can update DMA source address register, destination address register, and byte count register during a cascade operation, without finishing the accelerator operation.
     * |[7]     |DMAEN     |SHA/HMAC Engine DMA Enable Bit
     * |        |          |0 = SHA/HMAC DMA engine Disabled.
     * |        |          |SHA/HMAC engine operates in Non-DMA mode. The data need to be written in CRPT_HMAC_DATIN.
     * |        |          |1 = SHA/HMAC DMA engine Enabled.
     * |        |          |SHA/HMAC engine operates in DMA mode, and data movement from/to the engine is done by DMA logic.
     * |[10:8]  |OPMODE    |SHA/HMAC Engine Operation Modes
     * |        |          |When SHA3EN=0,.
     * |        |          |0x0xx: SHA1-160
     * |        |          |0x100: SHA2-256
     * |        |          |0x101: SHA2-224
     * |        |          |0x110: SHA2-512
     * |        |          |0x111: SHA2-384
     * |        |          |When SHA3EN=1,.
     * |        |          |0x100: SHA3-256
     * |        |          |0x101: SHA3-224
     * |        |          |0x110: SHA3-512
     * |        |          |0x111: SHA3-384
     * |        |          |0x000: SHAKE128
     * |        |          |0x001: SHAKE256
     * |        |          |Note: These bits can be read and written. But writing to them wouldnu2019t take effect as BUSY is 1.
     * |[11]    |HMACEN    |HMAC_SHA Engine Operating Mode
     * |        |          |0 = Execute SHA function.
     * |        |          |1 = Execute HMAC function.
     * |[12]    |SHA3EN    |SHA3 Engine Enable Bit
     * |        |          |0 = Execute other function.
     * |        |          |1 = Execute SHA3 function.
     * |[20]    |FBIN      |Feedback Input to SHA/HMAC Via DMA Automatically
     * |        |          |0 = DMA automatic feedback input function Disabled.
     * |        |          |1 = DMA automatic feedback input function Enabled when DMAEN = 1.
     * |[21]    |FBOUT     |Feedback Output From SHA/HMAC Via DMA Automatically
     * |        |          |0 = DMA automatic feedback output function Disabled.
     * |        |          |1 = DMA automatic feedback output function Enabled when DMAEN = 1.
     * |[22]    |OUTSWAP   |SHA/HMAC Engine Output Data Swap
     * |        |          |0 = Keep the original order.
     * |        |          |1 = The order that CPU feeds data to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
     * |[23]    |INSWAP    |SHA/HMAC Engine Input Data Swap
     * |        |          |0 = Keep the original order.
     * |        |          |1 = The order that CPU feeds data to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
     * |[24]    |NEXTDGST  |SHAKE128/256 Next Digest Start
     * |        |          |0 = No effect.
     * |        |          |1 = Start SHAKE engine to generate the next digest only when SHAKEBUSY is 0
     * |        |          |BUSY and SHAKEBUSY flag will be set.
     * |[25]    |FINISHDGST|SHAKE128/256 Next Digest Finish
     * |        |          |0 = No effect.
     * |        |          |1 = finish generating the next digest.
     * @var CRPT_T::HMAC_STS
     * Offset: 0x304  SHA/HMAC Status Flag
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |SHA/HMAC Engine Busy
     * |        |          |0 = SHA/HMAC engine is idle or finished.
     * |        |          |1 = SHA/HMAC engine is busy.
     * |[1]     |DMABUSY   |SHA/HMAC Engine DMA Busy Flag
     * |        |          |0 = SHA/HMAC DMA engine is idle or finished.
     * |        |          |1 = SHA/HMAC DMA engine is busy.
     * |[2]     |SHAKEBUSY |SHAKE Engine Busy Flag
     * |        |          |0 = SHAKE engine is idle or finished.
     * |        |          |1 = SHAKE engine is busy.
     * |[8]     |DMAERR    |SHA/HMAC Engine DMA Error Flag
     * |        |          |0 = Show the SHA/HMAC engine access normal.
     * |        |          |1 = Show the SHA/HMAC engine access error.
     * |[9]     |KSERR     |HMAC Engine Access Key Store Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Access error will stop HMAC engine.
     * |[16]    |DATINREQ  |SHA/HMAC Non-DMA Mode Data Input Request
     * |        |          |0 = No effect.
     * |        |          |1 = Request SHA/HMAC Non-DMA mode data input.
     * @var CRPT_T::HMAC_DGST0
     * Offset: 0x308  SHA/HMAC Output Feedback Data 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST1
     * Offset: 0x30C  SHA/HMAC Output Feedback Data 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST2
     * Offset: 0x310  SHA/HMAC Output Feedback Data 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST3
     * Offset: 0x314  SHA/HMAC Output Feedback Data 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST4
     * Offset: 0x318  SHA/HMAC Output Feedback Data 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST5
     * Offset: 0x31C  SHA/HMAC Output Feedback Data 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST6
     * Offset: 0x320  SHA/HMAC Output Feedback Data 6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST7
     * Offset: 0x324  SHA/HMAC Output Feedback Data 7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST8
     * Offset: 0x328  SHA/HMAC Output Feedback Data 8
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST9
     * Offset: 0x32C  SHA/HMAC Output Feedback Data 9
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST10
     * Offset: 0x330  SHA/HMAC Output Feedback Data 10
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST11
     * Offset: 0x334  SHA/HMAC Output Feedback Data 11
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST12
     * Offset: 0x338  SHA/HMAC Output Feedback Data 12
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST13
     * Offset: 0x33C  SHA/HMAC Output Feedback Data 13
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST14
     * Offset: 0x340  SHA/HMAC Output Feedback Data 14
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_DGST15
     * Offset: 0x344  SHA/HMAC Output Feedback Data 15
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC Output Feedback Data Output Register
     * |        |          |For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
     * |        |          |For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
     * |        |          |For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
     * |        |          |For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
     * |        |          |For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
     * @var CRPT_T::HMAC_KEYCNT
     * Offset: 0x348  SHA/HMAC Key Byte Count Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |KEYCNT    |SHA/HMAC Key Byte Count
     * |        |          |The CRPT_HMAC_KEYCNT keeps the byte count of key that SHA/HMAC engine operates
     * |        |          |The register is 32-bit and the maximum byte count is 4G bytes
     * |        |          |It can be read and written.
     * |        |          |Writing to the register CRPT_HMAC_KEYCNT as the SHA/HMAC accelerator operating doesnu2019t affect the current SHA/HMAC operation
     * |        |          |But the value of CRPT_HMAC_KEYCNT will be updated later on
     * |        |          |Consequently, software can prepare the key count for the next SHA/HMAC operation.
     * @var CRPT_T::HMAC_SADDR
     * Offset: 0x34C  SHA/HMAC DMA Source Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SADDR     |SHA/HMAC DMA Source Address
     * |        |          |The SHA/HMAC accelerator supports DMA function to transfer the plain text between SRAM memory space and embedded FIFO
     * |        |          |The CRPT_HMAC_SADDR keeps the source address of the data buffer where the source text is stored
     * |        |          |Based on the source address, the SHA/HMAC accelerator can read the plain text from SRAM memory space and do SHA/HMAC operation
     * |        |          |The start of source address should be located at word boundary
     * |        |          |In other words, bit 1 and 0 of CRPT_HMAC_SADDR are ignored.
     * |        |          |CRPT_HMAC_SADDR can be read and written
     * |        |          |Writing to CRPT_HMAC_SADDR while the SHA/HMAC accelerator is operating doesnu2019t affect the current SHA/HMAC operation
     * |        |          |But the value of CRPT_HMAC_SADDR will be updated later on
     * |        |          |Consequently, software can prepare the DMA source address for the next SHA/HMAC operation.
     * |        |          |In DMA mode, software can update the next CRPT_HMAC_SADDR before triggering START.
     * |        |          |CRPT_HMAC_SADDR and CRPT_HMAC_DADDR can be the same in the value.
     * @var CRPT_T::HMAC_DMACNT
     * Offset: 0x350  SHA/HMAC Byte Count Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DMACNT    |SHA/HMAC Operation Byte Count
     * |        |          |The CRPT_HMAC_DMACNT keeps the byte count of source text that is for the SHA/HMAC engine operating in DMA mode
     * |        |          |The CRPT_HMAC_DMACNT is 32-bit and the maximum of byte count is 4G bytes.
     * |        |          |CRPT_HMAC_DMACNT can be read and written
     * |        |          |Writing to CRPT_HMAC_DMACNT while the SHA/HMAC accelerator is operating doesnu2019t affect the current SHA/HMAC operation
     * |        |          |But the value of CRPT_HMAC_DMACNT will be updated later on
     * |        |          |Consequently, software can prepare the byte count of data for the next SHA/HMAC operation.
     * |        |          |In Non-DMA mode, CRPT_HMAC_DMACNT must be set as the byte count of the last block before feeding in the last block of data.
     * @var CRPT_T::HMAC_DATIN
     * Offset: 0x354  SHA/HMAC Engine Non-DMA Mode Data Input Port Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATIN     |SHA/HMAC Engine Input Port
     * |        |          |CPU feeds data to SHA/HMAC engine through this port by checking CRPT_HMAC_STS
     * |        |          |Feed data as DATINREQ is 1.
     * @var CRPT_T::HMAC_FDBCK0
     * Offset: 0x358  SHA/HMAC Output Feedback Data 0 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK1
     * Offset: 0x35C  SHA/HMAC Output Feedback Data 1 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK2
     * Offset: 0x360  SHA/HMAC Output Feedback Data 2 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK3
     * Offset: 0x364  SHA/HMAC Output Feedback Data 3 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK4
     * Offset: 0x368  SHA/HMAC Output Feedback Data 4 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK5
     * Offset: 0x36C  SHA/HMAC Output Feedback Data 5 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK6
     * Offset: 0x370  SHA/HMAC Output Feedback Data 6 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK7
     * Offset: 0x374  SHA/HMAC Output Feedback Data 7 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK8
     * Offset: 0x378  SHA/HMAC Output Feedback Data 8 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK9
     * Offset: 0x37C  SHA/HMAC Output Feedback Data 9 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK10
     * Offset: 0x380  SHA/HMAC Output Feedback Data 10 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK11
     * Offset: 0x384  SHA/HMAC Output Feedback Data 11 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK12
     * Offset: 0x388  SHA/HMAC Output Feedback Data 12 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK13
     * Offset: 0x38C  SHA/HMAC Output Feedback Data 13 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK14
     * Offset: 0x390  SHA/HMAC Output Feedback Data 14 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK15
     * Offset: 0x394  SHA/HMAC Output Feedback Data 15 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK16
     * Offset: 0x398  SHA/HMAC Output Feedback Data 16 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK17
     * Offset: 0x39C  SHA/HMAC Output Feedback Data 17 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK18
     * Offset: 0x3A0  SHA/HMAC Output Feedback Data 18 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK19
     * Offset: 0x3A4  SHA/HMAC Output Feedback Data 19 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK20
     * Offset: 0x3A8  SHA/HMAC Output Feedback Data 20 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK21
     * Offset: 0x3AC  SHA/HMAC Output Feedback Data 21 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK22
     * Offset: 0x3B0  SHA/HMAC Output Feedback Data 22 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK23
     * Offset: 0x3B4  SHA/HMAC Output Feedback Data 23 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK24
     * Offset: 0x3B8  SHA/HMAC Output Feedback Data 24 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK25
     * Offset: 0x3BC  SHA/HMAC Output Feedback Data 25 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK26
     * Offset: 0x3C0  SHA/HMAC Output Feedback Data 26 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK27
     * Offset: 0x3C4  SHA/HMAC Output Feedback Data 27 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK28
     * Offset: 0x3C8  SHA/HMAC Output Feedback Data 28 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK29
     * Offset: 0x3CC  SHA/HMAC Output Feedback Data 29 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK30
     * Offset: 0x3D0  SHA/HMAC Output Feedback Data 30 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK31
     * Offset: 0x3D4  SHA/HMAC Output Feedback Data 31 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK32
     * Offset: 0x3D8  SHA/HMAC Output Feedback Data 32 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK33
     * Offset: 0x3DC  SHA/HMAC Output Feedback Data 33 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK34
     * Offset: 0x3E0  SHA/HMAC Output Feedback Data 34 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK35
     * Offset: 0x3E4  SHA/HMAC Output Feedback Data 35 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK36
     * Offset: 0x3E8  SHA/HMAC Output Feedback Data 36 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK37
     * Offset: 0x3EC  SHA/HMAC Output Feedback Data 37 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK38
     * Offset: 0x3F0  SHA/HMAC Output Feedback Data 38 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK39
     * Offset: 0x3F4  SHA/HMAC Output Feedback Data 39 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK40
     * Offset: 0x3F8  SHA/HMAC Output Feedback Data 40 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK41
     * Offset: 0x3FC  SHA/HMAC Output Feedback Data 41 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK42
     * Offset: 0x400  SHA/HMAC Output Feedback Data 42 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK43
     * Offset: 0x404  SHA/HMAC Output Feedback Data 43 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK44
     * Offset: 0x408  SHA/HMAC Output Feedback Data 44 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK45
     * Offset: 0x40C  SHA/HMAC Output Feedback Data 45 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK46
     * Offset: 0x410  SHA/HMAC Output Feedback Data 46 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK47
     * Offset: 0x414  SHA/HMAC Output Feedback Data 47 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK48
     * Offset: 0x418  SHA/HMAC Output Feedback Data 48 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK49
     * Offset: 0x41C  SHA/HMAC Output Feedback Data 49 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK50
     * Offset: 0x420  SHA/HMAC Output Feedback Data 50 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK51
     * Offset: 0x424  SHA/HMAC Output Feedback Data 51 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK52
     * Offset: 0x428  SHA/HMAC Output Feedback Data 52 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK53
     * Offset: 0x42C  SHA/HMAC Output Feedback Data 53 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK54
     * Offset: 0x430  SHA/HMAC Output Feedback Data 54 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK55
     * Offset: 0x434  SHA/HMAC Output Feedback Data 55 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK56
     * Offset: 0x438  SHA/HMAC Output Feedback Data 56 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK57
     * Offset: 0x43C  SHA/HMAC Output Feedback Data 57 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK58
     * Offset: 0x440  SHA/HMAC Output Feedback Data 58 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK59
     * Offset: 0x444  SHA/HMAC Output Feedback Data 59 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK60
     * Offset: 0x448  SHA/HMAC Output Feedback Data 60 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK61
     * Offset: 0x44C  SHA/HMAC Output Feedback Data 61 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK62
     * Offset: 0x450  SHA/HMAC Output Feedback Data 62 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK63
     * Offset: 0x454  SHA/HMAC Output Feedback Data 63 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK64
     * Offset: 0x458  SHA/HMAC Output Feedback Data 64 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK65
     * Offset: 0x45C  SHA/HMAC Output Feedback Data 65 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK66
     * Offset: 0x460  SHA/HMAC Output Feedback Data 66 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK67
     * Offset: 0x464  SHA/HMAC Output Feedback Data 67 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK68
     * Offset: 0x468  SHA/HMAC Output Feedback Data 68 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK69
     * Offset: 0x46C  SHA/HMAC Output Feedback Data 69 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK70
     * Offset: 0x470  SHA/HMAC Output Feedback Data 70 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK71
     * Offset: 0x474  SHA/HMAC Output Feedback Data 71 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK72
     * Offset: 0x478  SHA/HMAC Output Feedback Data 72 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK73
     * Offset: 0x47C  SHA/HMAC Output Feedback Data 73 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK74
     * Offset: 0x480  SHA/HMAC Output Feedback Data 74 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK75
     * Offset: 0x484  SHA/HMAC Output Feedback Data 75 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK76
     * Offset: 0x488  SHA/HMAC Output Feedback Data 76 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK77
     * Offset: 0x48C  SHA/HMAC Output Feedback Data 77 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK78
     * Offset: 0x490  SHA/HMAC Output Feedback Data 78 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK79
     * Offset: 0x494  SHA/HMAC Output Feedback Data 79 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK80
     * Offset: 0x498  SHA/HMAC Output Feedback Data 80 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK81
     * Offset: 0x49C  SHA/HMAC Output Feedback Data 81 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK82
     * Offset: 0x4A0  SHA/HMAC Output Feedback Data 82 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK83
     * Offset: 0x4A4  SHA/HMAC Output Feedback Data 83 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK84
     * Offset: 0x4A8  SHA/HMAC Output Feedback Data 84 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK85
     * Offset: 0x4AC  SHA/HMAC Output Feedback Data 85 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK86
     * Offset: 0x4B0  SHA/HMAC Output Feedback Data 86 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_FDBCK87
     * Offset: 0x4B4  SHA/HMAC Output Feedback Data 87 After SHA/HMAC Operation
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FDBCK     |SHA/HMAC Feedback Information
     * |        |          |The feedback value is 1728 bits in size for SHA1/2 and 2784 bits in size for SHA3.
     * |        |          |The SHA/HMAC engine uses the data from CRPT_HMAC_FDBCKx as the data inputted to CRPT_HMAC_FDBCKx for the next block in DMA cascade mode.
     * |        |          |The SHA/HMAC engine outputs feedback information for initial setting in the next blocku2019s operation
     * |        |          |Software can store that feedback value temporarily
     * |        |          |After switching back, fill the stored feedback value to CRPT_HMAC_FDBCKx in the same operation, and then continue the operation with the original setting.
     * @var CRPT_T::HMAC_SHA512T
     * Offset: 0x4F8  SHA/HMAC SHA512/t Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SHA512TEN |SHA512/t Engine Enable Bit
     * |        |          |0 = Execute other function.
     * |        |          |1 = Execute SHA512/t function if SHA3EN=0.
     * |        |          |Note: When SHA512TEN=1, SHA/HMAC only execute SHA2-512.
     * |[16:8]  |TLEN      |SHA512/t output digest length
     * |        |          |The TLEN is equal to value t of SHA512/t. It also means the output digest length of SHA512 /t.
     * |        |          |Note: TLEN < 512, and TLEN is not 384
     * @var CRPT_T::HMAC_FBADDR
     * Offset: 0x4FC  SHA/HMAC DMA Feedback Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |FBADDR    |SHA/HMAC DMA Feedback Address
     * |        |          |In DMA cascade mode, software can update DMA feedback address register for automatically reading and writing feedback values via DMA
     * |        |          |The FBADDR keeps the feedback address of the feedback data for the next cascade operation
     * |        |          |Based on the feedback address, the SHA/HMAC accelerator can read the feedback data of the last cascade operation from SRAM memory space and write the feedback data of the current cascade operation to SRAM memory space
     * |        |          |The start of feedback address should be located at word boundary
     * |        |          |In other words, bit 1 and 0 of FBADDR are ignored.
     * |        |          |FBADDR can be read and written.
     * |        |          |In DMA mode, software can update the next CRPT_HMAC_FBADDR before triggering START.
     * @var CRPT_T::HMAC_SHAKEDGST0
     * Offset: 0x500  SHA/HMAC SHAKE Digest Message 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST1
     * Offset: 0x504  SHA/HMAC SHAKE Digest Message 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST2
     * Offset: 0x508  SHA/HMAC SHAKE Digest Message 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST3
     * Offset: 0x50C  SHA/HMAC SHAKE Digest Message 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST4
     * Offset: 0x510  SHA/HMAC SHAKE Digest Message 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST5
     * Offset: 0x514  SHA/HMAC SHAKE Digest Message 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST6
     * Offset: 0x518  SHA/HMAC SHAKE Digest Message 6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST7
     * Offset: 0x51C  SHA/HMAC SHAKE Digest Message 7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST8
     * Offset: 0x520  SHA/HMAC SHAKE Digest Message 8
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST9
     * Offset: 0x524  SHA/HMAC SHAKE Digest Message 9
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST10
     * Offset: 0x528  SHA/HMAC SHAKE Digest Message 10
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST11
     * Offset: 0x52C  SHA/HMAC SHAKE Digest Message 11
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST12
     * Offset: 0x530  SHA/HMAC SHAKE Digest Message 12
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST13
     * Offset: 0x534  SHA/HMAC SHAKE Digest Message 13
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST14
     * Offset: 0x538  SHA/HMAC SHAKE Digest Message 14
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST15
     * Offset: 0x53C  SHA/HMAC SHAKE Digest Message 15
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST16
     * Offset: 0x540  SHA/HMAC SHAKE Digest Message 16
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST17
     * Offset: 0x544  SHA/HMAC SHAKE Digest Message 17
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST18
     * Offset: 0x548  SHA/HMAC SHAKE Digest Message 18
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST19
     * Offset: 0x54C  SHA/HMAC SHAKE Digest Message 19
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST20
     * Offset: 0x550  SHA/HMAC SHAKE Digest Message 20
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST21
     * Offset: 0x554  SHA/HMAC SHAKE Digest Message 21
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST22
     * Offset: 0x558  SHA/HMAC SHAKE Digest Message 22
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST23
     * Offset: 0x55C  SHA/HMAC SHAKE Digest Message 23
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST24
     * Offset: 0x560  SHA/HMAC SHAKE Digest Message 24
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST25
     * Offset: 0x564  SHA/HMAC SHAKE Digest Message 25
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST26
     * Offset: 0x568  SHA/HMAC SHAKE Digest Message 26
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST27
     * Offset: 0x56C  SHA/HMAC SHAKE Digest Message 27
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST28
     * Offset: 0x570  SHA/HMAC SHAKE Digest Message 28
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST29
     * Offset: 0x574  SHA/HMAC SHAKE Digest Message 29
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST30
     * Offset: 0x578  SHA/HMAC SHAKE Digest Message 30
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST31
     * Offset: 0x57C  SHA/HMAC SHAKE Digest Message 31
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST32
     * Offset: 0x580  SHA/HMAC SHAKE Digest Message 32
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST33
     * Offset: 0x584  SHA/HMAC SHAKE Digest Message 33
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST34
     * Offset: 0x588  SHA/HMAC SHAKE Digest Message 34
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST35
     * Offset: 0x58C  SHA/HMAC SHAKE Digest Message 35
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST36
     * Offset: 0x590  SHA/HMAC SHAKE Digest Message 36
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST37
     * Offset: 0x594  SHA/HMAC SHAKE Digest Message 37
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST38
     * Offset: 0x598  SHA/HMAC SHAKE Digest Message 38
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST39
     * Offset: 0x59C  SHA/HMAC SHAKE Digest Message 39
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST40
     * Offset: 0x5A0  SHA/HMAC SHAKE Digest Message 40
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::HMAC_SHAKEDGST41
     * Offset: 0x5A4  SHA/HMAC SHAKE Digest Message 41
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DGST      |SHA/HMAC SHAKE Digest Message Register
     * |        |          |For SHAKE-128, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 41.
     * |        |          |For SHAKE-256, the digest is stored in CRPT_HMAC_SHAKEDGST0 0 ~ CRPT_HMAC_ SHAKEDGST0 33.
     * @var CRPT_T::ECC_CTL
     * Offset: 0x800  ECC Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |ECC Accelerator Start
     * |        |          |0 = No effect.
     * |        |          |1 = Start ECC accelerator. BUSY flag will be set.
     * |        |          |This bit is always 0 when it is read back.
     * |        |          |ECC accelerator will ignore this START signal when BUSY flag is 1.
     * |[1]     |STOP      |ECC Accelerator Stop
     * |        |          |0 = No effect.
     * |        |          |1 = Abort ECC accelerator and make it into idle state.
     * |        |          |This bit is always 0 when it is read back.
     * |        |          |Remember to clear ECC interrupt flag after stopping ECC accelerator.
     * |[3]     |PFA2C     |Prime Field Adder with 2 Cycles
     * |        |          |0 = cost 1 cycle .
     * |        |          |1 = cost 2 cycles.
     * |[4]     |ECDSAS    |Generate S in ECDSA Signature Generation
     * |        |          |0 = No effect.
     * |        |          |1 = Formula for generating S.
     * |        |          |POINTX1 = ((POINTX2 * POINTY1 + POINTY2 ) / POINTX1) % CURVEN.
     * |[5]     |ECDSAR    |Generate R in ECDSA Signature Generation
     * |        |          |0 = No effect.
     * |        |          |1 = Formula for generating R.
     * |        |          |(POINTX1, POINTY1) = SCALARK * (POINTX1, POINTY1).
     * |[6]     |DFAP      |Differential Fault Attack Protection
     * |        |          |0 = Differential fault attack protection Disabled.
     * |        |          |1 = Differential fault attack protection Enabled.
     * |[7]     |DMAEN     |ECC Accelerator DMA Enable Bit
     * |        |          |0 = ECC DMA engine Disabled.
     * |        |          |1 = ECC DMA engine Enabled.
     * |        |          |Only when START and DMAEN are 1, ECC DMA engine will be active.
     * |[8]     |FSEL      |Field Selection
     * |        |          |0 = Binary Field (GF(2m )).
     * |        |          |1 = Prime Field (GF(p)).
     * |[10:9]  |ECCOP     |Point Operation for BF and PF
     * |        |          |00 = Point multiplication:.
     * |        |          |(POINTX1, POINTY1) = SCALARK * (POINTX1, POINTY1).
     * |        |          |01 = Modulus operation: choose by MODOP (CRPT_ECC_CTL[12:11]).
     * |        |          |10 = Point addition:.
     * |        |          |(POINTX1, POINTY1) = (POINTX1, POINTY1) +.
     * |        |          |(POINTX2, POINTY2)
     * |        |          |11 = Point doubling:.
     * |        |          |(POINTX1, POINTY1) = 2 * (POINTX1, POINTY1).
     * |        |          |Besides above three input data, point operations still need the parameters of elliptic curve (CURVEA, CURVEB, CURVEN and CURVEM) as shown in Figure 6.27-11
     * |[12:11] |MODOP     |Modulus Operation for PF
     * |        |          |00 = Division:.
     * |        |          |POINTX1 = (POINTY1 / POINTX1) % CURVEN.
     * |        |          |01 = Multiplication:.
     * |        |          |POINTX1 = (POINTX1 * POINTY1) % CURVEN.
     * |        |          |10 = Addition:.
     * |        |          |POINTX1 = (POINTX1 + POINTY1) % CURVEN.
     * |        |          |11 = Subtraction:.
     * |        |          |POINTX1 = (POINTX1 - POINTY1) % CURVEN.
     * |        |          |MODOP is active only when ECCOP = 01.
     * |[13]    |CSEL      |Curve Selection
     * |        |          |0 = NIST suggested curve.
     * |        |          |1 = Montgomery curve.
     * |[14]    |SCAP      |Side-channel Attack Protection
     * |        |          |0 = Full speed without side-channel protection.
     * |        |          |1 = Less speed with side-channel protection.
     * |[16]    |LDP1      |The Control Signal of Register POINTX1 and POINTY1 for the x and Y Coordinate of the First Point
     * |        |          |0 = The register for POINTX1 and POINTY1 is not modified by DMA or user.
     * |        |          |1 = The register for POINTX1 and POINTY1 is modified by DMA or user.
     * |[17]    |LDP2      |The Control Signal of Register POINTX2 and POINTY2 for the x and Y Coordinate of the Second Point
     * |        |          |0 = The register for POINTX2 and POINTY2 is not modified by DMA or user.
     * |        |          |1 = The register for POINTX2 and POINTY2 is modified by DMA or user.
     * |[18]    |LDA       |The Control Signal of Register for the Parameter CURVEA of Elliptic Curve
     * |        |          |0 = The register for CURVEA is not modified by DMA or user.
     * |        |          |1 = The register for CURVEA is modified by DMA or user.
     * |[19]    |LDB       |The Control Signal of Register for the Parameter CURVEB of Elliptic Curve
     * |        |          |0 = The register for CURVEB is not modified by DMA or user.
     * |        |          |1 = The register for CURVEB is modified by DMA or user.
     * |[20]    |LDN       |The Control Signal of Register for the Parameter CURVEN of Elliptic Curve
     * |        |          |0 = The register for CURVEN is not modified by DMA or user.
     * |        |          |1 = The register for CURVEN is modified by DMA or user.
     * |[21]    |LDK       |The Control Signal of Register for SCALARK
     * |        |          |0 = The register for SCALARK is not modified by DMA or user.
     * |        |          |1 = The register for SCALARK is modified by DMA or user.
     * |[31:22] |CURVEM    |The key length of elliptic curve.
     * @var CRPT_T::ECC_STS
     * Offset: 0x804  ECC Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |ECC Accelerator Busy Flag
     * |        |          |0 = The ECC accelerator is idle or finished.
     * |        |          |1 = The ECC accelerator is under processing and protects all registers.
     * |        |          |Note: Remember to clear ECC interrupt flag after ECC accelerator is finished
     * |[1]     |DMABUSY   |ECC DMA Busy Flag
     * |        |          |0 = ECC DMA is idle or finished.
     * |        |          |1 = ECC DMA is busy.
     * |[16]    |BUSERR    |ECC DMA Access Bus Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Bus error will stop DMA operation and ECC accelerator.
     * |[17]    |KSERR     |ECC Engine Access Key Store Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Access error will stop ECC engine.
     * |[18]    |DFAERR    |ECC Engine Differential Fault Attack Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Differential Fault Attack happened in ECC engine. The results from ECC engine are wrong.
     * @var CRPT_T::ECC_X1_00
     * Offset: 0x808  ECC the X-coordinate Word0 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_01
     * Offset: 0x80C  ECC the X-coordinate Word1 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_02
     * Offset: 0x810  ECC the X-coordinate Word2 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_03
     * Offset: 0x814  ECC the X-coordinate Word3 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_04
     * Offset: 0x818  ECC the X-coordinate Word4 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_05
     * Offset: 0x81C  ECC the X-coordinate Word5 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_06
     * Offset: 0x820  ECC the X-coordinate Word6 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_07
     * Offset: 0x824  ECC the X-coordinate Word7 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_08
     * Offset: 0x828  ECC the X-coordinate Word8 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_09
     * Offset: 0x82C  ECC the X-coordinate Word9 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_10
     * Offset: 0x830  ECC the X-coordinate Word10 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_11
     * Offset: 0x834  ECC the X-coordinate Word11 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_12
     * Offset: 0x838  ECC the X-coordinate Word12 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_13
     * Offset: 0x83C  ECC the X-coordinate Word13 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_14
     * Offset: 0x840  ECC the X-coordinate Word14 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_15
     * Offset: 0x844  ECC the X-coordinate Word15 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_16
     * Offset: 0x848  ECC the X-coordinate Word16 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_X1_17
     * Offset: 0x84C  ECC the X-coordinate Word17 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX1   |ECC the X-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
     * |        |          |For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
     * |        |          |For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
     * |        |          |For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
     * |        |          |For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
     * |        |          |For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
     * |        |          |For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
     * |        |          |For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
     * @var CRPT_T::ECC_Y1_00
     * Offset: 0x850  ECC the Y-coordinate Word0 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_01
     * Offset: 0x854  ECC the Y-coordinate Word1 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_02
     * Offset: 0x858  ECC the Y-coordinate Word2 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_03
     * Offset: 0x85C  ECC the Y-coordinate Word3 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_04
     * Offset: 0x860  ECC the Y-coordinate Word4 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_05
     * Offset: 0x864  ECC the Y-coordinate Word5 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_06
     * Offset: 0x868  ECC the Y-coordinate Word6 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_07
     * Offset: 0x86C  ECC the Y-coordinate Word7 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_08
     * Offset: 0x870  ECC the Y-coordinate Word8 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_09
     * Offset: 0x874  ECC the Y-coordinate Word9 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_10
     * Offset: 0x878  ECC the Y-coordinate Word10 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_11
     * Offset: 0x87C  ECC the Y-coordinate Word11 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_12
     * Offset: 0x880  ECC the Y-coordinate Word12 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_13
     * Offset: 0x884  ECC the Y-coordinate Word13 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_14
     * Offset: 0x888  ECC the Y-coordinate Word14 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_15
     * Offset: 0x88C  ECC the Y-coordinate Word15 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_16
     * Offset: 0x890  ECC the Y-coordinate Word16 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_Y1_17
     * Offset: 0x894  ECC the Y-coordinate Word17 of the First Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY1   |ECC the Y-coordinate Value of the First Point
     * |        |          |For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
     * |        |          |For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
     * |        |          |For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
     * |        |          |For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
     * |        |          |For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
     * |        |          |For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
     * |        |          |For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
     * |        |          |For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
     * @var CRPT_T::ECC_X2_00
     * Offset: 0x898  ECC the X-coordinate Word0 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_01
     * Offset: 0x89C  ECC the X-coordinate Word1 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_02
     * Offset: 0x8A0  ECC the X-coordinate Word2 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_03
     * Offset: 0x8A4  ECC the X-coordinate Word3 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_04
     * Offset: 0x8A8  ECC the X-coordinate Word4 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_05
     * Offset: 0x8AC  ECC the X-coordinate Word5 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_06
     * Offset: 0x8B0  ECC the X-coordinate Word6 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_07
     * Offset: 0x8B4  ECC the X-coordinate Word7 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_08
     * Offset: 0x8B8  ECC the X-coordinate Word8 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_09
     * Offset: 0x8BC  ECC the X-coordinate Word9 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_10
     * Offset: 0x8C0  ECC the X-coordinate Word10 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_11
     * Offset: 0x8C4  ECC the X-coordinate Word11 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_12
     * Offset: 0x8C8  ECC the X-coordinate Word12 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_13
     * Offset: 0x8CC  ECC the X-coordinate Word13 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_14
     * Offset: 0x8D0  ECC the X-coordinate Word14 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_15
     * Offset: 0x8D4  ECC the X-coordinate Word15 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_16
     * Offset: 0x8D8  ECC the X-coordinate Word16 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_X2_17
     * Offset: 0x8DC  ECC the X-coordinate Word17 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTX2   |ECC the X-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
     * |        |          |For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
     * |        |          |For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
     * |        |          |For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
     * |        |          |For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
     * |        |          |For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
     * |        |          |For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
     * |        |          |For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
     * @var CRPT_T::ECC_Y2_00
     * Offset: 0x8E0  ECC the Y-coordinate Word0 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_01
     * Offset: 0x8E4  ECC the Y-coordinate Word1 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_02
     * Offset: 0x8E8  ECC the Y-coordinate Word2 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_03
     * Offset: 0x8EC  ECC the Y-coordinate Word3 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_04
     * Offset: 0x8F0  ECC the Y-coordinate Word4 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_05
     * Offset: 0x8F4  ECC the Y-coordinate Word5 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_06
     * Offset: 0x8F8  ECC the Y-coordinate Word6 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_07
     * Offset: 0x8FC  ECC the Y-coordinate Word7 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_08
     * Offset: 0x900  ECC the Y-coordinate Word8 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_09
     * Offset: 0x904  ECC the Y-coordinate Word9 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_10
     * Offset: 0x908  ECC the Y-coordinate Word10 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_11
     * Offset: 0x90C  ECC the Y-coordinate Word11 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_12
     * Offset: 0x910  ECC the Y-coordinate Word12 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_13
     * Offset: 0x914  ECC the Y-coordinate Word13 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_14
     * Offset: 0x918  ECC the Y-coordinate Word14 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_15
     * Offset: 0x91C  ECC the Y-coordinate Word15 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_16
     * Offset: 0x920  ECC the Y-coordinate Word16 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_Y2_17
     * Offset: 0x924  ECC the Y-coordinate Word17 of the Second Point
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |POINTY2   |ECC the Y-coordinate Value of the Second Point
     * |        |          |For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
     * |        |          |For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
     * |        |          |For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
     * |        |          |For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
     * |        |          |For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
     * |        |          |For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
     * |        |          |For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
     * |        |          |For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
     * @var CRPT_T::ECC_A_00
     * Offset: 0x928  ECC the Parameter CURVEA Word0 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_01
     * Offset: 0x92C  ECC the Parameter CURVEA Word1 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_02
     * Offset: 0x930  ECC the Parameter CURVEA Word2 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_03
     * Offset: 0x934  ECC the Parameter CURVEA Word3 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_04
     * Offset: 0x938  ECC the Parameter CURVEA Word4 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_05
     * Offset: 0x93C  ECC the Parameter CURVEA Word5 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_06
     * Offset: 0x940  ECC the Parameter CURVEA Word6 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_07
     * Offset: 0x944  ECC the Parameter CURVEA Word7 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_08
     * Offset: 0x948  ECC the Parameter CURVEA Word8 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_09
     * Offset: 0x94C  ECC the Parameter CURVEA Word9 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_10
     * Offset: 0x950  ECC the Parameter CURVEA Word10 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_11
     * Offset: 0x954  ECC the Parameter CURVEA Word11 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_12
     * Offset: 0x958  ECC the Parameter CURVEA Word12 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_13
     * Offset: 0x95C  ECC the Parameter CURVEA Word13 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_14
     * Offset: 0x960  ECC the Parameter CURVEA Word14 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_15
     * Offset: 0x964  ECC the Parameter CURVEA Word15 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_16
     * Offset: 0x968  ECC the Parameter CURVEA Word16 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_A_17
     * Offset: 0x96C  ECC the Parameter CURVEA Word17 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEA    |ECC the Parameter CURVEA Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
     * |        |          |For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
     * |        |          |For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
     * |        |          |For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
     * |        |          |For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
     * |        |          |For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
     * |        |          |For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
     * |        |          |For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
     * @var CRPT_T::ECC_B_00
     * Offset: 0x970  ECC the Parameter CURVEB Word0 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_01
     * Offset: 0x974  ECC the Parameter CURVEB Word1 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_02
     * Offset: 0x978  ECC the Parameter CURVEB Word2 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_03
     * Offset: 0x97C  ECC the Parameter CURVEB Word3 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_04
     * Offset: 0x980  ECC the Parameter CURVEB Word4 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_05
     * Offset: 0x984  ECC the Parameter CURVEB Word5 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_06
     * Offset: 0x988  ECC the Parameter CURVEB Word6 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_07
     * Offset: 0x98C  ECC the Parameter CURVEB Word7 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_08
     * Offset: 0x990  ECC the Parameter CURVEB Word8 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_09
     * Offset: 0x994  ECC the Parameter CURVEB Word9 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_10
     * Offset: 0x998  ECC the Parameter CURVEB Word10 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_11
     * Offset: 0x99C  ECC the Parameter CURVEB Word11 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_12
     * Offset: 0x9A0  ECC the Parameter CURVEB Word12 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_13
     * Offset: 0x9A4  ECC the Parameter CURVEB Word13 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_14
     * Offset: 0x9A8  ECC the Parameter CURVEB Word14 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_15
     * Offset: 0x9AC  ECC the Parameter CURVEB Word15 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_16
     * Offset: 0x9B0  ECC the Parameter CURVEB Word16 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_B_17
     * Offset: 0x9B4  ECC the Parameter CURVEB Word17 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEB    |ECC the Parameter CURVEB Value of Elliptic Curve
     * |        |          |The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2m).
     * |        |          |For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
     * |        |          |For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
     * |        |          |For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
     * |        |          |For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
     * |        |          |For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
     * |        |          |For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
     * |        |          |For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
     * |        |          |For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
     * @var CRPT_T::ECC_N_00
     * Offset: 0x9B8  ECC the Parameter CURVEN Word0 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_01
     * Offset: 0x9BC  ECC the Parameter CURVEN Word1 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_02
     * Offset: 0x9C0  ECC the Parameter CURVEN Word2 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_03
     * Offset: 0x9C4  ECC the Parameter CURVEN Word3 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_04
     * Offset: 0x9C8  ECC the Parameter CURVEN Word4 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_05
     * Offset: 0x9CC  ECC the Parameter CURVEN Word5 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_06
     * Offset: 0x9D0  ECC the Parameter CURVEN Word6 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_07
     * Offset: 0x9D4  ECC the Parameter CURVEN Word7 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_08
     * Offset: 0x9D8  ECC the Parameter CURVEN Word8 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_09
     * Offset: 0x9DC  ECC the Parameter CURVEN Word9 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_10
     * Offset: 0x9E0  ECC the Parameter CURVEN Word10 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_11
     * Offset: 0x9E4  ECC the Parameter CURVEN Word11 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_12
     * Offset: 0x9E8  ECC the Parameter CURVEN Word12 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_13
     * Offset: 0x9EC  ECC the Parameter CURVEN Word13 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_14
     * Offset: 0x9F0  ECC the Parameter CURVEN Word14 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_15
     * Offset: 0x9F4  ECC the Parameter CURVEN Word15 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_16
     * Offset: 0x9F8  ECC the Parameter CURVEN Word16 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_N_17
     * Offset: 0x9FC  ECC the Parameter CURVEN Word17 of Elliptic Curve
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURVEN    |ECC the Parameter CURVEN Value of Elliptic Curve
     * |        |          |In GF(p), CURVEN is the prime p.
     * |        |          |In GF(2m), CURVEN is the irreducible polynomial.
     * |        |          |For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
     * |        |          |For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
     * |        |          |For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
     * |        |          |For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
     * |        |          |For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
     * |        |          |For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
     * |        |          |For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
     * |        |          |For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
     * @var CRPT_T::ECC_K_00
     * Offset: 0xA00  ECC the Scalar SCALARK Word0 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_01
     * Offset: 0xA04  ECC the Scalar SCALARK Word1 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_02
     * Offset: 0xA08  ECC the Scalar SCALARK Word2 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_03
     * Offset: 0xA0C  ECC the Scalar SCALARK Word3 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_04
     * Offset: 0xA10  ECC the Scalar SCALARK Word4 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_05
     * Offset: 0xA14  ECC the Scalar SCALARK Word5 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_06
     * Offset: 0xA18  ECC the Scalar SCALARK Word6 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_07
     * Offset: 0xA1C  ECC the Scalar SCALARK Word7 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_08
     * Offset: 0xA20  ECC the Scalar SCALARK Word8 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_09
     * Offset: 0xA24  ECC the Scalar SCALARK Word9 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_10
     * Offset: 0xA28  ECC the Scalar SCALARK Word10 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_11
     * Offset: 0xA2C  ECC the Scalar SCALARK Word11 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_12
     * Offset: 0xA30  ECC the Scalar SCALARK Word12 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_13
     * Offset: 0xA34  ECC the Scalar SCALARK Word13 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_14
     * Offset: 0xA38  ECC the Scalar SCALARK Word14 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_15
     * Offset: 0xA3C  ECC the Scalar SCALARK Word15 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_16
     * Offset: 0xA40  ECC the Scalar SCALARK Word16 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_K_17
     * Offset: 0xA44  ECC the Scalar SCALARK Word17 of Point Multiplication
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SCALARK   |ECC the Scalar SCALARK Value of Point Multiplication
     * |        |          |Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
     * |        |          |For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
     * |        |          |For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
     * |        |          |For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
     * |        |          |For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
     * |        |          |For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
     * |        |          |For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
     * |        |          |For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
     * |        |          |For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
     * @var CRPT_T::ECC_SADDR
     * Offset: 0xA48  ECC DMA Source Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var CRPT_T::ECC_DADDR
     * Offset: 0xA4C  ECC DMA Destination Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DADDR     |ECC DMA Destination Address
     * |        |          |The ECC accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory and ECC accelerator
     * |        |          |The DADDR keeps the destination address of the data buffer where output data of ECC engine will be stored
     * |        |          |Based on the destination address, the ECC accelerator can write the result data back to SRAM memory space after the ECC operation is finished
     * |        |          |The start of destination address should be located at word boundary
     * |        |          |That is, bit 1 and 0 of DADDR are ignored
     * |        |          |DADDR can be read and written
     * |        |          |In DMA mode, software must update the CRPT_ECC_DADDR before triggering START
     * @var CRPT_T::ECC_STARTREG
     * Offset: 0xA50  ECC Starting Address of Updated Registers
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |STARTREG  |ECC Starting Address of Updated Registers
     * |        |          |The address of the updated registers that DMA feeds the first data or parameter to ECC engine
     * |        |          |When ECC engine is active, ECC accelerator does not allow users to modify STARTRE.G
     * |        |          |For example, to update input data from register CRPT_ECC POINTX1
     * |        |          |Thus, the value of STARTREG is 0x808.
     * @var CRPT_T::ECC_WORDCNT
     * Offset: 0xA54  ECC DMA Word Count
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |WORDCNT   |ECC DMA Word Count
     * |        |          |The CRPT_ECC_WORDCNT keeps the word count of source data that is for the required input data of ECC accelerator with various operations in DMA mode
     * |        |          |Although CRPT_ECC_WORDCNT is 32-bit, the maximum of word count in ECC accelerator is 144 words
     * |        |          |CRPT_ECC_WORDCNT can be read and written
     * @var CRPT_T::RSA_CTL
     * Offset: 0xB00  RSA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |START     |RSA Accelerator Start
     * |        |          |0 = No effect.
     * |        |          |1 = Start RSA accelerator. BUSY flag will be set.
     * |        |          |This bit is always 0 when it is read back.
     * |        |          |RSA accelerator will ignore this START signal when BUSY flag is 1.
     * |[1]     |STOP      |RSA Accelerator Stop
     * |        |          |0 = No effect.
     * |        |          |1 = Abort RSA accelerator and make it into initial state.
     * |        |          |This bit is always 0 when it is read back.
     * |        |          |Remember to clear RSA interrupt flag after stopping RSA accelerator.
     * |[2]     |CRT       |CRT Enable Control
     * |        |          |0 = CRT Disabled.
     * |        |          |1 = CRT Enabled.
     * |        |          |CRT is only used in decryption with key length 2048, 3072,4096 bits.
     * |[3]     |CRTBYP    |CRT Bypass Enable Control
     * |        |          |0 = CRT Bypass Disabled.
     * |        |          |1 = CRT Bypass Enabled.
     * |        |          |CRT bypass is only used in CRT decryption with the same key.
     * |        |          |Note: If users want to decrypt repeatedly with the same key, they can execute CRT bypass mode after the first time CRT decryption (means the second time to the latest time), but they cannot set CRTBYP to 1 in non-CRT mode.
     * |[5:4]   |KEYLENG   |The Key Length of RSA Operation
     * |        |          |00 = 1024-bits.
     * |        |          |01 = 2048-bits.
     * |        |          |10 = 3072-bits.
     * |        |          |11 = 4096-bits.
     * |[8]     |SCAP      |Side Channel Attack Protection Enable Control
     * |        |          |0 = Side Channel Attack Protection Disabled.
     * |        |          |1 = Side Channel Attack Protection Enabled.
     * @var CRPT_T::RSA_STS
     * Offset: 0xB04  RSA Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BUSY      |RSA Accelerator Busy Flag
     * |        |          |0 = The RSA accelerator is idle or finished.
     * |        |          |1 = The RSA accelerator is under processing and protects all registers.
     * |        |          |Remember to clear RSA interrupt flag after RSA accelerator finished.
     * |[1]     |DMABUSY   |RSA DMA Busy Flag
     * |        |          |0 = RSA DMA is idle or finished.
     * |        |          |1 = RSA DMA is busy.
     * |[16]    |BUSERR    |RSA DMA Access Bus Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Bus error will stop DMA operation and RSA accelerator.
     * |[17]    |CTLERR    |RSA Control Register Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = RSA control error. RSA will not start in the unsupported situation.
     * |        |          |Note: If users use the error combination of control, even though they donu2019t set START(CRPT_RSA_CTL[0]) to 1, CTLERR still be set to 1.
     * |[18]    |KSERR     |RSA Engine Access Key Store Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = Access error will stop RSA engine.
     * @var CRPT_T::RSA_SADDR0
     * Offset: 0xB08  RSA DMA Source Address Register0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SADDR0    |RSA DMA Source Address Register0
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA the Base of Exponentiation (M).
     * @var CRPT_T::RSA_SADDR1
     * Offset: 0xB0C  RSA DMA Source Address Register1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SADDR1    |RSA DMA Source Address Register1
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA the Base of Modulus Operation (N).
     * @var CRPT_T::RSA_SADDR2
     * Offset: 0xB10  RSA DMA Source Address Register2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SADDR2    |RSA DMA Source Address Register2
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA the Exponent of Exponentiation (E).
     * @var CRPT_T::RSA_SADDR3
     * Offset: 0xB14  RSA DMA Source Address Register3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SADDR3    |RSA DMA Source Address Register3
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA the Factor of Modulus Operation (p).
     * @var CRPT_T::RSA_SADDR4
     * Offset: 0xB18  RSA DMA Source Address Register4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SADDR4    |RSA DMA Source Address Register4
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA the Factor of Modulus Operation (q).
     * @var CRPT_T::RSA_DADDR
     * Offset: 0xB1C  RSA DMA Destination Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DADDR     |RSA DMA Destination Address Register
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA DMA Destination Address Register (Ans).
     * @var CRPT_T::RSA_MADDR0
     * Offset: 0xB20  RSA DMA Middle Address Register0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MADDR0    |RSA DMA Middle Address Register0
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA CRT the Temporary Value (Cp -> Mp -> Sp).
     * @var CRPT_T::RSA_MADDR1
     * Offset: 0xB24  RSA DMA Middle Address Register1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MADDR1    |RSA DMA Middle Address Register1
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA CRT the Temporary Value (Cq -> Mq -> Sq).
     * @var CRPT_T::RSA_MADDR2
     * Offset: 0xB28  RSA DMA Middle Address Register2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MADDR2    |RSA DMA Middle Address Register2
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA CRT the Temporary Value (Dp).
     * @var CRPT_T::RSA_MADDR3
     * Offset: 0xB2C  RSA DMA Middle Address Register3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MADDR3    |RSA DMA Middle Address Register3
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA CRT the Temporary Value (Dq).
     * @var CRPT_T::RSA_MADDR4
     * Offset: 0xB30  RSA DMA Middle Address Register4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MADDR4    |RSA DMA Middle Address Register4
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA CRT the Temporary Value (Rp).
     * @var CRPT_T::RSA_MADDR5
     * Offset: 0xB34  RSA DMA Middle Address Register5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MADDR5    |RSA DMA Middle Address Register5
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA CRT the Temporary Value (Rq).
     * @var CRPT_T::RSA_MADDR6
     * Offset: 0xB38  RSA DMA Middle Address Register6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MADDR6    |RSA DMA Middle Address Register6
     * |        |          |The RSA accelerator supports DMA function to transfer the DATA and PARAMETER between SRAM memory space and RSA accelerator.
     * |        |          |This register is stored the address of RSA SCA Protection the Temporary Value (Eu2019).
     * @var CRPT_T::PRNG_KSCTL
     * Offset: 0xF00  PRNG Key Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM       |Write Key Number
     * |        |          |The key number is sent to key store
     * |        |          |Note: Only for destination Is OTP of key store.
     * |[16]    |TRUST     |Write Key Trust Selection Bit
     * |        |          |0 = Set written key as the non-secure key.
     * |        |          |1 = Set written key as the secure key.
     * |[19]    |ECDH      |ECDH Control Bit
     * |        |          |0 = reserved.
     * |        |          |1 = key is written to key store and used in ECDH.
     * |        |          |Note: When ECDH was set to u20181u2019,  1
     * |        |          |PRNG seed must from TRNG and key is must written to the SRAM of key store (WSDST, CRPT_PRNG_KSCTL[23:22] must set to u201800u2019)
     * |        |          |Otherwise, KCTLERR will become u20181u2019(CRPT_PRNG_KSSTS[16])
     * |        |          |2
     * |        |          |Key must in the interval [1, n-1] (the parameter n is from ECC)
     * |        |          |The value of n cannot be 0 or 1, otherwise, PRNG will always keep busy.
     * |[20]    |ECDSA     |ECDSA Control Bit
     * |        |          |0 = reserved.
     * |        |          |1 = key is written to key store and used in ECDSA.
     * |        |          |Note: When ECDSA was set to u20181u2019,  1
     * |        |          |PRNG seed must from TRNG and key is must written to the SRAM of key store (WSDST, CRPT_PRNG_KSCTL[23:22] must set to u201800u2019)
     * |        |          |Otherwise, KCTLERR will become u20181u2019(CRPT_PRNG_KSSTS[16])
     * |        |          |2
     * |        |          |Key must in the interval [1, n-1] (the parameter n is from ECC)
     * |        |          |The value of n cannot be 0 or 1, otherwise, PRNG will always keep busy.
     * |[21]    |WDST      |Write Key Destination
     * |        |          |0 = key is written to registers CRPT_PRNG_KEYx.
     * |        |          |1 = key is written to key store.
     * |[23:22] |WSDST     |Write Key Store Destination
     * |        |          |00 = key is written to the SRAM of key store.
     * |        |          |01 = key is written to the flash of key store.
     * |        |          |10 = key is written to the OTP of key store.
     * |        |          |Others = reserved.
     * |[26:24] |OWNER     |Write Key Owner Selection Bits
     * |        |          |000 = Only for AES used.
     * |        |          |001 = Only for HMAC engine used.
     * |        |          |100 = Only for ECC engine used.
     * |        |          |101 = Only for CPU engine use.
     * |        |          |Others = reserved.
     * @var CRPT_T::PRNG_KSSTS
     * Offset: 0xF04  PRNG Key Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM       |Key Number
     * |        |          |The key number is generated by key store
     * |[16]    |KCTLERR   |PRNG Key Control Register Error Flag
     * |        |          |0 = No error.
     * |        |          |1 = PRNG key control error
     * |        |          |When PRNG execute ECDSA or ECDH, but PRNG seed not from TRNG or key is not written to the SRAM of key store (WSDST, CRPT_PRNG_KSCTL[23:22] is not equal to u201900u2019).
     * @var CRPT_T::AES_KSCTL
     * Offset: 0xF10  AES Key Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM       |Read Key Number
     * |        |          |The key number is sent to key store
     * |[5]     |RSRC      |Read Key Source
     * |        |          |0 = key is read from registers CRPT_AESx_KEYx.
     * |        |          |1 = key is read from key store.
     * |[7:6]   |RSSRC     |Read Key Store Source
     * |        |          |00 = key is read from the SRAM of key store.
     * |        |          |01 = key is read from the flash of key store.
     * |        |          |10 = key is read from the OTP of key store.
     * |        |          |Others = reserved.
     * @var CRPT_T::HMAC_KSCTL
     * Offset: 0xF30  HMAC Key Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM       |Read Key Number
     * |        |          |The key number is sent to key store
     * |[5]     |RSRC      |Read Key Source
     * |        |          |0 = key is read from HMAC registers.
     * |        |          |1 = key is read from key store.
     * |[7:6]   |RSSRC     |Read Key Store Source
     * |        |          |00 = key is read from the SRAM of key store.
     * |        |          |01 = key is read from the flash of key store.
     * |        |          |10 = key is read from the OTP of key store.
     * |        |          |Others = reserved.
     * @var CRPT_T::ECC_KSCTL
     * Offset: 0xF40  ECC Key Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUMK      |Read Key Number K
     * |        |          |The key number of CRPT_ECC_K is sent to key store when RSRCK =1.
     * |[5]     |RSRCK     |Read Key Source for Key Number K
     * |        |          |0 = key is read from ECC registers.
     * |        |          |1 = key is read from key store.
     * |[7:6]   |RSSRCK    |Read Key Store Source for Key Number K
     * |        |          |00 = key is read from the SRAM of key store.
     * |        |          |01 = key is read from the flash of key store.
     * |        |          |10 = key is read from the OTP of key store.
     * |        |          |Others = reserved.
     * |[14]    |ECDH      |ECDH Control Bit
     * |        |          |0 = reserved.
     * |        |          |1 = Set ECC operation is in ECDH
     * |        |          |When this bit and RSRCK are equal to 0x1, ECC will read ECDH private key to CRPT_ECC_K from key store.
     * |[16]    |TRUST     |Write Key Trust Selection Bit
     * |        |          |0 = Set ECDH written key as the non-secure key.
     * |        |          |1 = Set ECDH written key as the secure key.
     * |[20]    |XY        |ECDH Output Select Bit
     * |        |          |0 = The ECDH written key is from X-coordinate Value.
     * |        |          |1 = The ECDH written key is from Y-coordinate Value.
     * |[21]    |WDST      |Write Key Destination
     * |        |          |0 = The ECDH written key is in registers CRPT_ECC_X1 and CRPT_ECC_Y.
     * |        |          |1 = The ECDH written key is written to key store.
     * |[23:22] |WSDST     |Write Key Store Destination
     * |        |          |00 = The ECDH written key is written to the SRAM of key store.
     * |        |          |01 = The ECDH written key is written to the flash of key store.
     * |        |          |10 = The ECDH written key is written to the OTP of key store.
     * |        |          |Others = reserved.
     * |[26:24] |OWNER     |Write Key Owner Selection Bits
     * |        |          |000 = The ECDH written key is only for AES used.
     * |        |          |001 = The ECDH written key is only for HMAC engine used.
     * |        |          |100 = The ECDH written key is only for ECC engine used.
     * |        |          |101 = The ECDH written key is only for CPU engine use.
     * |        |          |Others = reserved.
     * @var CRPT_T::ECC_KSSTS
     * Offset: 0xF44  ECC Key Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM       |Key Number
     * |        |          |The key number is generated by key store after ECDH.
     * @var CRPT_T::ECC_KSXY
     * Offset: 0xF48  ECC XY Number Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUMX      |Read Key Number X
     * |        |          |The key number of CRPT_ECC_X1 is sent to key store when RSRCXY =1.
     * |[5]     |RSRCXY    |Read Key Source for Key Number x and Y
     * |        |          |0 = Key is read from ECC registers.
     * |        |          |1 = Key is read from key store.
     * |[7:6]   |RSSRCX    |Read Key Store Source for Key Number X
     * |        |          |00 = Key is read from the SRAM of key store.
     * |        |          |01 = Key is read from the flash of key store.
     * |        |          |10 = Key is read from the OTP of key store.
     * |        |          |Others = reserved.
     * |[12:8]  |NUMY      |Read Key Number Y
     * |        |          |The key number of CRPT_ECC_Y1 is sent to key store when RSRCXY =1.
     * |[15:14] |RSSRCY    |Read Key Store Source for Key Number Y
     * |        |          |00 = Key is read from the SRAM of key store.
     * |        |          |01 = Key is read from the flash of key store.
     * |        |          |10 = Key is read from the OTP of key store.
     * |        |          |Others = reserved.
     * @var CRPT_T::RSA_KSCTL
     * Offset: 0xF50  RSA Key Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM       |Read Key Number
     * |        |          |The key number is sent to key store
     * |[5]     |RSRC      |Read Key Source
     * |        |          |0 = Key is read from RSA engine.
     * |        |          |1 = Key is read from key store.
     * |[7:6]   |RSSRC     |Read Key Store Source
     * |        |          |00 = Key is read from the SRAM of key store.
     * |        |          |Others = Reserved.
     * |[12:8]  |BKNUM     |Read Exponent Blind Key Number
     * |        |          |The key number is sent to key store, and its destination always be the SRAM of key store
     * |        |          |CPU cannot read the exponent blind key.
     * |        |          |Note: Use this key number, only when executing SCA protection but no-CRT mode
     * |        |          |When allocate space of key store, key owner selection bits(KS_METADATA[18:16]) should be u2018010u2019.
     * @var CRPT_T::RSA_KSSTS0
     * Offset: 0xF54  RSA Key Status Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM0      |Key Number0
     * |        |          |The key number is generated by key store, RSA can get complete p by key number in key store while operating.
     * |        |          |Note: The size of this key as half key length.
     * |[12:8]  |NUM1      |Key Number1
     * |        |          |The key number is generated by key store, RSA can get complete q by key number in Key Store while operating.
     * |        |          |Note: The size of this key as half key length.
     * |[20:16] |NUM2      |Key Number2
     * |        |          |The key number is generated by key store, RSA can get or store the intermediate temporary value(Cp) by key number in the key store while operating.
     * |        |          |Note: The size of this key as key length.
     * |[28:24] |NUM3      |Key Number3
     * |        |          |The key number is generated by key store, RSA can get or store the intermediate temporary value(Cq) by key number in the key store while operating.
     * |        |          |Note: The size of this key as key length.
     * @var CRPT_T::RSA_KSSTS1
     * Offset: 0xF58  RSA Key Status Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NUM4      |Key Number4
     * |        |          |The key number is generated by key store, RSA can get or store the intermediate temporary value(Dp) by key number in key store while operating.
     * |        |          |Note: The size of this key as half key length.
     * |[12:8]  |NUM5      |Key Number5
     * |        |          |The key number is generated by key store, RSA can get or store the intermediate temporary value(Dq) by key number in key store while operating.
     * |        |          |Note: The size of this key as half key length.
     * |[20:16] |NUM6      |Key Number6
     * |        |          |The key number is generated by key store, RSA can get or store the intermediate temporary value(Rp) by key number in key store while operating.
     * |        |          |Note: The size of this key as key length.
     * |[28:24] |NUM7      |Key Number7
     * |        |          |The key number is generated by key store, RSA can get or store the intermediate temporary value(Rq) by key number in key store while operating.
     * |        |          |Note: The size of this key as key length.
     * @var CRPT_T::VERSION
     * Offset: 0xFFC  Crypto RTL Design Version Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MINOR     |RTL Design Minor Version Number
     * |        |          |Minor version number is dependent on moduleu2019s ECO version control.
     * |        |          |0x1000:(Current Minor Version Number)
     * |[23:16] |SUB       |RTL Design Sub Version Number
     * |        |          |Sub version number is correlated to moduleu2019s key feature.
     * |        |          |0x01:(Current Sub Version Number)
     * |[31:24] |MAJOR     |RTL Design Major Version Number
     * |        |          |Major version number is correlated to Product Line.
     * |        |          |0x02:(Current Major Version Number)
     */
    __IO uint32_t INTEN;                 /*!< [0x0000] Crypto Interrupt Enable Control Register                         */
    __IO uint32_t INTSTS;                /*!< [0x0004] Crypto Interrupt Flag                                            */
    __IO uint32_t PRNG_CTL;              /*!< [0x0008] PRNG Control Register                                            */
    __O  uint32_t PRNG_SEED;             /*!< [0x000c] Seed for PRNG                                                    */
    __I  uint32_t PRNG_KEY[8];           /*!< [0x0010 - 0x002c] PRNG Generated Key0                                     */
    __I  uint32_t PRNG_STS;              /*!< [0x0030] PRNG Status Register                                             */
    __I  uint32_t RESERVE0[7];
    __I  uint32_t AES_FDBCK[4];          /*!< [0x0050 - 0x005c] AES Engine Output Feedback Data After Cryptographic Operation  */
    __I  uint32_t RESERVE1[8];
    __IO uint32_t AES_GCM_IVCNT[2];      /*!< [0x0080 - 0x0084] AES GCM IV Byte Count Register 0                                 */
    __IO uint32_t AES_GCM_ACNT[2];         /*!< [0x0088 - 0x008c] AES GCM A Byte Count Register 0                                  */
    __IO uint32_t AES_GCM_PCNT[2];         /*!< [0x0090 - 0x0094] AES GCM P Byte Count Register 0                                  */
    __I  uint32_t RESERVE2[2];
    __IO uint32_t AES_FBADDR;            /*!< [0x00a0] AES DMA Feedback Address Register                                */
    __I  uint32_t RESERVE3[23];
    __IO uint32_t AES_CTL;               /*!< [0x0100] AES Control Register                                             */
    __I  uint32_t AES_STS;               /*!< [0x0104] AES Engine Flag                                                  */
    __IO uint32_t AES_DATIN;             /*!< [0x0108] AES Engine Data Input Port Register                              */
    __I  uint32_t AES_DATOUT;            /*!< [0x010c] AES Engine Data Output Port Register                             */
    __IO uint32_t AES_KEY[8];              /*!< [0x0110 - 0x012c] AES Key Word 0 Register                                          */
    __IO uint32_t AES_IV[4];               /*!< [0x0130 - 0x013c] AES Initial Vector Word 0 Register                               */
    __IO uint32_t AES_SADDR;             /*!< [0x0140] AES DMA Source Address Register                                  */
    __IO uint32_t AES_DADDR;             /*!< [0x0144] AES DMA Destination Address Register                             */
    __IO uint32_t AES_CNT;               /*!< [0x0148] AES Byte Count Register                                          */
    __I  uint32_t RESERVE4[109];
    __IO uint32_t HMAC_CTL;              /*!< [0x0300] SHA/HMAC Control Register                                        */
    __I  uint32_t HMAC_STS;              /*!< [0x0304] SHA/HMAC Status Flag                                             */
    __I  uint32_t HMAC_DGST[16];            /*!< [0x0308 - 0x0344] SHA/HMAC Output Feedback Data 0                                  */
    __IO uint32_t HMAC_KEYCNT;           /*!< [0x0348] SHA/HMAC Key Byte Count Register                                 */
    __IO uint32_t HMAC_SADDR;            /*!< [0x034c] SHA/HMAC DMA Source Address Register                             */
    __IO uint32_t HMAC_DMACNT;           /*!< [0x0350] SHA/HMAC Byte Count Register                                     */
    __IO uint32_t HMAC_DATIN;            /*!< [0x0354] SHA/HMAC Engine Non-DMA Mode Data Input Port Register            */
    __IO uint32_t HMAC_FDBCK[88];           /*!< [0x0358 - 0x04b4] SHA/HMAC Output Feedback Data 0 After SHA/HMAC Operation         */
    __I  uint32_t RESERVE5[16];
    __IO uint32_t HMAC_SHA512T;          /*!< [0x04f8] SHA/HMAC SHA512/t Control Register                               */
    __IO uint32_t HMAC_FBADDR;           /*!< [0x04fc] SHA/HMAC DMA Feedback Address Register                           */
    __I  uint32_t HMAC_SHAKEDGST[42];       /*!< [0x0500 - 0x05a4] SHA/HMAC SHAKE Digest Message 0                                  */
    __I  uint32_t RESERVE6[150];
    __IO uint32_t ECC_CTL;               /*!< [0x0800] ECC Control Register                                             */
    __I  uint32_t ECC_STS;               /*!< [0x0804] ECC Status Register                                              */
    __IO uint32_t ECC_X1[18];             /*!< [0x0808 - 0x084c] ECC the X-coordinate Word0 of the First Point                    */
    __IO uint32_t ECC_Y1[18];             /*!< [0x0850 - 0x0894] ECC the Y-coordinate Word0 of the First Point                    */
    __IO uint32_t ECC_X2[18];             /*!< [0x0898 - 0x08dc] ECC the X-coordinate Word0 of the Second Point                   */
    __IO uint32_t ECC_Y2[18];             /*!< [0x08e0 - 0x0924] ECC the Y-coordinate Word0 of the Second Point                   */
    __IO uint32_t ECC_A[18];              /*!< [0x0928 - 0x096c] ECC the Parameter CURVEA Word0 of Elliptic Curve                 */
    __IO uint32_t ECC_B[18];              /*!< [0x0970 - 0x09b4] ECC the Parameter CURVEB Word0 of Elliptic Curve                 */
    __IO uint32_t ECC_N[18];              /*!< [0x09b8 - 0x09fc] ECC the Parameter CURVEN Word0 of Elliptic Curve                 */
    __O  uint32_t ECC_K[18];              /*!< [0x0a00 - 0x0a44] ECC the Scalar SCALARK Word0 of Point Multiplication             */
    __IO uint32_t ECC_SADDR;             /*!< [0x0a48] ECC DMA Source Address Register                                  */
    __IO uint32_t ECC_DADDR;             /*!< [0x0a4c] ECC DMA Destination Address Register                             */
    __IO uint32_t ECC_STARTREG;          /*!< [0x0a50] ECC Starting Address of Updated Registers                        */
    __IO uint32_t ECC_WORDCNT;           /*!< [0x0a54] ECC DMA Word Count                                               */
    __I  uint32_t RESERVE7[42];
    __IO uint32_t RSA_CTL;               /*!< [0x0b00] RSA Control Register                                             */
    __I  uint32_t RSA_STS;               /*!< [0x0b04] RSA Status Register                                              */
    __IO uint32_t RSA_SADDR[5];            /*!< [0x0b08 - 0x0b18] RSA DMA Source Address Register0                                 */
    __IO uint32_t RSA_DADDR;             /*!< [0x0b1c] RSA DMA Destination Address Register                             */
    __IO uint32_t RSA_MADDR[7];            /*!< [0x0b20 - 0x0b38] RSA DMA Middle Address Register0                                 */
    __I  uint32_t RESERVE8[241];
    __O  uint32_t PRNG_KSCTL;            /*!< [0x0f00] PRNG Key Control Register                                        */
    __I  uint32_t PRNG_KSSTS;            /*!< [0x0f04] PRNG Key Status Register                                         */
    __I  uint32_t RESERVE9[2];
    __O  uint32_t AES_KSCTL;             /*!< [0x0f10] AES Key Control Register                                         */
    __I  uint32_t RESERVE10[7];
    __O  uint32_t HMAC_KSCTL;            /*!< [0x0f30] HMAC Key Control Register                                        */
    __I  uint32_t RESERVE11[3];
    __O  uint32_t ECC_KSCTL;             /*!< [0x0f40] ECC Key Control Register                                         */
    __I  uint32_t ECC_KSSTS;             /*!< [0x0f44] ECC Key Status Register                                          */
    __O  uint32_t ECC_KSXY;              /*!< [0x0f48] ECC XY Number Register                                           */
    __I  uint32_t RESERVE12[1];
    __O  uint32_t RSA_KSCTL;             /*!< [0x0f50] RSA Key Control Register                                         */
    __IO uint32_t RSA_KSSTS[2];            /*!< [0x0f54 - 0x0f58] RSA Key Status Register 0                                        */
    __I  uint32_t RESERVE13[40];
    __I  uint32_t VERSION;               /*!< [0x0ffc] Crypto RTL Design Version Register                               */

} CRPT_T;

/**
    @addtogroup CRPT_CONST CRPT Bit Field Definition
    Constant Definitions for CRPT Controller
@{ */

#define CRPT_INTEN_AESIEN_Pos            (0)                                               /*!< CRPT_T::INTEN: AESIEN Position         */
#define CRPT_INTEN_AESIEN_Msk            (0x1ul << CRPT_INTEN_AESIEN_Pos)                  /*!< CRPT_T::INTEN: AESIEN Mask             */

#define CRPT_INTEN_AESEIEN_Pos           (1)                                               /*!< CRPT_T::INTEN: AESEIEN Position        */
#define CRPT_INTEN_AESEIEN_Msk           (0x1ul << CRPT_INTEN_AESEIEN_Pos)                 /*!< CRPT_T::INTEN: AESEIEN Mask            */

#define CRPT_INTEN_PRNGIEN_Pos           (16)                                              /*!< CRPT_T::INTEN: PRNGIEN Position        */
#define CRPT_INTEN_PRNGIEN_Msk           (0x1ul << CRPT_INTEN_PRNGIEN_Pos)                 /*!< CRPT_T::INTEN: PRNGIEN Mask            */

#define CRPT_INTEN_PRNGEIEN_Pos          (17)                                              /*!< CRPT_T::INTEN: PRNGEIEN Position       */
#define CRPT_INTEN_PRNGEIEN_Msk          (0x1ul << CRPT_INTEN_PRNGEIEN_Pos)                /*!< CRPT_T::INTEN: PRNGEIEN Mask           */

#define CRPT_INTEN_ECCIEN_Pos            (22)                                              /*!< CRPT_T::INTEN: ECCIEN Position         */
#define CRPT_INTEN_ECCIEN_Msk            (0x1ul << CRPT_INTEN_ECCIEN_Pos)                  /*!< CRPT_T::INTEN: ECCIEN Mask             */

#define CRPT_INTEN_ECCEIEN_Pos           (23)                                              /*!< CRPT_T::INTEN: ECCEIEN Position        */
#define CRPT_INTEN_ECCEIEN_Msk           (0x1ul << CRPT_INTEN_ECCEIEN_Pos)                 /*!< CRPT_T::INTEN: ECCEIEN Mask            */

#define CRPT_INTEN_HMACIEN_Pos           (24)                                              /*!< CRPT_T::INTEN: HMACIEN Position        */
#define CRPT_INTEN_HMACIEN_Msk           (0x1ul << CRPT_INTEN_HMACIEN_Pos)                 /*!< CRPT_T::INTEN: HMACIEN Mask            */

#define CRPT_INTEN_HMACEIEN_Pos          (25)                                              /*!< CRPT_T::INTEN: HMACEIEN Position       */
#define CRPT_INTEN_HMACEIEN_Msk          (0x1ul << CRPT_INTEN_HMACEIEN_Pos)                /*!< CRPT_T::INTEN: HMACEIEN Mask           */

#define CRPT_INTEN_RSAIEN_Pos            (30)                                              /*!< CRPT_T::INTEN: RSAIEN Position         */
#define CRPT_INTEN_RSAIEN_Msk            (0x1ul << CRPT_INTEN_RSAIEN_Pos)                  /*!< CRPT_T::INTEN: RSAIEN Mask             */

#define CRPT_INTEN_RSAEIEN_Pos           (31)                                              /*!< CRPT_T::INTEN: RSAEIEN Position        */
#define CRPT_INTEN_RSAEIEN_Msk           (0x1ul << CRPT_INTEN_RSAEIEN_Pos)                 /*!< CRPT_T::INTEN: RSAEIEN Mask            */

#define CRPT_INTSTS_AESIF_Pos            (0)                                               /*!< CRPT_T::INTSTS: AESIF Position         */
#define CRPT_INTSTS_AESIF_Msk            (0x1ul << CRPT_INTSTS_AESIF_Pos)                  /*!< CRPT_T::INTSTS: AESIF Mask             */

#define CRPT_INTSTS_AESEIF_Pos           (1)                                               /*!< CRPT_T::INTSTS: AESEIF Position        */
#define CRPT_INTSTS_AESEIF_Msk           (0x1ul << CRPT_INTSTS_AESEIF_Pos)                 /*!< CRPT_T::INTSTS: AESEIF Mask            */

#define CRPT_INTSTS_PRNGIF_Pos           (16)                                              /*!< CRPT_T::INTSTS: PRNGIF Position        */
#define CRPT_INTSTS_PRNGIF_Msk           (0x1ul << CRPT_INTSTS_PRNGIF_Pos)                 /*!< CRPT_T::INTSTS: PRNGIF Mask            */

#define CRPT_INTSTS_PRNGEIF_Pos          (17)                                              /*!< CRPT_T::INTSTS: PRNGEIF Position       */
#define CRPT_INTSTS_PRNGEIF_Msk          (0x1ul << CRPT_INTSTS_PRNGEIF_Pos)                /*!< CRPT_T::INTSTS: PRNGEIF Mask           */

#define CRPT_INTSTS_ECCIF_Pos            (22)                                              /*!< CRPT_T::INTSTS: ECCIF Position         */
#define CRPT_INTSTS_ECCIF_Msk            (0x1ul << CRPT_INTSTS_ECCIF_Pos)                  /*!< CRPT_T::INTSTS: ECCIF Mask             */

#define CRPT_INTSTS_ECCEIF_Pos           (23)                                              /*!< CRPT_T::INTSTS: ECCEIF Position        */
#define CRPT_INTSTS_ECCEIF_Msk           (0x1ul << CRPT_INTSTS_ECCEIF_Pos)                 /*!< CRPT_T::INTSTS: ECCEIF Mask            */

#define CRPT_INTSTS_HMACIF_Pos           (24)                                              /*!< CRPT_T::INTSTS: HMACIF Position        */
#define CRPT_INTSTS_HMACIF_Msk           (0x1ul << CRPT_INTSTS_HMACIF_Pos)                 /*!< CRPT_T::INTSTS: HMACIF Mask            */

#define CRPT_INTSTS_HMACEIF_Pos          (25)                                              /*!< CRPT_T::INTSTS: HMACEIF Position       */
#define CRPT_INTSTS_HMACEIF_Msk          (0x1ul << CRPT_INTSTS_HMACEIF_Pos)                /*!< CRPT_T::INTSTS: HMACEIF Mask           */

#define CRPT_INTSTS_RSAIF_Pos            (30)                                              /*!< CRPT_T::INTSTS: RSAIF Position         */
#define CRPT_INTSTS_RSAIF_Msk            (0x1ul << CRPT_INTSTS_RSAIF_Pos)                  /*!< CRPT_T::INTSTS: RSAIF Mask             */

#define CRPT_INTSTS_RSAEIF_Pos           (31)                                              /*!< CRPT_T::INTSTS: RSAEIF Position        */
#define CRPT_INTSTS_RSAEIF_Msk           (0x1ul << CRPT_INTSTS_RSAEIF_Pos)                 /*!< CRPT_T::INTSTS: RSAEIF Mask            */

#define CRPT_PRNG_CTL_START_Pos          (0)                                               /*!< CRPT_T::PRNG_CTL: START Position       */
#define CRPT_PRNG_CTL_START_Msk          (0x1ul << CRPT_PRNG_CTL_START_Pos)                /*!< CRPT_T::PRNG_CTL: START Mask           */

#define CRPT_PRNG_CTL_SEEDRLD_Pos        (1)                                               /*!< CRPT_T::PRNG_CTL: SEEDRLD Position     */
#define CRPT_PRNG_CTL_SEEDRLD_Msk        (0x1ul << CRPT_PRNG_CTL_SEEDRLD_Pos)              /*!< CRPT_T::PRNG_CTL: SEEDRLD Mask         */

#define CRPT_PRNG_CTL_KEYSZ_Pos          (2)                                               /*!< CRPT_T::PRNG_CTL: KEYSZ Position       */
#define CRPT_PRNG_CTL_KEYSZ_Msk          (0xful << CRPT_PRNG_CTL_KEYSZ_Pos)                /*!< CRPT_T::PRNG_CTL: KEYSZ Mask           */

#define CRPT_PRNG_CTL_BUSY_Pos           (8)                                               /*!< CRPT_T::PRNG_CTL: BUSY Position        */
#define CRPT_PRNG_CTL_BUSY_Msk           (0x1ul << CRPT_PRNG_CTL_BUSY_Pos)                 /*!< CRPT_T::PRNG_CTL: BUSY Mask            */

#define CRPT_PRNG_CTL_SEEDSRC_Pos        (16)                                              /*!< CRPT_T::PRNG_CTL: SEEDSRC Position     */
#define CRPT_PRNG_CTL_SEEDSRC_Msk        (0x1ul << CRPT_PRNG_CTL_SEEDSRC_Pos)              /*!< CRPT_T::PRNG_CTL: SEEDSRC Mask         */

#define CRPT_PRNG_SEED_SEED_Pos          (0)                                               /*!< CRPT_T::PRNG_SEED: SEED Position       */
#define CRPT_PRNG_SEED_SEED_Msk          (0xfffffffful << CRPT_PRNG_SEED_SEED_Pos)         /*!< CRPT_T::PRNG_SEED: SEED Mask           */

#define CRPT_PRNG_KEY0_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY0: KEY Position        */
#define CRPT_PRNG_KEY0_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY0_KEY_Pos)          /*!< CRPT_T::PRNG_KEY0: KEY Mask            */

#define CRPT_PRNG_KEY1_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY1: KEY Position        */
#define CRPT_PRNG_KEY1_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY1_KEY_Pos)          /*!< CRPT_T::PRNG_KEY1: KEY Mask            */

#define CRPT_PRNG_KEY2_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY2: KEY Position        */
#define CRPT_PRNG_KEY2_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY2_KEY_Pos)          /*!< CRPT_T::PRNG_KEY2: KEY Mask            */

#define CRPT_PRNG_KEY3_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY3: KEY Position        */
#define CRPT_PRNG_KEY3_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY3_KEY_Pos)          /*!< CRPT_T::PRNG_KEY3: KEY Mask            */

#define CRPT_PRNG_KEY4_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY4: KEY Position        */
#define CRPT_PRNG_KEY4_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY4_KEY_Pos)          /*!< CRPT_T::PRNG_KEY4: KEY Mask            */

#define CRPT_PRNG_KEY5_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY5: KEY Position        */
#define CRPT_PRNG_KEY5_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY5_KEY_Pos)          /*!< CRPT_T::PRNG_KEY5: KEY Mask            */

#define CRPT_PRNG_KEY6_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY6: KEY Position        */
#define CRPT_PRNG_KEY6_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY6_KEY_Pos)          /*!< CRPT_T::PRNG_KEY6: KEY Mask            */

#define CRPT_PRNG_KEY7_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY7: KEY Position        */
#define CRPT_PRNG_KEY7_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEY7_KEY_Pos)          /*!< CRPT_T::PRNG_KEY7: KEY Mask            */

#define CRPT_PRNG_STS_BUSY_Pos           (0)                                               /*!< CRPT_T::PRNG_STS: BUSY Position        */
#define CRPT_PRNG_STS_BUSY_Msk           (0x1ul << CRPT_PRNG_STS_BUSY_Pos)                 /*!< CRPT_T::PRNG_STS: BUSY Mask            */

#define CRPT_PRNG_STS_KCTLERR_Pos        (16)                                              /*!< CRPT_T::PRNG_STS: KCTLERR Position     */
#define CRPT_PRNG_STS_KCTLERR_Msk        (0x1ul << CRPT_PRNG_STS_KCTLERR_Pos)              /*!< CRPT_T::PRNG_STS: KCTLERR Mask         */

#define CRPT_PRNG_STS_KSERR_Pos          (17)                                              /*!< CRPT_T::PRNG_STS: KSERR Position       */
#define CRPT_PRNG_STS_KSERR_Msk          (0x1ul << CRPT_PRNG_STS_KSERR_Pos)                /*!< CRPT_T::PRNG_STS: KSERR Mask           */

#define CRPT_AES_FDBCK0_FDBCK_Pos        (0)                                               /*!< CRPT_T::AES_FDBCK0: FDBCK Position     */
#define CRPT_AES_FDBCK0_FDBCK_Msk        (0xfffffffful << CRPT_AES_FDBCK0_FDBCK_Pos)       /*!< CRPT_T::AES_FDBCK0: FDBCK Mask         */

#define CRPT_AES_FDBCK1_FDBCK_Pos        (0)                                               /*!< CRPT_T::AES_FDBCK1: FDBCK Position     */
#define CRPT_AES_FDBCK1_FDBCK_Msk        (0xfffffffful << CRPT_AES_FDBCK1_FDBCK_Pos)       /*!< CRPT_T::AES_FDBCK1: FDBCK Mask         */

#define CRPT_AES_FDBCK2_FDBCK_Pos        (0)                                               /*!< CRPT_T::AES_FDBCK2: FDBCK Position     */
#define CRPT_AES_FDBCK2_FDBCK_Msk        (0xfffffffful << CRPT_AES_FDBCK2_FDBCK_Pos)       /*!< CRPT_T::AES_FDBCK2: FDBCK Mask         */

#define CRPT_AES_FDBCK3_FDBCK_Pos        (0)                                               /*!< CRPT_T::AES_FDBCK3: FDBCK Position     */
#define CRPT_AES_FDBCK3_FDBCK_Msk        (0xfffffffful << CRPT_AES_FDBCK3_FDBCK_Pos)       /*!< CRPT_T::AES_FDBCK3: FDBCK Mask         */

#define CRPT_AES_GCM_IVCNT0_CNT_Pos      (0)                                               /*!< CRPT_T::AES_GCM_IVCNT0: CNT Position   */
#define CRPT_AES_GCM_IVCNT0_CNT_Msk      (0xfffffffful << CRPT_AES_GCM_IVCNT0_CNT_Pos)     /*!< CRPT_T::AES_GCM_IVCNT0: CNT Mask       */

#define CRPT_AES_GCM_IVCNT1_CNT_Pos      (0)                                               /*!< CRPT_T::AES_GCM_IVCNT1: CNT Position   */
#define CRPT_AES_GCM_IVCNT1_CNT_Msk      (0x1ffffffful << CRPT_AES_GCM_IVCNT1_CNT_Pos)     /*!< CRPT_T::AES_GCM_IVCNT1: CNT Mask       */

#define CRPT_AES_GCM_ACNT0_CNT_Pos       (0)                                               /*!< CRPT_T::AES_GCM_ACNT0: CNT Position    */
#define CRPT_AES_GCM_ACNT0_CNT_Msk       (0xfffffffful << CRPT_AES_GCM_ACNT0_CNT_Pos)      /*!< CRPT_T::AES_GCM_ACNT0: CNT Mask        */

#define CRPT_AES_GCM_ACNT1_CNT_Pos       (0)                                               /*!< CRPT_T::AES_GCM_ACNT1: CNT Position    */
#define CRPT_AES_GCM_ACNT1_CNT_Msk       (0x1ffffffful << CRPT_AES_GCM_ACNT1_CNT_Pos)      /*!< CRPT_T::AES_GCM_ACNT1: CNT Mask        */

#define CRPT_AES_GCM_PCNT0_CNT_Pos       (0)                                               /*!< CRPT_T::AES_GCM_PCNT0: CNT Position    */
#define CRPT_AES_GCM_PCNT0_CNT_Msk       (0xfffffffful << CRPT_AES_GCM_PCNT0_CNT_Pos)      /*!< CRPT_T::AES_GCM_PCNT0: CNT Mask        */

#define CRPT_AES_GCM_PCNT1_CNT_Pos       (0)                                               /*!< CRPT_T::AES_GCM_PCNT1: CNT Position    */
#define CRPT_AES_GCM_PCNT1_CNT_Msk       (0x1ffffffful << CRPT_AES_GCM_PCNT1_CNT_Pos)      /*!< CRPT_T::AES_GCM_PCNT1: CNT Mask        */

#define CRPT_AES_FBADDR_FBADDR_Pos       (0)                                               /*!< CRPT_T::AES_FBADDR: FBADDR Position    */
#define CRPT_AES_FBADDR_FBADDR_Msk       (0xfffffffful << CRPT_AES_FBADDR_FBADDR_Pos)      /*!< CRPT_T::AES_FBADDR: FBADDR Mask        */

#define CRPT_AES_CTL_START_Pos           (0)                                               /*!< CRPT_T::AES_CTL: START Position        */
#define CRPT_AES_CTL_START_Msk           (0x1ul << CRPT_AES_CTL_START_Pos)                 /*!< CRPT_T::AES_CTL: START Mask            */

#define CRPT_AES_CTL_STOP_Pos            (1)                                               /*!< CRPT_T::AES_CTL: STOP Position         */
#define CRPT_AES_CTL_STOP_Msk            (0x1ul << CRPT_AES_CTL_STOP_Pos)                  /*!< CRPT_T::AES_CTL: STOP Mask             */

#define CRPT_AES_CTL_KEYSZ_Pos           (2)                                               /*!< CRPT_T::AES_CTL: KEYSZ Position        */
#define CRPT_AES_CTL_KEYSZ_Msk           (0x3ul << CRPT_AES_CTL_KEYSZ_Pos)                 /*!< CRPT_T::AES_CTL: KEYSZ Mask            */

#define CRPT_AES_CTL_DMALAST_Pos         (5)                                               /*!< CRPT_T::AES_CTL: DMALAST Position      */
#define CRPT_AES_CTL_DMALAST_Msk         (0x1ul << CRPT_AES_CTL_DMALAST_Pos)               /*!< CRPT_T::AES_CTL: DMALAST Mask          */

#define CRPT_AES_CTL_DMACSCAD_Pos        (6)                                               /*!< CRPT_T::AES_CTL: DMACSCAD Position     */
#define CRPT_AES_CTL_DMACSCAD_Msk        (0x1ul << CRPT_AES_CTL_DMACSCAD_Pos)              /*!< CRPT_T::AES_CTL: DMACSCAD Mask         */

#define CRPT_AES_CTL_DMAEN_Pos           (7)                                               /*!< CRPT_T::AES_CTL: DMAEN Position        */
#define CRPT_AES_CTL_DMAEN_Msk           (0x1ul << CRPT_AES_CTL_DMAEN_Pos)                 /*!< CRPT_T::AES_CTL: DMAEN Mask            */

#define CRPT_AES_CTL_OPMODE_Pos          (8)                                               /*!< CRPT_T::AES_CTL: OPMODE Position       */
#define CRPT_AES_CTL_OPMODE_Msk          (0xfful << CRPT_AES_CTL_OPMODE_Pos)               /*!< CRPT_T::AES_CTL: OPMODE Mask           */

#define CRPT_AES_CTL_ENCRPT_Pos          (16)                                              /*!< CRPT_T::AES_CTL: ENCRPT Position     */
#define CRPT_AES_CTL_ENCRPT_Msk          (0x1ul << CRPT_AES_CTL_ENCRPT_Pos)                /*!< CRPT_T::AES_CTL: ENCRPT Mask         */

#define CRPT_AES_CTL_FBIN_Pos            (20)                                              /*!< CRPT_T::AES_CTL: FBIN Position         */
#define CRPT_AES_CTL_FBIN_Msk            (0x1ul << CRPT_AES_CTL_FBIN_Pos)                  /*!< CRPT_T::AES_CTL: FBIN Mask             */

#define CRPT_AES_CTL_FBOUT_Pos           (21)                                              /*!< CRPT_T::AES_CTL: FBOUT Position        */
#define CRPT_AES_CTL_FBOUT_Msk           (0x1ul << CRPT_AES_CTL_FBOUT_Pos)                 /*!< CRPT_T::AES_CTL: FBOUT Mask            */

#define CRPT_AES_CTL_OUTSWAP_Pos         (22)                                              /*!< CRPT_T::AES_CTL: OUTSWAP Position      */
#define CRPT_AES_CTL_OUTSWAP_Msk         (0x1ul << CRPT_AES_CTL_OUTSWAP_Pos)               /*!< CRPT_T::AES_CTL: OUTSWAP Mask          */

#define CRPT_AES_CTL_INSWAP_Pos          (23)                                              /*!< CRPT_T::AES_CTL: INSWAP Position       */
#define CRPT_AES_CTL_INSWAP_Msk          (0x1ul << CRPT_AES_CTL_INSWAP_Pos)                /*!< CRPT_T::AES_CTL: INSWAP Mask           */

#define CRPT_AES_CTL_KOUTSWAP_Pos        (24)                                              /*!< CRPT_T::AES_CTL: KOUTSWAP Position     */
#define CRPT_AES_CTL_KOUTSWAP_Msk        (0x1ul << CRPT_AES_CTL_KOUTSWAP_Pos)              /*!< CRPT_T::AES_CTL: KOUTSWAP Mask         */

#define CRPT_AES_CTL_KINSWAP_Pos         (25)                                              /*!< CRPT_T::AES_CTL: KINSWAP Position      */
#define CRPT_AES_CTL_KINSWAP_Msk         (0x1ul << CRPT_AES_CTL_KINSWAP_Pos)               /*!< CRPT_T::AES_CTL: KINSWAP Mask          */

#define CRPT_AES_CTL_KEYUNPRT_Pos        (26)                                              /*!< CRPT_T::AES_CTL: KEYUNPRT Position     */
#define CRPT_AES_CTL_KEYUNPRT_Msk        (0x1ful << CRPT_AES_CTL_KEYUNPRT_Pos)             /*!< CRPT_T::AES_CTL: KEYUNPRT Mask         */

#define CRPT_AES_CTL_KEYPRT_Pos          (31)                                              /*!< CRPT_T::AES_CTL: KEYPRT Position       */
#define CRPT_AES_CTL_KEYPRT_Msk          (0x1ul << CRPT_AES_CTL_KEYPRT_Pos)                /*!< CRPT_T::AES_CTL: KEYPRT Mask           */

#define CRPT_AES_STS_BUSY_Pos            (0)                                               /*!< CRPT_T::AES_STS: BUSY Position         */
#define CRPT_AES_STS_BUSY_Msk            (0x1ul << CRPT_AES_STS_BUSY_Pos)                  /*!< CRPT_T::AES_STS: BUSY Mask             */

#define CRPT_AES_STS_INBUFEMPTY_Pos      (8)                                               /*!< CRPT_T::AES_STS: INBUFEMPTY Position   */
#define CRPT_AES_STS_INBUFEMPTY_Msk      (0x1ul << CRPT_AES_STS_INBUFEMPTY_Pos)            /*!< CRPT_T::AES_STS: INBUFEMPTY Mask       */

#define CRPT_AES_STS_INBUFFULL_Pos       (9)                                               /*!< CRPT_T::AES_STS: INBUFFULL Position    */
#define CRPT_AES_STS_INBUFFULL_Msk       (0x1ul << CRPT_AES_STS_INBUFFULL_Pos)             /*!< CRPT_T::AES_STS: INBUFFULL Mask        */

#define CRPT_AES_STS_INBUFERR_Pos        (10)                                              /*!< CRPT_T::AES_STS: INBUFERR Position     */
#define CRPT_AES_STS_INBUFERR_Msk        (0x1ul << CRPT_AES_STS_INBUFERR_Pos)              /*!< CRPT_T::AES_STS: INBUFERR Mask         */

#define CRPT_AES_STS_CNTERR_Pos          (12)                                              /*!< CRPT_T::AES_STS: CNTERR Position       */
#define CRPT_AES_STS_CNTERR_Msk          (0x1ul << CRPT_AES_STS_CNTERR_Pos)                /*!< CRPT_T::AES_STS: CNTERR Mask           */

#define CRPT_AES_STS_OUTBUFEMPTY_Pos     (16)                                              /*!< CRPT_T::AES_STS: OUTBUFEMPTY Position  */
#define CRPT_AES_STS_OUTBUFEMPTY_Msk     (0x1ul << CRPT_AES_STS_OUTBUFEMPTY_Pos)           /*!< CRPT_T::AES_STS: OUTBUFEMPTY Mask      */

#define CRPT_AES_STS_OUTBUFFULL_Pos      (17)                                              /*!< CRPT_T::AES_STS: OUTBUFFULL Position   */
#define CRPT_AES_STS_OUTBUFFULL_Msk      (0x1ul << CRPT_AES_STS_OUTBUFFULL_Pos)            /*!< CRPT_T::AES_STS: OUTBUFFULL Mask       */

#define CRPT_AES_STS_OUTBUFERR_Pos       (18)                                              /*!< CRPT_T::AES_STS: OUTBUFERR Position    */
#define CRPT_AES_STS_OUTBUFERR_Msk       (0x1ul << CRPT_AES_STS_OUTBUFERR_Pos)             /*!< CRPT_T::AES_STS: OUTBUFERR Mask        */

#define CRPT_AES_STS_BUSERR_Pos          (20)                                              /*!< CRPT_T::AES_STS: BUSERR Position       */
#define CRPT_AES_STS_BUSERR_Msk          (0x1ul << CRPT_AES_STS_BUSERR_Pos)                /*!< CRPT_T::AES_STS: BUSERR Mask           */

#define CRPT_AES_STS_KSERR_Pos           (21)                                              /*!< CRPT_T::AES_STS: KSERR Position        */
#define CRPT_AES_STS_KSERR_Msk           (0x1ul << CRPT_AES_STS_KSERR_Pos)                 /*!< CRPT_T::AES_STS: KSERR Mask            */

#define CRPT_AES_DATIN_DATIN_Pos         (0)                                               /*!< CRPT_T::AES_DATIN: DATIN Position      */
#define CRPT_AES_DATIN_DATIN_Msk         (0xfffffffful << CRPT_AES_DATIN_DATIN_Pos)        /*!< CRPT_T::AES_DATIN: DATIN Mask          */

#define CRPT_AES_DATOUT_DATOUT_Pos       (0)                                               /*!< CRPT_T::AES_DATOUT: DATOUT Position    */
#define CRPT_AES_DATOUT_DATOUT_Msk       (0xfffffffful << CRPT_AES_DATOUT_DATOUT_Pos)      /*!< CRPT_T::AES_DATOUT: DATOUT Mask        */

#define CRPT_AES_KEY0_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY0: KEY Position         */
#define CRPT_AES_KEY0_KEY_Msk            (0xfffffffful << CRPT_AES_KEY0_KEY_Pos)           /*!< CRPT_T::AES_KEY0: KEY Mask             */

#define CRPT_AES_KEY1_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY1: KEY Position         */
#define CRPT_AES_KEY1_KEY_Msk            (0xfffffffful << CRPT_AES_KEY1_KEY_Pos)           /*!< CRPT_T::AES_KEY1: KEY Mask             */

#define CRPT_AES_KEY2_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY2: KEY Position         */
#define CRPT_AES_KEY2_KEY_Msk            (0xfffffffful << CRPT_AES_KEY2_KEY_Pos)           /*!< CRPT_T::AES_KEY2: KEY Mask             */

#define CRPT_AES_KEY3_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY3: KEY Position         */
#define CRPT_AES_KEY3_KEY_Msk            (0xfffffffful << CRPT_AES_KEY3_KEY_Pos)           /*!< CRPT_T::AES_KEY3: KEY Mask             */

#define CRPT_AES_KEY4_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY4: KEY Position         */
#define CRPT_AES_KEY4_KEY_Msk            (0xfffffffful << CRPT_AES_KEY4_KEY_Pos)           /*!< CRPT_T::AES_KEY4: KEY Mask             */

#define CRPT_AES_KEY5_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY5: KEY Position         */
#define CRPT_AES_KEY5_KEY_Msk            (0xfffffffful << CRPT_AES_KEY5_KEY_Pos)           /*!< CRPT_T::AES_KEY5: KEY Mask             */

#define CRPT_AES_KEY6_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY6: KEY Position         */
#define CRPT_AES_KEY6_KEY_Msk            (0xfffffffful << CRPT_AES_KEY6_KEY_Pos)           /*!< CRPT_T::AES_KEY6: KEY Mask             */

#define CRPT_AES_KEY7_KEY_Pos            (0)                                               /*!< CRPT_T::AES_KEY7: KEY Position         */
#define CRPT_AES_KEY7_KEY_Msk            (0xfffffffful << CRPT_AES_KEY7_KEY_Pos)           /*!< CRPT_T::AES_KEY7: KEY Mask             */

#define CRPT_AES_IV0_IV_Pos              (0)                                               /*!< CRPT_T::AES_IV0: IV Position           */
#define CRPT_AES_IV0_IV_Msk              (0xfffffffful << CRPT_AES_IV0_IV_Pos)             /*!< CRPT_T::AES_IV0: IV Mask               */

#define CRPT_AES_IV1_IV_Pos              (0)                                               /*!< CRPT_T::AES_IV1: IV Position           */
#define CRPT_AES_IV1_IV_Msk              (0xfffffffful << CRPT_AES_IV1_IV_Pos)             /*!< CRPT_T::AES_IV1: IV Mask               */

#define CRPT_AES_IV2_IV_Pos              (0)                                               /*!< CRPT_T::AES_IV2: IV Position           */
#define CRPT_AES_IV2_IV_Msk              (0xfffffffful << CRPT_AES_IV2_IV_Pos)             /*!< CRPT_T::AES_IV2: IV Mask               */

#define CRPT_AES_IV3_IV_Pos              (0)                                               /*!< CRPT_T::AES_IV3: IV Position           */
#define CRPT_AES_IV3_IV_Msk              (0xfffffffful << CRPT_AES_IV3_IV_Pos)             /*!< CRPT_T::AES_IV3: IV Mask               */

#define CRPT_AES_SADDR_SADDR_Pos         (0)                                               /*!< CRPT_T::AES_SADDR: SADDR Position      */
#define CRPT_AES_SADDR_SADDR_Msk         (0xfffffffful << CRPT_AES_SADDR_SADDR_Pos)        /*!< CRPT_T::AES_SADDR: SADDR Mask          */

#define CRPT_AES_DADDR_DADDR_Pos         (0)                                               /*!< CRPT_T::AES_DADDR: DADDR Position      */
#define CRPT_AES_DADDR_DADDR_Msk         (0xfffffffful << CRPT_AES_DADDR_DADDR_Pos)        /*!< CRPT_T::AES_DADDR: DADDR Mask          */

#define CRPT_AES_CNT_CNT_Pos             (0)                                               /*!< CRPT_T::AES_CNT: CNT Position          */
#define CRPT_AES_CNT_CNT_Msk             (0xfffffffful << CRPT_AES_CNT_CNT_Pos)            /*!< CRPT_T::AES_CNT: CNT Mask              */

#define CRPT_HMAC_CTL_START_Pos          (0)                                               /*!< CRPT_T::HMAC_CTL: START Position       */
#define CRPT_HMAC_CTL_START_Msk          (0x1ul << CRPT_HMAC_CTL_START_Pos)                /*!< CRPT_T::HMAC_CTL: START Mask           */

#define CRPT_HMAC_CTL_STOP_Pos           (1)                                               /*!< CRPT_T::HMAC_CTL: STOP Position        */
#define CRPT_HMAC_CTL_STOP_Msk           (0x1ul << CRPT_HMAC_CTL_STOP_Pos)                 /*!< CRPT_T::HMAC_CTL: STOP Mask            */

#define CRPT_HMAC_CTL_DMAFIRST_Pos       (4)                                               /*!< CRPT_T::HMAC_CTL: DMAFIRST Position    */
#define CRPT_HMAC_CTL_DMAFIRST_Msk       (0x1ul << CRPT_HMAC_CTL_DMAFIRST_Pos)             /*!< CRPT_T::HMAC_CTL: DMAFIRST Mask        */

#define CRPT_HMAC_CTL_DMALAST_Pos        (5)                                               /*!< CRPT_T::HMAC_CTL: DMALAST Position     */
#define CRPT_HMAC_CTL_DMALAST_Msk        (0x1ul << CRPT_HMAC_CTL_DMALAST_Pos)              /*!< CRPT_T::HMAC_CTL: DMALAST Mask         */

#define CRPT_HMAC_CTL_DMACSCAD_Pos       (6)                                               /*!< CRPT_T::HMAC_CTL: DMACSCAD Position    */
#define CRPT_HMAC_CTL_DMACSCAD_Msk       (0x1ul << CRPT_HMAC_CTL_DMACSCAD_Pos)             /*!< CRPT_T::HMAC_CTL: DMACSCAD Mask        */

#define CRPT_HMAC_CTL_DMAEN_Pos          (7)                                               /*!< CRPT_T::HMAC_CTL: DMAEN Position       */
#define CRPT_HMAC_CTL_DMAEN_Msk          (0x1ul << CRPT_HMAC_CTL_DMAEN_Pos)                /*!< CRPT_T::HMAC_CTL: DMAEN Mask           */

#define CRPT_HMAC_CTL_OPMODE_Pos         (8)                                               /*!< CRPT_T::HMAC_CTL: OPMODE Position      */
#define CRPT_HMAC_CTL_OPMODE_Msk         (0x7ul << CRPT_HMAC_CTL_OPMODE_Pos)               /*!< CRPT_T::HMAC_CTL: OPMODE Mask          */

#define CRPT_HMAC_CTL_HMACEN_Pos         (11)                                              /*!< CRPT_T::HMAC_CTL: HMACEN Position      */
#define CRPT_HMAC_CTL_HMACEN_Msk         (0x1ul << CRPT_HMAC_CTL_HMACEN_Pos)               /*!< CRPT_T::HMAC_CTL: HMACEN Mask          */

#define CRPT_HMAC_CTL_SHA3EN_Pos         (12)                                              /*!< CRPT_T::HMAC_CTL: SHA3EN Position      */
#define CRPT_HMAC_CTL_SHA3EN_Msk         (0x1ul << CRPT_HMAC_CTL_SHA3EN_Pos)               /*!< CRPT_T::HMAC_CTL: SHA3EN Mask          */

#define CRPT_HMAC_CTL_FBIN_Pos           (20)                                              /*!< CRPT_T::HMAC_CTL: FBIN Position        */
#define CRPT_HMAC_CTL_FBIN_Msk           (0x1ul << CRPT_HMAC_CTL_FBIN_Pos)                 /*!< CRPT_T::HMAC_CTL: FBIN Mask            */

#define CRPT_HMAC_CTL_FBOUT_Pos          (21)                                              /*!< CRPT_T::HMAC_CTL: FBOUT Position       */
#define CRPT_HMAC_CTL_FBOUT_Msk          (0x1ul << CRPT_HMAC_CTL_FBOUT_Pos)                /*!< CRPT_T::HMAC_CTL: FBOUT Mask           */

#define CRPT_HMAC_CTL_OUTSWAP_Pos        (22)                                              /*!< CRPT_T::HMAC_CTL: OUTSWAP Position     */
#define CRPT_HMAC_CTL_OUTSWAP_Msk        (0x1ul << CRPT_HMAC_CTL_OUTSWAP_Pos)              /*!< CRPT_T::HMAC_CTL: OUTSWAP Mask         */

#define CRPT_HMAC_CTL_INSWAP_Pos         (23)                                              /*!< CRPT_T::HMAC_CTL: INSWAP Position      */
#define CRPT_HMAC_CTL_INSWAP_Msk         (0x1ul << CRPT_HMAC_CTL_INSWAP_Pos)               /*!< CRPT_T::HMAC_CTL: INSWAP Mask          */

#define CRPT_HMAC_CTL_NEXTDGST_Pos       (24)                                              /*!< CRPT_T::HMAC_CTL: NEXTDGST Position    */
#define CRPT_HMAC_CTL_NEXTDGST_Msk       (0x1ul << CRPT_HMAC_CTL_NEXTDGST_Pos)             /*!< CRPT_T::HMAC_CTL: NEXTDGST Mask        */

#define CRPT_HMAC_CTL_FINISHDGST_Pos     (25)                                              /*!< CRPT_T::HMAC_CTL: FINISHDGST Position  */
#define CRPT_HMAC_CTL_FINISHDGST_Msk     (0x1ul << CRPT_HMAC_CTL_FINISHDGST_Pos)           /*!< CRPT_T::HMAC_CTL: FINISHDGST Mask      */

#define CRPT_HMAC_STS_BUSY_Pos           (0)                                               /*!< CRPT_T::HMAC_STS: BUSY Position        */
#define CRPT_HMAC_STS_BUSY_Msk           (0x1ul << CRPT_HMAC_STS_BUSY_Pos)                 /*!< CRPT_T::HMAC_STS: BUSY Mask            */

#define CRPT_HMAC_STS_DMABUSY_Pos        (1)                                               /*!< CRPT_T::HMAC_STS: DMABUSY Position     */
#define CRPT_HMAC_STS_DMABUSY_Msk        (0x1ul << CRPT_HMAC_STS_DMABUSY_Pos)              /*!< CRPT_T::HMAC_STS: DMABUSY Mask         */

#define CRPT_HMAC_STS_SHAKEBUSY_Pos      (2)                                               /*!< CRPT_T::HMAC_STS: SHAKEBUSY Position   */
#define CRPT_HMAC_STS_SHAKEBUSY_Msk      (0x1ul << CRPT_HMAC_STS_SHAKEBUSY_Pos)            /*!< CRPT_T::HMAC_STS: SHAKEBUSY Mask       */

#define CRPT_HMAC_STS_DMAERR_Pos         (8)                                               /*!< CRPT_T::HMAC_STS: DMAERR Position      */
#define CRPT_HMAC_STS_DMAERR_Msk         (0x1ul << CRPT_HMAC_STS_DMAERR_Pos)               /*!< CRPT_T::HMAC_STS: DMAERR Mask          */

#define CRPT_HMAC_STS_KSERR_Pos          (9)                                               /*!< CRPT_T::HMAC_STS: KSERR Position       */
#define CRPT_HMAC_STS_KSERR_Msk          (0x1ul << CRPT_HMAC_STS_KSERR_Pos)                /*!< CRPT_T::HMAC_STS: KSERR Mask           */

#define CRPT_HMAC_STS_DATINREQ_Pos       (16)                                              /*!< CRPT_T::HMAC_STS: DATINREQ Position    */
#define CRPT_HMAC_STS_DATINREQ_Msk       (0x1ul << CRPT_HMAC_STS_DATINREQ_Pos)             /*!< CRPT_T::HMAC_STS: DATINREQ Mask        */

#define CRPT_HMAC_DGST0_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST0: DGST Position      */
#define CRPT_HMAC_DGST0_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST0_DGST_Pos)        /*!< CRPT_T::HMAC_DGST0: DGST Mask          */

#define CRPT_HMAC_DGST1_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST1: DGST Position      */
#define CRPT_HMAC_DGST1_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST1_DGST_Pos)        /*!< CRPT_T::HMAC_DGST1: DGST Mask          */

#define CRPT_HMAC_DGST2_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST2: DGST Position      */
#define CRPT_HMAC_DGST2_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST2_DGST_Pos)        /*!< CRPT_T::HMAC_DGST2: DGST Mask          */

#define CRPT_HMAC_DGST3_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST3: DGST Position      */
#define CRPT_HMAC_DGST3_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST3_DGST_Pos)        /*!< CRPT_T::HMAC_DGST3: DGST Mask          */

#define CRPT_HMAC_DGST4_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST4: DGST Position      */
#define CRPT_HMAC_DGST4_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST4_DGST_Pos)        /*!< CRPT_T::HMAC_DGST4: DGST Mask          */

#define CRPT_HMAC_DGST5_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST5: DGST Position      */
#define CRPT_HMAC_DGST5_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST5_DGST_Pos)        /*!< CRPT_T::HMAC_DGST5: DGST Mask          */

#define CRPT_HMAC_DGST6_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST6: DGST Position      */
#define CRPT_HMAC_DGST6_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST6_DGST_Pos)        /*!< CRPT_T::HMAC_DGST6: DGST Mask          */

#define CRPT_HMAC_DGST7_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST7: DGST Position      */
#define CRPT_HMAC_DGST7_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST7_DGST_Pos)        /*!< CRPT_T::HMAC_DGST7: DGST Mask          */

#define CRPT_HMAC_DGST8_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST8: DGST Position      */
#define CRPT_HMAC_DGST8_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST8_DGST_Pos)        /*!< CRPT_T::HMAC_DGST8: DGST Mask          */

#define CRPT_HMAC_DGST9_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST9: DGST Position      */
#define CRPT_HMAC_DGST9_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGST9_DGST_Pos)        /*!< CRPT_T::HMAC_DGST9: DGST Mask          */

#define CRPT_HMAC_DGST10_DGST_Pos        (0)                                               /*!< CRPT_T::HMAC_DGST10: DGST Position     */
#define CRPT_HMAC_DGST10_DGST_Msk        (0xfffffffful << CRPT_HMAC_DGST10_DGST_Pos)       /*!< CRPT_T::HMAC_DGST10: DGST Mask         */

#define CRPT_HMAC_DGST11_DGST_Pos        (0)                                               /*!< CRPT_T::HMAC_DGST11: DGST Position     */
#define CRPT_HMAC_DGST11_DGST_Msk        (0xfffffffful << CRPT_HMAC_DGST11_DGST_Pos)       /*!< CRPT_T::HMAC_DGST11: DGST Mask         */

#define CRPT_HMAC_DGST12_DGST_Pos        (0)                                               /*!< CRPT_T::HMAC_DGST12: DGST Position     */
#define CRPT_HMAC_DGST12_DGST_Msk        (0xfffffffful << CRPT_HMAC_DGST12_DGST_Pos)       /*!< CRPT_T::HMAC_DGST12: DGST Mask         */

#define CRPT_HMAC_DGST13_DGST_Pos        (0)                                               /*!< CRPT_T::HMAC_DGST13: DGST Position     */
#define CRPT_HMAC_DGST13_DGST_Msk        (0xfffffffful << CRPT_HMAC_DGST13_DGST_Pos)       /*!< CRPT_T::HMAC_DGST13: DGST Mask         */

#define CRPT_HMAC_DGST14_DGST_Pos        (0)                                               /*!< CRPT_T::HMAC_DGST14: DGST Position     */
#define CRPT_HMAC_DGST14_DGST_Msk        (0xfffffffful << CRPT_HMAC_DGST14_DGST_Pos)       /*!< CRPT_T::HMAC_DGST14: DGST Mask         */

#define CRPT_HMAC_DGST15_DGST_Pos        (0)                                               /*!< CRPT_T::HMAC_DGST15: DGST Position     */
#define CRPT_HMAC_DGST15_DGST_Msk        (0xfffffffful << CRPT_HMAC_DGST15_DGST_Pos)       /*!< CRPT_T::HMAC_DGST15: DGST Mask         */

#define CRPT_HMAC_KEYCNT_KEYCNT_Pos      (0)                                               /*!< CRPT_T::HMAC_KEYCNT: KEYCNT Position   */
#define CRPT_HMAC_KEYCNT_KEYCNT_Msk      (0xfffffffful << CRPT_HMAC_KEYCNT_KEYCNT_Pos)     /*!< CRPT_T::HMAC_KEYCNT: KEYCNT Mask       */

#define CRPT_HMAC_SADDR_SADDR_Pos        (0)                                               /*!< CRPT_T::HMAC_SADDR: SADDR Position     */
#define CRPT_HMAC_SADDR_SADDR_Msk        (0xfffffffful << CRPT_HMAC_SADDR_SADDR_Pos)       /*!< CRPT_T::HMAC_SADDR: SADDR Mask         */

#define CRPT_HMAC_DMACNT_DMACNT_Pos      (0)                                               /*!< CRPT_T::HMAC_DMACNT: DMACNT Position   */
#define CRPT_HMAC_DMACNT_DMACNT_Msk      (0xfffffffful << CRPT_HMAC_DMACNT_DMACNT_Pos)     /*!< CRPT_T::HMAC_DMACNT: DMACNT Mask       */

#define CRPT_HMAC_DATIN_DATIN_Pos        (0)                                               /*!< CRPT_T::HMAC_DATIN: DATIN Position     */
#define CRPT_HMAC_DATIN_DATIN_Msk        (0xfffffffful << CRPT_HMAC_DATIN_DATIN_Pos)       /*!< CRPT_T::HMAC_DATIN: DATIN Mask         */

#define CRPT_HMAC_FDBCK0_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK0: FDBCK Position    */
#define CRPT_HMAC_FDBCK0_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK0_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK0: FDBCK Mask        */

#define CRPT_HMAC_FDBCK1_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK1: FDBCK Position    */
#define CRPT_HMAC_FDBCK1_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK1_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK1: FDBCK Mask        */

#define CRPT_HMAC_FDBCK2_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK2: FDBCK Position    */
#define CRPT_HMAC_FDBCK2_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK2_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK2: FDBCK Mask        */

#define CRPT_HMAC_FDBCK3_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK3: FDBCK Position    */
#define CRPT_HMAC_FDBCK3_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK3_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK3: FDBCK Mask        */

#define CRPT_HMAC_FDBCK4_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK4: FDBCK Position    */
#define CRPT_HMAC_FDBCK4_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK4_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK4: FDBCK Mask        */

#define CRPT_HMAC_FDBCK5_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK5: FDBCK Position    */
#define CRPT_HMAC_FDBCK5_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK5_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK5: FDBCK Mask        */

#define CRPT_HMAC_FDBCK6_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK6: FDBCK Position    */
#define CRPT_HMAC_FDBCK6_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK6_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK6: FDBCK Mask        */

#define CRPT_HMAC_FDBCK7_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK7: FDBCK Position    */
#define CRPT_HMAC_FDBCK7_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK7_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK7: FDBCK Mask        */

#define CRPT_HMAC_FDBCK8_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK8: FDBCK Position    */
#define CRPT_HMAC_FDBCK8_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK8_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK8: FDBCK Mask        */

#define CRPT_HMAC_FDBCK9_FDBCK_Pos       (0)                                               /*!< CRPT_T::HMAC_FDBCK9: FDBCK Position    */
#define CRPT_HMAC_FDBCK9_FDBCK_Msk       (0xfffffffful << CRPT_HMAC_FDBCK9_FDBCK_Pos)      /*!< CRPT_T::HMAC_FDBCK9: FDBCK Mask        */

#define CRPT_HMAC_FDBCK10_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK10: FDBCK Position   */
#define CRPT_HMAC_FDBCK10_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK10_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK10: FDBCK Mask       */

#define CRPT_HMAC_FDBCK11_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK11: FDBCK Position   */
#define CRPT_HMAC_FDBCK11_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK11_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK11: FDBCK Mask       */

#define CRPT_HMAC_FDBCK12_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK12: FDBCK Position   */
#define CRPT_HMAC_FDBCK12_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK12_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK12: FDBCK Mask       */

#define CRPT_HMAC_FDBCK13_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK13: FDBCK Position   */
#define CRPT_HMAC_FDBCK13_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK13_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK13: FDBCK Mask       */

#define CRPT_HMAC_FDBCK14_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK14: FDBCK Position   */
#define CRPT_HMAC_FDBCK14_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK14_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK14: FDBCK Mask       */

#define CRPT_HMAC_FDBCK15_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK15: FDBCK Position   */
#define CRPT_HMAC_FDBCK15_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK15_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK15: FDBCK Mask       */

#define CRPT_HMAC_FDBCK16_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK16: FDBCK Position   */
#define CRPT_HMAC_FDBCK16_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK16_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK16: FDBCK Mask       */

#define CRPT_HMAC_FDBCK17_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK17: FDBCK Position   */
#define CRPT_HMAC_FDBCK17_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK17_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK17: FDBCK Mask       */

#define CRPT_HMAC_FDBCK18_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK18: FDBCK Position   */
#define CRPT_HMAC_FDBCK18_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK18_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK18: FDBCK Mask       */

#define CRPT_HMAC_FDBCK19_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK19: FDBCK Position   */
#define CRPT_HMAC_FDBCK19_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK19_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK19: FDBCK Mask       */

#define CRPT_HMAC_FDBCK20_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK20: FDBCK Position   */
#define CRPT_HMAC_FDBCK20_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK20_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK20: FDBCK Mask       */

#define CRPT_HMAC_FDBCK21_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK21: FDBCK Position   */
#define CRPT_HMAC_FDBCK21_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK21_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK21: FDBCK Mask       */

#define CRPT_HMAC_FDBCK22_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK22: FDBCK Position   */
#define CRPT_HMAC_FDBCK22_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK22_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK22: FDBCK Mask       */

#define CRPT_HMAC_FDBCK23_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK23: FDBCK Position   */
#define CRPT_HMAC_FDBCK23_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK23_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK23: FDBCK Mask       */

#define CRPT_HMAC_FDBCK24_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK24: FDBCK Position   */
#define CRPT_HMAC_FDBCK24_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK24_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK24: FDBCK Mask       */

#define CRPT_HMAC_FDBCK25_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK25: FDBCK Position   */
#define CRPT_HMAC_FDBCK25_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK25_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK25: FDBCK Mask       */

#define CRPT_HMAC_FDBCK26_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK26: FDBCK Position   */
#define CRPT_HMAC_FDBCK26_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK26_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK26: FDBCK Mask       */

#define CRPT_HMAC_FDBCK27_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK27: FDBCK Position   */
#define CRPT_HMAC_FDBCK27_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK27_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK27: FDBCK Mask       */

#define CRPT_HMAC_FDBCK28_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK28: FDBCK Position   */
#define CRPT_HMAC_FDBCK28_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK28_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK28: FDBCK Mask       */

#define CRPT_HMAC_FDBCK29_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK29: FDBCK Position   */
#define CRPT_HMAC_FDBCK29_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK29_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK29: FDBCK Mask       */

#define CRPT_HMAC_FDBCK30_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK30: FDBCK Position   */
#define CRPT_HMAC_FDBCK30_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK30_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK30: FDBCK Mask       */

#define CRPT_HMAC_FDBCK31_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK31: FDBCK Position   */
#define CRPT_HMAC_FDBCK31_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK31_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK31: FDBCK Mask       */

#define CRPT_HMAC_FDBCK32_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK32: FDBCK Position   */
#define CRPT_HMAC_FDBCK32_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK32_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK32: FDBCK Mask       */

#define CRPT_HMAC_FDBCK33_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK33: FDBCK Position   */
#define CRPT_HMAC_FDBCK33_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK33_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK33: FDBCK Mask       */

#define CRPT_HMAC_FDBCK34_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK34: FDBCK Position   */
#define CRPT_HMAC_FDBCK34_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK34_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK34: FDBCK Mask       */

#define CRPT_HMAC_FDBCK35_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK35: FDBCK Position   */
#define CRPT_HMAC_FDBCK35_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK35_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK35: FDBCK Mask       */

#define CRPT_HMAC_FDBCK36_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK36: FDBCK Position   */
#define CRPT_HMAC_FDBCK36_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK36_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK36: FDBCK Mask       */

#define CRPT_HMAC_FDBCK37_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK37: FDBCK Position   */
#define CRPT_HMAC_FDBCK37_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK37_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK37: FDBCK Mask       */

#define CRPT_HMAC_FDBCK38_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK38: FDBCK Position   */
#define CRPT_HMAC_FDBCK38_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK38_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK38: FDBCK Mask       */

#define CRPT_HMAC_FDBCK39_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK39: FDBCK Position   */
#define CRPT_HMAC_FDBCK39_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK39_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK39: FDBCK Mask       */

#define CRPT_HMAC_FDBCK40_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK40: FDBCK Position   */
#define CRPT_HMAC_FDBCK40_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK40_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK40: FDBCK Mask       */

#define CRPT_HMAC_FDBCK41_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK41: FDBCK Position   */
#define CRPT_HMAC_FDBCK41_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK41_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK41: FDBCK Mask       */

#define CRPT_HMAC_FDBCK42_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK42: FDBCK Position   */
#define CRPT_HMAC_FDBCK42_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK42_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK42: FDBCK Mask       */

#define CRPT_HMAC_FDBCK43_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK43: FDBCK Position   */
#define CRPT_HMAC_FDBCK43_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK43_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK43: FDBCK Mask       */

#define CRPT_HMAC_FDBCK44_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK44: FDBCK Position   */
#define CRPT_HMAC_FDBCK44_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK44_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK44: FDBCK Mask       */

#define CRPT_HMAC_FDBCK45_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK45: FDBCK Position   */
#define CRPT_HMAC_FDBCK45_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK45_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK45: FDBCK Mask       */

#define CRPT_HMAC_FDBCK46_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK46: FDBCK Position   */
#define CRPT_HMAC_FDBCK46_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK46_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK46: FDBCK Mask       */

#define CRPT_HMAC_FDBCK47_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK47: FDBCK Position   */
#define CRPT_HMAC_FDBCK47_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK47_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK47: FDBCK Mask       */

#define CRPT_HMAC_FDBCK48_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK48: FDBCK Position   */
#define CRPT_HMAC_FDBCK48_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK48_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK48: FDBCK Mask       */

#define CRPT_HMAC_FDBCK49_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK49: FDBCK Position   */
#define CRPT_HMAC_FDBCK49_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK49_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK49: FDBCK Mask       */

#define CRPT_HMAC_FDBCK50_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK50: FDBCK Position   */
#define CRPT_HMAC_FDBCK50_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK50_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK50: FDBCK Mask       */

#define CRPT_HMAC_FDBCK51_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK51: FDBCK Position   */
#define CRPT_HMAC_FDBCK51_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK51_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK51: FDBCK Mask       */

#define CRPT_HMAC_FDBCK52_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK52: FDBCK Position   */
#define CRPT_HMAC_FDBCK52_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK52_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK52: FDBCK Mask       */

#define CRPT_HMAC_FDBCK53_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK53: FDBCK Position   */
#define CRPT_HMAC_FDBCK53_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK53_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK53: FDBCK Mask       */

#define CRPT_HMAC_FDBCK54_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK54: FDBCK Position   */
#define CRPT_HMAC_FDBCK54_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK54_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK54: FDBCK Mask       */

#define CRPT_HMAC_FDBCK55_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK55: FDBCK Position   */
#define CRPT_HMAC_FDBCK55_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK55_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK55: FDBCK Mask       */

#define CRPT_HMAC_FDBCK56_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK56: FDBCK Position   */
#define CRPT_HMAC_FDBCK56_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK56_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK56: FDBCK Mask       */

#define CRPT_HMAC_FDBCK57_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK57: FDBCK Position   */
#define CRPT_HMAC_FDBCK57_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK57_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK57: FDBCK Mask       */

#define CRPT_HMAC_FDBCK58_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK58: FDBCK Position   */
#define CRPT_HMAC_FDBCK58_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK58_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK58: FDBCK Mask       */

#define CRPT_HMAC_FDBCK59_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK59: FDBCK Position   */
#define CRPT_HMAC_FDBCK59_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK59_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK59: FDBCK Mask       */

#define CRPT_HMAC_FDBCK60_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK60: FDBCK Position   */
#define CRPT_HMAC_FDBCK60_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK60_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK60: FDBCK Mask       */

#define CRPT_HMAC_FDBCK61_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK61: FDBCK Position   */
#define CRPT_HMAC_FDBCK61_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK61_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK61: FDBCK Mask       */

#define CRPT_HMAC_FDBCK62_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK62: FDBCK Position   */
#define CRPT_HMAC_FDBCK62_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK62_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK62: FDBCK Mask       */

#define CRPT_HMAC_FDBCK63_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK63: FDBCK Position   */
#define CRPT_HMAC_FDBCK63_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK63_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK63: FDBCK Mask       */

#define CRPT_HMAC_FDBCK64_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK64: FDBCK Position   */
#define CRPT_HMAC_FDBCK64_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK64_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK64: FDBCK Mask       */

#define CRPT_HMAC_FDBCK65_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK65: FDBCK Position   */
#define CRPT_HMAC_FDBCK65_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK65_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK65: FDBCK Mask       */

#define CRPT_HMAC_FDBCK66_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK66: FDBCK Position   */
#define CRPT_HMAC_FDBCK66_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK66_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK66: FDBCK Mask       */

#define CRPT_HMAC_FDBCK67_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK67: FDBCK Position   */
#define CRPT_HMAC_FDBCK67_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK67_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK67: FDBCK Mask       */

#define CRPT_HMAC_FDBCK68_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK68: FDBCK Position   */
#define CRPT_HMAC_FDBCK68_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK68_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK68: FDBCK Mask       */

#define CRPT_HMAC_FDBCK69_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK69: FDBCK Position   */
#define CRPT_HMAC_FDBCK69_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK69_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK69: FDBCK Mask       */

#define CRPT_HMAC_FDBCK70_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK70: FDBCK Position   */
#define CRPT_HMAC_FDBCK70_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK70_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK70: FDBCK Mask       */

#define CRPT_HMAC_FDBCK71_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK71: FDBCK Position   */
#define CRPT_HMAC_FDBCK71_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK71_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK71: FDBCK Mask       */

#define CRPT_HMAC_FDBCK72_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK72: FDBCK Position   */
#define CRPT_HMAC_FDBCK72_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK72_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK72: FDBCK Mask       */

#define CRPT_HMAC_FDBCK73_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK73: FDBCK Position   */
#define CRPT_HMAC_FDBCK73_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK73_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK73: FDBCK Mask       */

#define CRPT_HMAC_FDBCK74_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK74: FDBCK Position   */
#define CRPT_HMAC_FDBCK74_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK74_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK74: FDBCK Mask       */

#define CRPT_HMAC_FDBCK75_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK75: FDBCK Position   */
#define CRPT_HMAC_FDBCK75_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK75_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK75: FDBCK Mask       */

#define CRPT_HMAC_FDBCK76_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK76: FDBCK Position   */
#define CRPT_HMAC_FDBCK76_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK76_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK76: FDBCK Mask       */

#define CRPT_HMAC_FDBCK77_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK77: FDBCK Position   */
#define CRPT_HMAC_FDBCK77_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK77_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK77: FDBCK Mask       */

#define CRPT_HMAC_FDBCK78_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK78: FDBCK Position   */
#define CRPT_HMAC_FDBCK78_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK78_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK78: FDBCK Mask       */

#define CRPT_HMAC_FDBCK79_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK79: FDBCK Position   */
#define CRPT_HMAC_FDBCK79_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK79_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK79: FDBCK Mask       */

#define CRPT_HMAC_FDBCK80_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK80: FDBCK Position   */
#define CRPT_HMAC_FDBCK80_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK80_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK80: FDBCK Mask       */

#define CRPT_HMAC_FDBCK81_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK81: FDBCK Position   */
#define CRPT_HMAC_FDBCK81_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK81_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK81: FDBCK Mask       */

#define CRPT_HMAC_FDBCK82_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK82: FDBCK Position   */
#define CRPT_HMAC_FDBCK82_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK82_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK82: FDBCK Mask       */

#define CRPT_HMAC_FDBCK83_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK83: FDBCK Position   */
#define CRPT_HMAC_FDBCK83_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK83_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK83: FDBCK Mask       */

#define CRPT_HMAC_FDBCK84_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK84: FDBCK Position   */
#define CRPT_HMAC_FDBCK84_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK84_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK84: FDBCK Mask       */

#define CRPT_HMAC_FDBCK85_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK85: FDBCK Position   */
#define CRPT_HMAC_FDBCK85_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK85_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK85: FDBCK Mask       */

#define CRPT_HMAC_FDBCK86_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK86: FDBCK Position   */
#define CRPT_HMAC_FDBCK86_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK86_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK86: FDBCK Mask       */

#define CRPT_HMAC_FDBCK87_FDBCK_Pos      (0)                                               /*!< CRPT_T::HMAC_FDBCK87: FDBCK Position   */
#define CRPT_HMAC_FDBCK87_FDBCK_Msk      (0xfffffffful << CRPT_HMAC_FDBCK87_FDBCK_Pos)     /*!< CRPT_T::HMAC_FDBCK87: FDBCK Mask       */

#define CRPT_HMAC_SHA512T_SHA512TEN_Pos  (0)                                               /*!< CRPT_T::HMAC_SHA512T: SHA512TEN Position*/
#define CRPT_HMAC_SHA512T_SHA512TEN_Msk  (0x1ul << CRPT_HMAC_SHA512T_SHA512TEN_Pos)        /*!< CRPT_T::HMAC_SHA512T: SHA512TEN Mask   */

#define CRPT_HMAC_SHA512T_TLEN_Pos       (8)                                               /*!< CRPT_T::HMAC_SHA512T: TLEN Position    */
#define CRPT_HMAC_SHA512T_TLEN_Msk       (0x1fful << CRPT_HMAC_SHA512T_TLEN_Pos)           /*!< CRPT_T::HMAC_SHA512T: TLEN Mask        */

#define CRPT_HMAC_FBADDR_FBADDR_Pos      (0)                                               /*!< CRPT_T::HMAC_FBADDR: FBADDR Position   */
#define CRPT_HMAC_FBADDR_FBADDR_Msk      (0xfffffffful << CRPT_HMAC_FBADDR_FBADDR_Pos)     /*!< CRPT_T::HMAC_FBADDR: FBADDR Mask       */

#define CRPT_HMAC_SHAKEDGST0_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST0: DGST Position */
#define CRPT_HMAC_SHAKEDGST0_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST0_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST0: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST1_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST1: DGST Position */
#define CRPT_HMAC_SHAKEDGST1_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST1_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST1: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST2_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST2: DGST Position */
#define CRPT_HMAC_SHAKEDGST2_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST2_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST2: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST3_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST3: DGST Position */
#define CRPT_HMAC_SHAKEDGST3_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST3_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST3: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST4_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST4: DGST Position */
#define CRPT_HMAC_SHAKEDGST4_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST4_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST4: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST5_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST5: DGST Position */
#define CRPT_HMAC_SHAKEDGST5_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST5_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST5: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST6_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST6: DGST Position */
#define CRPT_HMAC_SHAKEDGST6_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST6_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST6: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST7_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST7: DGST Position */
#define CRPT_HMAC_SHAKEDGST7_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST7_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST7: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST8_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST8: DGST Position */
#define CRPT_HMAC_SHAKEDGST8_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST8_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST8: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST9_DGST_Pos    (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST9: DGST Position */
#define CRPT_HMAC_SHAKEDGST9_DGST_Msk    (0xfffffffful << CRPT_HMAC_SHAKEDGST9_DGST_Pos)   /*!< CRPT_T::HMAC_SHAKEDGST9: DGST Mask     */

#define CRPT_HMAC_SHAKEDGST10_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST10: DGST Position*/
#define CRPT_HMAC_SHAKEDGST10_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST10_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST10: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST11_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST11: DGST Position*/
#define CRPT_HMAC_SHAKEDGST11_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST11_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST11: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST12_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST12: DGST Position*/
#define CRPT_HMAC_SHAKEDGST12_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST12_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST12: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST13_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST13: DGST Position*/
#define CRPT_HMAC_SHAKEDGST13_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST13_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST13: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST14_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST14: DGST Position*/
#define CRPT_HMAC_SHAKEDGST14_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST14_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST14: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST15_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST15: DGST Position*/
#define CRPT_HMAC_SHAKEDGST15_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST15_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST15: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST16_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST16: DGST Position*/
#define CRPT_HMAC_SHAKEDGST16_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST16_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST16: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST17_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST17: DGST Position*/
#define CRPT_HMAC_SHAKEDGST17_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST17_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST17: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST18_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST18: DGST Position*/
#define CRPT_HMAC_SHAKEDGST18_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST18_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST18: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST19_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST19: DGST Position*/
#define CRPT_HMAC_SHAKEDGST19_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST19_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST19: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST20_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST20: DGST Position*/
#define CRPT_HMAC_SHAKEDGST20_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST20_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST20: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST21_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST21: DGST Position*/
#define CRPT_HMAC_SHAKEDGST21_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST21_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST21: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST22_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST22: DGST Position*/
#define CRPT_HMAC_SHAKEDGST22_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST22_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST22: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST23_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST23: DGST Position*/
#define CRPT_HMAC_SHAKEDGST23_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST23_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST23: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST24_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST24: DGST Position*/
#define CRPT_HMAC_SHAKEDGST24_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST24_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST24: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST25_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST25: DGST Position*/
#define CRPT_HMAC_SHAKEDGST25_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST25_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST25: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST26_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST26: DGST Position*/
#define CRPT_HMAC_SHAKEDGST26_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST26_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST26: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST27_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST27: DGST Position*/
#define CRPT_HMAC_SHAKEDGST27_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST27_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST27: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST28_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST28: DGST Position*/
#define CRPT_HMAC_SHAKEDGST28_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST28_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST28: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST29_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST29: DGST Position*/
#define CRPT_HMAC_SHAKEDGST29_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST29_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST29: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST30_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST30: DGST Position*/
#define CRPT_HMAC_SHAKEDGST30_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST30_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST30: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST31_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST31: DGST Position*/
#define CRPT_HMAC_SHAKEDGST31_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST31_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST31: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST32_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST32: DGST Position*/
#define CRPT_HMAC_SHAKEDGST32_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST32_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST32: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST33_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST33: DGST Position*/
#define CRPT_HMAC_SHAKEDGST33_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST33_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST33: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST34_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST34: DGST Position*/
#define CRPT_HMAC_SHAKEDGST34_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST34_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST34: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST35_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST35: DGST Position*/
#define CRPT_HMAC_SHAKEDGST35_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST35_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST35: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST36_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST36: DGST Position*/
#define CRPT_HMAC_SHAKEDGST36_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST36_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST36: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST37_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST37: DGST Position*/
#define CRPT_HMAC_SHAKEDGST37_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST37_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST37: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST38_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST38: DGST Position*/
#define CRPT_HMAC_SHAKEDGST38_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST38_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST38: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST39_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST39: DGST Position*/
#define CRPT_HMAC_SHAKEDGST39_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST39_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST39: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST40_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST40: DGST Position*/
#define CRPT_HMAC_SHAKEDGST40_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST40_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST40: DGST Mask    */

#define CRPT_HMAC_SHAKEDGST41_DGST_Pos   (0)                                               /*!< CRPT_T::HMAC_SHAKEDGST41: DGST Position*/
#define CRPT_HMAC_SHAKEDGST41_DGST_Msk   (0xfffffffful << CRPT_HMAC_SHAKEDGST41_DGST_Pos)  /*!< CRPT_T::HMAC_SHAKEDGST41: DGST Mask    */

#define CRPT_ECC_CTL_START_Pos           (0)                                               /*!< CRPT_T::ECC_CTL: START Position        */
#define CRPT_ECC_CTL_START_Msk           (0x1ul << CRPT_ECC_CTL_START_Pos)                 /*!< CRPT_T::ECC_CTL: START Mask            */

#define CRPT_ECC_CTL_STOP_Pos            (1)                                               /*!< CRPT_T::ECC_CTL: STOP Position         */
#define CRPT_ECC_CTL_STOP_Msk            (0x1ul << CRPT_ECC_CTL_STOP_Pos)                  /*!< CRPT_T::ECC_CTL: STOP Mask             */

#define CRPT_ECC_CTL_PFA2C_Pos           (3)                                               /*!< CRPT_T::ECC_CTL: PFA2C Position        */
#define CRPT_ECC_CTL_PFA2C_Msk           (0x1ul << CRPT_ECC_CTL_PFA2C_Pos)                 /*!< CRPT_T::ECC_CTL: PFA2C Mask            */

#define CRPT_ECC_CTL_ECDSAS_Pos          (4)                                               /*!< CRPT_T::ECC_CTL: ECDSAS Position       */
#define CRPT_ECC_CTL_ECDSAS_Msk          (0x1ul << CRPT_ECC_CTL_ECDSAS_Pos)                /*!< CRPT_T::ECC_CTL: ECDSAS Mask           */

#define CRPT_ECC_CTL_ECDSAR_Pos          (5)                                               /*!< CRPT_T::ECC_CTL: ECDSAR Position       */
#define CRPT_ECC_CTL_ECDSAR_Msk          (0x1ul << CRPT_ECC_CTL_ECDSAR_Pos)                /*!< CRPT_T::ECC_CTL: ECDSAR Mask           */

#define CRPT_ECC_CTL_DFAP_Pos            (6)                                               /*!< CRPT_T::ECC_CTL: DFAP Position         */
#define CRPT_ECC_CTL_DFAP_Msk            (0x1ul << CRPT_ECC_CTL_DFAP_Pos)                  /*!< CRPT_T::ECC_CTL: DFAP Mask             */

#define CRPT_ECC_CTL_DMAEN_Pos           (7)                                               /*!< CRPT_T::ECC_CTL: DMAEN Position        */
#define CRPT_ECC_CTL_DMAEN_Msk           (0x1ul << CRPT_ECC_CTL_DMAEN_Pos)                 /*!< CRPT_T::ECC_CTL: DMAEN Mask            */

#define CRPT_ECC_CTL_FSEL_Pos            (8)                                               /*!< CRPT_T::ECC_CTL: FSEL Position         */
#define CRPT_ECC_CTL_FSEL_Msk            (0x1ul << CRPT_ECC_CTL_FSEL_Pos)                  /*!< CRPT_T::ECC_CTL: FSEL Mask             */

#define CRPT_ECC_CTL_ECCOP_Pos           (9)                                               /*!< CRPT_T::ECC_CTL: ECCOP Position        */
#define CRPT_ECC_CTL_ECCOP_Msk           (0x3ul << CRPT_ECC_CTL_ECCOP_Pos)                 /*!< CRPT_T::ECC_CTL: ECCOP Mask            */

#define CRPT_ECC_CTL_MODOP_Pos           (11)                                              /*!< CRPT_T::ECC_CTL: MODOP Position        */
#define CRPT_ECC_CTL_MODOP_Msk           (0x3ul << CRPT_ECC_CTL_MODOP_Pos)                 /*!< CRPT_T::ECC_CTL: MODOP Mask            */

#define CRPT_ECC_CTL_CSEL_Pos            (13)                                              /*!< CRPT_T::ECC_CTL: CSEL Position         */
#define CRPT_ECC_CTL_CSEL_Msk            (0x1ul << CRPT_ECC_CTL_CSEL_Pos)                  /*!< CRPT_T::ECC_CTL: CSEL Mask             */

#define CRPT_ECC_CTL_SCAP_Pos            (14)                                              /*!< CRPT_T::ECC_CTL: SCAP Position         */
#define CRPT_ECC_CTL_SCAP_Msk            (0x1ul << CRPT_ECC_CTL_SCAP_Pos)                  /*!< CRPT_T::ECC_CTL: SCAP Mask             */

#define CRPT_ECC_CTL_LDP1_Pos            (16)                                              /*!< CRPT_T::ECC_CTL: LDP1 Position         */
#define CRPT_ECC_CTL_LDP1_Msk            (0x1ul << CRPT_ECC_CTL_LDP1_Pos)                  /*!< CRPT_T::ECC_CTL: LDP1 Mask             */

#define CRPT_ECC_CTL_LDP2_Pos            (17)                                              /*!< CRPT_T::ECC_CTL: LDP2 Position         */
#define CRPT_ECC_CTL_LDP2_Msk            (0x1ul << CRPT_ECC_CTL_LDP2_Pos)                  /*!< CRPT_T::ECC_CTL: LDP2 Mask             */

#define CRPT_ECC_CTL_LDA_Pos             (18)                                              /*!< CRPT_T::ECC_CTL: LDA Position          */
#define CRPT_ECC_CTL_LDA_Msk             (0x1ul << CRPT_ECC_CTL_LDA_Pos)                   /*!< CRPT_T::ECC_CTL: LDA Mask              */

#define CRPT_ECC_CTL_LDB_Pos             (19)                                              /*!< CRPT_T::ECC_CTL: LDB Position          */
#define CRPT_ECC_CTL_LDB_Msk             (0x1ul << CRPT_ECC_CTL_LDB_Pos)                   /*!< CRPT_T::ECC_CTL: LDB Mask              */

#define CRPT_ECC_CTL_LDN_Pos             (20)                                              /*!< CRPT_T::ECC_CTL: LDN Position          */
#define CRPT_ECC_CTL_LDN_Msk             (0x1ul << CRPT_ECC_CTL_LDN_Pos)                   /*!< CRPT_T::ECC_CTL: LDN Mask              */

#define CRPT_ECC_CTL_LDK_Pos             (21)                                              /*!< CRPT_T::ECC_CTL: LDK Position          */
#define CRPT_ECC_CTL_LDK_Msk             (0x1ul << CRPT_ECC_CTL_LDK_Pos)                   /*!< CRPT_T::ECC_CTL: LDK Mask              */

#define CRPT_ECC_CTL_CURVEM_Pos          (22)                                              /*!< CRPT_T::ECC_CTL: CURVEM Position       */
#define CRPT_ECC_CTL_CURVEM_Msk          (0x3fful << CRPT_ECC_CTL_CURVEM_Pos)              /*!< CRPT_T::ECC_CTL: CURVEM Mask           */

#define CRPT_ECC_STS_BUSY_Pos            (0)                                               /*!< CRPT_T::ECC_STS: BUSY Position         */
#define CRPT_ECC_STS_BUSY_Msk            (0x1ul << CRPT_ECC_STS_BUSY_Pos)                  /*!< CRPT_T::ECC_STS: BUSY Mask             */

#define CRPT_ECC_STS_DMABUSY_Pos         (1)                                               /*!< CRPT_T::ECC_STS: DMABUSY Position      */
#define CRPT_ECC_STS_DMABUSY_Msk         (0x1ul << CRPT_ECC_STS_DMABUSY_Pos)               /*!< CRPT_T::ECC_STS: DMABUSY Mask          */

#define CRPT_ECC_STS_BUSERR_Pos          (16)                                              /*!< CRPT_T::ECC_STS: BUSERR Position       */
#define CRPT_ECC_STS_BUSERR_Msk          (0x1ul << CRPT_ECC_STS_BUSERR_Pos)                /*!< CRPT_T::ECC_STS: BUSERR Mask           */

#define CRPT_ECC_STS_KSERR_Pos           (17)                                              /*!< CRPT_T::ECC_STS: KSERR Position        */
#define CRPT_ECC_STS_KSERR_Msk           (0x1ul << CRPT_ECC_STS_KSERR_Pos)                 /*!< CRPT_T::ECC_STS: KSERR Mask            */

#define CRPT_ECC_STS_DFAERR_Pos          (18)                                              /*!< CRPT_T::ECC_STS: DFAERR Position       */
#define CRPT_ECC_STS_DFAERR_Msk          (0x1ul << CRPT_ECC_STS_DFAERR_Pos)                /*!< CRPT_T::ECC_STS: DFAERR Mask           */

#define CRPT_ECC_X1_00_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_00: POINTX1 Position    */
#define CRPT_ECC_X1_00_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_00_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_00: POINTX1 Mask        */

#define CRPT_ECC_X1_01_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_01: POINTX1 Position    */
#define CRPT_ECC_X1_01_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_01_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_01: POINTX1 Mask        */

#define CRPT_ECC_X1_02_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_02: POINTX1 Position    */
#define CRPT_ECC_X1_02_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_02_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_02: POINTX1 Mask        */

#define CRPT_ECC_X1_03_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_03: POINTX1 Position    */
#define CRPT_ECC_X1_03_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_03_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_03: POINTX1 Mask        */

#define CRPT_ECC_X1_04_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_04: POINTX1 Position    */
#define CRPT_ECC_X1_04_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_04_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_04: POINTX1 Mask        */

#define CRPT_ECC_X1_05_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_05: POINTX1 Position    */
#define CRPT_ECC_X1_05_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_05_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_05: POINTX1 Mask        */

#define CRPT_ECC_X1_06_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_06: POINTX1 Position    */
#define CRPT_ECC_X1_06_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_06_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_06: POINTX1 Mask        */

#define CRPT_ECC_X1_07_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_07: POINTX1 Position    */
#define CRPT_ECC_X1_07_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_07_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_07: POINTX1 Mask        */

#define CRPT_ECC_X1_08_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_08: POINTX1 Position    */
#define CRPT_ECC_X1_08_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_08_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_08: POINTX1 Mask        */

#define CRPT_ECC_X1_09_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_09: POINTX1 Position    */
#define CRPT_ECC_X1_09_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_09_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_09: POINTX1 Mask        */

#define CRPT_ECC_X1_10_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_10: POINTX1 Position    */
#define CRPT_ECC_X1_10_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_10_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_10: POINTX1 Mask        */

#define CRPT_ECC_X1_11_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_11: POINTX1 Position    */
#define CRPT_ECC_X1_11_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_11_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_11: POINTX1 Mask        */

#define CRPT_ECC_X1_12_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_12: POINTX1 Position    */
#define CRPT_ECC_X1_12_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_12_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_12: POINTX1 Mask        */

#define CRPT_ECC_X1_13_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_13: POINTX1 Position    */
#define CRPT_ECC_X1_13_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_13_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_13: POINTX1 Mask        */

#define CRPT_ECC_X1_14_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_14: POINTX1 Position    */
#define CRPT_ECC_X1_14_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_14_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_14: POINTX1 Mask        */

#define CRPT_ECC_X1_15_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_15: POINTX1 Position    */
#define CRPT_ECC_X1_15_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_15_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_15: POINTX1 Mask        */

#define CRPT_ECC_X1_16_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_16: POINTX1 Position    */
#define CRPT_ECC_X1_16_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_16_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_16: POINTX1 Mask        */

#define CRPT_ECC_X1_17_POINTX1_Pos       (0)                                               /*!< CRPT_T::ECC_X1_17: POINTX1 Position    */
#define CRPT_ECC_X1_17_POINTX1_Msk       (0xfffffffful << CRPT_ECC_X1_17_POINTX1_Pos)      /*!< CRPT_T::ECC_X1_17: POINTX1 Mask        */

#define CRPT_ECC_Y1_00_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_00: POINTY1 Position    */
#define CRPT_ECC_Y1_00_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_00_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_00: POINTY1 Mask        */

#define CRPT_ECC_Y1_01_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_01: POINTY1 Position    */
#define CRPT_ECC_Y1_01_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_01_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_01: POINTY1 Mask        */

#define CRPT_ECC_Y1_02_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_02: POINTY1 Position    */
#define CRPT_ECC_Y1_02_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_02_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_02: POINTY1 Mask        */

#define CRPT_ECC_Y1_03_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_03: POINTY1 Position    */
#define CRPT_ECC_Y1_03_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_03_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_03: POINTY1 Mask        */

#define CRPT_ECC_Y1_04_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_04: POINTY1 Position    */
#define CRPT_ECC_Y1_04_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_04_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_04: POINTY1 Mask        */

#define CRPT_ECC_Y1_05_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_05: POINTY1 Position    */
#define CRPT_ECC_Y1_05_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_05_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_05: POINTY1 Mask        */

#define CRPT_ECC_Y1_06_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_06: POINTY1 Position    */
#define CRPT_ECC_Y1_06_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_06_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_06: POINTY1 Mask        */

#define CRPT_ECC_Y1_07_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_07: POINTY1 Position    */
#define CRPT_ECC_Y1_07_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_07_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_07: POINTY1 Mask        */

#define CRPT_ECC_Y1_08_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_08: POINTY1 Position    */
#define CRPT_ECC_Y1_08_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_08_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_08: POINTY1 Mask        */

#define CRPT_ECC_Y1_09_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_09: POINTY1 Position    */
#define CRPT_ECC_Y1_09_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_09_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_09: POINTY1 Mask        */

#define CRPT_ECC_Y1_10_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_10: POINTY1 Position    */
#define CRPT_ECC_Y1_10_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_10_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_10: POINTY1 Mask        */

#define CRPT_ECC_Y1_11_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_11: POINTY1 Position    */
#define CRPT_ECC_Y1_11_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_11_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_11: POINTY1 Mask        */

#define CRPT_ECC_Y1_12_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_12: POINTY1 Position    */
#define CRPT_ECC_Y1_12_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_12_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_12: POINTY1 Mask        */

#define CRPT_ECC_Y1_13_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_13: POINTY1 Position    */
#define CRPT_ECC_Y1_13_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_13_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_13: POINTY1 Mask        */

#define CRPT_ECC_Y1_14_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_14: POINTY1 Position    */
#define CRPT_ECC_Y1_14_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_14_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_14: POINTY1 Mask        */

#define CRPT_ECC_Y1_15_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_15: POINTY1 Position    */
#define CRPT_ECC_Y1_15_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_15_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_15: POINTY1 Mask        */

#define CRPT_ECC_Y1_16_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_16: POINTY1 Position    */
#define CRPT_ECC_Y1_16_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_16_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_16: POINTY1 Mask        */

#define CRPT_ECC_Y1_17_POINTY1_Pos       (0)                                               /*!< CRPT_T::ECC_Y1_17: POINTY1 Position    */
#define CRPT_ECC_Y1_17_POINTY1_Msk       (0xfffffffful << CRPT_ECC_Y1_17_POINTY1_Pos)      /*!< CRPT_T::ECC_Y1_17: POINTY1 Mask        */

#define CRPT_ECC_X2_00_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_00: POINTX2 Position    */
#define CRPT_ECC_X2_00_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_00_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_00: POINTX2 Mask        */

#define CRPT_ECC_X2_01_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_01: POINTX2 Position    */
#define CRPT_ECC_X2_01_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_01_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_01: POINTX2 Mask        */

#define CRPT_ECC_X2_02_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_02: POINTX2 Position    */
#define CRPT_ECC_X2_02_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_02_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_02: POINTX2 Mask        */

#define CRPT_ECC_X2_03_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_03: POINTX2 Position    */
#define CRPT_ECC_X2_03_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_03_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_03: POINTX2 Mask        */

#define CRPT_ECC_X2_04_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_04: POINTX2 Position    */
#define CRPT_ECC_X2_04_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_04_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_04: POINTX2 Mask        */

#define CRPT_ECC_X2_05_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_05: POINTX2 Position    */
#define CRPT_ECC_X2_05_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_05_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_05: POINTX2 Mask        */

#define CRPT_ECC_X2_06_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_06: POINTX2 Position    */
#define CRPT_ECC_X2_06_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_06_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_06: POINTX2 Mask        */

#define CRPT_ECC_X2_07_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_07: POINTX2 Position    */
#define CRPT_ECC_X2_07_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_07_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_07: POINTX2 Mask        */

#define CRPT_ECC_X2_08_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_08: POINTX2 Position    */
#define CRPT_ECC_X2_08_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_08_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_08: POINTX2 Mask        */

#define CRPT_ECC_X2_09_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_09: POINTX2 Position    */
#define CRPT_ECC_X2_09_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_09_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_09: POINTX2 Mask        */

#define CRPT_ECC_X2_10_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_10: POINTX2 Position    */
#define CRPT_ECC_X2_10_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_10_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_10: POINTX2 Mask        */

#define CRPT_ECC_X2_11_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_11: POINTX2 Position    */
#define CRPT_ECC_X2_11_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_11_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_11: POINTX2 Mask        */

#define CRPT_ECC_X2_12_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_12: POINTX2 Position    */
#define CRPT_ECC_X2_12_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_12_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_12: POINTX2 Mask        */

#define CRPT_ECC_X2_13_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_13: POINTX2 Position    */
#define CRPT_ECC_X2_13_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_13_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_13: POINTX2 Mask        */

#define CRPT_ECC_X2_14_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_14: POINTX2 Position    */
#define CRPT_ECC_X2_14_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_14_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_14: POINTX2 Mask        */

#define CRPT_ECC_X2_15_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_15: POINTX2 Position    */
#define CRPT_ECC_X2_15_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_15_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_15: POINTX2 Mask        */

#define CRPT_ECC_X2_16_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_16: POINTX2 Position    */
#define CRPT_ECC_X2_16_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_16_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_16: POINTX2 Mask        */

#define CRPT_ECC_X2_17_POINTX2_Pos       (0)                                               /*!< CRPT_T::ECC_X2_17: POINTX2 Position    */
#define CRPT_ECC_X2_17_POINTX2_Msk       (0xfffffffful << CRPT_ECC_X2_17_POINTX2_Pos)      /*!< CRPT_T::ECC_X2_17: POINTX2 Mask        */

#define CRPT_ECC_Y2_00_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_00: POINTY2 Position    */
#define CRPT_ECC_Y2_00_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_00_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_00: POINTY2 Mask        */

#define CRPT_ECC_Y2_01_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_01: POINTY2 Position    */
#define CRPT_ECC_Y2_01_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_01_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_01: POINTY2 Mask        */

#define CRPT_ECC_Y2_02_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_02: POINTY2 Position    */
#define CRPT_ECC_Y2_02_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_02_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_02: POINTY2 Mask        */

#define CRPT_ECC_Y2_03_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_03: POINTY2 Position    */
#define CRPT_ECC_Y2_03_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_03_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_03: POINTY2 Mask        */

#define CRPT_ECC_Y2_04_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_04: POINTY2 Position    */
#define CRPT_ECC_Y2_04_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_04_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_04: POINTY2 Mask        */

#define CRPT_ECC_Y2_05_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_05: POINTY2 Position    */
#define CRPT_ECC_Y2_05_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_05_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_05: POINTY2 Mask        */

#define CRPT_ECC_Y2_06_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_06: POINTY2 Position    */
#define CRPT_ECC_Y2_06_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_06_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_06: POINTY2 Mask        */

#define CRPT_ECC_Y2_07_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_07: POINTY2 Position    */
#define CRPT_ECC_Y2_07_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_07_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_07: POINTY2 Mask        */

#define CRPT_ECC_Y2_08_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_08: POINTY2 Position    */
#define CRPT_ECC_Y2_08_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_08_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_08: POINTY2 Mask        */

#define CRPT_ECC_Y2_09_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_09: POINTY2 Position    */
#define CRPT_ECC_Y2_09_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_09_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_09: POINTY2 Mask        */

#define CRPT_ECC_Y2_10_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_10: POINTY2 Position    */
#define CRPT_ECC_Y2_10_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_10_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_10: POINTY2 Mask        */

#define CRPT_ECC_Y2_11_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_11: POINTY2 Position    */
#define CRPT_ECC_Y2_11_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_11_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_11: POINTY2 Mask        */

#define CRPT_ECC_Y2_12_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_12: POINTY2 Position    */
#define CRPT_ECC_Y2_12_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_12_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_12: POINTY2 Mask        */

#define CRPT_ECC_Y2_13_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_13: POINTY2 Position    */
#define CRPT_ECC_Y2_13_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_13_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_13: POINTY2 Mask        */

#define CRPT_ECC_Y2_14_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_14: POINTY2 Position    */
#define CRPT_ECC_Y2_14_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_14_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_14: POINTY2 Mask        */

#define CRPT_ECC_Y2_15_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_15: POINTY2 Position    */
#define CRPT_ECC_Y2_15_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_15_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_15: POINTY2 Mask        */

#define CRPT_ECC_Y2_16_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_16: POINTY2 Position    */
#define CRPT_ECC_Y2_16_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_16_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_16: POINTY2 Mask        */

#define CRPT_ECC_Y2_17_POINTY2_Pos       (0)                                               /*!< CRPT_T::ECC_Y2_17: POINTY2 Position    */
#define CRPT_ECC_Y2_17_POINTY2_Msk       (0xfffffffful << CRPT_ECC_Y2_17_POINTY2_Pos)      /*!< CRPT_T::ECC_Y2_17: POINTY2 Mask        */

#define CRPT_ECC_A_00_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_00: CURVEA Position      */
#define CRPT_ECC_A_00_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_00_CURVEA_Pos)        /*!< CRPT_T::ECC_A_00: CURVEA Mask          */

#define CRPT_ECC_A_01_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_01: CURVEA Position      */
#define CRPT_ECC_A_01_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_01_CURVEA_Pos)        /*!< CRPT_T::ECC_A_01: CURVEA Mask          */

#define CRPT_ECC_A_02_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_02: CURVEA Position      */
#define CRPT_ECC_A_02_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_02_CURVEA_Pos)        /*!< CRPT_T::ECC_A_02: CURVEA Mask          */

#define CRPT_ECC_A_03_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_03: CURVEA Position      */
#define CRPT_ECC_A_03_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_03_CURVEA_Pos)        /*!< CRPT_T::ECC_A_03: CURVEA Mask          */

#define CRPT_ECC_A_04_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_04: CURVEA Position      */
#define CRPT_ECC_A_04_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_04_CURVEA_Pos)        /*!< CRPT_T::ECC_A_04: CURVEA Mask          */

#define CRPT_ECC_A_05_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_05: CURVEA Position      */
#define CRPT_ECC_A_05_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_05_CURVEA_Pos)        /*!< CRPT_T::ECC_A_05: CURVEA Mask          */

#define CRPT_ECC_A_06_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_06: CURVEA Position      */
#define CRPT_ECC_A_06_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_06_CURVEA_Pos)        /*!< CRPT_T::ECC_A_06: CURVEA Mask          */

#define CRPT_ECC_A_07_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_07: CURVEA Position      */
#define CRPT_ECC_A_07_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_07_CURVEA_Pos)        /*!< CRPT_T::ECC_A_07: CURVEA Mask          */

#define CRPT_ECC_A_08_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_08: CURVEA Position      */
#define CRPT_ECC_A_08_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_08_CURVEA_Pos)        /*!< CRPT_T::ECC_A_08: CURVEA Mask          */

#define CRPT_ECC_A_09_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_09: CURVEA Position      */
#define CRPT_ECC_A_09_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_09_CURVEA_Pos)        /*!< CRPT_T::ECC_A_09: CURVEA Mask          */

#define CRPT_ECC_A_10_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_10: CURVEA Position      */
#define CRPT_ECC_A_10_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_10_CURVEA_Pos)        /*!< CRPT_T::ECC_A_10: CURVEA Mask          */

#define CRPT_ECC_A_11_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_11: CURVEA Position      */
#define CRPT_ECC_A_11_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_11_CURVEA_Pos)        /*!< CRPT_T::ECC_A_11: CURVEA Mask          */

#define CRPT_ECC_A_12_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_12: CURVEA Position      */
#define CRPT_ECC_A_12_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_12_CURVEA_Pos)        /*!< CRPT_T::ECC_A_12: CURVEA Mask          */

#define CRPT_ECC_A_13_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_13: CURVEA Position      */
#define CRPT_ECC_A_13_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_13_CURVEA_Pos)        /*!< CRPT_T::ECC_A_13: CURVEA Mask          */

#define CRPT_ECC_A_14_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_14: CURVEA Position      */
#define CRPT_ECC_A_14_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_14_CURVEA_Pos)        /*!< CRPT_T::ECC_A_14: CURVEA Mask          */

#define CRPT_ECC_A_15_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_15: CURVEA Position      */
#define CRPT_ECC_A_15_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_15_CURVEA_Pos)        /*!< CRPT_T::ECC_A_15: CURVEA Mask          */

#define CRPT_ECC_A_16_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_16: CURVEA Position      */
#define CRPT_ECC_A_16_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_16_CURVEA_Pos)        /*!< CRPT_T::ECC_A_16: CURVEA Mask          */

#define CRPT_ECC_A_17_CURVEA_Pos         (0)                                               /*!< CRPT_T::ECC_A_17: CURVEA Position      */
#define CRPT_ECC_A_17_CURVEA_Msk         (0xfffffffful << CRPT_ECC_A_17_CURVEA_Pos)        /*!< CRPT_T::ECC_A_17: CURVEA Mask          */

#define CRPT_ECC_B_00_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_00: CURVEB Position      */
#define CRPT_ECC_B_00_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_00_CURVEB_Pos)        /*!< CRPT_T::ECC_B_00: CURVEB Mask          */

#define CRPT_ECC_B_01_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_01: CURVEB Position      */
#define CRPT_ECC_B_01_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_01_CURVEB_Pos)        /*!< CRPT_T::ECC_B_01: CURVEB Mask          */

#define CRPT_ECC_B_02_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_02: CURVEB Position      */
#define CRPT_ECC_B_02_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_02_CURVEB_Pos)        /*!< CRPT_T::ECC_B_02: CURVEB Mask          */

#define CRPT_ECC_B_03_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_03: CURVEB Position      */
#define CRPT_ECC_B_03_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_03_CURVEB_Pos)        /*!< CRPT_T::ECC_B_03: CURVEB Mask          */

#define CRPT_ECC_B_04_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_04: CURVEB Position      */
#define CRPT_ECC_B_04_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_04_CURVEB_Pos)        /*!< CRPT_T::ECC_B_04: CURVEB Mask          */

#define CRPT_ECC_B_05_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_05: CURVEB Position      */
#define CRPT_ECC_B_05_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_05_CURVEB_Pos)        /*!< CRPT_T::ECC_B_05: CURVEB Mask          */

#define CRPT_ECC_B_06_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_06: CURVEB Position      */
#define CRPT_ECC_B_06_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_06_CURVEB_Pos)        /*!< CRPT_T::ECC_B_06: CURVEB Mask          */

#define CRPT_ECC_B_07_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_07: CURVEB Position      */
#define CRPT_ECC_B_07_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_07_CURVEB_Pos)        /*!< CRPT_T::ECC_B_07: CURVEB Mask          */

#define CRPT_ECC_B_08_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_08: CURVEB Position      */
#define CRPT_ECC_B_08_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_08_CURVEB_Pos)        /*!< CRPT_T::ECC_B_08: CURVEB Mask          */

#define CRPT_ECC_B_09_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_09: CURVEB Position      */
#define CRPT_ECC_B_09_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_09_CURVEB_Pos)        /*!< CRPT_T::ECC_B_09: CURVEB Mask          */

#define CRPT_ECC_B_10_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_10: CURVEB Position      */
#define CRPT_ECC_B_10_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_10_CURVEB_Pos)        /*!< CRPT_T::ECC_B_10: CURVEB Mask          */

#define CRPT_ECC_B_11_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_11: CURVEB Position      */
#define CRPT_ECC_B_11_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_11_CURVEB_Pos)        /*!< CRPT_T::ECC_B_11: CURVEB Mask          */

#define CRPT_ECC_B_12_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_12: CURVEB Position      */
#define CRPT_ECC_B_12_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_12_CURVEB_Pos)        /*!< CRPT_T::ECC_B_12: CURVEB Mask          */

#define CRPT_ECC_B_13_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_13: CURVEB Position      */
#define CRPT_ECC_B_13_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_13_CURVEB_Pos)        /*!< CRPT_T::ECC_B_13: CURVEB Mask          */

#define CRPT_ECC_B_14_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_14: CURVEB Position      */
#define CRPT_ECC_B_14_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_14_CURVEB_Pos)        /*!< CRPT_T::ECC_B_14: CURVEB Mask          */

#define CRPT_ECC_B_15_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_15: CURVEB Position      */
#define CRPT_ECC_B_15_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_15_CURVEB_Pos)        /*!< CRPT_T::ECC_B_15: CURVEB Mask          */

#define CRPT_ECC_B_16_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_16: CURVEB Position      */
#define CRPT_ECC_B_16_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_16_CURVEB_Pos)        /*!< CRPT_T::ECC_B_16: CURVEB Mask          */

#define CRPT_ECC_B_17_CURVEB_Pos         (0)                                               /*!< CRPT_T::ECC_B_17: CURVEB Position      */
#define CRPT_ECC_B_17_CURVEB_Msk         (0xfffffffful << CRPT_ECC_B_17_CURVEB_Pos)        /*!< CRPT_T::ECC_B_17: CURVEB Mask          */

#define CRPT_ECC_N_00_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_00: CURVEN Position      */
#define CRPT_ECC_N_00_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_00_CURVEN_Pos)        /*!< CRPT_T::ECC_N_00: CURVEN Mask          */

#define CRPT_ECC_N_01_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_01: CURVEN Position      */
#define CRPT_ECC_N_01_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_01_CURVEN_Pos)        /*!< CRPT_T::ECC_N_01: CURVEN Mask          */

#define CRPT_ECC_N_02_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_02: CURVEN Position      */
#define CRPT_ECC_N_02_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_02_CURVEN_Pos)        /*!< CRPT_T::ECC_N_02: CURVEN Mask          */

#define CRPT_ECC_N_03_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_03: CURVEN Position      */
#define CRPT_ECC_N_03_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_03_CURVEN_Pos)        /*!< CRPT_T::ECC_N_03: CURVEN Mask          */

#define CRPT_ECC_N_04_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_04: CURVEN Position      */
#define CRPT_ECC_N_04_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_04_CURVEN_Pos)        /*!< CRPT_T::ECC_N_04: CURVEN Mask          */

#define CRPT_ECC_N_05_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_05: CURVEN Position      */
#define CRPT_ECC_N_05_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_05_CURVEN_Pos)        /*!< CRPT_T::ECC_N_05: CURVEN Mask          */

#define CRPT_ECC_N_06_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_06: CURVEN Position      */
#define CRPT_ECC_N_06_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_06_CURVEN_Pos)        /*!< CRPT_T::ECC_N_06: CURVEN Mask          */

#define CRPT_ECC_N_07_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_07: CURVEN Position      */
#define CRPT_ECC_N_07_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_07_CURVEN_Pos)        /*!< CRPT_T::ECC_N_07: CURVEN Mask          */

#define CRPT_ECC_N_08_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_08: CURVEN Position      */
#define CRPT_ECC_N_08_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_08_CURVEN_Pos)        /*!< CRPT_T::ECC_N_08: CURVEN Mask          */

#define CRPT_ECC_N_09_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_09: CURVEN Position      */
#define CRPT_ECC_N_09_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_09_CURVEN_Pos)        /*!< CRPT_T::ECC_N_09: CURVEN Mask          */

#define CRPT_ECC_N_10_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_10: CURVEN Position      */
#define CRPT_ECC_N_10_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_10_CURVEN_Pos)        /*!< CRPT_T::ECC_N_10: CURVEN Mask          */

#define CRPT_ECC_N_11_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_11: CURVEN Position      */
#define CRPT_ECC_N_11_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_11_CURVEN_Pos)        /*!< CRPT_T::ECC_N_11: CURVEN Mask          */

#define CRPT_ECC_N_12_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_12: CURVEN Position      */
#define CRPT_ECC_N_12_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_12_CURVEN_Pos)        /*!< CRPT_T::ECC_N_12: CURVEN Mask          */

#define CRPT_ECC_N_13_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_13: CURVEN Position      */
#define CRPT_ECC_N_13_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_13_CURVEN_Pos)        /*!< CRPT_T::ECC_N_13: CURVEN Mask          */

#define CRPT_ECC_N_14_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_14: CURVEN Position      */
#define CRPT_ECC_N_14_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_14_CURVEN_Pos)        /*!< CRPT_T::ECC_N_14: CURVEN Mask          */

#define CRPT_ECC_N_15_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_15: CURVEN Position      */
#define CRPT_ECC_N_15_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_15_CURVEN_Pos)        /*!< CRPT_T::ECC_N_15: CURVEN Mask          */

#define CRPT_ECC_N_16_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_16: CURVEN Position      */
#define CRPT_ECC_N_16_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_16_CURVEN_Pos)        /*!< CRPT_T::ECC_N_16: CURVEN Mask          */

#define CRPT_ECC_N_17_CURVEN_Pos         (0)                                               /*!< CRPT_T::ECC_N_17: CURVEN Position      */
#define CRPT_ECC_N_17_CURVEN_Msk         (0xfffffffful << CRPT_ECC_N_17_CURVEN_Pos)        /*!< CRPT_T::ECC_N_17: CURVEN Mask          */

#define CRPT_ECC_K_00_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_00: SCALARK Position     */
#define CRPT_ECC_K_00_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_00_SCALARK_Pos)       /*!< CRPT_T::ECC_K_00: SCALARK Mask         */

#define CRPT_ECC_K_01_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_01: SCALARK Position     */
#define CRPT_ECC_K_01_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_01_SCALARK_Pos)       /*!< CRPT_T::ECC_K_01: SCALARK Mask         */

#define CRPT_ECC_K_02_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_02: SCALARK Position     */
#define CRPT_ECC_K_02_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_02_SCALARK_Pos)       /*!< CRPT_T::ECC_K_02: SCALARK Mask         */

#define CRPT_ECC_K_03_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_03: SCALARK Position     */
#define CRPT_ECC_K_03_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_03_SCALARK_Pos)       /*!< CRPT_T::ECC_K_03: SCALARK Mask         */

#define CRPT_ECC_K_04_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_04: SCALARK Position     */
#define CRPT_ECC_K_04_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_04_SCALARK_Pos)       /*!< CRPT_T::ECC_K_04: SCALARK Mask         */

#define CRPT_ECC_K_05_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_05: SCALARK Position     */
#define CRPT_ECC_K_05_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_05_SCALARK_Pos)       /*!< CRPT_T::ECC_K_05: SCALARK Mask         */

#define CRPT_ECC_K_06_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_06: SCALARK Position     */
#define CRPT_ECC_K_06_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_06_SCALARK_Pos)       /*!< CRPT_T::ECC_K_06: SCALARK Mask         */

#define CRPT_ECC_K_07_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_07: SCALARK Position     */
#define CRPT_ECC_K_07_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_07_SCALARK_Pos)       /*!< CRPT_T::ECC_K_07: SCALARK Mask         */

#define CRPT_ECC_K_08_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_08: SCALARK Position     */
#define CRPT_ECC_K_08_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_08_SCALARK_Pos)       /*!< CRPT_T::ECC_K_08: SCALARK Mask         */

#define CRPT_ECC_K_09_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_09: SCALARK Position     */
#define CRPT_ECC_K_09_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_09_SCALARK_Pos)       /*!< CRPT_T::ECC_K_09: SCALARK Mask         */

#define CRPT_ECC_K_10_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_10: SCALARK Position     */
#define CRPT_ECC_K_10_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_10_SCALARK_Pos)       /*!< CRPT_T::ECC_K_10: SCALARK Mask         */

#define CRPT_ECC_K_11_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_11: SCALARK Position     */
#define CRPT_ECC_K_11_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_11_SCALARK_Pos)       /*!< CRPT_T::ECC_K_11: SCALARK Mask         */

#define CRPT_ECC_K_12_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_12: SCALARK Position     */
#define CRPT_ECC_K_12_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_12_SCALARK_Pos)       /*!< CRPT_T::ECC_K_12: SCALARK Mask         */

#define CRPT_ECC_K_13_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_13: SCALARK Position     */
#define CRPT_ECC_K_13_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_13_SCALARK_Pos)       /*!< CRPT_T::ECC_K_13: SCALARK Mask         */

#define CRPT_ECC_K_14_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_14: SCALARK Position     */
#define CRPT_ECC_K_14_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_14_SCALARK_Pos)       /*!< CRPT_T::ECC_K_14: SCALARK Mask         */

#define CRPT_ECC_K_15_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_15: SCALARK Position     */
#define CRPT_ECC_K_15_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_15_SCALARK_Pos)       /*!< CRPT_T::ECC_K_15: SCALARK Mask         */

#define CRPT_ECC_K_16_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_16: SCALARK Position     */
#define CRPT_ECC_K_16_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_16_SCALARK_Pos)       /*!< CRPT_T::ECC_K_16: SCALARK Mask         */

#define CRPT_ECC_K_17_SCALARK_Pos        (0)                                               /*!< CRPT_T::ECC_K_17: SCALARK Position     */
#define CRPT_ECC_K_17_SCALARK_Msk        (0xfffffffful << CRPT_ECC_K_17_SCALARK_Pos)       /*!< CRPT_T::ECC_K_17: SCALARK Mask         */

#define CRPT_ECC_DADDR_DADDR_Pos         (0)                                               /*!< CRPT_T::ECC_DADDR: DADDR Position      */
#define CRPT_ECC_DADDR_DADDR_Msk         (0xfffffffful << CRPT_ECC_DADDR_DADDR_Pos)        /*!< CRPT_T::ECC_DADDR: DADDR Mask          */

#define CRPT_ECC_STARTREG_STARTREG_Pos   (0)                                               /*!< CRPT_T::ECC_STARTREG: STARTREG Position*/
#define CRPT_ECC_STARTREG_STARTREG_Msk   (0xfffffffful << CRPT_ECC_STARTREG_STARTREG_Pos)  /*!< CRPT_T::ECC_STARTREG: STARTREG Mask    */

#define CRPT_ECC_WORDCNT_WORDCNT_Pos     (0)                                               /*!< CRPT_T::ECC_WORDCNT: WORDCNT Position  */
#define CRPT_ECC_WORDCNT_WORDCNT_Msk     (0xfffffffful << CRPT_ECC_WORDCNT_WORDCNT_Pos)    /*!< CRPT_T::ECC_WORDCNT: WORDCNT Mask      */

#define CRPT_RSA_CTL_START_Pos           (0)                                               /*!< CRPT_T::RSA_CTL: START Position        */
#define CRPT_RSA_CTL_START_Msk           (0x1ul << CRPT_RSA_CTL_START_Pos)                 /*!< CRPT_T::RSA_CTL: START Mask            */

#define CRPT_RSA_CTL_STOP_Pos            (1)                                               /*!< CRPT_T::RSA_CTL: STOP Position         */
#define CRPT_RSA_CTL_STOP_Msk            (0x1ul << CRPT_RSA_CTL_STOP_Pos)                  /*!< CRPT_T::RSA_CTL: STOP Mask             */

#define CRPT_RSA_CTL_CRT_Pos             (2)                                               /*!< CRPT_T::RSA_CTL: CRT Position          */
#define CRPT_RSA_CTL_CRT_Msk             (0x1ul << CRPT_RSA_CTL_CRT_Pos)                   /*!< CRPT_T::RSA_CTL: CRT Mask              */

#define CRPT_RSA_CTL_CRTBYP_Pos          (3)                                               /*!< CRPT_T::RSA_CTL: CRTBYP Position       */
#define CRPT_RSA_CTL_CRTBYP_Msk          (0x1ul << CRPT_RSA_CTL_CRTBYP_Pos)                /*!< CRPT_T::RSA_CTL: CRTBYP Mask           */

#define CRPT_RSA_CTL_KEYLENG_Pos         (4)                                               /*!< CRPT_T::RSA_CTL: KEYLENG Position      */
#define CRPT_RSA_CTL_KEYLENG_Msk         (0x3ul << CRPT_RSA_CTL_KEYLENG_Pos)               /*!< CRPT_T::RSA_CTL: KEYLENG Mask          */

#define CRPT_RSA_CTL_SCAP_Pos            (8)                                               /*!< CRPT_T::RSA_CTL: SCAP Position         */
#define CRPT_RSA_CTL_SCAP_Msk            (0x1ul << CRPT_RSA_CTL_SCAP_Pos)                  /*!< CRPT_T::RSA_CTL: SCAP Mask             */

#define CRPT_RSA_STS_BUSY_Pos            (0)                                               /*!< CRPT_T::RSA_STS: BUSY Position         */
#define CRPT_RSA_STS_BUSY_Msk            (0x1ul << CRPT_RSA_STS_BUSY_Pos)                  /*!< CRPT_T::RSA_STS: BUSY Mask             */

#define CRPT_RSA_STS_DMABUSY_Pos         (1)                                               /*!< CRPT_T::RSA_STS: DMABUSY Position      */
#define CRPT_RSA_STS_DMABUSY_Msk         (0x1ul << CRPT_RSA_STS_DMABUSY_Pos)               /*!< CRPT_T::RSA_STS: DMABUSY Mask          */

#define CRPT_RSA_STS_BUSERR_Pos          (16)                                              /*!< CRPT_T::RSA_STS: BUSERR Position       */
#define CRPT_RSA_STS_BUSERR_Msk          (0x1ul << CRPT_RSA_STS_BUSERR_Pos)                /*!< CRPT_T::RSA_STS: BUSERR Mask           */

#define CRPT_RSA_STS_CTLERR_Pos          (17)                                              /*!< CRPT_T::RSA_STS: CTLERR Position       */
#define CRPT_RSA_STS_CTLERR_Msk          (0x1ul << CRPT_RSA_STS_CTLERR_Pos)                /*!< CRPT_T::RSA_STS: CTLERR Mask           */

#define CRPT_RSA_STS_KSERR_Pos           (18)                                              /*!< CRPT_T::RSA_STS: KSERR Position        */
#define CRPT_RSA_STS_KSERR_Msk           (0x1ul << CRPT_RSA_STS_KSERR_Pos)                 /*!< CRPT_T::RSA_STS: KSERR Mask            */

#define CRPT_RSA_SADDR0_SADDR0_Pos       (0)                                               /*!< CRPT_T::RSA_SADDR0: SADDR0 Position    */
#define CRPT_RSA_SADDR0_SADDR0_Msk       (0xfffffffful << CRPT_RSA_SADDR0_SADDR0_Pos)      /*!< CRPT_T::RSA_SADDR0: SADDR0 Mask        */

#define CRPT_RSA_SADDR1_SADDR1_Pos       (0)                                               /*!< CRPT_T::RSA_SADDR1: SADDR1 Position    */
#define CRPT_RSA_SADDR1_SADDR1_Msk       (0xfffffffful << CRPT_RSA_SADDR1_SADDR1_Pos)      /*!< CRPT_T::RSA_SADDR1: SADDR1 Mask        */

#define CRPT_RSA_SADDR2_SADDR2_Pos       (0)                                               /*!< CRPT_T::RSA_SADDR2: SADDR2 Position    */
#define CRPT_RSA_SADDR2_SADDR2_Msk       (0xfffffffful << CRPT_RSA_SADDR2_SADDR2_Pos)      /*!< CRPT_T::RSA_SADDR2: SADDR2 Mask        */

#define CRPT_RSA_SADDR3_SADDR3_Pos       (0)                                               /*!< CRPT_T::RSA_SADDR3: SADDR3 Position    */
#define CRPT_RSA_SADDR3_SADDR3_Msk       (0xfffffffful << CRPT_RSA_SADDR3_SADDR3_Pos)      /*!< CRPT_T::RSA_SADDR3: SADDR3 Mask        */

#define CRPT_RSA_SADDR4_SADDR4_Pos       (0)                                               /*!< CRPT_T::RSA_SADDR4: SADDR4 Position    */
#define CRPT_RSA_SADDR4_SADDR4_Msk       (0xfffffffful << CRPT_RSA_SADDR4_SADDR4_Pos)      /*!< CRPT_T::RSA_SADDR4: SADDR4 Mask        */

#define CRPT_RSA_DADDR_DADDR_Pos         (0)                                               /*!< CRPT_T::RSA_DADDR: DADDR Position      */
#define CRPT_RSA_DADDR_DADDR_Msk         (0xfffffffful << CRPT_RSA_DADDR_DADDR_Pos)        /*!< CRPT_T::RSA_DADDR: DADDR Mask          */

#define CRPT_RSA_MADDR0_MADDR0_Pos       (0)                                               /*!< CRPT_T::RSA_MADDR0: MADDR0 Position    */
#define CRPT_RSA_MADDR0_MADDR0_Msk       (0xfffffffful << CRPT_RSA_MADDR0_MADDR0_Pos)      /*!< CRPT_T::RSA_MADDR0: MADDR0 Mask        */

#define CRPT_RSA_MADDR1_MADDR1_Pos       (0)                                               /*!< CRPT_T::RSA_MADDR1: MADDR1 Position    */
#define CRPT_RSA_MADDR1_MADDR1_Msk       (0xfffffffful << CRPT_RSA_MADDR1_MADDR1_Pos)      /*!< CRPT_T::RSA_MADDR1: MADDR1 Mask        */

#define CRPT_RSA_MADDR2_MADDR2_Pos       (0)                                               /*!< CRPT_T::RSA_MADDR2: MADDR2 Position    */
#define CRPT_RSA_MADDR2_MADDR2_Msk       (0xfffffffful << CRPT_RSA_MADDR2_MADDR2_Pos)      /*!< CRPT_T::RSA_MADDR2: MADDR2 Mask        */

#define CRPT_RSA_MADDR3_MADDR3_Pos       (0)                                               /*!< CRPT_T::RSA_MADDR3: MADDR3 Position    */
#define CRPT_RSA_MADDR3_MADDR3_Msk       (0xfffffffful << CRPT_RSA_MADDR3_MADDR3_Pos)      /*!< CRPT_T::RSA_MADDR3: MADDR3 Mask        */

#define CRPT_RSA_MADDR4_MADDR4_Pos       (0)                                               /*!< CRPT_T::RSA_MADDR4: MADDR4 Position    */
#define CRPT_RSA_MADDR4_MADDR4_Msk       (0xfffffffful << CRPT_RSA_MADDR4_MADDR4_Pos)      /*!< CRPT_T::RSA_MADDR4: MADDR4 Mask        */

#define CRPT_RSA_MADDR5_MADDR5_Pos       (0)                                               /*!< CRPT_T::RSA_MADDR5: MADDR5 Position    */
#define CRPT_RSA_MADDR5_MADDR5_Msk       (0xfffffffful << CRPT_RSA_MADDR5_MADDR5_Pos)      /*!< CRPT_T::RSA_MADDR5: MADDR5 Mask        */

#define CRPT_RSA_MADDR6_MADDR6_Pos       (0)                                               /*!< CRPT_T::RSA_MADDR6: MADDR6 Position    */
#define CRPT_RSA_MADDR6_MADDR6_Msk       (0xfffffffful << CRPT_RSA_MADDR6_MADDR6_Pos)      /*!< CRPT_T::RSA_MADDR6: MADDR6 Mask        */

#define CRPT_PRNG_KSCTL_NUM_Pos          (0)                                               /*!< CRPT_T::PRNG_KSCTL: NUM Position       */
#define CRPT_PRNG_KSCTL_NUM_Msk          (0x1ful << CRPT_PRNG_KSCTL_NUM_Pos)               /*!< CRPT_T::PRNG_KSCTL: NUM Mask           */

#define CRPT_PRNG_KSCTL_TRUST_Pos        (16)                                              /*!< CRPT_T::PRNG_KSCTL: TRUST Position     */
#define CRPT_PRNG_KSCTL_TRUST_Msk        (0x1ul << CRPT_PRNG_KSCTL_TRUST_Pos)              /*!< CRPT_T::PRNG_KSCTL: TRUST Mask         */

#define CRPT_PRNG_KSCTL_ECDH_Pos         (19)                                              /*!< CRPT_T::PRNG_KSCTL: ECDH Position      */
#define CRPT_PRNG_KSCTL_ECDH_Msk         (0x1ul << CRPT_PRNG_KSCTL_ECDH_Pos)               /*!< CRPT_T::PRNG_KSCTL: ECDH Mask          */

#define CRPT_PRNG_KSCTL_ECDSA_Pos        (20)                                              /*!< CRPT_T::PRNG_KSCTL: ECDSA Position     */
#define CRPT_PRNG_KSCTL_ECDSA_Msk        (0x1ul << CRPT_PRNG_KSCTL_ECDSA_Pos)              /*!< CRPT_T::PRNG_KSCTL: ECDSA Mask         */

#define CRPT_PRNG_KSCTL_WDST_Pos         (21)                                              /*!< CRPT_T::PRNG_KSCTL: WDST Position      */
#define CRPT_PRNG_KSCTL_WDST_Msk         (0x1ul << CRPT_PRNG_KSCTL_WDST_Pos)               /*!< CRPT_T::PRNG_KSCTL: WDST Mask          */

#define CRPT_PRNG_KSCTL_WSDST_Pos        (22)                                              /*!< CRPT_T::PRNG_KSCTL: WSDST Position     */
#define CRPT_PRNG_KSCTL_WSDST_Msk        (0x3ul << CRPT_PRNG_KSCTL_WSDST_Pos)              /*!< CRPT_T::PRNG_KSCTL: WSDST Mask         */

#define CRPT_PRNG_KSCTL_OWNER_Pos        (24)                                              /*!< CRPT_T::PRNG_KSCTL: OWNER Position     */
#define CRPT_PRNG_KSCTL_OWNER_Msk        (0x7ul << CRPT_PRNG_KSCTL_OWNER_Pos)              /*!< CRPT_T::PRNG_KSCTL: OWNER Mask         */

#define CRPT_PRNG_KSSTS_NUM_Pos          (0)                                               /*!< CRPT_T::PRNG_KSSTS: NUM Position       */
#define CRPT_PRNG_KSSTS_NUM_Msk          (0x1ful << CRPT_PRNG_KSSTS_NUM_Pos)               /*!< CRPT_T::PRNG_KSSTS: NUM Mask           */

#define CRPT_PRNG_KSSTS_KCTLERR_Pos      (16)                                              /*!< CRPT_T::PRNG_KSSTS: KCTLERR Position   */
#define CRPT_PRNG_KSSTS_KCTLERR_Msk      (0x1ul << CRPT_PRNG_KSSTS_KCTLERR_Pos)            /*!< CRPT_T::PRNG_KSSTS: KCTLERR Mask       */

#define CRPT_AES_KSCTL_NUM_Pos           (0)                                               /*!< CRPT_T::AES_KSCTL: NUM Position        */
#define CRPT_AES_KSCTL_NUM_Msk           (0x1ful << CRPT_AES_KSCTL_NUM_Pos)                /*!< CRPT_T::AES_KSCTL: NUM Mask            */

#define CRPT_AES_KSCTL_RSRC_Pos          (5)                                               /*!< CRPT_T::AES_KSCTL: RSRC Position       */
#define CRPT_AES_KSCTL_RSRC_Msk          (0x1ul << CRPT_AES_KSCTL_RSRC_Pos)                /*!< CRPT_T::AES_KSCTL: RSRC Mask           */

#define CRPT_AES_KSCTL_RSSRC_Pos         (6)                                               /*!< CRPT_T::AES_KSCTL: RSSRC Position      */
#define CRPT_AES_KSCTL_RSSRC_Msk         (0x3ul << CRPT_AES_KSCTL_RSSRC_Pos)               /*!< CRPT_T::AES_KSCTL: RSSRC Mask          */

#define CRPT_HMAC_KSCTL_NUM_Pos          (0)                                               /*!< CRPT_T::HMAC_KSCTL: NUM Position       */
#define CRPT_HMAC_KSCTL_NUM_Msk          (0x1ful << CRPT_HMAC_KSCTL_NUM_Pos)               /*!< CRPT_T::HMAC_KSCTL: NUM Mask           */

#define CRPT_HMAC_KSCTL_RSRC_Pos         (5)                                               /*!< CRPT_T::HMAC_KSCTL: RSRC Position      */
#define CRPT_HMAC_KSCTL_RSRC_Msk         (0x1ul << CRPT_HMAC_KSCTL_RSRC_Pos)               /*!< CRPT_T::HMAC_KSCTL: RSRC Mask          */

#define CRPT_HMAC_KSCTL_RSSRC_Pos        (6)                                               /*!< CRPT_T::HMAC_KSCTL: RSSRC Position     */
#define CRPT_HMAC_KSCTL_RSSRC_Msk        (0x3ul << CRPT_HMAC_KSCTL_RSSRC_Pos)              /*!< CRPT_T::HMAC_KSCTL: RSSRC Mask         */

#define CRPT_ECC_KSCTL_NUMK_Pos          (0)                                               /*!< CRPT_T::ECC_KSCTL: NUMK Position       */
#define CRPT_ECC_KSCTL_NUMK_Msk          (0x1ful << CRPT_ECC_KSCTL_NUMK_Pos)               /*!< CRPT_T::ECC_KSCTL: NUMK Mask           */

#define CRPT_ECC_KSCTL_RSRCK_Pos         (5)                                               /*!< CRPT_T::ECC_KSCTL: RSRCK Position      */
#define CRPT_ECC_KSCTL_RSRCK_Msk         (0x1ul << CRPT_ECC_KSCTL_RSRCK_Pos)               /*!< CRPT_T::ECC_KSCTL: RSRCK Mask          */

#define CRPT_ECC_KSCTL_RSSRCK_Pos        (6)                                               /*!< CRPT_T::ECC_KSCTL: RSSRCK Position     */
#define CRPT_ECC_KSCTL_RSSRCK_Msk        (0x3ul << CRPT_ECC_KSCTL_RSSRCK_Pos)              /*!< CRPT_T::ECC_KSCTL: RSSRCK Mask         */

#define CRPT_ECC_KSCTL_ECDH_Pos          (14)                                              /*!< CRPT_T::ECC_KSCTL: ECDH Position       */
#define CRPT_ECC_KSCTL_ECDH_Msk          (0x1ul << CRPT_ECC_KSCTL_ECDH_Pos)                /*!< CRPT_T::ECC_KSCTL: ECDH Mask           */

#define CRPT_ECC_KSCTL_TRUST_Pos         (16)                                              /*!< CRPT_T::ECC_KSCTL: TRUST Position      */
#define CRPT_ECC_KSCTL_TRUST_Msk         (0x1ul << CRPT_ECC_KSCTL_TRUST_Pos)               /*!< CRPT_T::ECC_KSCTL: TRUST Mask          */

#define CRPT_ECC_KSCTL_XY_Pos            (20)                                              /*!< CRPT_T::ECC_KSCTL: XY Position         */
#define CRPT_ECC_KSCTL_XY_Msk            (0x1ul << CRPT_ECC_KSCTL_XY_Pos)                  /*!< CRPT_T::ECC_KSCTL: XY Mask             */

#define CRPT_ECC_KSCTL_WDST_Pos          (21)                                              /*!< CRPT_T::ECC_KSCTL: WDST Position       */
#define CRPT_ECC_KSCTL_WDST_Msk          (0x1ul << CRPT_ECC_KSCTL_WDST_Pos)                /*!< CRPT_T::ECC_KSCTL: WDST Mask           */

#define CRPT_ECC_KSCTL_WSDST_Pos         (22)                                              /*!< CRPT_T::ECC_KSCTL: WSDST Position      */
#define CRPT_ECC_KSCTL_WSDST_Msk         (0x3ul << CRPT_ECC_KSCTL_WSDST_Pos)               /*!< CRPT_T::ECC_KSCTL: WSDST Mask          */

#define CRPT_ECC_KSCTL_OWNER_Pos         (24)                                              /*!< CRPT_T::ECC_KSCTL: OWNER Position      */
#define CRPT_ECC_KSCTL_OWNER_Msk         (0x7ul << CRPT_ECC_KSCTL_OWNER_Pos)               /*!< CRPT_T::ECC_KSCTL: OWNER Mask          */

#define CRPT_ECC_KSSTS_NUM_Pos           (0)                                               /*!< CRPT_T::ECC_KSSTS: NUM Position        */
#define CRPT_ECC_KSSTS_NUM_Msk           (0x1ful << CRPT_ECC_KSSTS_NUM_Pos)                /*!< CRPT_T::ECC_KSSTS: NUM Mask            */

#define CRPT_ECC_KSXY_NUMX_Pos           (0)                                               /*!< CRPT_T::ECC_KSXY: NUMX Position        */
#define CRPT_ECC_KSXY_NUMX_Msk           (0x1ful << CRPT_ECC_KSXY_NUMX_Pos)                /*!< CRPT_T::ECC_KSXY: NUMX Mask            */

#define CRPT_ECC_KSXY_RSRCXY_Pos         (5)                                               /*!< CRPT_T::ECC_KSXY: RSRCXY Position      */
#define CRPT_ECC_KSXY_RSRCXY_Msk         (0x1ul << CRPT_ECC_KSXY_RSRCXY_Pos)               /*!< CRPT_T::ECC_KSXY: RSRCXY Mask          */

#define CRPT_ECC_KSXY_RSSRCX_Pos         (6)                                               /*!< CRPT_T::ECC_KSXY: RSSRCX Position      */
#define CRPT_ECC_KSXY_RSSRCX_Msk         (0x3ul << CRPT_ECC_KSXY_RSSRCX_Pos)               /*!< CRPT_T::ECC_KSXY: RSSRCX Mask          */

#define CRPT_ECC_KSXY_NUMY_Pos           (8)                                               /*!< CRPT_T::ECC_KSXY: NUMY Position        */
#define CRPT_ECC_KSXY_NUMY_Msk           (0x1ful << CRPT_ECC_KSXY_NUMY_Pos)                /*!< CRPT_T::ECC_KSXY: NUMY Mask            */

#define CRPT_ECC_KSXY_RSSRCY_Pos         (14)                                              /*!< CRPT_T::ECC_KSXY: RSSRCY Position      */
#define CRPT_ECC_KSXY_RSSRCY_Msk         (0x3ul << CRPT_ECC_KSXY_RSSRCY_Pos)               /*!< CRPT_T::ECC_KSXY: RSSRCY Mask          */

#define CRPT_RSA_KSCTL_NUM_Pos           (0)                                               /*!< CRPT_T::RSA_KSCTL: NUM Position        */
#define CRPT_RSA_KSCTL_NUM_Msk           (0x1ful << CRPT_RSA_KSCTL_NUM_Pos)                /*!< CRPT_T::RSA_KSCTL: NUM Mask            */

#define CRPT_RSA_KSCTL_RSRC_Pos          (5)                                               /*!< CRPT_T::RSA_KSCTL: RSRC Position       */
#define CRPT_RSA_KSCTL_RSRC_Msk          (0x1ul << CRPT_RSA_KSCTL_RSRC_Pos)                /*!< CRPT_T::RSA_KSCTL: RSRC Mask           */

#define CRPT_RSA_KSCTL_RSSRC_Pos         (6)                                               /*!< CRPT_T::RSA_KSCTL: RSSRC Position      */
#define CRPT_RSA_KSCTL_RSSRC_Msk         (0x3ul << CRPT_RSA_KSCTL_RSSRC_Pos)               /*!< CRPT_T::RSA_KSCTL: RSSRC Mask          */

#define CRPT_RSA_KSCTL_BKNUM_Pos         (8)                                               /*!< CRPT_T::RSA_KSCTL: BKNUM Position      */
#define CRPT_RSA_KSCTL_BKNUM_Msk         (0x1ful << CRPT_RSA_KSCTL_BKNUM_Pos)              /*!< CRPT_T::RSA_KSCTL: BKNUM Mask          */

#define CRPT_RSA_KSSTS0_NUM0_Pos         (0)                                               /*!< CRPT_T::RSA_KSSTS0: NUM0 Position      */
#define CRPT_RSA_KSSTS0_NUM0_Msk         (0x1ful << CRPT_RSA_KSSTS0_NUM0_Pos)              /*!< CRPT_T::RSA_KSSTS0: NUM0 Mask          */

#define CRPT_RSA_KSSTS0_NUM1_Pos         (8)                                               /*!< CRPT_T::RSA_KSSTS0: NUM1 Position      */
#define CRPT_RSA_KSSTS0_NUM1_Msk         (0x1ful << CRPT_RSA_KSSTS0_NUM1_Pos)              /*!< CRPT_T::RSA_KSSTS0: NUM1 Mask          */

#define CRPT_RSA_KSSTS0_NUM2_Pos         (16)                                              /*!< CRPT_T::RSA_KSSTS0: NUM2 Position      */
#define CRPT_RSA_KSSTS0_NUM2_Msk         (0x1ful << CRPT_RSA_KSSTS0_NUM2_Pos)              /*!< CRPT_T::RSA_KSSTS0: NUM2 Mask          */

#define CRPT_RSA_KSSTS0_NUM3_Pos         (24)                                              /*!< CRPT_T::RSA_KSSTS0: NUM3 Position      */
#define CRPT_RSA_KSSTS0_NUM3_Msk         (0x1ful << CRPT_RSA_KSSTS0_NUM3_Pos)              /*!< CRPT_T::RSA_KSSTS0: NUM3 Mask          */

#define CRPT_RSA_KSSTS1_NUM4_Pos         (0)                                               /*!< CRPT_T::RSA_KSSTS1: NUM4 Position      */
#define CRPT_RSA_KSSTS1_NUM4_Msk         (0x1ful << CRPT_RSA_KSSTS1_NUM4_Pos)              /*!< CRPT_T::RSA_KSSTS1: NUM4 Mask          */

#define CRPT_RSA_KSSTS1_NUM5_Pos         (8)                                               /*!< CRPT_T::RSA_KSSTS1: NUM5 Position      */
#define CRPT_RSA_KSSTS1_NUM5_Msk         (0x1ful << CRPT_RSA_KSSTS1_NUM5_Pos)              /*!< CRPT_T::RSA_KSSTS1: NUM5 Mask          */

#define CRPT_RSA_KSSTS1_NUM6_Pos         (16)                                              /*!< CRPT_T::RSA_KSSTS1: NUM6 Position      */
#define CRPT_RSA_KSSTS1_NUM6_Msk         (0x1ful << CRPT_RSA_KSSTS1_NUM6_Pos)              /*!< CRPT_T::RSA_KSSTS1: NUM6 Mask          */

#define CRPT_RSA_KSSTS1_NUM7_Pos         (24)                                              /*!< CRPT_T::RSA_KSSTS1: NUM7 Position      */
#define CRPT_RSA_KSSTS1_NUM7_Msk         (0x1ful << CRPT_RSA_KSSTS1_NUM7_Pos)              /*!< CRPT_T::RSA_KSSTS1: NUM7 Mask          */

#define CRPT_VERSION_MINOR_Pos           (0)                                               /*!< CRPT_T::VERSION: MINOR Position        */
#define CRPT_VERSION_MINOR_Msk           (0xfffful << CRPT_VERSION_MINOR_Pos)              /*!< CRPT_T::VERSION: MINOR Mask            */

#define CRPT_VERSION_SUB_Pos             (16)                                              /*!< CRPT_T::VERSION: SUB Position          */
#define CRPT_VERSION_SUB_Msk             (0xfful << CRPT_VERSION_SUB_Pos)                  /*!< CRPT_T::VERSION: SUB Mask              */

#define CRPT_VERSION_MAJOR_Pos           (24)                                              /*!< CRPT_T::VERSION: MAJOR Position        */
#define CRPT_VERSION_MAJOR_Msk           (0xfful << CRPT_VERSION_MAJOR_Pos)                /*!< CRPT_T::VERSION: MAJOR Mask            */

/**@}*/ /* CRPT_CONST */
/**@}*/ /* end of CRPT register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __CRYPTO_REG_H__ */
