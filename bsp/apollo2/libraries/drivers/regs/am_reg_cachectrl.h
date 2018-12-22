//*****************************************************************************
//
//  am_reg_cachectrl.h
//! @file
//!
//! @brief Register macros for the CACHECTRL module
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_REG_CACHECTRL_H
#define AM_REG_CACHECTRL_H

//*****************************************************************************
//
// Instance finder. (1 instance(s) available)
//
//*****************************************************************************
#define AM_REG_CACHECTRL_NUM_MODULES                 1
#define AM_REG_CACHECTRLn(n) \
    (REG_CACHECTRL_BASEADDR + 0x00001000 * n)

//*****************************************************************************
//
// Register offsets.
//
//*****************************************************************************
#define AM_REG_CACHECTRL_CACHECFG_O                  0x00000000
#define AM_REG_CACHECTRL_FLASHCFG_O                  0x00000004
#define AM_REG_CACHECTRL_CACHECTRL_O                 0x00000008
#define AM_REG_CACHECTRL_NCR0START_O                 0x00000010
#define AM_REG_CACHECTRL_NCR0END_O                   0x00000014
#define AM_REG_CACHECTRL_NCR1START_O                 0x00000018
#define AM_REG_CACHECTRL_NCR1END_O                   0x0000001C
#define AM_REG_CACHECTRL_CACHEMODE_O                 0x00000030
#define AM_REG_CACHECTRL_DMON0_O                     0x00000040
#define AM_REG_CACHECTRL_DMON1_O                     0x00000044
#define AM_REG_CACHECTRL_DMON2_O                     0x00000048
#define AM_REG_CACHECTRL_DMON3_O                     0x0000004C
#define AM_REG_CACHECTRL_IMON0_O                     0x00000050
#define AM_REG_CACHECTRL_IMON1_O                     0x00000054
#define AM_REG_CACHECTRL_IMON2_O                     0x00000058
#define AM_REG_CACHECTRL_IMON3_O                     0x0000005C

//*****************************************************************************
//
// CACHECTRL_CACHECFG - Flash Cache Control Register
//
//*****************************************************************************
// Enable Cache Monitoring Stats.  Only enable this for debug/performance
// analysis since it will consume additional power.  See IMON/DMON registers for
// data.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR_S   24
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR_M   0x01000000
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR(n)  (((uint32_t)(n) << 24) & 0x01000000)

// Enable clock gating of entire cache data array subsystem.  This should be
// enabled for normal operation.
#define AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE_S     20
#define AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE_M     0x00100000
#define AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE(n)    (((uint32_t)(n) << 20) & 0x00100000)

// Unused.  Should be left at default value.
#define AM_REG_CACHECTRL_CACHECFG_SMDLY_S            16
#define AM_REG_CACHECTRL_CACHECFG_SMDLY_M            0x000F0000
#define AM_REG_CACHECTRL_CACHECFG_SMDLY(n)           (((uint32_t)(n) << 16) & 0x000F0000)

// Unused.  Should be left at default value.
#define AM_REG_CACHECTRL_CACHECFG_DLY_S              12
#define AM_REG_CACHECTRL_CACHECFG_DLY_M              0x0000F000
#define AM_REG_CACHECTRL_CACHECFG_DLY(n)             (((uint32_t)(n) << 12) & 0x0000F000)

// Enable LS (light sleep) of cache RAMs.  This should not be enabled for normal
// operation.  When this bit is set, the cache's RAMS will be put into light
// sleep mode while inactive.  NOTE:  if the cache is actively used, this may
// have an adverse affect on power since entering/exiting LS mode may consume
// more power than would be saved.
#define AM_REG_CACHECTRL_CACHECFG_CACHE_LS_S         11
#define AM_REG_CACHECTRL_CACHECFG_CACHE_LS_M         0x00000800
#define AM_REG_CACHECTRL_CACHECFG_CACHE_LS(n)        (((uint32_t)(n) << 11) & 0x00000800)

// Enable clock gating of individual cache RAMs.  This bit should be enabled for
// normal operation for lowest power consumption.
#define AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE_S    10
#define AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE_M    0x00000400
#define AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE(n)   (((uint32_t)(n) << 10) & 0x00000400)

// Enable Flash Data Caching.  When set to 1, all instruction accesses to flash
// will be cached.
#define AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE_S    9
#define AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE_M    0x00000200
#define AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE(n)   (((uint32_t)(n) << 9) & 0x00000200)

