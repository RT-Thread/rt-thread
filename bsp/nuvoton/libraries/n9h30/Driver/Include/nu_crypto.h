/**************************************************************************//**
 * @file     crypto.h
 * @version  V1.10
 * $Revision: 2 $
 * $Date: 15/05/06 3:55p $
 * @brief    Cryptographic Accelerator driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_CRYPTO_H__
#define __NU_CRYPTO_H__

#include "N9H30.h"
#include "nu_sys.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_CRYPTO_Driver CRYPTO Driver
  @{
*/

/// @cond HIDDEN_SYMBOLS

typedef struct
{
    __IO uint32_t INTEN;           /*!< Offset: 0x000:  Crypto Interrupt Enable Control Register      */
    __IO uint32_t INTSTS;          /*!< Offset: 0x004:  Crypto Interrupt Flag                         */
    __IO uint32_t PRNG_CTL;        /*!< Offset: 0x008:  PRNG Control Flag                             */
    __IO uint32_t PRNG_SEED;       /*!< Offset: 0x00C:  PRNG Control Flag                             */
    __I  uint32_t PRNG_KEY[8];     /*!< Offset: 0x010:  PRNG Generated Key0 - Key7                    */
    uint32_t RESERVE0[8];
    __I  uint32_t AES_FDBCK0;      /*!< Offset: 0x050:  AES Engine Output Feedback Data after Cryptographic Operation */
    __I  uint32_t AES_FDBCK1;      /*!< Offset: 0x054:  AES Engine Output Feedback Data after Cryptographic Operation */
    __I  uint32_t AES_FDBCK2;      /*!< Offset: 0x058:  AES Engine Output Feedback Data after Cryptographic Operation */
    __I  uint32_t AES_FDBCK3;      /*!< Offset: 0x05C:  AES Engine Output Feedback Data after Cryptographic Operation */
    __I  uint32_t TDES_FDBCKH;     /*!< Offset: 0x060:  TDES/DES Engine Output Feedback High Word Data after Cryptographic Operation */
    __I  uint32_t TDES_FDBCKL;     /*!< Offset: 0x064:  TDES/DES Engine Output Feedback Low Word Data after Cryptographic Operation  */
    uint32_t RESERVE1[38];
    __IO uint32_t AES_CTL;         /*!< Offset: 0x100:  AES Control Register                          */
    __IO uint32_t AES_STS;         /*!< Offset: 0x104:  AES Engine Flag                               */
    __IO uint32_t AES_DATIN;       /*!< Offset: 0x108:  AES Engine Data Input Port Register           */
    __I  uint32_t AES_DATOUT;      /*!< Offset: 0x10C:  AES Engine Data Output Port Register          */
    __IO uint32_t AES0_KEY0;       /*!< Offset: 0x110:  AES Key Word 0 Register for Channel 0         */
    __IO uint32_t AES0_KEY1;       /*!< Offset: 0x114:  AES Key Word 1 Register for Channel 0         */
    __IO uint32_t AES0_KEY2;       /*!< Offset: 0x118:  AES Key Word 2 Register for Channel 0         */
    __IO uint32_t AES0_KEY3;       /*!< Offset: 0x11C:  AES Key Word 3 Register for Channel 0         */
    __IO uint32_t AES0_KEY4;       /*!< Offset: 0x120:  AES Key Word 4 Register for Channel 0         */
    __IO uint32_t AES0_KEY5;       /*!< Offset: 0x124:  AES Key Word 5 Register for Channel 0         */
    __IO uint32_t AES0_KEY6;       /*!< Offset: 0x128:  AES Key Word 6 Register for Channel 0         */
    __IO uint32_t AES0_KEY7;       /*!< Offset: 0x12C:  AES Key Word 7 Register for Channel 0         */
    __IO uint32_t AES0_IV0;        /*!< Offset: 0x130:  AES Initial Vector Word 0 Register for Channel 0   */
    __IO uint32_t AES0_IV1;        /*!< Offset: 0x134:  AES Initial Vector Word 1 Register for Channel 0   */
    __IO uint32_t AES0_IV2;        /*!< Offset: 0x138:  AES Initial Vector Word 2 Register for Channel 0   */
    __IO uint32_t AES0_IV3;        /*!< Offset: 0x13C:  AES Initial Vector Word 3 Register for Channel 0   */
    __IO uint32_t AES0_SADDR;      /*!< Offset: 0x140:  AES DMA Source Address Register for Channel 0      */
    __IO uint32_t AES0_DADDR;      /*!< Offset: 0x144:  AES DMA Destination Address Register for Channel 0 */
    __IO uint32_t AES0_CNT;        /*!< Offset: 0x148:  AES Byte Count Register for Channel 0              */
    __IO uint32_t AES1_KEY0;       /*!< Offset: 0x14C:  AES Key Word 0 Register for Channel 1         */
    __IO uint32_t AES1_KEY1;       /*!< Offset: 0x150:  AES Key Word 1 Register for Channel 1         */
    __IO uint32_t AES1_KEY2;       /*!< Offset: 0x154:  AES Key Word 2 Register for Channel 1         */
    __IO uint32_t AES1_KEY3;       /*!< Offset: 0x158:  AES Key Word 3 Register for Channel 1         */
    __IO uint32_t AES1_KEY4;       /*!< Offset: 0x15C:  AES Key Word 4 Register for Channel 1         */
    __IO uint32_t AES1_KEY5;       /*!< Offset: 0x160:  AES Key Word 5 Register for Channel 1         */
    __IO uint32_t AES1_KEY6;       /*!< Offset: 0x164:  AES Key Word 6 Register for Channel 1         */
    __IO uint32_t AES1_KEY7;       /*!< Offset: 0x168:  AES Key Word 7 Register for Channel 1         */
    __IO uint32_t AES1_IV0;        /*!< Offset: 0x16C:  AES Initial Vector Word 0 Register for Channel 1   */
    __IO uint32_t AES1_IV1;        /*!< Offset: 0x170:  AES Initial Vector Word 1 Register for Channel 1   */
    __IO uint32_t AES1_IV2;        /*!< Offset: 0x174:  AES Initial Vector Word 2 Register for Channel 1   */
    __IO uint32_t AES1_IV3;        /*!< Offset: 0x178:  AES Initial Vector Word 3 Register for Channel 1   */
    __IO uint32_t AES1_SADDR;      /*!< Offset: 0x17C:  AES DMA Source Address Register for Channel 1      */
    __IO uint32_t AES1_DADDR;      /*!< Offset: 0x180:  AES DMA Destination Address Register for Channel 1 */
    __IO uint32_t AES1_CNT;        /*!< Offset: 0x184:  AES Byte Count Register for Channel 1              */
    __IO uint32_t AES2_KEY0;       /*!< Offset: 0x188:  AES Key Word 0 Register for Channel 2         */
    __IO uint32_t AES2_KEY1;       /*!< Offset: 0x18C:  AES Key Word 1 Register for Channel 2         */
    __IO uint32_t AES2_KEY2;       /*!< Offset: 0x190:  AES Key Word 2 Register for Channel 2         */
    __IO uint32_t AES2_KEY3;       /*!< Offset: 0x194:  AES Key Word 3 Register for Channel 2         */
    __IO uint32_t AES2_KEY4;       /*!< Offset: 0x198:  AES Key Word 4 Register for Channel 2         */
    __IO uint32_t AES2_KEY5;       /*!< Offset: 0x19C:  AES Key Word 5 Register for Channel 2         */
    __IO uint32_t AES2_KEY6;       /*!< Offset: 0x1A0:  AES Key Word 6 Register for Channel 2         */
    __IO uint32_t AES2_KEY7;       /*!< Offset: 0x1A4:  AES Key Word 7 Register for Channel 2         */
    __IO uint32_t AES2_IV0;        /*!< Offset: 0x1A8:  AES Initial Vector Word 0 Register for Channel 2   */
    __IO uint32_t AES2_IV1;        /*!< Offset: 0x1AC:  AES Initial Vector Word 1 Register for Channel 2   */
    __IO uint32_t AES2_IV2;        /*!< Offset: 0x1B0:  AES Initial Vector Word 2 Register for Channel 2   */
    __IO uint32_t AES2_IV3;        /*!< Offset: 0x1B4:  AES Initial Vector Word 3 Register for Channel 2   */
    __IO uint32_t AES2_SADDR;      /*!< Offset: 0x1B8:  AES DMA Source Address Register for Channel 2      */
    __IO uint32_t AES2_DADDR;      /*!< Offset: 0x1BC:  AES DMA Destination Address Register for Channel 2 */
    __IO uint32_t AES2_CNT;        /*!< Offset: 0x1C0:  AES Byte Count Register for Channel 2              */
    __IO uint32_t AES3_KEY0;       /*!< Offset: 0x1C4:  AES Key Word 0 Register for Channel 3         */
    __IO uint32_t AES3_KEY1;       /*!< Offset: 0x1C8:  AES Key Word 1 Register for Channel 3         */
    __IO uint32_t AES3_KEY2;       /*!< Offset: 0x1CC:  AES Key Word 2 Register for Channel 3         */
    __IO uint32_t AES3_KEY3;       /*!< Offset: 0x1D0:  AES Key Word 3 Register for Channel 3         */
    __IO uint32_t AES3_KEY4;       /*!< Offset: 0x1D4:  AES Key Word 4 Register for Channel 3         */
    __IO uint32_t AES3_KEY5;       /*!< Offset: 0x1D8:  AES Key Word 5 Register for Channel 3         */
    __IO uint32_t AES3_KEY6;       /*!< Offset: 0x1DC:  AES Key Word 6 Register for Channel 3         */
    __IO uint32_t AES3_KEY7;       /*!< Offset: 0x1E0:  AES Key Word 7 Register for Channel 3         */
    __IO uint32_t AES3_IV0;        /*!< Offset: 0x1E4:  AES Initial Vector Word 0 Register for Channel 3   */
    __IO uint32_t AES3_IV1;        /*!< Offset: 0x1E8:  AES Initial Vector Word 1 Register for Channel 3   */
    __IO uint32_t AES3_IV2;        /*!< Offset: 0x1EC:  AES Initial Vector Word 2 Register for Channel 3   */
    __IO uint32_t AES3_IV3;        /*!< Offset: 0x1F0:  AES Initial Vector Word 3 Register for Channel 3   */
    __IO uint32_t AES3_SADDR;      /*!< Offset: 0x1F4:  AES DMA Source Address Register for Channel 3      */
    __IO uint32_t AES3_DADDR;      /*!< Offset: 0x1F8:  AES DMA Destination Address Register for Channel 3 */
    __IO uint32_t AES3_CNT;        /*!< Offset: 0x1FC:  AES Byte Count Register for Channel 3              */
    __IO uint32_t TDES_CTL;        /*!< Offset: 0x200:  TDES/DES Control Register                     */
    __IO uint32_t TDES_STS;        /*!< Offset: 0x204:  TDES/DES Engine Flag                          */
    __IO uint32_t TDES0_KEY1H;     /*!< Offset: 0x208:  TDES/DES Key 1 High Word Register for Channel 0    */
    __IO uint32_t TDES0_KEY1L;     /*!< Offset: 0x20C:  TDES/DES Key 1 Low Word Register for Channel 0     */
    __IO uint32_t TDES0_KEY2H;     /*!< Offset: 0x210:  TDES/DES Key 2 High Word Register for Channel 0    */
    __IO uint32_t TDES0_KEY2L;     /*!< Offset: 0x214:  TDES/DES Key 2 Low Word Register for Channel 0     */
    __IO uint32_t TDES0_KEY3H;     /*!< Offset: 0x218:  TDES/DES Key 3 High Word Register for Channel 0    */
    __IO uint32_t TDES0_KEY3L;     /*!< Offset: 0x21C:  TDES/DES Key 3 Low Word Register for Channel 0     */
    __IO uint32_t TDES0_IVH;       /*!< Offset: 0x220:  TDES/DES Initial Vector High Word Register for Channel 0  */
    __IO uint32_t TDES0_IVL;       /*!< Offset: 0x224:  TDES/DES Initial Vector Low Word Register for Channel 0   */
    __IO uint32_t TDES0_SADDR;     /*!< Offset: 0x228:  TDES/DES DMA Source Address Register for Channel 0        */
    __IO uint32_t TDES0_DADDR;     /*!< Offset: 0x22C:  TDES/DES DMA Destination Address Register for Channel 0   */
    __IO uint32_t TDES0_CNT;       /*!< Offset: 0x230:  TDES/DES Byte Count Register for Channel 0    */
    __IO uint32_t TDES_DATIN;      /*!< Offset: 0x234:  TDES/DES Engine Input data Word Register      */
    __IO uint32_t TDES_DATOUT;     /*!< Offset: 0x238:  TDES/DES Engine Output data Word Register     */
    uint32_t RESERVE2[3];
    __IO uint32_t TDES1_KEY1H;     /*!< Offset: 0x248:  TDES/DES Key 1 High Word Register for Channel 1    */
    __IO uint32_t TDES1_KEY1L;     /*!< Offset: 0x24C:  TDES/DES Key 1 Low Word Register for Channel 1     */
    __IO uint32_t TDES1_KEY2H;     /*!< Offset: 0x250:  TDES/DES Key 2 High Word Register for Channel 1    */
    __IO uint32_t TDES1_KEY2L;     /*!< Offset: 0x254:  TDES/DES Key 2 Low Word Register for Channel 1     */
    __IO uint32_t TDES1_KEY3H;     /*!< Offset: 0x258:  TDES/DES Key 3 High Word Register for Channel 1    */
    __IO uint32_t TDES1_KEY3L;     /*!< Offset: 0x25C:  TDES/DES Key 3 Low Word Register for Channel 1     */
    __IO uint32_t TDES1_IVH;       /*!< Offset: 0x260:  TDES/DES Initial Vector High Word Register for Channel 1  */
    __IO uint32_t TDES1_IVL;       /*!< Offset: 0x264:  TDES/DES Initial Vector Low Word Register for Channel 1   */
    __IO uint32_t TDES1_SADDR;     /*!< Offset: 0x268:  TDES/DES DMA Source Address Register for Channel 1        */
    __IO uint32_t TDES1_DADDR;     /*!< Offset: 0x26C:  TDES/DES DMA Destination Address Register for Channel 1   */
    __IO uint32_t TDES1_CNT;       /*!< Offset: 0x270:  TDES/DES Byte Count Register for Channel 1    */
    uint32_t RESERVE3[5];
    __IO uint32_t TDES2_KEY1H;     /*!< Offset: 0x288:  TDES/DES Key 1 High Word Register for Channel 2    */
    __IO uint32_t TDES2_KEY1L;     /*!< Offset: 0x28C:  TDES/DES Key 1 Low Word Register for Channel 2     */
    __IO uint32_t TDES2_KEY2H;     /*!< Offset: 0x290:  TDES/DES Key 2 High Word Register for Channel 2    */
    __IO uint32_t TDES2_KEY2L;     /*!< Offset: 0x294:  TDES/DES Key 2 Low Word Register for Channel 2     */
    __IO uint32_t TDES2_KEY3H;     /*!< Offset: 0x298:  TDES/DES Key 3 High Word Register for Channel 2    */
    __IO uint32_t TDES2_KEY3L;     /*!< Offset: 0x29C:  TDES/DES Key 3 Low Word Register for Channel 2     */
    __IO uint32_t TDES2_IVH;       /*!< Offset: 0x2A0:  TDES/DES Initial Vector High Word Register for Channel 2  */
    __IO uint32_t TDES2_IVL;       /*!< Offset: 0x2A4:  TDES/DES Initial Vector Low Word Register for Channel 2   */
    __IO uint32_t TDES2_SADDR;     /*!< Offset: 0x2A8:  TDES/DES DMA Source Address Register for Channel 2        */
    __IO uint32_t TDES2_DADDR;     /*!< Offset: 0x2AC:  TDES/DES DMA Destination Address Register for Channel 2   */
    __IO uint32_t TDES2_CNT;       /*!< Offset: 0x2B0:  TDES/DES Byte Count Register for Channel 2    */
    uint32_t RESERVE4[5];
    __IO uint32_t TDES3_KEY1H;     /*!< Offset: 0x2C8:  TDES/DES Key 1 High Word Register for Channel 3    */
    __IO uint32_t TDES3_KEY1L;     /*!< Offset: 0x2CC:  TDES/DES Key 1 Low Word Register for Channel 3     */
    __IO uint32_t TDES3_KEY2H;     /*!< Offset: 0x2D0:  TDES/DES Key 2 High Word Register for Channel 3    */
    __IO uint32_t TDES3_KEY2L;     /*!< Offset: 0x2D4:  TDES/DES Key 2 Low Word Register for Channel 3     */
    __IO uint32_t TDES3_KEY3H;     /*!< Offset: 0x2D8:  TDES/DES Key 3 High Word Register for Channel 3    */
    __IO uint32_t TDES3_KEY3L;     /*!< Offset: 0x2DC:  TDES/DES Key 3 Low Word Register for Channel 3     */
    __IO uint32_t TDES3_IVH;       /*!< Offset: 0x2E0:  TDES/DES Initial Vector High Word Register for Channel 3  */
    __IO uint32_t TDES3_IVL;       /*!< Offset: 0x2E4:  TDES/DES Initial Vector Low Word Register for Channel 3   */
    __IO uint32_t TDES3_SADDR;     /*!< Offset: 0x2E8:  TDES/DES DMA Source Address Register for Channel 3        */
    __IO uint32_t TDES3_DADDR;     /*!< Offset: 0x2EC:  TDES/DES DMA Destination Address Register for Channel 3   */
    __IO uint32_t TDES3_CNT;       /*!< Offset: 0x2F0:  TDES/DES Byte Count Register for Channel 3    */
    uint32_t RESERVE5[3];
    __IO uint32_t HMAC_CTL;        /*!< Offset: 0x300:  SHA/HMAC Control Register                     */
    __IO uint32_t HMAC_STS;        /*!< Offset: 0x304:  SHA/HMAC Status Register                      */
    __IO uint32_t HMAC_DGST0;      /*!< Offset: 0x308:  SHA/HMAC Digest Message 0                     */
    __IO uint32_t HMAC_DGST1;      /*!< Offset: 0x30C:  SHA/HMAC Digest Message 1                     */
    __IO uint32_t HMAC_DGST2;      /*!< Offset: 0x310:  SHA/HMAC Digest Message 2                     */
    __IO uint32_t HMAC_DGST3;      /*!< Offset: 0x314:  SHA/HMAC Digest Message 3                     */
    __IO uint32_t HMAC_DGST4;      /*!< Offset: 0x318:  SHA/HMAC Digest Message 4                     */
    __IO uint32_t HMAC_DGST5;      /*!< Offset: 0x31C:  SHA/HMAC Digest Message 5                     */
    __IO uint32_t HMAC_DGST6;      /*!< Offset: 0x320:  SHA/HMAC Digest Message 6                     */
    __IO uint32_t HMAC_DGST7;      /*!< Offset: 0x324:  SHA/HMAC Digest Message 7                     */
    __IO uint32_t HMAC_DGST8;      /*!< Offset: 0x328:  SHA/HMAC Digest Message 8                     */
    __IO uint32_t HMAC_DGST9;      /*!< Offset: 0x32C:  SHA/HMAC Digest Message 9                     */
    __IO uint32_t HMAC_DGST10;     /*!< Offset: 0x330:  SHA/HMAC Digest Message 10                    */
    __IO uint32_t HMAC_DGST11;     /*!< Offset: 0x334:  SHA/HMAC Digest Message 11                    */
    __IO uint32_t HMAC_DGST12;     /*!< Offset: 0x338:  SHA/HMAC Digest Message 12                    */
    __IO uint32_t HMAC_DGST13;     /*!< Offset: 0x33C:  SHA/HMAC Digest Message 13                    */
    __IO uint32_t HMAC_DGST14;     /*!< Offset: 0x340:  SHA/HMAC Digest Message 14                    */
    __IO uint32_t HMAC_DGST15;     /*!< Offset: 0x344:  SHA/HMAC Digest Message 15                    */
    __IO uint32_t HMAC_KEYCNT;     /*!< Offset: 0x348:  SHA/HMAC Key Byte Count                       */
    __IO uint32_t HMAC_SADDR;      /*!< Offset: 0x34C:  SHA/HMAC DMA Source Address Register          */
    __IO uint32_t HMAC_DMACNT;     /*!< Offset: 0x350:  SHA/HMAC Byte Count Register                  */
    __IO uint32_t HMAC_DATIN;      /*!< Offset: 0x354:  SHA/HMAC Engine Non-DMA Mode Data Input Port Register */
} CRPT_T;


