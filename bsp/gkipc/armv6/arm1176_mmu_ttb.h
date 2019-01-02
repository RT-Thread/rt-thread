/*
********************************************************************************
********************************************************************************
**
** \file        ./boot/startup/src/arm1176_mmu_ttb.h
**
** \version     $Id: arm1176_mmu_ttb.h 5280 2011-02-21 16:39:28Z wlaris $
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
#ifndef STARTUP_ARM1176_MMU_TTB_H
#define STARTUP_ARM1176_MMU_TTB_H

#define ARM1176_MMU_TTB_ENTRIES 4096

#define ARM1176_MMU_TTB_NUMS    8

#define ARM1176_1MB_NOCACHE_BUFFER      0x00000DE6  // non-cachable/bufferable
#define ARM1176_1MB_CACHE_NOBUFFER      0x00000DEA  // cachable/non-bufferable
#define ARM1176_1MB_CACHE_BUFFER        0x00000DEE  // cachable/bufferable
#define ARM1176_1MB_NOCACHE_NOBUFFER    0x00000DE2  // non-cachable/non-bufferable
#define ARM1176_1MB_NORMAL_NOCACHE      0x00001DE2  // Normal memory, non-cachable/non-bufferable
#define ARM1176_1MB_CACHE_BUFFER_RO     0x000011EE  // cachable/bufferable read-only
#define ARM1176_1MB_NOCACHE_NOBUFFER_RO 0x000011E2  // non-cachable/non-bufferable read-only
#endif
