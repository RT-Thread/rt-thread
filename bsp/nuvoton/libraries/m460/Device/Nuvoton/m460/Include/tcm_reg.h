/**************************************************************************//**
 * @file     tcm_reg.h
 * @version  V1.00
 * @brief    Tight Couple Memory Controller
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __TCM_REG_H__
#define __TCM_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Tight Couple Memory Controller -------------------------*/
/**
    @addtogroup TCM Tight Couple Memory Controller(TCM)
    Memory Mapped Structure for TCM Controller
@{ */

typedef struct
{


    /**
     * @var TCM_T::GCTL
     * Offset: 0x00  Tight Couple Memory Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |WAYNUM    |Number of TCM ways configured (Read Only)
     * |        |          |00 = 1 way, NUM_WAY == 1
     * |        |          |01 = 2 way, NUM_WAY == 2
     * |        |          |10 = 3 way, NUM_WAY == 3
     * |        |          |11 = 4 way, NUM_WAY == 4
     * |[3:2]   |WAYSIZE   |Size of each TCM ways (Read Only)
     * |        |          |00 = 1 Kbyte (WAY_SIZE == 0)
     * |        |          |01 = 2 Kbyte (WAY_SIZE == 1)
     * |        |          |10 = 4 Kbyte (WAY_SIZE == 2)
     * |        |          |11 = 8 Kbyte (WAY_SIZE == 3)
     * |[4]     |CACHECFG  |Cache Configuration Bit
     * |        |          |(default: 0) When a TCM way is configured as a cache-way, setting this bit to 1 enables the write-back/write-allocate cache management policy
     * |        |          |Otherwise, a 0 in this bit enables the write-through/no-write-allocate policy
     * |        |          |This bit can be modified only when none of the TCM ways is enabled as a cache-way.
     * |[5]     |FIXAZERO  |Fix Auto Zero (Read Only)
     * |        |          |(default: 0) Asserting this bit to 1 to prohibit update of the AutoZero bits in the TCM way configuration registers by the core
     * |        |          |The default 0 setting allows them to be modified
     * |        |          |This bit itself is not modifiable by the core
     * |        |          |Its value can only be changed during the chip configuration stage when the PORESETn input is HIGH and the SYSRESETn input is LOW
     * |[8]     |WAY0EN    |TCM way0 Enable Contorl
     * |        |          |0 = TCM way0 Disabled.
     * |        |          |1 = TCM way0 Enabled.
     * |        |          |When this bit toggles, the corresponding TCM way is enabled/disabled according to the CacheMode bit in the TCM_WayX_Config_Registers
     * |        |          |Note that a TCM way is not fully enabled until the pre-/post-condition is met
     * |        |          |Specifically, when CacheMode bit is 0, the TCM way is not fully enabled until the PreLoading bit is 0
     * |        |          |It is not fully disabled until both AutoFlushing and AutoZeroing bits are 0
     * |        |          |When CacheMode bit is 1, the TCM way is not fully enabled until the Invalidating bit is 0, and not fully disabled until the AutoZeroing bit is 0.
     * |[9]     |WAY1EN    |TCM way1 Enable Contorl
     * |        |          |0 = TCM way1 Disabled.
     * |        |          |1 = TCM way1 Enabled.
     * |[10]    |WAY2EN    |TCM way2 Enable Contorl
     * |        |          |0 = TCM way2 Disabled.
     * |        |          |1 = TCM way2 Enabled.
     * |[11]    |WAY3EN    |TCM way3 Enable Contorl
     * |        |          |0 = TCM way3 Disabled.
     * |        |          |1 = TCM way3 Enabled.
     * @var TCM_T::W0CTL
     * Offset: 0x10  Tight Couple Memory Way0 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CACHEMD   |Cache Mode Enable Bit
     * |        |          |0 = TCM as Local Memory Block (LMB)
     * |        |          |1 = TCM as Cache
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |[1]     |PRELD     |Pre-load the TCM way
     * |        |          |When CacheMode bit is clear, setting this bit to 1 instructs TCM control to pre-load the TCM way according to the size/addr setting in the corresponding DMA register
     * |        |          |The TCM way is not enabled as a LMB until the preloading operation is completed
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[2]     |PRELDST   |Pre-loading Status
     * |        |          |This is a status bit that returns 1 when the pre-loading of the TCM way (as a LMB) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a LMB
     * |        |          |An access request to the would-be-mapped address range will be wait-stated to avoid the multi-caching scenario that can happens when another TCM way is enabled as a cache-way and the requested target can become cached there because the I-/D-bus request is not blocked.
     * |[3]     |INVALST   |Invalidation Status
     * |        |          |This is a status bit that returns 1 when the pre-enabling invalidation of the TCM way (as a cache-way) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a cache-way
     * |        |          |However, since no multi-caching scenario can occur, no any incoming request is blocked due the on-going invalidation.
     * |[4]     |AFLUSH    |auto-flush the data array
     * |        |          |When CacheMode is clear, setting this bit to 1 instructs TCM control to auto-flush the data array according to the size/addr setting in the corresponding DMA register
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |The data array is always fully flushed when a TCM way is disabled from a write-back/write-allocate cache way
     * |        |          |The TCM way is not fully disabled until the flushing operation is completed
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[5]     |AFLUSHST  |This is a status bit that returns 1 when auto-flushing of the TCM way is on-going. The auto-flushing is triggered when the TCM way is disabled as a LMB with the AutoFlush bit set, or when the TCM way is disabled as a cache-way and the cache is configured with write-back/write-allocate. Until this bit is clear, a TCM way is not fully disabled. While it is set, accesses to targets residing in the TCM way are wait-stated. This can occur when the TCM way is configured as a LMB and the target falls in the mapped address range, or when the TCM way is configured as a cache-way in general. The blocking is to avoid memory consistency issue when a late arrival write access, whose target data has been flushed out to the memory.
     * |[6]     |AZERO     |Setting this bit to 1 instructs TCM control to auto-zero a TCM way when it is to be disabled as either a LMB or a cache-way. Auto-zeroing of a LMB is not controlled by the size/addr setting in DMA_control register. The whole TCM way is zerou2019ed out. This bit is reset-configurable like FixAutoZero bit when PORESETn is high and SYSRESETn is low. After that, it is modifiable by the core only if the FixAutoZero bit is clear and the corresponding WayEnable bit is also clear.
     * |[7]     |AZEROST   |Auto-zeroing Status
     * |        |          |This is a status bit that returns 1 when auto-zeroing is on-going
     * |        |          |Similar to AutoFlushing bit
     * |        |          |Accesses with target potentially residing in the TCM way are all wait-stated.
     * |[8]     |XOMERROR  |XOM Error Flag
     * |        |          |This is a status bit that returns 1 when the TCM way is configured as a LMB and is currently mapping a XOM region
     * |        |          |This bit is read-only by the core
     * |        |          |It is set/cleared automatically by the TCM logic.
     * |[9]     |ERROR     |Operating Error Flag
     * |        |          |0 = No error is recored
     * |        |          |1 = An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way).
     * |        |          |An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way)
     * |        |          |The operation didnu2019t complete successfully
     * |        |          |No error can occur to invalidation or zeroing operation
     * |        |          |This bit is set by TCM logic and can only be cleared by the core.
     * |[23:13] |LMBTAG    |LMB TAG Base Address
     * |        |          |When TCM way configure as LMB used, these bits define the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB.
     * |        |          |Note: This field can be modified only when the corresponding WAYxEN bit is clear.
     * |        |          |(default: 0) When CacheMode is clear, these bits store the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB
     * |        |          |Depending on LMBSize setting, some of the bits are ignored.
     * |        |          |LMBSize == 1K : all bits used
     * |        |          |LMBSize == 2K : bit 10 ignored
     * |        |          |LMBSize == 4K : bit 11:10 ignored
     * |        |          |LMBSize == 8K : bit 12:10 ignored
     * @var TCM_T::W1CTL
     * Offset: 0x14  Tight Couple Memory Way1 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CACHEMD   |Cache Mode Enable Bit
     * |        |          |0 = TCM as Local Memory Block (LMB)
     * |        |          |1 = TCM as Cache
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |[1]     |PRELD     |Pre-load the TCM way
     * |        |          |When CacheMode bit is clear, setting this bit to 1 instructs TCM control to pre-load the TCM way according to the size/addr setting in the corresponding DMA register
     * |        |          |The TCM way is not enabled as a LMB until the preloading operation is completed
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[2]     |PRELDST   |Pre-loading Status
     * |        |          |This is a status bit that returns 1 when the pre-loading of the TCM way (as a LMB) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a LMB
     * |        |          |An access request to the would-be-mapped address range will be wait-stated to avoid the multi-caching scenario that can happens when another TCM way is enabled as a cache-way and the requested target can become cached there because the I-/D-bus request is not blocked.
     * |[3]     |INVALST   |Invalidation Status
     * |        |          |This is a status bit that returns 1 when the pre-enabling invalidation of the TCM way (as a cache-way) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a cache-way
     * |        |          |However, since no multi-caching scenario can occur, no any incoming request is blocked due the on-going invalidation.
     * |[4]     |AFLUSH    |auto-flush the data array
     * |        |          |When CacheMode is clear, setting this bit to 1 instructs TCM control to auto-flush the data array according to the size/addr setting in the corresponding DMA register
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |The data array is always fully flushed when a TCM way is disabled from a write-back/write-allocate cache way
     * |        |          |The TCM way is not fully disabled until the flushing operation is completed
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[5]     |AFLUSHST  |This is a status bit that returns 1 when auto-flushing of the TCM way is on-going. The auto-flushing is triggered when the TCM way is disabled as a LMB with the AutoFlush bit set, or when the TCM way is disabled as a cache-way and the cache is configured with write-back/write-allocate. Until this bit is clear, a TCM way is not fully disabled. While it is set, accesses to targets residing in the TCM way are wait-stated. This can occur when the TCM way is configured as a LMB and the target falls in the mapped address range, or when the TCM way is configured as a cache-way in general. The blocking is to avoid memory consistency issue when a late arrival write access, whose target data has been flushed out to the memory.
     * |[6]     |AZERO     |Setting this bit to 1 instructs TCM control to auto-zero a TCM way when it is to be disabled as either a LMB or a cache-way. Auto-zeroing of a LMB is not controlled by the size/addr setting in DMA_control register. The whole TCM way is zerou2019ed out. This bit is reset-configurable like FixAutoZero bit when PORESETn is high and SYSRESETn is low. After that, it is modifiable by the core only if the FixAutoZero bit is clear and the corresponding WayEnable bit is also clear.
     * |[7]     |AZEROST   |Auto-zeroing Status
     * |        |          |This is a status bit that returns 1 when auto-zeroing is on-going
     * |        |          |Similar to AutoFlushing bit
     * |        |          |Accesses with target potentially residing in the TCM way are all wait-stated.
     * |[8]     |XOMERROR  |XOM Error Flag
     * |        |          |This is a status bit that returns 1 when the TCM way is configured as a LMB and is currently mapping a XOM region
     * |        |          |This bit is read-only by the core
     * |        |          |It is set/cleared automatically by the TCM logic.
     * |[9]     |ERROR     |Operating Error Flag
     * |        |          |0 = No error is recored
     * |        |          |1 = An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way).
     * |        |          |An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way)
     * |        |          |The operation didnu2019t complete successfully
     * |        |          |No error can occur to invalidation or zeroing operation
     * |        |          |This bit is set by TCM logic and can only be cleared by the core.
     * |[23:13] |LMBTAG    |LMB TAG Base Address
     * |        |          |When TCM way configure as LMB used, these bits define the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB.
     * |        |          |Note: This field can be modified only when the corresponding WAYxEN bit is clear.
     * |        |          |(default: 0) When CacheMode is clear, these bits store the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB
     * |        |          |Depending on LMBSize setting, some of the bits are ignored.
     * |        |          |LMBSize == 1K : all bits used
     * |        |          |LMBSize == 2K : bit 10 ignored
     * |        |          |LMBSize == 4K : bit 11:10 ignored
     * |        |          |LMBSize == 8K : bit 12:10 ignored
     * @var TCM_T::W2CTL
     * Offset: 0x18  Tight Couple Memory Way2 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CACHEMD   |Cache Mode Enable Bit
     * |        |          |0 = TCM as Local Memory Block (LMB)
     * |        |          |1 = TCM as Cache
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |[1]     |PRELD     |Pre-load the TCM way
     * |        |          |When CacheMode bit is clear, setting this bit to 1 instructs TCM control to pre-load the TCM way according to the size/addr setting in the corresponding DMA register
     * |        |          |The TCM way is not enabled as a LMB until the preloading operation is completed
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[2]     |PRELDST   |Pre-loading Status
     * |        |          |This is a status bit that returns 1 when the pre-loading of the TCM way (as a LMB) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a LMB
     * |        |          |An access request to the would-be-mapped address range will be wait-stated to avoid the multi-caching scenario that can happens when another TCM way is enabled as a cache-way and the requested target can become cached there because the I-/D-bus request is not blocked.
     * |[3]     |INVALST   |Invalidation Status
     * |        |          |This is a status bit that returns 1 when the pre-enabling invalidation of the TCM way (as a cache-way) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a cache-way
     * |        |          |However, since no multi-caching scenario can occur, no any incoming request is blocked due the on-going invalidation.
     * |[4]     |AFLUSH    |auto-flush the data array
     * |        |          |When CacheMode is clear, setting this bit to 1 instructs TCM control to auto-flush the data array according to the size/addr setting in the corresponding DMA register
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |The data array is always fully flushed when a TCM way is disabled from a write-back/write-allocate cache way
     * |        |          |The TCM way is not fully disabled until the flushing operation is completed
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[5]     |AFLUSHST  |This is a status bit that returns 1 when auto-flushing of the TCM way is on-going. The auto-flushing is triggered when the TCM way is disabled as a LMB with the AutoFlush bit set, or when the TCM way is disabled as a cache-way and the cache is configured with write-back/write-allocate. Until this bit is clear, a TCM way is not fully disabled. While it is set, accesses to targets residing in the TCM way are wait-stated. This can occur when the TCM way is configured as a LMB and the target falls in the mapped address range, or when the TCM way is configured as a cache-way in general. The blocking is to avoid memory consistency issue when a late arrival write access, whose target data has been flushed out to the memory.
     * |[6]     |AZERO     |Setting this bit to 1 instructs TCM control to auto-zero a TCM way when it is to be disabled as either a LMB or a cache-way. Auto-zeroing of a LMB is not controlled by the size/addr setting in DMA_control register. The whole TCM way is zerou2019ed out. This bit is reset-configurable like FixAutoZero bit when PORESETn is high and SYSRESETn is low. After that, it is modifiable by the core only if the FixAutoZero bit is clear and the corresponding WayEnable bit is also clear.
     * |[7]     |AZEROST   |Auto-zeroing Status
     * |        |          |This is a status bit that returns 1 when auto-zeroing is on-going
     * |        |          |Similar to AutoFlushing bit
     * |        |          |Accesses with target potentially residing in the TCM way are all wait-stated.
     * |[8]     |XOMERROR  |XOM Error Flag
     * |        |          |This is a status bit that returns 1 when the TCM way is configured as a LMB and is currently mapping a XOM region
     * |        |          |This bit is read-only by the core
     * |        |          |It is set/cleared automatically by the TCM logic.
     * |[9]     |ERROR     |Operating Error Flag
     * |        |          |0 = No error is recored
     * |        |          |1 = An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way).
     * |        |          |An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way)
     * |        |          |The operation didnu2019t complete successfully
     * |        |          |No error can occur to invalidation or zeroing operation
     * |        |          |This bit is set by TCM logic and can only be cleared by the core.
     * |[23:13] |LMBTAG    |LMB TAG Base Address
     * |        |          |When TCM way configure as LMB used, these bits define the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB.
     * |        |          |Note: This field can be modified only when the corresponding WAYxEN bit is clear.
     * |        |          |(default: 0) When CacheMode is clear, these bits store the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB
     * |        |          |Depending on LMBSize setting, some of the bits are ignored.
     * |        |          |LMBSize == 1K : all bits used
     * |        |          |LMBSize == 2K : bit 10 ignored
     * |        |          |LMBSize == 4K : bit 11:10 ignored
     * |        |          |LMBSize == 8K : bit 12:10 ignored
     * @var TCM_T::W3CTL
     * Offset: 0x1C  Tight Couple Memory Way3 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CACHEMD   |Cache Mode Enable Bit
     * |        |          |0 = TCM as Local Memory Block (LMB)
     * |        |          |1 = TCM as Cache
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |[1]     |PRELD     |Pre-load the TCM way
     * |        |          |When CacheMode bit is clear, setting this bit to 1 instructs TCM control to pre-load the TCM way according to the size/addr setting in the corresponding DMA register
     * |        |          |The TCM way is not enabled as a LMB until the preloading operation is completed
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[2]     |PRELDST   |Pre-loading Status
     * |        |          |This is a status bit that returns 1 when the pre-loading of the TCM way (as a LMB) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a LMB
     * |        |          |An access request to the would-be-mapped address range will be wait-stated to avoid the multi-caching scenario that can happens when another TCM way is enabled as a cache-way and the requested target can become cached there because the I-/D-bus request is not blocked.
     * |[3]     |INVALST   |Invalidation Status
     * |        |          |This is a status bit that returns 1 when the pre-enabling invalidation of the TCM way (as a cache-way) is on-going
     * |        |          |Until this bit is clear, the TCM way is not fully enabled to serve I-/D-bus requests as a cache-way
     * |        |          |However, since no multi-caching scenario can occur, no any incoming request is blocked due the on-going invalidation.
     * |[4]     |AFLUSH    |auto-flush the data array
     * |        |          |When CacheMode is clear, setting this bit to 1 instructs TCM control to auto-flush the data array according to the size/addr setting in the corresponding DMA register
     * |        |          |When CacheMode is set, this bit has no meaning
     * |        |          |The data array is always fully flushed when a TCM way is disabled from a write-back/write-allocate cache way
     * |        |          |The TCM way is not fully disabled until the flushing operation is completed
     * |        |          |This bit can be modified only when the corresponding WayEnable bit is clear.
     * |[5]     |AFLUSHST  |This is a status bit that returns 1 when auto-flushing of the TCM way is on-going. The auto-flushing is triggered when the TCM way is disabled as a LMB with the AutoFlush bit set, or when the TCM way is disabled as a cache-way and the cache is configured with write-back/write-allocate. Until this bit is clear, a TCM way is not fully disabled. While it is set, accesses to targets residing in the TCM way are wait-stated. This can occur when the TCM way is configured as a LMB and the target falls in the mapped address range, or when the TCM way is configured as a cache-way in general. The blocking is to avoid memory consistency issue when a late arrival write access, whose target data has been flushed out to the memory.
     * |[6]     |AZERO     |Setting this bit to 1 instructs TCM control to auto-zero a TCM way when it is to be disabled as either a LMB or a cache-way. Auto-zeroing of a LMB is not controlled by the size/addr setting in DMA_control register. The whole TCM way is zerou2019ed out. This bit is reset-configurable like FixAutoZero bit when PORESETn is high and SYSRESETn is low. After that, it is modifiable by the core only if the FixAutoZero bit is clear and the corresponding WayEnable bit is also clear.
     * |[7]     |AZEROST   |Auto-zeroing Status
     * |        |          |This is a status bit that returns 1 when auto-zeroing is on-going
     * |        |          |Similar to AutoFlushing bit
     * |        |          |Accesses with target potentially residing in the TCM way are all wait-stated.
     * |[8]     |XOMERROR  |XOM Error Flag
     * |        |          |This is a status bit that returns 1 when the TCM way is configured as a LMB and is currently mapping a XOM region
     * |        |          |This bit is read-only by the core
     * |        |          |It is set/cleared automatically by the TCM logic.
     * |[9]     |ERROR     |Operating Error Flag
     * |        |          |0 = No error is recored
     * |        |          |1 = An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way).
     * |        |          |An AHB error occurred during the last pre-loading (for LMB) or auto-flushing operation (for LMB or cache-way)
     * |        |          |The operation didnu2019t complete successfully
     * |        |          |No error can occur to invalidation or zeroing operation
     * |        |          |This bit is set by TCM logic and can only be cleared by the core.
     * |[23:13] |LMBTAG    |LMB TAG Base Address
     * |        |          |When TCM way configure as LMB used, these bits define the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB.
     * |        |          |Note: This field can be modified only when the corresponding WAYxEN bit is clear.
     * |        |          |(default: 0) When CacheMode is clear, these bits store the base address of the mapped region
     * |        |          |This tag is compared against the incoming address to determine if the address hits in the LMB
     * |        |          |Depending on LMBSize setting, some of the bits are ignored.
     * |        |          |LMBSize == 1K : all bits used
     * |        |          |LMBSize == 2K : bit 10 ignored
     * |        |          |LMBSize == 4K : bit 11:10 ignored
     * |        |          |LMBSize == 8K : bit 12:10 ignored
     * @var TCM_T::W0DMACTL
     * Offset: 0x20  Tight Couple Memory Way0 DMA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMASIZE   |DMA Size Selection Bit
     * |        |          |This field indicate and size of moving external memory to LMB after DMA is trigged.
     * |        |          |000 = Full TCM way
     * |        |          |001 = 1/2 TCM way
     * |        |          |010 = 1/4 TCM way
     * |        |          |011 = 1/8 TCM way
     * |        |          |100 = 1/16 TCM way
     * |        |          |101 = 1/32 TCM way
     * |        |          |110 = 1/64 TCM way
     * |        |          |111 = 1/128 TCM way
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |        |          |(default: 0) When the embedded DMA engine is triggered for either LMB preloading or auto-flushing, this field defines the size of the operation according to the following table
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |[23:4]  |DMAADDR   |DMA starting RAM address
     * |        |          |When a LMB-related DMA operation is triggered, this field provides the starting RAM address of the operation
     * |        |          |Depending on the setting of the WaySize and DMASize, not all bits are used
     * |        |          |The following table lists the DMAAddr bits used to construct the base of the starting RAM address according to WaySize
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |        |          |WaySize / RAMBase 8K / {[23:13], 13u2019b0} 4K / {[23:12], 12u2019b0} 2K / {[23:11], 11u2019b0} 1K / {[23:10], 10u2019b0}
     * |        |          |The following table lists the DMAAddr bits used as the offset for the RAM starting address
     * |        |          |Note that the minimal DMA operation size is 16-byte (or 4-word).
     * |        |          |Offset WaySize
     * |        |          |DMASize 8K 4K 2K 1K
     * |        |          |0 - - - -
     * |        |          |1 [12] [11] [10] [9]
     * |        |          |2 [12:11] [11:10] [10:9] [9:8]
     * |        |          |3 [12:10] [11:9] [10:8] [9:7]
     * |        |          |4 [12:9] [11:8] [10:7] [9:6]
     * |        |          |5 [12:8] [11:7] [10:6] [9:5]
     * |        |          |6 [12:7] [11:6] [10:5] [9:4]
     * |        |          |7 [12:6] [11:5] [10:4] -
     * |[30]    |DMAFLUSH  |Flushing DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a flushing DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a preloading DMA is on-going, this bit is not modifiable.
     * |[31]    |DMAPRELD  |Preloading DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a preloading DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a flushing DMA is on-going, this bit is not modifiable.
     * @var TCM_T::W1DMACTL
     * Offset: 0x24  Tight Couple Memory Way1 DMA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMASIZE   |DMA Size Selection Bit
     * |        |          |This field indicate and size of moving external memory to LMB after DMA is trigged.
     * |        |          |000 = Full TCM way
     * |        |          |001 = 1/2 TCM way
     * |        |          |010 = 1/4 TCM way
     * |        |          |011 = 1/8 TCM way
     * |        |          |100 = 1/16 TCM way
     * |        |          |101 = 1/32 TCM way
     * |        |          |110 = 1/64 TCM way
     * |        |          |111 = 1/128 TCM way
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |        |          |(default: 0) When the embedded DMA engine is triggered for either LMB preloading or auto-flushing, this field defines the size of the operation according to the following table
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |[23:4]  |DMAADDR   |DMA starting RAM address
     * |        |          |When a LMB-related DMA operation is triggered, this field provides the starting RAM address of the operation
     * |        |          |Depending on the setting of the WaySize and DMASize, not all bits are used
     * |        |          |The following table lists the DMAAddr bits used to construct the base of the starting RAM address according to WaySize
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |        |          |WaySize / RAMBase 8K / {[23:13], 13u2019b0} 4K / {[23:12], 12u2019b0} 2K / {[23:11], 11u2019b0} 1K / {[23:10], 10u2019b0}
     * |        |          |The following table lists the DMAAddr bits used as the offset for the RAM starting address
     * |        |          |Note that the minimal DMA operation size is 16-byte (or 4-word).
     * |        |          |Offset WaySize
     * |        |          |DMASize 8K 4K 2K 1K
     * |        |          |0 - - - -
     * |        |          |1 [12] [11] [10] [9]
     * |        |          |2 [12:11] [11:10] [10:9] [9:8]
     * |        |          |3 [12:10] [11:9] [10:8] [9:7]
     * |        |          |4 [12:9] [11:8] [10:7] [9:6]
     * |        |          |5 [12:8] [11:7] [10:6] [9:5]
     * |        |          |6 [12:7] [11:6] [10:5] [9:4]
     * |        |          |7 [12:6] [11:5] [10:4] -
     * |[30]    |DMAFLUSH  |Flushing DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a flushing DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a preloading DMA is on-going, this bit is not modifiable.
     * |[31]    |DMAPRELD  |Preloading DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a preloading DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a flushing DMA is on-going, this bit is not modifiable.
     * @var TCM_T::W2DMACTL
     * Offset: 0x28  Tight Couple Memory Way2 DMA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMASIZE   |DMA Size Selection Bit
     * |        |          |This field indicate and size of moving external memory to LMB after DMA is trigged.
     * |        |          |000 = Full TCM way
     * |        |          |001 = 1/2 TCM way
     * |        |          |010 = 1/4 TCM way
     * |        |          |011 = 1/8 TCM way
     * |        |          |100 = 1/16 TCM way
     * |        |          |101 = 1/32 TCM way
     * |        |          |110 = 1/64 TCM way
     * |        |          |111 = 1/128 TCM way
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |        |          |(default: 0) When the embedded DMA engine is triggered for either LMB preloading or auto-flushing, this field defines the size of the operation according to the following table
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |[23:4]  |DMAADDR   |DMA starting RAM address
     * |        |          |When a LMB-related DMA operation is triggered, this field provides the starting RAM address of the operation
     * |        |          |Depending on the setting of the WaySize and DMASize, not all bits are used
     * |        |          |The following table lists the DMAAddr bits used to construct the base of the starting RAM address according to WaySize
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |        |          |WaySize / RAMBase 8K / {[23:13], 13u2019b0} 4K / {[23:12], 12u2019b0} 2K / {[23:11], 11u2019b0} 1K / {[23:10], 10u2019b0}
     * |        |          |The following table lists the DMAAddr bits used as the offset for the RAM starting address
     * |        |          |Note that the minimal DMA operation size is 16-byte (or 4-word).
     * |        |          |Offset WaySize
     * |        |          |DMASize 8K 4K 2K 1K
     * |        |          |0 - - - -
     * |        |          |1 [12] [11] [10] [9]
     * |        |          |2 [12:11] [11:10] [10:9] [9:8]
     * |        |          |3 [12:10] [11:9] [10:8] [9:7]
     * |        |          |4 [12:9] [11:8] [10:7] [9:6]
     * |        |          |5 [12:8] [11:7] [10:6] [9:5]
     * |        |          |6 [12:7] [11:6] [10:5] [9:4]
     * |        |          |7 [12:6] [11:5] [10:4] -
     * |[30]    |DMAFLUSH  |Flushing DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a flushing DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a preloading DMA is on-going, this bit is not modifiable.
     * |[31]    |DMAPRELD  |Preloading DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a preloading DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a flushing DMA is on-going, this bit is not modifiable.
     * @var TCM_T::W3DMACTL
     * Offset: 0x2C  Tight Couple Memory Way3 DMA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMASIZE   |DMA Size Selection Bit
     * |        |          |This field indicate and size of moving external memory to LMB after DMA is trigged.
     * |        |          |000 = Full TCM way
     * |        |          |001 = 1/2 TCM way
     * |        |          |010 = 1/4 TCM way
     * |        |          |011 = 1/8 TCM way
     * |        |          |100 = 1/16 TCM way
     * |        |          |101 = 1/32 TCM way
     * |        |          |110 = 1/64 TCM way
     * |        |          |111 = 1/128 TCM way
     * |        |          |Note: This bit can be modified only when the corresponding WAYxEN bit is clear
     * |        |          |(default: 0) When the embedded DMA engine is triggered for either LMB preloading or auto-flushing, this field defines the size of the operation according to the following table
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |[23:4]  |DMAADDR   |DMA starting RAM address
     * |        |          |When a LMB-related DMA operation is triggered, this field provides the starting RAM address of the operation
     * |        |          |Depending on the setting of the WaySize and DMASize, not all bits are used
     * |        |          |The following table lists the DMAAddr bits used to construct the base of the starting RAM address according to WaySize
     * |        |          |While a DMA operation is on-going, this field cannot be modified.
     * |        |          |WaySize / RAMBase 8K / {[23:13], 13u2019b0} 4K / {[23:12], 12u2019b0} 2K / {[23:11], 11u2019b0} 1K / {[23:10], 10u2019b0}
     * |        |          |The following table lists the DMAAddr bits used as the offset for the RAM starting address
     * |        |          |Note that the minimal DMA operation size is 16-byte (or 4-word).
     * |        |          |Offset WaySize
     * |        |          |DMASize 8K 4K 2K 1K
     * |        |          |0 - - - -
     * |        |          |1 [12] [11] [10] [9]
     * |        |          |2 [12:11] [11:10] [10:9] [9:8]
     * |        |          |3 [12:10] [11:9] [10:8] [9:7]
     * |        |          |4 [12:9] [11:8] [10:7] [9:6]
     * |        |          |5 [12:8] [11:7] [10:6] [9:5]
     * |        |          |6 [12:7] [11:6] [10:5] [9:4]
     * |        |          |7 [12:6] [11:5] [10:4] -
     * |[30]    |DMAFLUSH  |Flushing DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a flushing DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a preloading DMA is on-going, this bit is not modifiable.
     * |[31]    |DMAPRELD  |Preloading DMA
     * |        |          |When CacheMode bit is 0 (WayEnable bit 0 is OK), writing a 1 into this bit triggers a preloading DMA operation according to the setting in the DMASize and DMAAddr fields
     * |        |          |This bit cannot be written 0 by M4
     * |        |          |It is self-clearing when the DMA operation completes
     * |        |          |While a flushing DMA is on-going, this bit is not modifiable.
     */
    __IO uint32_t GCTL;                  /*!< [0x0000] Tight Couple Memory Control Register                             */
    __I  uint32_t RESERVE0[3];
    __IO uint32_t WAYCTL[4];             /*!< [0x10-0x1c] Tight Couple Memory Way0 Control Register                     */
    __IO uint32_t WDMACTL[4];            /*!< [0x20-0x2c] Tight Couple Memory Way0 DMA Control Register                 */

} TCM_T;