#define CRPT            ((CRPT_T *) CRPT_BA)


/**
    @addtogroup CRPT_CONST CRPT Bit Field Definition
    Constant Definitions for CRPT Controller
@{ */

#define CRPT_INTEN_AESIEN_Pos            (0)                                               /*!< CRPT INTEN: AESIEN Position            */
#define CRPT_INTEN_AESIEN_Msk            (0x1ul << CRPT_INTEN_AESIEN_Pos)                  /*!< CRPT INTEN: AESIEN Mask                */

#define CRPT_INTEN_AESERRIEN_Pos         (1)                                               /*!< CRPT INTEN: AESERRIEN Position         */
#define CRPT_INTEN_AESERRIEN_Msk         (0x1ul << CRPT_INTEN_AESERRIEN_Pos)               /*!< CRPT INTEN: AESERRIEN Mask             */

#define CRPT_INTEN_TDESIEN_Pos           (8)                                               /*!< CRPT INTEN: TDESIEN Position           */
#define CRPT_INTEN_TDESIEN_Msk           (0x1ul << CRPT_INTEN_TDESIEN_Pos)                 /*!< CRPT INTEN: TDESIEN Mask               */

#define CRPT_INTEN_TDESERRIEN_Pos        (9)                                               /*!< CRPT INTEN: TDESERRIEN Position        */
#define CRPT_INTEN_TDESERRIEN_Msk        (0x1ul << CRPT_INTEN_TDESERRIEN_Pos)              /*!< CRPT INTEN: TDESERRIEN Mask            */

