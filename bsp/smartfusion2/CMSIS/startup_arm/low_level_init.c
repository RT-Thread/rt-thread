/*******************************************************************************
 * (c) Copyright 2014 Microsemi SoC Products Group. All rights reserved.
 *
 *  Keil-MDK specific system initialization.
 *
 * SVN $Revision: 7375 $
 * SVN $Date: 2015-05-01 14:57:40 +0100 (Fri, 01 May 2015) $
 */
#ifdef MSCC_NO_RELATIVE_PATHS
#include "m2sxxx.h"
#else
#include "..\m2sxxx.h"
#endif

#define ENVM_BASE_ADDRESS       0x60000000U
#define MDDR_BASE_ADDRESS       0xA0000000U

//extern unsigned int Image$$ER_RW$$Base;
//extern unsigned int Image$$ER_RO$$Base;

/*==============================================================================
 * The __low_level_init() function is called after SystemInit. Therefore, the
 * external RAM should be configured at this stage if it is used.
 */
/* void low_level_init(void)
{
    volatile unsigned int rw_region_base;
    volatile unsigned int readonly_region_base;
    
    rw_region_base = (unsigned int)&Image$$ER_RW$$Base;
    if (rw_region_base >= MDDR_BASE_ADDRESS)
    {
        / --------------------------------------------------------------------------
         * Remap MDDR to address 0x00000000.
         /
        SYSREG->ESRAM_CR = 0u;
        SYSREG->ENVM_REMAP_BASE_CR = 0u;
        SYSREG->DDR_CR = 1u;
    }
    
    readonly_region_base = (unsigned int)&Image$$ER_RO$$Base;
    SCB->VTOR = readonly_region_base;
}  */