/**
    @addtogroup TCM_CONST TCM Bit Field Definition
    Constant Definitions for TCM Controller
@{ */

#define TCM_GCTL_WAYNUM_Pos              (0)                                               /*!< TCM_T::GCTL: WAYNUM Position           */
#define TCM_GCTL_WAYNUM_Msk              (0x3ul << TCM_GCTL_WAYNUM_Pos)                    /*!< TCM_T::GCTL: WAYNUM Mask               */

#define TCM_GCTL_WAYSIZE_Pos             (2)                                               /*!< TCM_T::GCTL: WAYSIZE Position          */
#define TCM_GCTL_WAYSIZE_Msk             (0x3ul << TCM_GCTL_WAYSIZE_Pos)                   /*!< TCM_T::GCTL: WAYSIZE Mask              */

#define TCM_GCTL_CACHECFG_Pos            (4)                                               /*!< TCM_T::GCTL: CACHECFG Position         */
#define TCM_GCTL_CACHECFG_Msk            (0x1ul << TCM_GCTL_CACHECFG_Pos)                  /*!< TCM_T::GCTL: CACHECFG Mask             */

#define TCM_GCTL_FIXAZERO_Pos            (5)                                               /*!< TCM_T::GCTL: FIXAZERO Position         */
#define TCM_GCTL_FIXAZERO_Msk            (0x1ul << TCM_GCTL_FIXAZERO_Pos)                  /*!< TCM_T::GCTL: FIXAZERO Mask             */