// Enable Flash Instruction Caching.  When set to 1, all instruction accesses to
// flash will be cached.
#define AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE_S    8
#define AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE_M    0x00000100
#define AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE(n)   (((uint32_t)(n) << 8) & 0x00000100)

// Bitfield should always be programmed to 0.
#define AM_REG_CACHECTRL_CACHECFG_SERIAL_S           7
#define AM_REG_CACHECTRL_CACHECFG_SERIAL_M           0x00000080
#define AM_REG_CACHECTRL_CACHECFG_SERIAL(n)          (((uint32_t)(n) << 7) & 0x00000080)

// Sets the cache configuration.  Only a single configuration of 0x5 is valid.
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_S           4
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_M           0x00000070
#define AM_REG_CACHECTRL_CACHECFG_CONFIG(n)          (((uint32_t)(n) << 4) & 0x00000070)
#define AM_REG_CACHECTRL_CACHECFG_CONFIG_W2_128B_512E 0x00000050

// Enable Non-cacheable region 1.  See the NCR1 registers to set the region
// boundaries and size.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1_S       3
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1_M       0x00000008
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1(n)      (((uint32_t)(n) << 3) & 0x00000008)

// Enable Non-cacheable region 0.  See the NCR0 registers to set the region
// boundaries and size.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0_S       2
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0_M       0x00000004
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0(n)      (((uint32_t)(n) << 2) & 0x00000004)

// Sets the cache replacement policy.  0=LRR (least recently replaced), 1=LRU
// (least recently used).  LRR minimizes writes to the TAG SRAM and is
// recommended.
#define AM_REG_CACHECTRL_CACHECFG_LRU_S              1
#define AM_REG_CACHECTRL_CACHECFG_LRU_M              0x00000002
#define AM_REG_CACHECTRL_CACHECFG_LRU(n)             (((uint32_t)(n) << 1) & 0x00000002)

// Enables the main flash cache controller logic and enables power to the cache
// RAMs.  Instruction and Data caching need to be enabled independently using
// the ICACHE_ENABLE and DCACHE_ENABLE bits.
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_S           0
#define AM_REG_CACHECTRL_CACHECFG_ENABLE_M           0x00000001
#define AM_REG_CACHECTRL_CACHECFG_ENABLE(n)          (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CACHECTRL_FLASHCFG - Flash Control Register
//
//*****************************************************************************
// Sets read waitstates for flash accesses (in clock cycles).  This should be
// left at the default value for normal flash operation.
#define AM_REG_CACHECTRL_FLASHCFG_RD_WAIT_S          0
#define AM_REG_CACHECTRL_FLASHCFG_RD_WAIT_M          0x00000007
#define AM_REG_CACHECTRL_FLASHCFG_RD_WAIT(n)         (((uint32_t)(n) << 0) & 0x00000007)

//*****************************************************************************
//
// CACHECTRL_CACHECTRL - Cache Control
//
//*****************************************************************************
// Enable Flash Sleep Mode.  After writing this bit, the flash instance 1 will
// enter a low-power mode until the CPU writes the SLM_DISABLE bit or a flash
// access occurs.  Wake from SLM requires ~5us, so this should only be set if
// the flash will not be accessed for reasonably long time.
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_ENABLE_S 10
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_ENABLE_M 0x00000400
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_ENABLE(n) (((uint32_t)(n) << 10) & 0x00000400)

// Disable Flash Sleep Mode.  Allows CPU to manually disable SLM mode.
// Performing a flash read will also wake the array.
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_DISABLE_S 9
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_DISABLE_M 0x00000200
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_DISABLE(n) (((uint32_t)(n) << 9) & 0x00000200)

// Flash Sleep Mode Status.  When 1, flash instance 1 is asleep.
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_STATUS_S 8
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_STATUS_M 0x00000100
#define AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_STATUS(n) (((uint32_t)(n) << 8) & 0x00000100)

// Enable Flash Sleep Mode.  After writing this bit, the flash instance 0 will
// enter a low-power mode until the CPU writes the SLM_DISABLE bit or a flash
// access occurs.  Wake from SLM requires ~5us, so this should only be set if
// the flash will not be accessed for reasonably long time.
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_ENABLE_S 6
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_ENABLE_M 0x00000040
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_ENABLE(n) (((uint32_t)(n) << 6) & 0x00000040)

// Disable Flash Sleep Mode.  Allows CPU to manually disable SLM mode.
// Performing a flash read will also wake the array.
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_DISABLE_S 5
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_DISABLE_M 0x00000020
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_DISABLE(n) (((uint32_t)(n) << 5) & 0x00000020)