#define CRPT_INTEN_PRNGIEN_Pos           (16)                                              /*!< CRPT INTEN: PRNGIEN Position           */
#define CRPT_INTEN_PRNGIEN_Msk           (0x1ul << CRPT_INTEN_PRNGIEN_Pos)                 /*!< CRPT INTEN: PRNGIEN Mask               */

#define CRPT_INTEN_SHAIEN_Pos            (24)                                              /*!< CRPT INTEN: SHAIEN Position            */
#define CRPT_INTEN_SHAIEN_Msk            (0x1ul << CRPT_INTEN_SHAIEN_Pos)                  /*!< CRPT INTEN: SHAIEN Mask                */

#define CRPT_INTEN_SHAERRIEN_Pos         (25)                                              /*!< CRPT INTEN: SHAERRIEN Position         */
#define CRPT_INTEN_SHAERRIEN_Msk         (0x1ul << CRPT_INTEN_SHAERRIEN_Pos)               /*!< CRPT INTEN: SHAERRIEN Mask             */

#define CRPT_INTSTS_AESIF_Pos            (0)                                               /*!< CRPT INTSTS: AESIF Position            */
#define CRPT_INTSTS_AESIF_Msk            (0x1ul << CRPT_INTSTS_AESIF_Pos)                  /*!< CRPT INTSTS: AESIF Mask                */

