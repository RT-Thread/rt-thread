/*********************************************************************************************************//**
 * @file    ht32_rand.c
 * @version $Rev:: 1736         $
 * @date    $Date:: 2019-06-25 #$
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
#if !(LIBCFG_ADC_V01)
__ALIGN4 static uc32 RandData[] =
{
  0x4fffe92d, 0xb0844948, 0x94016a4c, 0x94006b0c,
  0xf4446a4c, 0x624c3440, 0x4d446b0c, 0x630c432c,
  0x2135ea4f, 0xf004688c, 0xf5a40480, 0x608c4479,
  0x2403ea42, 0x4402ea44, 0x6403ea44, 0xea42610c,
  0xea442402, 0xea444403, 0x614c6403, 0x0282eb01,
  0x67142417, 0x0283eb01, 0x22016714, 0x2100f8c1,
  0xf042688a, 0x608a0280, 0x90c4f8df, 0x2004f8d9,
  0x4a309202, 0x93036853, 0x73fff64f, 0x3004f8c9,
  0xf8d96053, 0x69d7601c, 0x2104f8d1, 0x0201f042,
  0x2104f8c1, 0x2134f8d1, 0xd5fb0752, 0x2fb0f851,
  0x0b0ff002, 0xf002684a, 0x688a0e0f, 0x0a0ff002,
  0xf00268ca, 0x690a050f, 0x040ff002, 0xf002694a,
  0x698a030f, 0xf00269c9, 0xf8d0020f, 0xf8d9c000,
  0x44c4801c, 0xeb064466, 0x4f164607, 0xf8d76006,
  0xea4bc01c, 0xeb06180e, 0xea4f460c, 0xea4c2c0a,
  0xea483505, 0xea480805, 0xea444404, 0xea435303,
  0xea426202, 0x9a057101, 0x44114431, 0x98026001,
  0x0004f8c9, 0x60789803, 0x99014803, 0x99006241,
  0xb0086301, 0x8ff0e8bd, 0x40088000, 0x01000040,
  0x400b0000, 0x400b2000
};
#else
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
#endif
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