// Flash Sleep Mode Status.  When 1, flash instance 0 is asleep.
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_STATUS_S 4
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_STATUS_M 0x00000010
#define AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_STATUS(n) (((uint32_t)(n) << 4) & 0x00000010)

// Cache Ready Status.  A value of 1 indicates the cache is enabled and not
// processing an invalidate operation.
#define AM_REG_CACHECTRL_CACHECTRL_CACHE_READY_S     2
#define AM_REG_CACHECTRL_CACHECTRL_CACHE_READY_M     0x00000004
#define AM_REG_CACHECTRL_CACHECTRL_CACHE_READY(n)    (((uint32_t)(n) << 2) & 0x00000004)

// Writing a 1 to this bitfield will reset the cache monitor statistics
// (DMON0-3, IMON0-3).  Statistic gathering can be paused/stopped by disabling
// the MONITOR_ENABLE bit in CACHECFG, which will maintain the count values
// until the stats are reset by writing this bitfield.
#define AM_REG_CACHECTRL_CACHECTRL_RESET_STAT_S      1
#define AM_REG_CACHECTRL_CACHECTRL_RESET_STAT_M      0x00000002
#define AM_REG_CACHECTRL_CACHECTRL_RESET_STAT(n)     (((uint32_t)(n) << 1) & 0x00000002)
#define AM_REG_CACHECTRL_CACHECTRL_RESET_STAT_CLEAR  0x00000002

// Writing a 1 to this bitfield invalidates the flash cache contents.
#define AM_REG_CACHECTRL_CACHECTRL_INVALIDATE_S      0
#define AM_REG_CACHECTRL_CACHECTRL_INVALIDATE_M      0x00000001
#define AM_REG_CACHECTRL_CACHECTRL_INVALIDATE(n)     (((uint32_t)(n) << 0) & 0x00000001)
#define AM_REG_CACHECTRL_CACHECTRL_INVALIDATE_GO     0x00000001

//*****************************************************************************
//
// CACHECTRL_NCR0START - Flash Cache Noncachable Region 0 Start Address.
//
//*****************************************************************************
// Start address for non-cacheable region 0.  The physical address of the start
// of this region should be programmed to this register and must be aligned to a
// 16-byte boundary (thus the lower 4 address bits are unused).
#define AM_REG_CACHECTRL_NCR0START_ADDR_S            4
#define AM_REG_CACHECTRL_NCR0START_ADDR_M            0x000FFFF0
#define AM_REG_CACHECTRL_NCR0START_ADDR(n)           (((uint32_t)(n) << 4) & 0x000FFFF0)

//*****************************************************************************
//
// CACHECTRL_NCR0END - Flash Cache Noncachable Region 0 End
//
//*****************************************************************************
// End address for non-cacheable region 0.  The physical address of the end of
// this region should be programmed to this register and must be aligned to a
// 16-byte boundary (thus the lower 4 address bits are unused).
#define AM_REG_CACHECTRL_NCR0END_ADDR_S              4
#define AM_REG_CACHECTRL_NCR0END_ADDR_M              0x000FFFF0
#define AM_REG_CACHECTRL_NCR0END_ADDR(n)             (((uint32_t)(n) << 4) & 0x000FFFF0)

//*****************************************************************************
//
// CACHECTRL_NCR1START - Flash Cache Noncachable Region 1 Start
//
//*****************************************************************************
// Start address for non-cacheable region 1.  The physical address of the start
// of this region should be programmed to this register and must be aligned to a
// 16-byte boundary (thus the lower 4 address bits are unused).
#define AM_REG_CACHECTRL_NCR1START_ADDR_S            4
#define AM_REG_CACHECTRL_NCR1START_ADDR_M            0x000FFFF0
#define AM_REG_CACHECTRL_NCR1START_ADDR(n)           (((uint32_t)(n) << 4) & 0x000FFFF0)

//*****************************************************************************
//
// CACHECTRL_NCR1END - Flash Cache Noncachable Region 1 End
//
//*****************************************************************************
// End address for non-cacheable region 1.  The physical address of the end of
// this region should be programmed to this register and must be aligned to a
// 16-byte boundary (thus the lower 4 address bits are unused).
#define AM_REG_CACHECTRL_NCR1END_ADDR_S              4
#define AM_REG_CACHECTRL_NCR1END_ADDR_M              0x000FFFF0
#define AM_REG_CACHECTRL_NCR1END_ADDR(n)             (((uint32_t)(n) << 4) & 0x000FFFF0)