#define TCM_GCTL_WAY0EN_Pos              (8)                                               /*!< TCM_T::GCTL: WAY0EN Position           */
#define TCM_GCTL_WAY0EN_Msk              (0x1ul << TCM_GCTL_WAY0EN_Pos)                    /*!< TCM_T::GCTL: WAY0EN Mask               */

#define TCM_GCTL_WAY1EN_Pos              (9)                                               /*!< TCM_T::GCTL: WAY1EN Position           */
#define TCM_GCTL_WAY1EN_Msk              (0x1ul << TCM_GCTL_WAY1EN_Pos)                    /*!< TCM_T::GCTL: WAY1EN Mask               */

#define TCM_GCTL_WAY2EN_Pos              (10)                                              /*!< TCM_T::GCTL: WAY2EN Position           */
#define TCM_GCTL_WAY2EN_Msk              (0x1ul << TCM_GCTL_WAY2EN_Pos)                    /*!< TCM_T::GCTL: WAY2EN Mask               */

#define TCM_GCTL_WAY3EN_Pos              (11)                                              /*!< TCM_T::GCTL: WAY3EN Position           */
#define TCM_GCTL_WAY3EN_Msk              (0x1ul << TCM_GCTL_WAY3EN_Pos)                    /*!< TCM_T::GCTL: WAY3EN Mask               */