#define CRPT_INTSTS_AESERRIF_Pos         (1)                                               /*!< CRPT INTSTS: AESERRIF Position         */
#define CRPT_INTSTS_AESERRIF_Msk         (0x1ul << CRPT_INTSTS_AESERRIF_Pos)               /*!< CRPT INTSTS: AESERRIF Mask             */

#define CRPT_INTSTS_TDESIF_Pos           (8)                                               /*!< CRPT INTSTS: TDESIF Position           */
#define CRPT_INTSTS_TDESIF_Msk           (0x1ul << CRPT_INTSTS_TDESIF_Pos)                 /*!< CRPT INTSTS: TDESIF Mask               */

#define CRPT_INTSTS_TDESERRIF_Pos        (9)                                               /*!< CRPT INTSTS: TDESERRIF Position        */
#define CRPT_INTSTS_TDESERRIF_Msk        (0x1ul << CRPT_INTSTS_TDESERRIF_Pos)              /*!< CRPT INTSTS: TDESERRIF Mask            */

#define CRPT_INTSTS_PRNGIF_Pos           (16)                                              /*!< CRPT INTSTS: PRNGIF Position           */
#define CRPT_INTSTS_PRNGIF_Msk           (0x1ul << CRPT_INTSTS_PRNGIF_Pos)                 /*!< CRPT INTSTS: PRNGIF Mask               */

#define CRPT_INTSTS_SHAIF_Pos            (24)                                              /*!< CRPT INTSTS: SHAIF Position            */
#define CRPT_INTSTS_SHAIF_Msk            (0x1ul << CRPT_INTSTS_SHAIF_Pos)                  /*!< CRPT INTSTS: SHAIF Mask                */

#define CRPT_INTSTS_SHAERRIF_Pos         (25)                                              /*!< CRPT INTSTS: SHAERRIF Position         */
#define CRPT_INTSTS_SHAERRIF_Msk         (0x1ul << CRPT_INTSTS_SHAERRIF_Pos)               /*!< CRPT INTSTS: SHAERRIF Mask             */

#define CRPT_PRNG_CTL_START_Pos          (0)                                               /*!< CRPT PRNG_CTL: START Position          */
#define CRPT_PRNG_CTL_START_Msk          (0x1ul << CRPT_PRNG_CTL_START_Pos)                /*!< CRPT PRNG_CTL: START Mask              */

#define CRPT_PRNG_CTL_SEEDRLD_Pos        (1)                                               /*!< CRPT PRNG_CTL: SEEDRLD Position        */
#define CRPT_PRNG_CTL_SEEDRLD_Msk        (0x1ul << CRPT_PRNG_CTL_SEEDRLD_Pos)              /*!< CRPT PRNG_CTL: SEEDRLD Mask            */

#define CRPT_PRNG_CTL_KEYSZ_Pos          (2)                                               /*!< CRPT PRNG_CTL: KEYSZ Position          */
#define CRPT_PRNG_CTL_KEYSZ_Msk          (0x3ul << CRPT_PRNG_CTL_KEYSZ_Pos)                /*!< CRPT PRNG_CTL: KEYSZ Mask              */

#define CRPT_PRNG_CTL_BUSY_Pos           (8)                                               /*!< CRPT PRNG_CTL: BUSY Position           */
#define CRPT_PRNG_CTL_BUSY_Msk           (0x1ul << CRPT_PRNG_CTL_BUSY_Pos)                 /*!< CRPT PRNG_CTL: BUSY Mask               */

#define CRPT_AES_CTL_START_Pos           (0)                                               /*!< CRPT AES_CTL: START Position           */
#define CRPT_AES_CTL_START_Msk           (0x1ul << CRPT_AES_CTL_START_Pos)                 /*!< CRPT AES_CTL: START Mask               */

#define CRPT_AES_CTL_STOP_Pos            (1)                                               /*!< CRPT AES_CTL: STOP Position            */
#define CRPT_AES_CTL_STOP_Msk            (0x1ul << CRPT_AES_CTL_STOP_Pos)                  /*!< CRPT AES_CTL: STOP Mask                */

#define CRPT_AES_CTL_KEYSZ_Pos           (2)                                               /*!< CRPT AES_CTL: KEYSZ Position           */
#define CRPT_AES_CTL_KEYSZ_Msk           (0x3ul << CRPT_AES_CTL_KEYSZ_Pos)                 /*!< CRPT AES_CTL: KEYSZ Mask               */

#define CRPT_AES_CTL_DMALAST_Pos         (5)                                               /*!< CRPT AES_CTL: DMALAST Position         */
#define CRPT_AES_CTL_DMALAST_Msk         (0x1ul << CRPT_AES_CTL_DMALAST_Pos)               /*!< CRPT AES_CTL: DMALAST Mask             */

#define CRPT_AES_CTL_DMACSCAD_Pos        (6)                                               /*!< CRPT AES_CTL: DMACSCAD Position        */
#define CRPT_AES_CTL_DMACSCAD_Msk        (0x1ul << CRPT_AES_CTL_DMACSCAD_Pos)              /*!< CRPT AES_CTL: DMACSCAD Mask            */

#define CRPT_AES_CTL_DMAEN_Pos           (7)                                               /*!< CRPT AES_CTL: DMAEN Position           */
#define CRPT_AES_CTL_DMAEN_Msk           (0x1ul << CRPT_AES_CTL_DMAEN_Pos)                 /*!< CRPT AES_CTL: DMAEN Mask               */

#define CRPT_AES_CTL_OPMODE_Pos          (8)                                               /*!< CRPT AES_CTL: OPMODE Position          */
#define CRPT_AES_CTL_OPMODE_Msk          (0xfful << CRPT_AES_CTL_OPMODE_Pos)               /*!< CRPT AES_CTL: OPMODE Mask              */

#define CRPT_AES_CTL_ENCRPT_Pos          (16)                                              /*!< CRPT AES_CTL: ENCRPT Position          */
#define CRPT_AES_CTL_ENCRPT_Msk          (0x1ul << CRPT_AES_CTL_ENCRPT_Pos)                /*!< CRPT AES_CTL: ENCRPT Mask              */