//*****************************************************************************
//
// CACHECTRL_CACHEMODE - Flash Cache Mode Register.  Used to trim
// performance/power.
//
//*****************************************************************************
// Disallow Simultaneous Data RAM reads (from 2 line hits on each bus).  Value
// should be left at zero for optimal performance.
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE6_S       5
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE6_M       0x00000020
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE6(n)      (((uint32_t)(n) << 5) & 0x00000020)

// Disallow Data RAM reads (from line hits) during lookup read ops.  Value
// should be left at zero for optimal performance.
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE5_S       4
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE5_M       0x00000010
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE5(n)      (((uint32_t)(n) << 4) & 0x00000010)

// Disallow Data RAM reads (from line hits) on tag RAM fill cycles. Value should
// be left at zero for optimal performance.
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE4_S       3
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE4_M       0x00000008
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE4(n)      (((uint32_t)(n) << 3) & 0x00000008)

// Disallow cache data RAM writes on data RAM read cycles. Value should be left
// at zero for optimal performance.
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE3_S       2
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE3_M       0x00000004
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE3(n)      (((uint32_t)(n) << 2) & 0x00000004)

// Disallow cache data RAM writes on tag RAM read cycles. Value should be left
// at zero for optimal performance.
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE2_S       1
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE2_M       0x00000002
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE2(n)      (((uint32_t)(n) << 1) & 0x00000002)

// Disallow cache data RAM writes on tag RAM fill cycles. Value should be left
// at zero for optimal performance.
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE1_S       0
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE1_M       0x00000001
#define AM_REG_CACHECTRL_CACHEMODE_THROTTLE1(n)      (((uint32_t)(n) << 0) & 0x00000001)

//*****************************************************************************
//
// CACHECTRL_DMON0 - Data Cache Total Accesses
//
//*****************************************************************************
// Total accesses to data cache
#define AM_REG_CACHECTRL_DMON0_DACCESS_COUNT_S       0
#define AM_REG_CACHECTRL_DMON0_DACCESS_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON0_DACCESS_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_DMON1 - Data Cache Tag Lookups
//
//*****************************************************************************
// Total tag lookups from data cache
#define AM_REG_CACHECTRL_DMON1_DLOOKUP_COUNT_S       0
#define AM_REG_CACHECTRL_DMON1_DLOOKUP_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON1_DLOOKUP_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_DMON2 - Data Cache Hits
//
//*****************************************************************************
// Cache hits from lookup operations
#define AM_REG_CACHECTRL_DMON2_DHIT_COUNT_S          0
#define AM_REG_CACHECTRL_DMON2_DHIT_COUNT_M          0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON2_DHIT_COUNT(n)         (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_DMON3 - Data Cache Line Hits
//
//*****************************************************************************
// Cache hits from line cache
#define AM_REG_CACHECTRL_DMON3_DLINE_COUNT_S         0
#define AM_REG_CACHECTRL_DMON3_DLINE_COUNT_M         0xFFFFFFFF
#define AM_REG_CACHECTRL_DMON3_DLINE_COUNT(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON0 - Instruction Cache Total Accesses
//
//*****************************************************************************
// Total accesses to Instruction cache
#define AM_REG_CACHECTRL_IMON0_IACCESS_COUNT_S       0
#define AM_REG_CACHECTRL_IMON0_IACCESS_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON0_IACCESS_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON1 - Instruction Cache Tag Lookups
//
//*****************************************************************************
// Total tag lookups from Instruction cache
#define AM_REG_CACHECTRL_IMON1_ILOOKUP_COUNT_S       0
#define AM_REG_CACHECTRL_IMON1_ILOOKUP_COUNT_M       0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON1_ILOOKUP_COUNT(n)      (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON2 - Instruction Cache Hits
//
//*****************************************************************************
// Cache hits from lookup operations
#define AM_REG_CACHECTRL_IMON2_IHIT_COUNT_S          0
#define AM_REG_CACHECTRL_IMON2_IHIT_COUNT_M          0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON2_IHIT_COUNT(n)         (((uint32_t)(n) << 0) & 0xFFFFFFFF)

//*****************************************************************************
//
// CACHECTRL_IMON3 - Instruction Cache Line Hits
//
//*****************************************************************************
// Cache hits from line cache
#define AM_REG_CACHECTRL_IMON3_ILINE_COUNT_S         0
#define AM_REG_CACHECTRL_IMON3_ILINE_COUNT_M         0xFFFFFFFF
#define AM_REG_CACHECTRL_IMON3_ILINE_COUNT(n)        (((uint32_t)(n) << 0) & 0xFFFFFFFF)

#endif // AM_REG_CACHECTRL_H