#define TCM_W0CTL_CACHEMD_Pos            (0)                                               /*!< TCM_T::W0CTL: CACHEMD Position         */
#define TCM_W0CTL_CACHEMD_Msk            (0x1ul << TCM_W0CTL_CACHEMD_Pos)                  /*!< TCM_T::W0CTL: CACHEMD Mask             */

#define TCM_W0CTL_PRELD_Pos              (1)                                               /*!< TCM_T::W0CTL: PRELD Position           */
#define TCM_W0CTL_PRELD_Msk              (0x1ul << TCM_W0CTL_PRELD_Pos)                    /*!< TCM_T::W0CTL: PRELD Mask               */

#define TCM_W0CTL_PRELDST_Pos            (2)                                               /*!< TCM_T::W0CTL: PRELDST Position         */
#define TCM_W0CTL_PRELDST_Msk            (0x1ul << TCM_W0CTL_PRELDST_Pos)                  /*!< TCM_T::W0CTL: PRELDST Mask             */

#define TCM_W0CTL_INVALST_Pos            (3)                                               /*!< TCM_T::W0CTL: INVALST Position         */
#define TCM_W0CTL_INVALST_Msk            (0x1ul << TCM_W0CTL_INVALST_Pos)                  /*!< TCM_T::W0CTL: INVALST Mask             */