#define CRPT_AES_CTL_OUTSWAP_Pos         (22)                                              /*!< CRPT AES_CTL: OUTSWAP Position         */
#define CRPT_AES_CTL_OUTSWAP_Msk         (0x1ul << CRPT_AES_CTL_OUTSWAP_Pos)               /*!< CRPT AES_CTL: OUTSWAP Mask             */

#define CRPT_AES_CTL_INSWAP_Pos          (23)                                              /*!< CRPT AES_CTL: INSWAP Position          */
#define CRPT_AES_CTL_INSWAP_Msk          (0x1ul << CRPT_AES_CTL_INSWAP_Pos)                /*!< CRPT AES_CTL: INSWAP Mask              */

#define CRPT_AES_CTL_CHANNEL_Pos         (24)                                              /*!< CRPT AES_CTL: CHANNEL Position         */
#define CRPT_AES_CTL_CHANNEL_Msk         (0x3ul << CRPT_AES_CTL_CHANNEL_Pos)               /*!< CRPT AES_CTL: CHANNEL Mask             */

#define CRPT_AES_CTL_KEYUNPRT_Pos        (26)                                              /*!< CRPT AES_CTL: KEYUNPRT Position        */
#define CRPT_AES_CTL_KEYUNPRT_Msk        (0x1ful << CRPT_AES_CTL_KEYUNPRT_Pos)             /*!< CRPT AES_CTL: KEYUNPRT Mask            */

#define CRPT_AES_CTL_KEYPRT_Pos          (31)                                              /*!< CRPT AES_CTL: KEYPRT Position          */
#define CRPT_AES_CTL_KEYPRT_Msk          (0x1ul << CRPT_AES_CTL_KEYPRT_Pos)                /*!< CRPT AES_CTL: KEYPRT Mask              */

#define CRPT_AES_STS_BUSY_Pos            (0)                                               /*!< CRPT AES_STS: BUSY Position            */
#define CRPT_AES_STS_BUSY_Msk            (0x1ul << CRPT_AES_STS_BUSY_Pos)                  /*!< CRPT AES_STS: BUSY Mask                */

#define CRPT_AES_STS_INBUFEMPTY_Pos      (8)                                               /*!< CRPT AES_STS: INBUFEMPTY Position      */
#define CRPT_AES_STS_INBUFEMPTY_Msk      (0x1ul << CRPT_AES_STS_INBUFEMPTY_Pos)            /*!< CRPT AES_STS: INBUFEMPTY Mask          */

#define CRPT_AES_STS_INBUFFULL_Pos       (9)                                               /*!< CRPT AES_STS: INBUFFULL Position       */
#define CRPT_AES_STS_INBUFFULL_Msk       (0x1ul << CRPT_AES_STS_INBUFFULL_Pos)             /*!< CRPT AES_STS: INBUFFULL Mask           */

#define CRPT_AES_STS_INBUFERR_Pos        (10)                                              /*!< CRPT AES_STS: INBUFERR Position        */
#define CRPT_AES_STS_INBUFERR_Msk        (0x1ul << CRPT_AES_STS_INBUFERR_Pos)              /*!< CRPT AES_STS: INBUFERR Mask            */

#define CRPT_AES_STS_CNTERR_Pos          (12)                                              /*!< CRPT AES_STS: CNTERR Position          */
#define CRPT_AES_STS_CNTERR_Msk          (0x1ul << CRPT_AES_STS_CNTERR_Pos)                /*!< CRPT AES_STS: CNTERR Mask              */

#define CRPT_AES_STS_OUTBUFEMPTY_Pos     (16)                                              /*!< CRPT AES_STS: OUTBUFEMPTY Position     */
#define CRPT_AES_STS_OUTBUFEMPTY_Msk     (0x1ul << CRPT_AES_STS_OUTBUFEMPTY_Pos)           /*!< CRPT AES_STS: OUTBUFEMPTY Mask         */

#define CRPT_AES_STS_OUTBUFFULL_Pos      (17)                                              /*!< CRPT AES_STS: OUTBUFFULL Position      */
#define CRPT_AES_STS_OUTBUFFULL_Msk      (0x1ul << CRPT_AES_STS_OUTBUFFULL_Pos)            /*!< CRPT AES_STS: OUTBUFFULL Mask          */

#define CRPT_AES_STS_OUTBUFERR_Pos       (18)                                              /*!< CRPT AES_STS: OUTBUFERR Position       */
#define CRPT_AES_STS_OUTBUFERR_Msk       (0x1ul << CRPT_AES_STS_OUTBUFERR_Pos)             /*!< CRPT AES_STS: OUTBUFERR Mask           */

#define CRPT_AES_STS_BUSERR_Pos          (20)                                              /*!< CRPT AES_STS: BUSERR Position          */
#define CRPT_AES_STS_BUSERR_Msk          (0x1ul << CRPT_AES_STS_BUSERR_Pos)                /*!< CRPT AES_STS: BUSERR Mask              */

#define CRPT_TDES_CTL_START_Pos          (0)                                               /*!< CRPT TDES_CTL: START Position          */
#define CRPT_TDES_CTL_START_Msk          (0x1ul << CRPT_TDES_CTL_START_Pos)                /*!< CRPT TDES_CTL: START Mask              */

#define CRPT_TDES_CTL_STOP_Pos           (1)                                               /*!< CRPT TDES_CTL: STOP Position           */
#define CRPT_TDES_CTL_STOP_Msk           (0x1ul << CRPT_TDES_CTL_STOP_Pos)                 /*!< CRPT TDES_CTL: STOP Mask               */

#define CRPT_TDES_CTL_TMODE_Pos          (2)                                               /*!< CRPT TDES_CTL: TMODE Position          */
#define CRPT_TDES_CTL_TMODE_Msk          (0x1ul << CRPT_TDES_CTL_TMODE_Pos)                /*!< CRPT TDES_CTL: TMODE Mask              */

#define CRPT_TDES_CTL_3KEYS_Pos          (3)                                               /*!< CRPT TDES_CTL: 3KEYS Position          */
#define CRPT_TDES_CTL_3KEYS_Msk          (0x1ul << CRPT_TDES_CTL_3KEYS_Pos)                /*!< CRPT TDES_CTL: 3KEYS Mask              */

#define CRPT_TDES_CTL_DMALAST_Pos        (5)                                               /*!< CRPT TDES_CTL: DMALAST Position        */
#define CRPT_TDES_CTL_DMALAST_Msk        (0x1ul << CRPT_TDES_CTL_DMALAST_Pos)              /*!< CRPT TDES_CTL: DMALAST Mask            */

#define CRPT_TDES_CTL_DMACSCAD_Pos       (6)                                               /*!< CRPT TDES_CTL: DMACSCAD Position       */
#define CRPT_TDES_CTL_DMACSCAD_Msk       (0x1ul << CRPT_TDES_CTL_DMACSCAD_Pos)             /*!< CRPT TDES_CTL: DMACSCAD Mask           */

#define CRPT_TDES_CTL_DMAEN_Pos          (7)                                               /*!< CRPT TDES_CTL: DMAEN Position          */
#define CRPT_TDES_CTL_DMAEN_Msk          (0x1ul << CRPT_TDES_CTL_DMAEN_Pos)                /*!< CRPT TDES_CTL: DMAEN Mask              */

#define CRPT_TDES_CTL_OPMODE_Pos         (8)                                               /*!< CRPT TDES_CTL: OPMODE Position         */
#define CRPT_TDES_CTL_OPMODE_Msk         (0x7ul << CRPT_TDES_CTL_OPMODE_Pos)               /*!< CRPT TDES_CTL: OPMODE Mask             */

