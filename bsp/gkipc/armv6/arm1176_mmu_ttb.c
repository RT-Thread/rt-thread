/*
********************************************************************************
********************************************************************************
**
** \file        ./boot/startup/src/arm1176_mmu_ttb.c
**
** \version     $Id: arm1176_mmu_ttb.c 5280 2011-02-21 16:39:28Z wlaris $
**
** \brief       ARM1176 MMU page table.
**
** This files contains ARM1176 specific MMU page table variables.
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE SEMICONDUCTOR
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS.
**
********************************************************************************
********************************************************************************
*/
#include <stdint.h>
#include "arm1176_mmu_ttb.h"

#define ARM1176_MMU_TTB_ALIGNMENT 14
#define ARM1176_RVS_ALIGN(bits) __align(1UL<<bits)
#define ARM1176_GCC_ALIGN(bits) __attribute__((aligned(1UL<<bits)))

#if !defined(__GNUC__)
#define ARM1176_MMU_ALIGN_PRE ARM1176_RVS_ALIGN(ARM1176_MMU_TTB_ALIGNMENT)
#endif

#if defined(__GNUC__)
#define ARM1176_MMU_ALIGN_POST ARM1176_GCC_ALIGN(ARM1176_MMU_TTB_ALIGNMENT)
#endif

#if defined(__LINT__)
#undef ARM1176_RVS_ALIGN
#define ARM1176_RVS_ALIGN(bits)
#undef ARM1176_GCC_ALIGN
#define ARM1176_GCC_ALIGN(bits)
#endif

/*lint -save -e785 */

#if !defined(__GNUC__)

    ARM1176_RVS_ALIGN(ARM1176_MMU_TTB_ALIGNMENT)
    uint32_t ARM1176_MMU_ttb0[ARM1176_MMU_TTB_ENTRIES] __attribute__ ((section(".nocache_buffer"))) = { 0x000011E2UL };

    ARM1176_RVS_ALIGN(ARM1176_MMU_TTB_ALIGNMENT)
    uint32_t ARM1176_MMU_ttb1[ARM1176_MMU_TTB_ENTRIES] __attribute__ ((section(".nocache_buffer"))) = { 0x000011E2UL };

#endif

#if defined(__GNUC__)

    uint32_t ARM1176_MMU_ttb0[ARM1176_MMU_TTB_ENTRIES]
    ARM1176_GCC_ALIGN(ARM1176_MMU_TTB_ALIGNMENT) __attribute__ ((section(".nocache_buffer"))) = { 0x000011E2UL };

    uint32_t ARM1176_MMU_ttb1[ARM1176_MMU_TTB_ENTRIES]
    ARM1176_GCC_ALIGN(ARM1176_MMU_TTB_ALIGNMENT) __attribute__ ((section(".nocache_buffer"))) = { 0x000011E2UL };

#endif

/*lint -restore */