#define TCM_W0CTL_AFLUSH_Pos             (4)                                               /*!< TCM_T::W0CTL: AFLUSH Position          */
#define TCM_W0CTL_AFLUSH_Msk             (0x1ul << TCM_W0CTL_AFLUSH_Pos)                   /*!< TCM_T::W0CTL: AFLUSH Mask              */

#define TCM_W0CTL_AFLUSHST_Pos           (5)                                               /*!< TCM_T::W0CTL: AFLUSHST Position        */
#define TCM_W0CTL_AFLUSHST_Msk           (0x1ul << TCM_W0CTL_AFLUSHST_Pos)                 /*!< TCM_T::W0CTL: AFLUSHST Mask            */

#define TCM_W0CTL_AZERO_Pos              (6)                                               /*!< TCM_T::W0CTL: AZERO Position           */
#define TCM_W0CTL_AZERO_Msk              (0x1ul << TCM_W0CTL_AZERO_Pos)                    /*!< TCM_T::W0CTL: AZERO Mask               */

#define TCM_W0CTL_AZEROST_Pos            (7)                                               /*!< TCM_T::W0CTL: AZEROST Position         */
#define TCM_W0CTL_AZEROST_Msk            (0x1ul << TCM_W0CTL_AZEROST_Pos)                  /*!< TCM_T::W0CTL: AZEROST Mask             */