#define CRPT_TDES_CTL_ENCRPT_Pos         (16)                                              /*!< CRPT TDES_CTL: ENCRPT Position         */
#define CRPT_TDES_CTL_ENCRPT_Msk         (0x1ul << CRPT_TDES_CTL_ENCRPT_Pos)               /*!< CRPT TDES_CTL: ENCRPT Mask             */

#define CRPT_TDES_CTL_BLKSWAP_Pos        (21)                                              /*!< CRPT TDES_CTL: BLKSWAP Position        */
#define CRPT_TDES_CTL_BLKSWAP_Msk        (0x1ul << CRPT_TDES_CTL_BLKSWAP_Pos)              /*!< CRPT TDES_CTL: BLKSWAP Mask            */

#define CRPT_TDES_CTL_OUTSWAP_Pos        (22)                                              /*!< CRPT TDES_CTL: OUTSWAP Position        */
#define CRPT_TDES_CTL_OUTSWAP_Msk        (0x1ul << CRPT_TDES_CTL_OUTSWAP_Pos)              /*!< CRPT TDES_CTL: OUTSWAP Mask            */

#define CRPT_TDES_CTL_INSWAP_Pos         (23)                                              /*!< CRPT TDES_CTL: INSWAP Position         */
#define CRPT_TDES_CTL_INSWAP_Msk         (0x1ul << CRPT_TDES_CTL_INSWAP_Pos)               /*!< CRPT TDES_CTL: INSWAP Mask             */

#define CRPT_TDES_CTL_CHANNEL_Pos        (24)                                              /*!< CRPT TDES_CTL: CHANNEL Position        */
#define CRPT_TDES_CTL_CHANNEL_Msk        (0x3ul << CRPT_TDES_CTL_CHANNEL_Pos)              /*!< CRPT TDES_CTL: CHANNEL Mask            */

#define CRPT_TDES_CTL_KEYUNPRT_Pos       (26)                                              /*!< CRPT TDES_CTL: KEYUNPRT Position       */
#define CRPT_TDES_CTL_KEYUNPRT_Msk       (0x1ful << CRPT_TDES_CTL_KEYUNPRT_Pos)            /*!< CRPT TDES_CTL: KEYUNPRT Mask           */

#define CRPT_TDES_CTL_KEYPRT_Pos         (31)                                              /*!< CRPT TDES_CTL: KEYPRT Position         */
#define CRPT_TDES_CTL_KEYPRT_Msk         (0x1ul << CRPT_TDES_CTL_KEYPRT_Pos)               /*!< CRPT TDES_CTL: KEYPRT Mask             */

#define CRPT_TDES_STS_BUSY_Pos           (0)                                               /*!< CRPT TDES_STS: BUSY Position           */
#define CRPT_TDES_STS_BUSY_Msk           (0x1ul << CRPT_TDES_STS_BUSY_Pos)                 /*!< CRPT TDES_STS: BUSY Mask               */

#define CRPT_TDES_STS_INBUFEMPTY_Pos     (8)                                               /*!< CRPT TDES_STS: INBUFEMPTY Position     */
#define CRPT_TDES_STS_INBUFEMPTY_Msk     (0x1ul << CRPT_TDES_STS_INBUFEMPTY_Pos)           /*!< CRPT TDES_STS: INBUFEMPTY Mask         */

#define CRPT_TDES_STS_INBUFFULL_Pos      (9)                                               /*!< CRPT TDES_STS: INBUFFULL Position      */
#define CRPT_TDES_STS_INBUFFULL_Msk      (0x1ul << CRPT_TDES_STS_INBUFFULL_Pos)            /*!< CRPT TDES_STS: INBUFFULL Mask          */

#define CRPT_TDES_STS_INBUFERR_Pos       (10)                                              /*!< CRPT TDES_STS: INBUFERR Position       */
#define CRPT_TDES_STS_INBUFERR_Msk       (0x1ul << CRPT_TDES_STS_INBUFERR_Pos)             /*!< CRPT TDES_STS: INBUFERR Mask           */

#define CRPT_TDES_STS_OUTBUFEMPTY_Pos    (16)                                              /*!< CRPT TDES_STS: OUTBUFEMPTY Position    */
#define CRPT_TDES_STS_OUTBUFEMPTY_Msk    (0x1ul << CRPT_TDES_STS_OUTBUFEMPTY_Pos)          /*!< CRPT TDES_STS: OUTBUFEMPTY Mask        */

#define CRPT_TDES_STS_OUTBUFFULL_Pos     (17)                                              /*!< CRPT TDES_STS: OUTBUFFULL Position     */
#define CRPT_TDES_STS_OUTBUFFULL_Msk     (0x1ul << CRPT_TDES_STS_OUTBUFFULL_Pos)           /*!< CRPT TDES_STS: OUTBUFFULL Mask         */

#define CRPT_TDES_STS_OUTBUFERR_Pos      (18)                                              /*!< CRPT TDES_STS: OUTBUFERR Position      */
#define CRPT_TDES_STS_OUTBUFERR_Msk      (0x1ul << CRPT_TDES_STS_OUTBUFERR_Pos)            /*!< CRPT TDES_STS: OUTBUFERR Mask          */

#define CRPT_TDES_STS_BUSERR_Pos         (20)                                              /*!< CRPT TDES_STS: BUSERR Position         */
#define CRPT_TDES_STS_BUSERR_Msk         (0x1ul << CRPT_TDES_STS_BUSERR_Pos)               /*!< CRPT TDES_STS: BUSERR Mask             */

#define CRPT_HMAC_CTL_START_Pos          (0)                                               /*!< CRPT HMAC_CTL: START Position           */
#define CRPT_HMAC_CTL_START_Msk          (0x1ul << CRPT_HMAC_CTL_START_Pos)                /*!< CRPT HMAC_CTL: START Mask               */

#define CRPT_HMAC_CTL_STOP_Pos           (1)                                               /*!< CRPT HMAC_CTL: STOP Position            */
#define CRPT_HMAC_CTL_STOP_Msk           (0x1ul << CRPT_HMAC_CTL_STOP_Pos)                 /*!< CRPT HMAC_CTL: STOP Mask                */

#define CRPT_HMAC_CTL_HMACEN_Pos         (4)                                               /*!< CRPT HMAC_CTL: HMACEN Position          */
#define CRPT_HMAC_CTL_HMACEN_Msk         (0x1ul << CRPT_HMAC_CTL_HMACEN_Pos)               /*!< CRPT HMAC_CTL: HMACEN Mask              */

#define CRPT_HMAC_CTL_DMALAST_Pos        (5)                                               /*!< CRPT HMAC_CTL: DMALAST Position         */
#define CRPT_HMAC_CTL_DMALAST_Msk        (0x1ul << CRPT_HMAC_CTL_DMALAST_Pos)              /*!< CRPT HMAC_CTL: DMALAST Mask             */

#define CRPT_HMAC_CTL_DMAEN_Pos          (7)                                               /*!< CRPT HMAC_CTL: DMAEN Position           */
#define CRPT_HMAC_CTL_DMAEN_Msk          (0x1ul << CRPT_HMAC_CTL_DMAEN_Pos)                /*!< CRPT HMAC_CTL: DMAEN Mask               */

#define CRPT_HMAC_CTL_OPMODE_Pos         (8)                                               /*!< CRPT HMAC_CTL: OPMODE Position          */
#define CRPT_HMAC_CTL_OPMODE_Msk         (0x7ul << CRPT_HMAC_CTL_OPMODE_Pos)               /*!< CRPT HMAC_CTL: OPMODE Mask              */

