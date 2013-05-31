/** @file dmm.h
*   @brief DMM Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#ifndef __DMM_H__
#define __DMM_H__

#include "reg_dmm.h"


/** 
 *  @defgroup DMM DMM
 *  @brief Data Modification Module.
 *  
 *  The DMM module provides the capability to modify data in the entire 4 GB address space of the device from an external peripheral,
 *  with minimal interruption of the application.
 *
 *	Related Files
 *   - reg_dmm.h
 *   - dmm.h
 *   - dmm.c
 *  @addtogroup DMM
 *  @{
 */
/* DMM Interface Functions */

void dmmInit(void);

/**@}*/
#endif