#define TCM_W0CTL_XOMERROR_Pos           (8)                                               /*!< TCM_T::W0CTL: XOMERROR Position        */
#define TCM_W0CTL_XOMERROR_Msk           (0x1ul << TCM_W0CTL_XOMERROR_Pos)                 /*!< TCM_T::W0CTL: XOMERROR Mask            */

#define TCM_W0CTL_ERROR_Pos              (9)                                               /*!< TCM_T::W0CTL: ERROR Position           */
#define TCM_W0CTL_ERROR_Msk              (0x1ul << TCM_W0CTL_ERROR_Pos)                    /*!< TCM_T::W0CTL: ERROR Mask               */

#define TCM_W0CTL_LMBTAG_Pos             (13)                                              /*!< TCM_T::W0CTL: LMBTAG Position          */
#define TCM_W0CTL_LMBTAG_Msk             (0x7fful << TCM_W0CTL_LMBTAG_Pos)                 /*!< TCM_T::W0CTL: LMBTAG Mask              */

#define TCM_W1CTL_CACHEMD_Pos            (0)                                               /*!< TCM_T::W1CTL: CACHEMD Position         */
#define TCM_W1CTL_CACHEMD_Msk            (0x1ul << TCM_W1CTL_CACHEMD_Pos)                  /*!< TCM_T::W1CTL: CACHEMD Mask             */

#define TCM_W1CTL_PRELD_Pos              (1)                                               /*!< TCM_T::W1CTL: PRELD Position           */
#define TCM_W1CTL_PRELD_Msk              (0x1ul << TCM_W1CTL_PRELD_Pos)                    /*!< TCM_T::W1CTL: PRELD Mask               */

#define TCM_W1CTL_PRELDST_Pos            (2)                                               /*!< TCM_T::W1CTL: PRELDST Position         */
#define TCM_W1CTL_PRELDST_Msk            (0x1ul << TCM_W1CTL_PRELDST_Pos)                  /*!< TCM_T::W1CTL: PRELDST Mask             */

#define TCM_W1CTL_INVALST_Pos            (3)                                               /*!< TCM_T::W1CTL: INVALST Position         */
#define TCM_W1CTL_INVALST_Msk            (0x1ul << TCM_W1CTL_INVALST_Pos)                  /*!< TCM_T::W1CTL: INVALST Mask             */

#define TCM_W1CTL_AFLUSH_Pos             (4)                                               /*!< TCM_T::W1CTL: AFLUSH Position          */
#define TCM_W1CTL_AFLUSH_Msk             (0x1ul << TCM_W1CTL_AFLUSH_Pos)                   /*!< TCM_T::W1CTL: AFLUSH Mask              */

#define TCM_W1CTL_AFLUSHST_Pos           (5)                                               /*!< TCM_T::W1CTL: AFLUSHST Position        */
#define TCM_W1CTL_AFLUSHST_Msk           (0x1ul << TCM_W1CTL_AFLUSHST_Pos)                 /*!< TCM_T::W1CTL: AFLUSHST Mask            */

#define TCM_W1CTL_AZERO_Pos              (6)                                               /*!< TCM_T::W1CTL: AZERO Position           */
#define TCM_W1CTL_AZERO_Msk              (0x1ul << TCM_W1CTL_AZERO_Pos)                    /*!< TCM_T::W1CTL: AZERO Mask               */

#define TCM_W1CTL_AZEROST_Pos            (7)                                               /*!< TCM_T::W1CTL: AZEROST Position         */
#define TCM_W1CTL_AZEROST_Msk            (0x1ul << TCM_W1CTL_AZEROST_Pos)                  /*!< TCM_T::W1CTL: AZEROST Mask             */

#define TCM_W1CTL_XOMERROR_Pos           (8)                                               /*!< TCM_T::W1CTL: XOMERROR Position        */
#define TCM_W1CTL_XOMERROR_Msk           (0x1ul << TCM_W1CTL_XOMERROR_Pos)                 /*!< TCM_T::W1CTL: XOMERROR Mask            */

#define TCM_W1CTL_ERROR_Pos              (9)                                               /*!< TCM_T::W1CTL: ERROR Position           */
#define TCM_W1CTL_ERROR_Msk              (0x1ul << TCM_W1CTL_ERROR_Pos)                    /*!< TCM_T::W1CTL: ERROR Mask               */

