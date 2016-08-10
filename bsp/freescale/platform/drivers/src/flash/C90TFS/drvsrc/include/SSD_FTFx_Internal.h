/****************************************************************************
 (c) Copyright 2010-2014 Freescale Semiconductor, Inc.
 ALL RIGHTS RESERVED.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************


*****************************************************************************
*                                                                           *
*        Standard Software Flash Driver For FTFx                            *
*                                                                           *
* FILE NAME     :  SSD_FTFx.h                                               *
* DATE          :  Sep 25, 2014                                           *
*                                                                           *
* AUTHOR        :  FPT Team                                                 *
* E-mail        :  r56611@freescale.com                                     *
*                                                                           *
*****************************************************************************/

/************************** CHANGES *************************************
1.1.GA      09.25.2014      FPT Team      First version of SDK C90TFS flash driver
                                          inherited from BM C90TFS flash driver v1.02
                                          (08.04.2014, FPT Team)
*************************************************************************/
#ifndef _SSD_FTFx_H_
#define _SSD_FTFx_H_

#include "SSD_FTFx_Common.h"

#include "FTFx_KX_flash_config.h"


#ifndef C90TFS_ENABLE_DEBUG
    #define C90TFS_ENABLE_DEBUG 0
#endif

/* determine offset value for copy FlashLaunchCommand */
#if ((CPU_CORE == COLDFIRE)||(CPU_CORE == DSC_56800EX))
#define LAUNCH_COMMAND_OFFSET        0x0U  /* coldfile core dont need to shift address */
#else
#define LAUNCH_COMMAND_OFFSET        0x01U /* other cores need to shift address by 1 before copying */
#endif

/* This macros is used for copy command sequence feature*/
#if (CPU_CORE == DSC_56800EX)
    #define PGM2DATA(x) ((x>PROGRAM_RAM_SPACE_BASE)?(x-PROGRAM_RAM_SPACE_BASE + DATA_SPACE_BASE):(x + DATA_SPACE_BASE))
    #define DATA2PGM(x) (x+PROGRAM_RAM_SPACE_BASE)
#else
    #define PGM2DATA(x)    (x)
    #define DATA2PGM(x)    (x)
#endif

/* Enter debug mode macro */
#if (CPU_CORE == ARM_CORTEX_M)
    /* CW10, IAR */
    #if ((defined __ICCARM__) || (defined __GNUC__))
        #define ENTER_DEBUG_MODE  asm ("BKPT #0" )
    /* KIEL */
    #elif  (defined __ARMCC_VERSION)
        #define ENTER_DEBUG_MODE  __asm ("BKPT #0" )
    #endif
#endif
#if (CPU_CORE == DSC_56800EX)
    #define ENTER_DEBUG_MODE  asm ( debughlt)
#endif
#if (CPU_CORE == COLDFIRE)
    #define ENTER_DEBUG_MODE asm ( HALT    )
#endif

#if ((defined __GNUC__) && (CPU_CORE == ARM_CORTEX_M))
	#define SIZE_OPTIMIZATION	__attribute__((optimize("O4")))
#else
	#define SIZE_OPTIMIZATION
#endif

#endif /* _SSD_FTFx_H_ */


