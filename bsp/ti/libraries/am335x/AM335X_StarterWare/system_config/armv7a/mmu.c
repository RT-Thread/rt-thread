/**
 *  \file   mmu.c
 *
 *  \brief  APIs for configuring MMU
 *
 *  This file contains the APIs for configuring ARMv7a MMU.
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "mmu.h"
#include "cp15.h"

/*****************************************************************************
**                      INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define MMU_PAGETABLE_ENTRY_FAULT                (0x00)
#define MMU_PAGEBOUND_SHIFT                      (20)
#define MMU_PG_SUPSECT_SIZE_SHIFT                (14)
#define MMU_PGADDR_MASK                          (0xFFF00000)
#define MMU_PGTYPE_MASK                          (0x00040002)

/*****************************************************************************
**                         FUNCTION DEFINITIONS
******************************************************************************/
/**
 * \brief   Initializes the Page Table with fault entries and configures CP15
 *          registers required for MMU. The Page Table passed is the master
 *          page table containing 4096 words, which will be defined by the 
 *          application.
 *
 * \param   masterPt      Master Page Table Base Address
 *
 * \return  None.
 *
 * \Note    The StarterWare support for MMU needs only master page table 
 *          configuration. Only a single level paging is supported. Also, only
 *          TTB0 will be used for page table walking.
 **/
void MMUInit(unsigned int *masterPt)
{
    unsigned int idx;

   /* Invalidate the TLB entries */
    CP15TlbInvalidate();

    /* Set domain access rights */
    CP15DomainAccessClientSet();

    /* Disable TEX remapping, Access Flag usage and alignment check */
    CP15ControlFeatureDisable( CP15_CONTROL_TEXREMAP
                               | CP15_CONTROL_ACCESSFLAG
                               | CP15_CONTROL_ALIGN_CHCK
                               | CP15_CONTROL_MMU);

    /* Configure the TTB Control register to use only TTB0 */
    CP15TtbCtlTtb0Config();

    /* Se the master page table with fault entries */
    for(idx = MMU_PAGETABLE_NUM_ENTRY; idx !=0; idx--)
    {
        *masterPt++ = MMU_PAGETABLE_ENTRY_FAULT;
    }
}

/**
 * \brief   Maps a specific region for Virtual Address to Physical Address
 *          conversion. This API actually updates the corresponding page table 
 *          entries. The mapping for any region is such that Virtual Address
 *          = Physical Address. \n
 *          Any region can be mapped as per the attributes given. Regions
 *          can be specified with Memory Type, Inner/Outer Cache settings, 
 *          Security settings and Access Permissions.
 *          
 * \param   region      Memory Region to be mapped. This shall be a structure
 *                      pointer of Type REGION *. The structure is detailed in
 *                      mmu.h file. \n
 *
 *            Example Configuration: \n
 *              A 512MB RAM memory region starting at address 0x80000000 can be
 *              configured as shown below. The memory is to be cacheable, with
 *              Inner Cache - Write Through Write Allocate and Outer Cache -
 *              Write Back Write Allocate attributes. \n 
 *
 *              REGION regionRam = { MMU_PGTYPE_SECTION, \n
 *                                   0x80000000, \n
 *                                   512,  \n
 *                                   MMU_MEMTYPE_NORMAL_SHAREABLE 
 *                                     (MMU_CACHE_WT_NOWA, MMU_CACHE_WB_WA),\n
 *                                   MMU_REGION_NON_SECURE, \n
 *                                   MMU_AP_PRV_RW_USR_RW, \n
 *                                   (unsigned int*)pageTable};
 *
 * \return  None.
 *
 * \Note    The regions specify the desired cache policies. However, enabling
 *          of cache at all desired levels shall be done separately.
 **/
void MMUMemRegionMap(REGION *region)
{
    unsigned int *ptEntryPtr;
    unsigned int ptEntry;
    int idx;

    /* Get the first entry in the page table to set */
    ptEntryPtr = region->masterPtPtr + 
                 (region->startAddr >> MMU_PAGEBOUND_SHIFT);

    /* Set the pointer to the last entry */
    ptEntryPtr += (region->numPages - 1); 

    /* Get the start Address MSB 3 nibbles. Ignore extended address */
    ptEntry = (region->startAddr & region->pgType) & MMU_PGADDR_MASK;

    /*
    ** Update the page table entry with memory attributes and
    ** Access Permissions and Security.
    ** All the regions will be marked as global.
    */
    ptEntry |= ((MMU_PGTYPE_MASK & region->pgType) 
                | region->accsCtrl | region->memAttrib
                | region->secureType);

    /* Set the entries in the page table for the region attributes */
    for(idx = (region->numPages - 1); idx >= 0; idx--)
    {
       *ptEntryPtr-- = ptEntry + (idx << MMU_PAGEBOUND_SHIFT) ;
    }
}

/**
 * \brief   Updates the Translation Table Base with the address of Master Page
 *          Table and enables MMU.
 *
 * \param   masterPt      Master Page Table Base Address
 *
 * \return  None.
 *
 * \Note    Only TTB0 is used for page table walking.
 **/
void MMUEnable(unsigned int *masterPt)
{
    /* Set TTB0 register */
    CP15Ttb0Set((unsigned int)masterPt);

    /* Enable MMU */
    CP15MMUEnable();
}

/***************************** End Of File ***********************************/

