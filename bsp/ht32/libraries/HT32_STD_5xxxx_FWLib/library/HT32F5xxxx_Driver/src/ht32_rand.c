/*********************************************************************************************************//**
 * @file    ht32_rand.c
 * @version $Rev:: 2069         $
 * @date    $Date:: 2017-11-07 #$
 * @brief   The rundom number function.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include <stdlib.h>

/* Global variables ----------------------------------------------------------------------------------------*/
__ALIGN4 static uc32 RandData[] =
{
  0x4946b5ff, 0x6a4cb087, 0x6b0c9404, 0x6a4c9403,
  0x042d2503, 0x624c432c, 0x4d416b0c, 0x630c432c,
  0x68394f40, 0x2580463c, 0x402926f9, 0x1b890236,
  0x021e6039, 0x04114316, 0x0619430e, 0x607e430e,
  0x43160216, 0x4316041a, 0x60a6430e, 0x62212117,
  0x22014934, 0x630a3140, 0x432b6823, 0x4e326023,
  0x93056873, 0x685c4b31, 0x4c319406, 0x605c6074,
  0x69dd69f4, 0x43136b4b, 0x4a2a634b, 0x68533280,
  0xd5fc075b, 0x463a6b3b, 0x0f1b071b, 0x6b7b9302,
  0x071b6bbf, 0x073f0f1b, 0x97010f3f, 0x07176bd2,
  0x680a0f3f, 0x071746bc, 0x97000f3f, 0x0717684a,
  0x688a0f3f, 0x071246be, 0x0f1268c9, 0x68074e1a,
  0x042d69f6, 0x193419be, 0x4d181964, 0x69ed6004,
  0x011b9e02, 0x431e9f01, 0x023b042d, 0x46671964,
  0x432b033d, 0x431e9f00, 0x431e043b, 0x053b4677,
  0x0612431e, 0x07094316, 0x9a08430e, 0x18891931,
  0x48096001, 0x60419905, 0x99064808, 0x48036041,
  0x62419904, 0x63019903, 0xbdf0b00b, 0x40088000,
  0x01000040, 0x40010000, 0x400b0000, 0x400b2000,
  0x0000ffff
};

__ALIGN4 static uc32 RandData2[] =
{
  0x4604b510, 0x18406800, 0x46216020, 0x68084a03,
  0x4a034350, 0x60081880, 0xbd100840, 0x41c64e6d,
  0x00003039
};

typedef void (*Randinit_TypeDef) (u32 *, u32, u32, u32);
u32 (*Rand_Get)(u32 *, u32);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Rand init.
  * @param  uSeed
  * @param  uCount
  * @param  a
  * @param  b
  * @retval none
  ***********************************************************************************************************/
void Rand_Init(u32 *uSeed, u32 uCount, u32 a, u32 b)
{
  Randinit_TypeDef Randinit = (Randinit_TypeDef)((u32)RandData | 0x1);
  Rand_Get = (u32 (*)(u32 *, u32))((u32)RandData2 | 0x1);
  Randinit(uSeed, uCount, a, b);
}
