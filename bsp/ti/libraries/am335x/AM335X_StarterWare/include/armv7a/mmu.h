/**
 *  \file   mmu.h
 *
 *  \brief  MMU configuration API prototypes
 *
 *  This file contains the API prototypes and structure definitions
 *  for configuring ARMv7a MMU.
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

#ifndef __MMU_H
#define __MMU_H

#ifdef __cplusplus
extern "C" {
#endif

/*
** Number of entries in a page table. This is only for first level page table
*/
#define MMU_PAGETABLE_NUM_ENTRY                  (4096)

/*
** Alignment for Page Table. The Page Table shall be aligned to 16KB boundary.
*/
#define MMU_PAGETABLE_ALIGN_SIZE                 (16 * 1024)

/*****************************************************************************/
/*
** Page Type for a region. To be assigned to 'pgType' field of a REGION
** structure.
** Eg: region.pgType = MMU_PGTYPE_SECTION
*/
/* To configure as a section. Section Size is 1MB */
#define MMU_PGTYPE_SECTION                       (0xFFF04002)

/* To configure as a super section. Super Section Size is 16MB */
#define MMU_PGTYPE_SUPERSECTION                  (0xFF040002)

/*****************************************************************************/
/*
** Access Control for a section, to be assigned to 'memAttrib' field
** of a REGION structure.
** Eg: region1.memAttrib = MMU_MEMTYPE_DEVICE_SHAREABLE;
**     region2.memAttrib = MMU_MEMTYPE_NORMAL_SHAREABLE(MMU_CACHE_WB_WA,
**                                                      MMU_CACHE_WT_NOWA)
*/
/* Strongly Ordered memory - always shareable */
#define MMU_MEMTYPE_STRONG_ORD_SHAREABLE         (0x00000000)

/* Shareable Device memory */
#define MMU_MEMTYPE_DEVICE_SHAREABLE             (0x00000004)

/* Non-Shareable Device memory */
#define MMU_MEMTYPE_DEVICE_NON_SHAREABLE         (0x00002000)

/*
** Non-Shareable Normal memory. Cache Policies are given as parameters.
** Eg : MMU_MEMTYPE_NORMAL_NON_SHAREABLE(MMU_CACHE_WB_WA, MMU_CACHE_WT_NOWA)
*/
#define MMU_MEMTYPE_NORMAL_NON_SHAREABLE(innerCachePol, outerCachePol)   \
                                               (0x00004000               \
                                                | (outerCachePol << 12)  \
                                                | (innerCachePol << 2))

/*
** Shareable Normal memory. Cache Policies are given as parameters.
** Eg : MMU_MEMTYPE_NORMAL_NON_SHAREABLE(MMU_CACHE_WB_WA, MMU_CACHE_WT_NOWA)
*/
#define MMU_MEMTYPE_NORMAL_SHAREABLE(innerCachePol, outerCachePol)       \
                                               (0x00014000               \
                                                | (outerCachePol << 12)  \
                                                | (innerCachePol << 2))

/*
** Definitions for the parameters 'innerCachePol' & 'outerCachePol' to set
** cache policies for Normal Memory to MMU_MEMTYPE_NORMAL_* macros
*/
/* Non Cacheable Memory */
#define MMU_NON_CACHEABLE                        (0x00)

/* Write Back, Write Allocate */
#define MMU_CACHE_WB_WA                          (0x01)

/* Write Through, No Write Allocate */
#define MMU_CACHE_WT_NOWA                        (0x02)

/* Write Back, No Write Allocate */
#define MMU_CACHE_WB_NOWA                        (0x03)

/*****************************************************************************/
/*
** Access Control for a section, to be assigned to 'secureType' field
** of a REGION structure
*/
/* Secure physical address space is accessed */
#define MMU_REGION_SECURE                        (0x00000000)

/* Non-secure physical address space is accessed */
#define MMU_REGION_NON_SECURE                    (0x00080000)

/*****************************************************************************/
/*
** Access Control for a section, to be assigned to 'accsCtrl' field
** of a REGION structure
** region.accsCtrl = MMU_AP_PRV_RW_USR_RW;
**
** If the section is read sensitive, MMU_SECTION_EXEC_NEVER macro can be used
** OR'ed with Acess Permissions.
** region.accsCtrl = MMU_AP_PRV_RW_USR_NA | MMU_SECTION_EXEC_NEVER;
*/
/*
** Macros for Access Permissions in both privilege modes
*/
/* Both Privileged and User Permission- No Access*/
#define MMU_AP_PRV_NA_USR_NA                     (0x0000)

/* Privileged Permission - Read/Write, User Permission- No Access*/
#define MMU_AP_PRV_RW_USR_NA                     (0x0400)

/* Privileged Permission - Read/Write, User Permission- Read Only */
#define MMU_AP_PRV_RW_USR_RO                     (0x0800)

/* Both Privileged Permission and User  Permission - Read/Write*/
#define MMU_AP_PRV_RW_USR_RW                     (0x0C00)

/* Privileged Permission - Read Only, User  Permission- No Access*/
#define MMU_AP_PRV_RO_USR_NA                     (0x8400)

/*
** Macro to be used if the section is not to be executed and is
** read sensitive.
*/
#define MMU_SECTION_EXEC_NEVER                   (0x00000010)

/*****************************************************************************/
/*
** Structure for defining memory regions. 
** Assumed Virtual Address = Physical Address.
*/
typedef struct region {
    unsigned int pgType; /* Type of the Page (Section/ Super Section)*/
    unsigned int startAddr; /* Start Address of the page */
    unsigned int numPages;  /* Number of Pages in the region */
    unsigned int memAttrib; /* Memory Type and Cache Settings */
    unsigned int secureType; /* Security Type */
    unsigned int accsCtrl; /* Access Permissions for the page */
    unsigned int *masterPtPtr; /* Pointer to the Master Page table */
} REGION;

/****************************************************************************/
/*
** API prototypes for configuring ARMv7a MMU.
*/
extern void MMUInit(unsigned int *masterPt);
extern void MMUMemRegionMap(REGION *region);
extern void MMUEnable(unsigned int *masterPt);

#ifdef __cplusplus
}
#endif
#endif /* __MMU_H__ */