#define CRPT_HMAC_CTL_COMPEN_Pos         (15)                                              /*!< CRPT HMAC_CTL: COMPEN Position          */
#define CRPT_HMAC_CTL_COMPEN_Msk         (0x1ul << CRPT_HMAC_CTL_COMPEN_Pos)               /*!< CRPT HMAC_CTL: COMPEN Mask              */

#define CRPT_HMAC_CTL_OUTSWAP_Pos        (22)                                              /*!< CRPT HMAC_CTL: OUTSWAP Position         */
#define CRPT_HMAC_CTL_OUTSWAP_Msk        (0x1ul << CRPT_HMAC_CTL_OUTSWAP_Pos)              /*!< CRPT HMAC_CTL: OUTSWAP Mask             */

#define CRPT_HMAC_CTL_INSWAP_Pos         (23)                                              /*!< CRPT HMAC_CTL: INSWAP Position          */
#define CRPT_HMAC_CTL_INSWAP_Msk         (0x1ul << CRPT_HMAC_CTL_INSWAP_Pos)               /*!< CRPT HMAC_CTL: INSWAP Mask              */

#define CRPT_HMAC_STS_BUSY_Pos           (0)                                               /*!< CRPT HMAC_STS: BUSY Position            */
#define CRPT_HMAC_STS_BUSY_Msk           (0x1ul << CRPT_HMAC_STS_BUSY_Pos)                 /*!< CRPT HMAC_STS: BUSY Mask                */

#define CRPT_HMAC_STS_DMABUSY_Pos        (1)                                               /*!< CRPT HMAC_STS: DMABUSY Position         */
#define CRPT_HMAC_STS_DMABUSY_Msk        (0x1ul << CRPT_HMAC_STS_DMABUSY_Pos)              /*!< CRPT HMAC_STS: DMABUSY Mask             */

#define CRPT_HMAC_STS_DMAERR_Pos         (8)                                               /*!< CRPT HMAC_STS: DMAERR Position          */
#define CRPT_HMAC_STS_DMAERR_Msk         (0x1ul << CRPT_HMAC_STS_DMAERR_Pos)               /*!< CRPT HMAC_STS: DMAERR Mask              */

#define CRPT_HMAC_STS_COMPRES_Pos        (15)                                              /*!< CRPT HMAC_STS: COMPRES Position         */
#define CRPT_HMAC_STS_COMPRES_Msk        (0x1ul << CRPT_HMAC_STS_COMPRES_Pos)              /*!< CRPT HMAC_STS: COMPRES Mask             */

#define CRPT_HMAC_STS_DATINREQ_Pos       (16)                                              /*!< CRPT HMAC_STS: DATINREQ Position        */
#define CRPT_HMAC_STS_DATINREQ_Msk       (0x1ul << CRPT_HMAC_STS_DATINREQ_Pos)             /*!< CRPT HMAC_STS: DATINREQ Mask            */

/// @endcond HIDDEN_SYMBOLS



/** @addtogroup N9H30_CRYPTO_EXPORTED_CONSTANTS CRYPTO Exported Constants
  @{
*/

#define PRNG_KEY_SIZE_64        0       /*!< Select to generate 64-bit random key    \hideinitializer */
#define PRNG_KEY_SIZE_128       1       /*!< Select to generate 128-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_192       2       /*!< Select to generate 192-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_256       3       /*!< Select to generate 256-bit random key   \hideinitializer */

#define PRNG_SEED_CONT          0       /*!< PRNG using current seed                 \hideinitializer */
#define PRNG_SEED_RELOAD        1       /*!< PRNG reload new seed                    \hideinitializer */

#define AES_KEY_SIZE_128        0       /*!< AES select 128-bit key length           \hideinitializer */
#define AES_KEY_SIZE_192        1       /*!< AES select 192-bit key length           \hideinitializer */
#define AES_KEY_SIZE_256        2       /*!< AES select 256-bit key length           \hideinitializer */

#define AES_MODE_ECB            0       /*!< AES select ECB mode                     \hideinitializer */
#define AES_MODE_CBC            1       /*!< AES select CBC mode                     \hideinitializer */
#define AES_MODE_CFB            2       /*!< AES select CFB mode                     \hideinitializer */
#define AES_MODE_OFB            3       /*!< AES select OFB mode                     \hideinitializer */
#define AES_MODE_CTR            4       /*!< AES select CTR mode                     \hideinitializer */
#define AES_MODE_CBC_CS1        0x10    /*!< AES select CBC CS1 mode                 \hideinitializer */
#define AES_MODE_CBC_CS2        0x11    /*!< AES select CBC CS2 mode                 \hideinitializer */
#define AES_MODE_CBC_CS3        0x12    /*!< AES select CBC CS3 mode                 \hideinitializer */

#define AES_NO_SWAP             0       /*!< AES do not swap input and output data   \hideinitializer */
#define AES_OUT_SWAP            1       /*!< AES swap output data                    \hideinitializer */
#define AES_IN_SWAP             2       /*!< AES swap input data                     \hideinitializer */
#define AES_IN_OUT_SWAP         3       /*!< AES swap both input and output data     \hideinitializer */

#define DES_MODE_ECB            0x000   /*!< DES select ECB mode                     \hideinitializer */
#define DES_MODE_CBC            0x100   /*!< DES select CBC mode                     \hideinitializer */
#define DES_MODE_CFB            0x200   /*!< DES select CFB mode                     \hideinitializer */
#define DES_MODE_OFB            0x300   /*!< DES select OFB mode                     \hideinitializer */
#define DES_MODE_CTR            0x400   /*!< DES select CTR mode                     \hideinitializer */
#define TDES_MODE_ECB           0x004   /*!< TDES select ECB mode                    \hideinitializer */
#define TDES_MODE_CBC           0x104   /*!< TDES select CBC mode                    \hideinitializer */
#define TDES_MODE_CFB           0x204   /*!< TDES select CFB mode                    \hideinitializer */
#define TDES_MODE_OFB           0x304   /*!< TDES select OFB mode                    \hideinitializer */
#define TDES_MODE_CTR           0x404   /*!< TDES select CTR mode                    \hideinitializer */

#define TDES_NO_SWAP            0       /*!< TDES do not swap data                       \hideinitializer */
#define TDES_WHL_SWAP           1       /*!< TDES swap high-low word                     \hideinitializer */
#define TDES_OUT_SWAP           2       /*!< TDES swap output data                       \hideinitializer */
#define TDES_OUT_WHL_SWAP       3       /*!< TDES swap output data and high-low word     \hideinitializer */
#define TDES_IN_SWAP            4       /*!< TDES swap input data                        \hideinitializer */
#define TDES_IN_WHL_SWAP        5       /*!< TDES swap input data and high-low word      \hideinitializer */
#define TDES_IN_OUT_SWAP        6       /*!< TDES swap both input and output data        \hideinitializer */
#define TDES_IN_OUT_WHL_SWAP    7       /*!< TDES swap input, output and high-low word   \hideinitializer */

#define SHA_MODE_SHA1           0       /*!< SHA select SHA-1 160-bit                \hideinitializer */
#define SHA_MODE_SHA224         5       /*!< SHA select SHA-224 224-bit              \hideinitializer */
#define SHA_MODE_SHA256         4       /*!< SHA select SHA-256 256-bit              \hideinitializer */
#define SHA_MODE_SHA384         7       /*!< SHA select SHA-384 384-bit              \hideinitializer */
#define SHA_MODE_SHA512         6       /*!< SHA select SHA-512 512-bit              \hideinitializer */

