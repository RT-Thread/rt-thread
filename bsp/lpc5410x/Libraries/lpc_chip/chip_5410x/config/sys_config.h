/*
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __SYS_CONFIG_H_
#define __SYS_CONFIG_H_

/* Build for LPC5410X chip family */
#define CHIP_LPC5410X

/* Define ROMDRIVERSV2_PRESENT to enable v2 driver support in ROM. For LPC54xxx
     devices with boot ROM version 17.2 and later, this should be defined.
     For earlier versions, this should not be defined. If the definitions is
     not defined, the same v2 drivers will be used, but will use a version that
     is located in FLASH instead. */
// #define ROMDRIVERSV2_PRESENT

#endif /* __SYS_CONFIG_H_ */
