/*********************************************************************************************************//**
 * @file    ht32_div.c
 * @version $Rev:: 220          $
 * @date    $Date:: 2016-02-16 #$
 * @brief   The division assembly.
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

#include "ht32.h"

/* Global variables ----------------------------------------------------------------------------------------*/
//__ALIGN4 static uc32 Data[] =
__ALIGN4 static u32 Data[] =
{
0x09032200, 0xD32C428B, 0x428B0A03, 0x2300D311, 0xE04E469C, 0x430B4603, 0x2200D43C, 0x428B0843,
0x0903D331, 0xD31C428B, 0x428B0A03, 0x4694D301, 0x09C3E03F, 0xD301428B, 0x1AC001CB, 0x09834152,
0xD301428B, 0x1AC0018B, 0x09434152, 0xD301428B, 0x1AC0014B, 0x09034152, 0xD301428B, 0x1AC0010B,
0x08C34152, 0xD301428B, 0x1AC000CB, 0x08834152, 0xD301428B, 0x1AC0008B, 0x08434152, 0xD301428B,
0x1AC0004B, 0x1A414152, 0x4601D200, 0x46104152, 0xE05D4770, 0xD0000FCA, 0x10034249, 0x4240D300,
0x22004053, 0x0903469C, 0xD32D428B, 0x428B0A03, 0x22FCD312, 0xBA120189, 0x428B0A03, 0x0189D30C,
0x428B1192, 0x0189D308, 0x428B1192, 0x0189D304, 0x1192D03A, 0x0989E000, 0x428B09C3, 0x01CBD301,
0x41521AC0, 0x428B0983, 0x018BD301, 0x41521AC0, 0x428B0943, 0x014BD301, 0x41521AC0, 0x428B0903,
0x010BD301, 0x41521AC0, 0x428B08C3, 0x00CBD301, 0x41521AC0, 0x428B0883, 0x008BD301, 0x41521AC0,
0x0843D2D9, 0xD301428B, 0x1AC0004B, 0x1A414152, 0x4601D200, 0x41524663, 0x4610105B, 0x4240D301,
0xD5002B00, 0x47704249, 0x105B4663, 0x4240D300, 0x2000B501, 0x46C046C0, 0x0000BD02
};

u32 (*UDIV32)(u32, u32);
s32 (*SDIV32)(s32, s32);

void DIV32_Init(void)
{
  u32 fptr = (u32)Data;
  UDIV32 = (u32 (*)(u32, u32))(fptr + 0x1);
  SDIV32 = (s32 (*)(s32, s32))(fptr + 0x15);
}