#define TCM_W1CTL_LMBTAG_Pos             (13)                                              /*!< TCM_T::W1CTL: LMBTAG Position          */
#define TCM_W1CTL_LMBTAG_Msk             (0x7fful << TCM_W1CTL_LMBTAG_Pos)                 /*!< TCM_T::W1CTL: LMBTAG Mask              */

#define TCM_W2CTL_CACHEMD_Pos            (0)                                               /*!< TCM_T::W2CTL: CACHEMD Position         */
#define TCM_W2CTL_CACHEMD_Msk            (0x1ul << TCM_W2CTL_CACHEMD_Pos)                  /*!< TCM_T::W2CTL: CACHEMD Mask             */

#define TCM_W2CTL_PRELD_Pos              (1)                                               /*!< TCM_T::W2CTL: PRELD Position           */
#define TCM_W2CTL_PRELD_Msk              (0x1ul << TCM_W2CTL_PRELD_Pos)                    /*!< TCM_T::W2CTL: PRELD Mask               */

#define TCM_W2CTL_PRELDST_Pos            (2)                                               /*!< TCM_T::W2CTL: PRELDST Position         */
#define TCM_W2CTL_PRELDST_Msk            (0x1ul << TCM_W2CTL_PRELDST_Pos)                  /*!< TCM_T::W2CTL: PRELDST Mask             */

#define TCM_W2CTL_INVALST_Pos            (3)                                               /*!< TCM_T::W2CTL: INVALST Position         */
#define TCM_W2CTL_INVALST_Msk            (0x1ul << TCM_W2CTL_INVALST_Pos)                  /*!< TCM_T::W2CTL: INVALST Mask             */

#define TCM_W2CTL_AFLUSH_Pos             (4)                                               /*!< TCM_T::W2CTL: AFLUSH Position          */
#define TCM_W2CTL_AFLUSH_Msk             (0x1ul << TCM_W2CTL_AFLUSH_Pos)                   /*!< TCM_T::W2CTL: AFLUSH Mask              */

#define TCM_W2CTL_AFLUSHST_Pos           (5)                                               /*!< TCM_T::W2CTL: AFLUSHST Position        */
#define TCM_W2CTL_AFLUSHST_Msk           (0x1ul << TCM_W2CTL_AFLUSHST_Pos)                 /*!< TCM_T::W2CTL: AFLUSHST Mask            */

#define TCM_W2CTL_AZERO_Pos              (6)                                               /*!< TCM_T::W2CTL: AZERO Position           */
#define TCM_W2CTL_AZERO_Msk              (0x1ul << TCM_W2CTL_AZERO_Pos)                    /*!< TCM_T::W2CTL: AZERO Mask               */

#define TCM_W2CTL_AZEROST_Pos            (7)                                               /*!< TCM_T::W2CTL: AZEROST Position         */
#define TCM_W2CTL_AZEROST_Msk            (0x1ul << TCM_W2CTL_AZEROST_Pos)                  /*!< TCM_T::W2CTL: AZEROST Mask             */

#define TCM_W2CTL_XOMERROR_Pos           (8)                                               /*!< TCM_T::W2CTL: XOMERROR Position        */
#define TCM_W2CTL_XOMERROR_Msk           (0x1ul << TCM_W2CTL_XOMERROR_Pos)                 /*!< TCM_T::W2CTL: XOMERROR Mask            */

#define TCM_W2CTL_ERROR_Pos              (9)                                               /*!< TCM_T::W2CTL: ERROR Position           */
#define TCM_W2CTL_ERROR_Msk              (0x1ul << TCM_W2CTL_ERROR_Pos)                    /*!< TCM_T::W2CTL: ERROR Mask               */

#define TCM_W2CTL_LMBTAG_Pos             (13)                                              /*!< TCM_T::W2CTL: LMBTAG Position          */
#define TCM_W2CTL_LMBTAG_Msk             (0x7fful << TCM_W2CTL_LMBTAG_Pos)                 /*!< TCM_T::W2CTL: LMBTAG Mask              */

#define TCM_W3CTL_CACHEMD_Pos            (0)                                               /*!< TCM_T::W3CTL: CACHEMD Position         */
#define TCM_W3CTL_CACHEMD_Msk            (0x1ul << TCM_W3CTL_CACHEMD_Pos)                  /*!< TCM_T::W3CTL: CACHEMD Mask             */

#define TCM_W3CTL_PRELD_Pos              (1)                                               /*!< TCM_T::W3CTL: PRELD Position           */
#define TCM_W3CTL_PRELD_Msk              (0x1ul << TCM_W3CTL_PRELD_Pos)                    /*!< TCM_T::W3CTL: PRELD Mask               */

#define TCM_W3CTL_PRELDST_Pos            (2)                                               /*!< TCM_T::W3CTL: PRELDST Position         */
#define TCM_W3CTL_PRELDST_Msk            (0x1ul << TCM_W3CTL_PRELDST_Pos)                  /*!< TCM_T::W3CTL: PRELDST Mask             */

#define TCM_W3CTL_INVALST_Pos            (3)                                               /*!< TCM_T::W3CTL: INVALST Position         */
#define TCM_W3CTL_INVALST_Msk            (0x1ul << TCM_W3CTL_INVALST_Pos)                  /*!< TCM_T::W3CTL: INVALST Mask             */

#define TCM_W3CTL_AFLUSH_Pos             (4)                                               /*!< TCM_T::W3CTL: AFLUSH Position          */
#define TCM_W3CTL_AFLUSH_Msk             (0x1ul << TCM_W3CTL_AFLUSH_Pos)                   /*!< TCM_T::W3CTL: AFLUSH Mask              */

#define TCM_W3CTL_AFLUSHST_Pos           (5)                                               /*!< TCM_T::W3CTL: AFLUSHST Position        */
#define TCM_W3CTL_AFLUSHST_Msk           (0x1ul << TCM_W3CTL_AFLUSHST_Pos)                 /*!< TCM_T::W3CTL: AFLUSHST Mask            */

#define TCM_W3CTL_AZERO_Pos              (6)                                               /*!< TCM_T::W3CTL: AZERO Position           */
#define TCM_W3CTL_AZERO_Msk              (0x1ul << TCM_W3CTL_AZERO_Pos)                    /*!< TCM_T::W3CTL: AZERO Mask               */

#define TCM_W3CTL_AZEROST_Pos            (7)                                               /*!< TCM_T::W3CTL: AZEROST Position         */
#define TCM_W3CTL_AZEROST_Msk            (0x1ul << TCM_W3CTL_AZEROST_Pos)                  /*!< TCM_T::W3CTL: AZEROST Mask             */

