/*********************************************************************************************************//**
 * @file    ht32_config.h
 * @version $Rev:: 7125         $
 * @date    $Date:: 2023-08-16 #$
 * @brief   Configuration file of HT32.
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
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_CONFIG_H
#define __HT32_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#ifdef USE_HT32F59999_SK
  #define USE_HT32F52352_SK
#endif
#ifdef USE_HT32F59999
  #define USE_HT32F52342_52
#endif
#ifdef USE_MEM_HT32F59999
  #define USE_MEM_HT32F52352
#endif

#ifdef USE_HT32F52142_SK
  #define USE_HT32F0008_SK
#endif
#ifdef USE_HT32F52142
  #define USE_HT32F0008
#endif
#ifdef USE_MEM_HT32F52142
  #define USE_MEM_HT32F0008
#endif

#ifdef USE_HT32F61352_DVB
  #define USE_HT32F0006_DVB
#endif
#ifdef USE_HT32F61352
  #define USE_HT32F0006
#endif
#ifdef USE_MEM_HT32F61352
  #define USE_MEM_HT32F0006
#endif
#ifdef USE_HT32F61355_56_57
  #define USE_HT32F0006
#endif
#ifdef USE_MEM_HT32F61355
  #define USE_MEM_HT32F0006
#endif
#ifdef USE_MEM_HT32F61356
  #define USE_MEM_HT32F0006
#endif
#ifdef USE_MEM_HT32F61357
  #define USE_MEM_HT32F0006
#endif

#ifdef USE_HT50F32002_SK
  #define USE_HT32F50230_SK
#endif
#ifdef USE_HT50F32002
  #define USE_HT32F50220_30
#endif
#ifdef USE_MEM_HT50F32002
  #define USE_MEM_HT32F50230
#endif

#ifdef USE_HT50F32003_SK
  #define USE_HT32F52352_SK
#endif
#ifdef USE_HT50F32003
  #define USE_HT32F52342_52
#endif
#ifdef USE_MEM_HT50F32003
  #define USE_MEM_HT32F52352
#endif

#ifdef USE_HT32F59041_SK
  #define USE_HT32F50241_SK
#endif
#ifdef USE_HT32F59041
  #define USE_HT32F50231_41
#endif
#ifdef USE_MEM_HT32F59041
  #define USE_MEM_HT32F50241
#endif

#ifdef USE_HT32F59741_SK
  #define USE_HT32F57341_SK
#endif
#ifdef USE_HT32F59741
  #define USE_HT32F57331_41
#endif
#ifdef USE_MEM_HT32F59741
  #define USE_MEM_HT32F57341
#endif

#ifdef USE_HT32F67741_SK
  #define USE_HT32F52241_SK
#endif
#ifdef USE_HT32F67741
  #define USE_HT32F52231_41
#endif
#ifdef USE_MEM_HT32F67741
  #define USE_MEM_HT32F52241
#endif

#ifdef USE_HF5032_SK
  #define USE_HT32F50230_SK
#endif
#ifdef USE_HF5032
  #define USE_HT32F50220_30
#endif
#ifdef USE_MEM_HF5032
  #define USE_MEM_HT32F50230
#endif

#ifdef USE_HT32F65240
  #undef USE_HT32F65230_40
  #define USE_HT32F65230_40
#elif defined USE_HT32F65230_40
  #undef USE_HT32F65240
  #define USE_HT32F65240
#endif

#ifdef USE_HT32F5828_SK
  #define USE_HT32F57352_SK
#endif
#ifdef USE_HT32F5828
  #define USE_HT32F57342_52
#endif
#ifdef USE_MEM_HT32F5828
  #define USE_MEM_HT32F57352
#endif

#ifdef USE_MXTX6306_SK
  #define USE_HT32F65240_SK
#endif
#ifdef USE_MXTX6306
  #define USE_HT32F65230_40
#endif
#ifdef USE_MEM_MXTX6306
  #define USE_MEM_HT32F65230
#endif

#ifdef USE_HT32F67232_SK
  #define USE_HT32F52230_SK
#endif
#ifdef USE_HT32F67232
  #define USE_HT32F52220_30
#endif
#ifdef USE_MEM_HT32F67232
  #define USE_MEM_HT32F52230
#endif

#ifdef USE_HT32F67233
  #define USE_HT32F52220_30
#endif
#ifdef USE_MEM_HT32F67233
  #define USE_MEM_HT32F52230
#endif

#ifdef USE_HT50F3200S_SK
  #define USE_HT32F65240_SK
#endif
#ifdef USE_HT50F3200S
  #define USE_HT32F65230_40
#endif
#ifdef USE_MEM_HT50F3200S
  #define USE_MEM_HT32F65240
#endif

#ifdef USE_HT50F3200T_SK
  #define USE_HT32F52367_SK
#endif
#ifdef USE_HT50F3200T
  #define USE_HT32F52357_67
#endif
#ifdef USE_MEM_HT50F3200T
  #define USE_MEM_HT32F52367
#endif

#ifdef USE_HT32F62030_SK
  #define USE_HT32F52230_SK
#endif
#ifdef USE_HT32F62030
  #define USE_HT32F52220_30
#endif
#ifdef USE_MEM_HT32F62030
  #define USE_MEM_HT32F52230
#endif

#ifdef USE_HT32F62040_SK
  #define USE_HT32F52241_SK
#endif
#ifdef USE_HT32F62040
  #define USE_HT32F52231_41
#endif
#ifdef USE_MEM_HT32F62040
  #define USE_MEM_HT32F52241
#endif

#ifdef USE_HT32F62050_SK
  #define USE_HT32F52253_SK
#endif
#ifdef USE_HT32F62050
  #define USE_HT32F52243_53
#endif
#ifdef USE_MEM_HT32F62050
  #define USE_MEM_HT32F52253
#endif

#ifdef USE_HT32F61630_SK
  #define USE_HT32F50030_SK
#endif
#ifdef USE_HT32F61630
  #define USE_HT32F50020_30
#endif
#ifdef USE_MEM_HT32F61630
  #define USE_MEM_HT32F50030
#endif

#ifdef USE_HT32F61641_SK
  #define USE_HT32F50241_SK
#endif
#ifdef USE_HT32F61641
  #define USE_HT32F50231_41
#endif
#ifdef USE_MEM_HT32F61641
  #define USE_MEM_HT32F50241
#endif

#ifdef USE_HT32F67742_SK
  #define USE_HT32F57341_SK
#endif
#ifdef USE_HT32F67742
  #define USE_HT32F57331_41
#endif
#ifdef USE_MEM_HT32F67742
  #define USE_MEM_HT32F57341
#endif

#ifdef USE_HT32F59046_SK
  #define USE_HT32F50241_SK
#endif
#ifdef USE_HT32F59046
  #define USE_HT32F50231_41
#endif
#ifdef USE_MEM_HT32F59046
  #define USE_MEM_HT32F50241
#endif

#ifdef USE_HT32F59746_SK
  #define USE_HT32F57341_SK
#endif
#ifdef USE_HT32F59746
  #define USE_HT32F57331_41
#endif
#ifdef USE_MEM_HT32F59746
  #define USE_MEM_HT32F57341
#endif

#ifdef USE_HT32F61030_SK
  #define USE_HT32F50030_SK
#endif
#ifdef USE_HT32F61030
  #define USE_HT32F50020_30
#endif
#ifdef USE_MEM_HT32F61030
  #define USE_MEM_HT32F50030
#endif

#ifdef USE_HT32F61041_SK
  #define USE_HT32F50241_SK
#endif
#ifdef USE_HT32F61041
  #define USE_HT32F50231_41
#endif
#ifdef USE_MEM_HT32F61041
  #define USE_MEM_HT32F50241
#endif

#ifdef __cplusplus
}
#endif

#endif
