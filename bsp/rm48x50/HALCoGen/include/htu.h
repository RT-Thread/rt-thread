/** @file htu.h
*   @brief HTU Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#ifndef __HTU_H__
#define __HTU_H__

#include "reg_htu.h"

/* HTU General Definitions */


#define HTU1PARLOC		(*(volatile uint32 *)0xFF4E0200U)
#define HTU2PARLOC		(*(volatile uint32 *)0xFF4C0200U)

#define HTU1RAMLOC		(*(volatile uint32 *)0xFF4E0000U)
#define HTU2RAMLOC		(*(volatile uint32 *)0xFF4C0000U)

#endif
