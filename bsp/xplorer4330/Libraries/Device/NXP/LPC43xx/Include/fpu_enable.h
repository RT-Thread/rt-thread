/*********************************************************************** 
 * $Id: fpu_enable.h 
 * 
 * Project: LPC43xx 
 * 
 * Description: fpu initialization routine header
 * 
 * Copyright(C) 2011, NXP Semiconductor
 * All rights reserved.
 * 
 ***********************************************************************
 * Software that is described herein is for illustrative purposes only  
 * which provides customers with programming information regarding the  
 * products. This software is supplied "AS IS" without any warranties.  
 * NXP Semiconductors assumes no responsibility or liability for the 
 * use of the software, conveys no license or title under any patent, 
 * copyright, or mask work right to the product. NXP Semiconductors 
 * reserves the right to make changes in the software without 
 * notification. NXP Semiconductors also make no representation or 
 * warranty that such application will be suitable for the specified 
 * use without further testing or modification. 
 **********************************************************************/

#ifndef __FPU_ENABLE_H 
#define __FPU_ENABLE_H 

#if defined(__ARMCC_VERSION)
void fpuEnable(void) __attribute__ ((section("BOOTSTRAP_CODE")));
#else
extern void fpuEnable(void);
#endif

#endif /* __FPU_ENABLE_H */