#define SHA_NO_SWAP             0       /*!< SHA do not swap input and output data   \hideinitializer */
#define SHA_OUT_SWAP            1       /*!< SHA swap output data                    \hideinitializer */
#define SHA_IN_SWAP             2       /*!< SHA swap input data                     \hideinitializer */
#define SHA_IN_OUT_SWAP         3       /*!< SHA swap both input and output data     \hideinitializer */

#define CRYPTO_DMA_FIRST        0x4     /*!< Do first encrypt/decrypt in DMA cascade \hideinitializer */
#define CRYPTO_DMA_ONE_SHOT     0x5     /*!< Do one shot encrypt/decrypt with DMA      \hideinitializer */
#define CRYPTO_DMA_CONTINUE     0x6     /*!< Do one continuous encrypt/decrypt with DMA \hideinitializer */
#define CRYPTO_DMA_LAST         0x7     /*!< Do last encrypt/decrypt with DMA          \hideinitializer */

/*@}*/ /* end of group N9H30_CRYPTO_EXPORTED_CONSTANTS */




/** @addtogroup N9H30_CRYPTO_EXPORTED_FUNCTIONS CRYPTO Exported Functions
  @{
*/

/*----------------------------------------------------------------------------------------------*/
/*  Macros                                                                                      */
/*----------------------------------------------------------------------------------------------*/

/**
  * @brief This macro enables PRNG interrupt.
  * @return None
  * \hideinitializer
  */
#define PRNG_ENABLE_INT()       (CRPT->INTEN |= CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro disables PRNG interrupt.
  * @return None
  * \hideinitializer
  */
#define PRNG_DISABLE_INT()      (CRPT->INTEN &= ~CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro gets PRNG interrupt flag.
  * @return PRNG interrupt flag.
  * \hideinitializer
  */
#define PRNG_GET_INT_FLAG()     (CRPT->INTSTS & CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro clears PRNG interrupt flag.
  * @return None
  * \hideinitializer
  */
#define PRNG_CLR_INT_FLAG()     (CRPT->INTSTS = CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro enables AES interrupt.
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_INT()        (CRPT->INTEN |= (CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESERRIEN_Msk))

/**
  * @brief This macro disables AES interrupt.
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_INT()       (CRPT->INTEN &= ~(CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESERRIEN_Msk))

/**
  * @brief This macro gets AES interrupt flag.
  * @return AES interrupt flag.
  * \hideinitializer
  */
#define AES_GET_INT_FLAG()      (CRPT->INTSTS & (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESERRIF_Msk))

/**
  * @brief This macro clears AES interrupt flag.
  * @return None
  * \hideinitializer
  */
#define AES_CLR_INT_FLAG()      (CRPT->INTSTS = (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESERRIF_Msk))

/**
  * @brief This macro enables AES key protection.
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_KEY_PROTECT()  (CRPT->AES_CTL |= CRPT_AES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables AES key protection.
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_KEY_PROTECT() (CRPT->AES_CTL = (CRPT->AES_CTL & ~CRPT_AES_CTL_KEYPRT_Msk) | (0x16<<CRPT_AES_CTL_KEYUNPRT_Pos))

/**
  * @brief This macro enables TDES interrupt.
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_INT()       (CRPT->INTEN |= (CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESERRIEN_Msk))

/**
  * @brief This macro disables TDES interrupt.
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_INT()      (CRPT->INTEN &= ~(CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESERRIEN_Msk))

/**
  * @brief This macro gets TDES interrupt flag.
  * @return TDES interrupt flag.
  * \hideinitializer
  */
#define TDES_GET_INT_FLAG()     (CRPT->INTSTS & (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESERRIF_Msk))

/**
  * @brief This macro clears TDES interrupt flag.
  * @return None
  * \hideinitializer
  */
#define TDES_CLR_INT_FLAG()     (CRPT->INTSTS = (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESERRIF_Msk))

/**
  * @brief This macro enables TDES key protection.
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_KEY_PROTECT()  (CRPT->TDES_CTL |= CRPT_TDES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables TDES key protection.
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_KEY_PROTECT() (CRPT->TDES_CTL = (CRPT->TDES_CTL & ~CRPT_TDES_CTL_KEYPRT_Msk) | (0x16<<CRPT_TDES_CTL_KEYUNPRT_Pos))

/**
  * @brief This macro enables SHA interrupt.
  * @return None
  * \hideinitializer
  */
#define SHA_ENABLE_INT()        (CRPT->INTEN |= (CRPT_INTEN_SHAIEN_Msk|CRPT_INTEN_SHAERRIEN_Msk))

/**
  * @brief This macro disables SHA interrupt.
  * @return None
  * \hideinitializer
  */
#define SHA_DISABLE_INT()       (CRPT->INTEN &= ~(CRPT_INTEN_SHAIEN_Msk|CRPT_INTEN_SHAERRIEN_Msk))

/**
  * @brief This macro gets SHA interrupt flag.
  * @return SHA interrupt flag.
  * \hideinitializer
  */
#define SHA_GET_INT_FLAG()      (CRPT->INTSTS & (CRPT_INTSTS_SHAIF_Msk|CRPT_INTSTS_SHAERRIF_Msk))

/**
  * @brief This macro clears SHA interrupt flag.
  * @return None
  * \hideinitializer
  */
#define SHA_CLR_INT_FLAG()      (CRPT->INTSTS = (CRPT_INTSTS_SHAIF_Msk|CRPT_INTSTS_SHAERRIF_Msk))



/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/

void PRNG_Open(uint32_t u32KeySize, uint32_t u32SeedReload, uint32_t u32Seed);
void PRNG_Start(void);
void PRNG_Read(uint32_t u32RandKey[]);
void AES_Open(uint32_t u32Channel, uint32_t u32EncDec, uint32_t u32OpMode, uint32_t u32KeySize, uint32_t u32SwapType);
void AES_Start(int32_t u32Channel, uint32_t u32DMAMode);
void AES_SetKey(uint32_t u32Channel, uint32_t au32Keys[], uint32_t u32KeySize);
void AES_SetInitVect(uint32_t u32Channel, uint32_t au32IV[]);
void AES_SetDMATransfer(uint32_t u32Channel, uint32_t u32SrcAddr, uint32_t u32DstAddr, uint32_t u32TransCnt);
void TDES_Open(uint32_t u32Channel, uint32_t u32EncDec, int32_t Is3DES, int32_t Is3Key, uint32_t u32OpMode, uint32_t u32SwapType);
void TDES_Start(int32_t u32Channel, uint32_t u32DMAMode);
void TDES_SetKey(uint32_t u32Channel, uint32_t au32Keys[3][2]);
void TDES_SetInitVect(uint32_t u32Channel, uint32_t u32IVH, uint32_t u32IVL);
void TDES_SetDMATransfer(uint32_t u32Channel, uint32_t u32SrcAddr, uint32_t u32DstAddr, uint32_t u32TransCnt);
void SHA_Open(uint32_t u32OpMode, uint32_t u32SwapType, int hmac_key_len);
void SHA_Start(uint32_t u32DMAMode);
void SHA_SetDMATransfer(uint32_t u32SrcAddr, uint32_t u32TransCnt);
void SHA_Read(uint32_t u32Digest[]);


/*@}*/ /* end of group N9H30_CRYPTO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_CRYPTO_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif  // __NU_CRYPTO_H__

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/