#define TCM_W3CTL_XOMERROR_Pos           (8)                                               /*!< TCM_T::W3CTL: XOMERROR Position        */
#define TCM_W3CTL_XOMERROR_Msk           (0x1ul << TCM_W3CTL_XOMERROR_Pos)                 /*!< TCM_T::W3CTL: XOMERROR Mask            */

#define TCM_W3CTL_ERROR_Pos              (9)                                               /*!< TCM_T::W3CTL: ERROR Position           */
#define TCM_W3CTL_ERROR_Msk              (0x1ul << TCM_W3CTL_ERROR_Pos)                    /*!< TCM_T::W3CTL: ERROR Mask               */

#define TCM_W3CTL_LMBTAG_Pos             (13)                                              /*!< TCM_T::W3CTL: LMBTAG Position          */
#define TCM_W3CTL_LMBTAG_Msk             (0x7fful << TCM_W3CTL_LMBTAG_Pos)                 /*!< TCM_T::W3CTL: LMBTAG Mask              */

#define TCM_W0DMACTL_DMASIZE_Pos         (0)                                               /*!< TCM_T::W0DMACTL: DMASIZE Position      */
#define TCM_W0DMACTL_DMASIZE_Msk         (0x1ul << TCM_W0DMACTL_DMASIZE_Pos)               /*!< TCM_T::W0DMACTL: DMASIZE Mask          */

#define TCM_W0DMACTL_DMAADDR_Pos         (4)                                               /*!< TCM_T::W0DMACTL: DMAADDR Position      */
#define TCM_W0DMACTL_DMAADDR_Msk         (0xffffful << TCM_W0DMACTL_DMAADDR_Pos)           /*!< TCM_T::W0DMACTL: DMAADDR Mask          */

#define TCM_W0DMACTL_DMAFLUSH_Pos        (30)                                              /*!< TCM_T::W0DMACTL: DMAFLUSH Position     */
#define TCM_W0DMACTL_DMAFLUSH_Msk        (0x1ul << TCM_W0DMACTL_DMAFLUSH_Pos)              /*!< TCM_T::W0DMACTL: DMAFLUSH Mask         */

#define TCM_W0DMACTL_DMAPRELD_Pos        (31)                                              /*!< TCM_T::W0DMACTL: DMAPRELD Position     */
#define TCM_W0DMACTL_DMAPRELD_Msk        (0x1ul << TCM_W0DMACTL_DMAPRELD_Pos)              /*!< TCM_T::W0DMACTL: DMAPRELD Mask         */

#define TCM_W1DMACTL_DMASIZE_Pos         (0)                                               /*!< TCM_T::W1DMACTL: DMASIZE Position      */
#define TCM_W1DMACTL_DMASIZE_Msk         (0x1ul << TCM_W1DMACTL_DMASIZE_Pos)               /*!< TCM_T::W1DMACTL: DMASIZE Mask          */

#define TCM_W1DMACTL_DMAADDR_Pos         (4)                                               /*!< TCM_T::W1DMACTL: DMAADDR Position      */
#define TCM_W1DMACTL_DMAADDR_Msk         (0xffffful << TCM_W1DMACTL_DMAADDR_Pos)           /*!< TCM_T::W1DMACTL: DMAADDR Mask          */

#define TCM_W1DMACTL_DMAFLUSH_Pos        (30)                                              /*!< TCM_T::W1DMACTL: DMAFLUSH Position     */
#define TCM_W1DMACTL_DMAFLUSH_Msk        (0x1ul << TCM_W1DMACTL_DMAFLUSH_Pos)              /*!< TCM_T::W1DMACTL: DMAFLUSH Mask         */

#define TCM_W1DMACTL_DMAPRELD_Pos        (31)                                              /*!< TCM_T::W1DMACTL: DMAPRELD Position     */
#define TCM_W1DMACTL_DMAPRELD_Msk        (0x1ul << TCM_W1DMACTL_DMAPRELD_Pos)              /*!< TCM_T::W1DMACTL: DMAPRELD Mask         */

#define TCM_W2DMACTL_DMASIZE_Pos         (0)                                               /*!< TCM_T::W2DMACTL: DMASIZE Position      */
#define TCM_W2DMACTL_DMASIZE_Msk         (0x1ul << TCM_W2DMACTL_DMASIZE_Pos)               /*!< TCM_T::W2DMACTL: DMASIZE Mask          */

#define TCM_W2DMACTL_DMAADDR_Pos         (4)                                               /*!< TCM_T::W2DMACTL: DMAADDR Position      */
#define TCM_W2DMACTL_DMAADDR_Msk         (0xffffful << TCM_W2DMACTL_DMAADDR_Pos)           /*!< TCM_T::W2DMACTL: DMAADDR Mask          */

#define TCM_W2DMACTL_DMAFLUSH_Pos        (30)                                              /*!< TCM_T::W2DMACTL: DMAFLUSH Position     */
#define TCM_W2DMACTL_DMAFLUSH_Msk        (0x1ul << TCM_W2DMACTL_DMAFLUSH_Pos)              /*!< TCM_T::W2DMACTL: DMAFLUSH Mask         */

#define TCM_W2DMACTL_DMAPRELD_Pos        (31)                                              /*!< TCM_T::W2DMACTL: DMAPRELD Position     */
#define TCM_W2DMACTL_DMAPRELD_Msk        (0x1ul << TCM_W2DMACTL_DMAPRELD_Pos)              /*!< TCM_T::W2DMACTL: DMAPRELD Mask         */

#define TCM_W3DMACTL_DMASIZE_Pos         (0)                                               /*!< TCM_T::W3DMACTL: DMASIZE Position      */
#define TCM_W3DMACTL_DMASIZE_Msk         (0x1ul << TCM_W3DMACTL_DMASIZE_Pos)               /*!< TCM_T::W3DMACTL: DMASIZE Mask          */

#define TCM_W3DMACTL_DMAADDR_Pos         (4)                                               /*!< TCM_T::W3DMACTL: DMAADDR Position      */
#define TCM_W3DMACTL_DMAADDR_Msk         (0xffffful << TCM_W3DMACTL_DMAADDR_Pos)           /*!< TCM_T::W3DMACTL: DMAADDR Mask          */

#define TCM_W3DMACTL_DMAFLUSH_Pos        (30)                                              /*!< TCM_T::W3DMACTL: DMAFLUSH Position     */
#define TCM_W3DMACTL_DMAFLUSH_Msk        (0x1ul << TCM_W3DMACTL_DMAFLUSH_Pos)              /*!< TCM_T::W3DMACTL: DMAFLUSH Mask         */

#define TCM_W3DMACTL_DMAPRELD_Pos        (31)                                              /*!< TCM_T::W3DMACTL: DMAPRELD Position     */
#define TCM_W3DMACTL_DMAPRELD_Msk        (0x1ul << TCM_W3DMACTL_DMAPRELD_Pos)              /*!< TCM_T::W3DMACTL: DMAPRELD Mask         */

/**@}*/ /* TCM_CONST */
/**@}*/ /* end of TCM register group */


/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __ACMP_REG_H__ */
