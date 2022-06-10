/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup CACHE
 *  @{
 */
#include "hal_base.h"
#include "hal_cache.h"

/** @defgroup CACHE_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/***************************** MACRO Definition ******************************/

/***************************** Structure Definition **************************/

/********************* Private Function Definition ***************************/

#if defined(__CORTEX_M)
__STATIC_INLINE unsigned long HAL_SYS_EnterCriticalSection(void)
{
    unsigned long flags;

    flags = __get_PRIMASK();
    __disable_irq();

    return flags;
}

__STATIC_INLINE void HAL_SYS_ExitCriticalSection(unsigned long flags)
{
    __set_PRIMASK(flags);
}
#else
__STATIC_INLINE unsigned long HAL_SYS_EnterCriticalSection(void)
{
    return 0;
}

__STATIC_INLINE void HAL_SYS_ExitCriticalSection(unsigned long flags)
{
}
#endif

/** @} */
/********************* Public Function Definition ****************************/
/** @defgroup CACHE_Exported_Functions_Group5 Other Functions
 *  @attention these APIs allow direct use in the HAL layer
 *  @{
 */

/**
 * @brief  translate the cpuAddr to sramAddr
 * @param cpuAddr: the address mapping to sram, only can be accessed by cpu
 * @return sramAddr: the real address of sram, it can be accessed by cpu & device
 */
uint32_t HAL_CpuAddrToDmaAddr(uint32_t cpuAddr)
{
    uint32_t sramAddr = cpuAddr;

#ifdef SRAM_IADDR_TO_DADDR_OFFSET

    if (cpuAddr >= SRAM_IADDR_START
        && cpuAddr < (SRAM_IADDR_START + SRAM_SIZE)) {
        sramAddr = cpuAddr + SRAM_IADDR_TO_DADDR_OFFSET;
    }

#endif

#ifdef XIP_NOR_IADDR_TO_DADDR_OFFSET

    if (cpuAddr >= XIP_NOR_IADDR_START
        && cpuAddr < (XIP_NOR_IADDR_START + XIP_NOR_SIZE)) {
        sramAddr = cpuAddr + XIP_NOR_IADDR_TO_DADDR_OFFSET;
    }

#endif

#ifdef XIP_PSRAM_IADDR_TO_DADDR_OFFSET

    if (cpuAddr >= XIP_PSRAM_IADDR_START
        && cpuAddr < (XIP_PSRAM_IADDR_START + XIP_PSRAM_SIZE)) {
        sramAddr = cpuAddr + XIP_PSRAM_IADDR_TO_DADDR_OFFSET;
    }

#endif

    return sramAddr;
}

#ifdef MPU
/**
 * @brief  check mpu is enable.
 * @return HAL_ENABLE if mpu enable.
 */
__STATIC_INLINE HAL_FuncStatus HAL_MPU_IsEnable(void)
{
    HAL_FuncStatus ret = HAL_DISABLE;

    if (MPU->CTRL & MPU_CTRL_ENABLE_Msk) {
        ret = HAL_ENABLE;
    }

    return ret;
}
#endif

/**
 * @brief  enable icache.
 * @return HAL_OK if success.
 * @attention The MPU must be configured before cache if you need the function.
 */
HAL_Status HAL_ICACHE_Enable(void)
{
#if defined(HAL_ICACHE_MODULE_ENABLED) && defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t status;
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    /* config icache: mpu disable, stb disable, write through, hot buffer enable,
       prefetch enable */
    ICACHE->CACHE_CTRL |=
        (ICACHE_CACHE_CTRL_CACHE_EN_MASK | ICACHE_CACHE_CTRL_CACHE_WT_EN_MASK);
    ICACHE->CACHE_CTRL &= (~ICACHE_CACHE_CTRL_CACHE_STB_EN_MASK);

    /* if mpu has been enable, we will enable cache mpu function */
#ifdef MPU
    if (HAL_MPU_IsEnable()) {
        ICACHE->CACHE_CTRL |= ICACHE_CACHE_CTRL_CACHE_MPU_MODE_MASK;
    }
#endif

    do {
        status =
            ICACHE->CACHE_STATUS & ICACHE_CACHE_STATUS_CACHE_INIT_FINISH_MASK;
    } while (status == 0);

    ICACHE->CACHE_CTRL &= ~ICACHE_CACHE_CTRL_CACHE_BYPASS_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  disable icache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_Disable(void)
{
#if defined(HAL_ICACHE_MODULE_ENABLED) && defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_CTRL |= ICACHE_CACHE_CTRL_CACHE_BYPASS_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  invalidate all of the icache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_Invalidate(void)
{
#if defined(HAL_ICACHE_MODULE_ENABLED) && defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t status = 0;
    unsigned long flags;

    if ((uint32_t)DCACHE == (uint32_t)ICACHE) {
        if (DCACHE->CACHE_CTRL & DCACHE_CACHE_CTRL_CACHE_WT_EN_MASK) {
            return HAL_OK;
        } else {
            return HAL_INVAL;
        }
    }

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_MAINTAIN[0] =
        CACHE_M_INVALID_ALL | ICACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;

    do {
        status = ICACHE->CACHE_MAINTAIN[0] &
                 ICACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;
    } while (status);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  invalidate the specified region of the icache.
 * @param  address: the start address of specified region which you want invalidate.
 * @param  sizeByte: the length in bytes of invalidate range.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_InvalidateByRange(uint32_t address,
                                        uint32_t sizeByte)
{
#if defined(HAL_ICACHE_MODULE_ENABLED) && defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t value = 0;
    uint32_t offset = 0;
    uint32_t status = 0;
    unsigned long flags;

    if (sizeByte == 0) {
        return HAL_OK;
    }

    address = HAL_CpuAddrToDmaAddr(address);

    offset = ((address & (CACHE_LINE_SIZE - 1)) + sizeByte - 1) >> CACHE_LINE_SHIFT;
    value = (address & ICACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_MASK) |
            CACHE_M_INVALID | ICACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_MAINTAIN[1] = offset;
    ICACHE->CACHE_MAINTAIN[0] = value;

    do {
        status = ICACHE->CACHE_MAINTAIN[0] &
                 ICACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;
    } while (status);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  enable performance measurement unit of icache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_EnablePMU(void)
{
#if defined(HAL_ICACHE_MODULE_ENABLED) && defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_CTRL |= ICACHE_CACHE_CTRL_CACHE_PMU_EN_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  disable performance measurement unit of icache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_DisablePMU(void)
{
#if defined(HAL_ICACHE_MODULE_ENABLED) && defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_CTRL &= (~ICACHE_CACHE_CTRL_CACHE_PMU_EN_MASK);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  get current state of performance measurement unit in icache.
 * @param  stat: return the current state if success.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_GetPMU(struct CACHE_PMU_CNT *stat)
{
#if defined(HAL_ICACHE_MODULE_ENABLED) && defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    HAL_ASSERT(stat != NULL);

    flags = HAL_SYS_EnterCriticalSection();

    stat->rdNum = ICACHE->PMU_RD_NUM_CNT;
    stat->wrNum = ICACHE->PMU_WR_NUM_CNT;
    stat->sramRdHit = ICACHE->PMU_SRAM_RD_HIT_CNT;
    stat->hbRdHit = ICACHE->PMU_HB_RD_HIT_CNT;
    stat->stbRdHit = ICACHE->PMU_STB_RD_HIT_CNT;
    stat->rdHit = ICACHE->PMU_RD_HIT_CNT;
    stat->wrHit = ICACHE->PMU_WR_HIT_CNT;
    stat->rdMissPenalty = ICACHE->PMU_RD_MISS_PENALTY_CNT;
    stat->wrMissPenalty = ICACHE->PMU_WR_MISS_PENALTY_CNT;
    stat->rdLat = ICACHE->PMU_RD_LAT_CNT;
    stat->wrLat = ICACHE->PMU_WR_LAT_CNT;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  Enable the interrupt of icache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_EnableInt(void)
{
#if defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_INT_EN |= ICACHE_CACHE_INT_EN_ERR_RECORD_EN_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  Disable the interrupt of icache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_DisableInt(void)
{
#if defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_INT_EN &= ~ICACHE_CACHE_INT_EN_ERR_RECORD_EN_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  Get the interrupt status of icache.
 * @return HAL_TRUE if ahb error occur.
 */
HAL_Check HAL_ICACHE_GetInt(void)
{
    uint32_t status = 0;

#if defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)

    status = ICACHE->CACHE_INT_ST & ICACHE_CACHE_INT_ST_AHB_ERROR_STATUS_MASK;

#endif

#endif

    return status ? HAL_TRUE : HAL_FALSE;
}

/**
 * @brief  Get the ahb bus error address of icache.
 * @return ahb buss error address if success.
 * @attention The return value is only valid if you get a ahb error from CACHE_INT_ST
 */
uint32_t HAL_ICACHE_GetErrAddr(void)
{
    uint32_t address = -1;

#if defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)

    address = ICACHE->CACHE_ERR_HADDR;

#endif

#endif

    return address;
}

/**
 * @brief  Clear the interrupt status of icache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_ICACHE_ClearInt(void)
{
#if defined(ICACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    ICACHE->CACHE_INT_ST |= ICACHE_CACHE_INT_ST_AHB_ERROR_STATUS_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief     enable dcache.
 * @return    HAL_OK if success.
 * @attention The MPU must be configured before cache if you need the feature.
 * @attention Dynamically disable and enable dcache is not allowed.
 */
HAL_Status HAL_DCACHE_Enable(void)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t status;
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    /* stb enable, stb_entry=7, stb_timeout enable, write back, prefetch enable */
    DCACHE->CACHE_CTRL |=
        DCACHE_CACHE_CTRL_CACHE_EN_MASK
        | (7U << DCACHE_CACHE_CTRL_CACHE_ENTRY_THRESH_SHIFT)
        | DCACHE_CACHE_CTRL_STB_TIMEOUT_EN_MASK;
    DCACHE->STB_TIMEOUT_CTRL = 1;

    /* if mpu has been enable, we will enable cache mpu function */
#ifdef MPU
    if (HAL_MPU_IsEnable()) {
        DCACHE->CACHE_CTRL |= DCACHE_CACHE_CTRL_CACHE_MPU_MODE_MASK;
    }
#endif

    do {
        status =
            DCACHE->CACHE_STATUS & DCACHE_CACHE_STATUS_CACHE_INIT_FINISH_MASK;
    } while (status == 0);

    DCACHE->CACHE_CTRL &= ~DCACHE_CACHE_CTRL_CACHE_BYPASS_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  disable dcache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_Disable(void)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_CTRL |= DCACHE_CACHE_CTRL_CACHE_BYPASS_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  invalidate all of the dcache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_Invalidate(void)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t status = 0;
    unsigned long flags;

    if ((uint32_t)DCACHE == (uint32_t)ICACHE) {
        if (DCACHE->CACHE_CTRL & DCACHE_CACHE_CTRL_CACHE_WT_EN_MASK) {
            return HAL_OK;
        } else {
            return HAL_INVAL;
        }
    }

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_MAINTAIN[0] =
        CACHE_M_INVALID_ALL | DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;

    do {
        status = DCACHE->CACHE_MAINTAIN[0] &
                 DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;
    } while (status);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  invalidate the specified region of the dcache.
 * @param  address: the start address of specified region which you want invalidate.
 * @param  sizeByte: the length in bytes of invalidate range.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_InvalidateByRange(uint32_t address,
                                        uint32_t sizeByte)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t value = 0;
    uint32_t offset = 0;
    uint32_t status = 0;
    unsigned long flags;

    if (sizeByte == 0) {
        return HAL_OK;
    }

    offset = ((address & (CACHE_LINE_SIZE - 1)) + sizeByte - 1) >> CACHE_LINE_SHIFT;
    value = (address & DCACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_MASK) |
            CACHE_M_INVALID | DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_MAINTAIN[1] = offset;
    DCACHE->CACHE_MAINTAIN[0] = value;

    do {
        status = DCACHE->CACHE_MAINTAIN[0] &
                 DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;
    } while (status);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  clean the specified region of the dcache, it will flush the dirty cache in
 *         the specified region.
 * @param  address: the start address of specified region which you want invalidate.
 * @param  sizeByte: the length in bytes of invalidate range.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_CleanByRange(uint32_t address,
                                   uint32_t sizeByte)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t value = 0;
    uint32_t offset = 0;
    uint32_t status = 0;
    unsigned long flags;

    if (sizeByte == 0) {
        return HAL_OK;
    }

    offset = ((address & (CACHE_LINE_SIZE - 1)) + sizeByte - 1) >> CACHE_LINE_SHIFT;
    value = (address & DCACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_MASK) |
            CACHE_M_CLEAN | DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_MAINTAIN[1] = offset;
    DCACHE->CACHE_MAINTAIN[0] = value;

    do {
        status = DCACHE->CACHE_MAINTAIN[0] &
                 DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;
    } while (status);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  clean and invalidate the specified region of the dcache, it will flush the dirty
 *         cache in the specified region, and set the cache line to invalid state.
 * @param  address: the start address of specified region which you want invalidate.
 * @param  sizeByte: the length in bytes of invalidate range.
 * @return HAL_OK if success.
 */
HAL_Status
HAL_DCACHE_CleanInvalidateByRange(uint32_t address, uint32_t sizeByte)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t value = 0;
    uint32_t offset = 0;
    uint32_t status = 0;
    unsigned long flags;

    if (sizeByte == 0) {
        return HAL_OK;
    }

    offset = ((address & (CACHE_LINE_SIZE - 1)) + sizeByte - 1) >> CACHE_LINE_SHIFT;
    value = (address & DCACHE_CACHE_MAINTAIN0_CACHE_M_ADDR_MASK) |
            CACHE_M_CLEAN_INVALID | DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_MAINTAIN[1] = offset;
    DCACHE->CACHE_MAINTAIN[0] = value;

    do {
        status = DCACHE->CACHE_MAINTAIN[0] &
                 DCACHE_CACHE_MAINTAIN0_CACHE_M_VALID_MASK;
    } while (status);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  clean and invalidate all of the dcache, the dirty cache line will be flush
 *         to external memory, and all of the cache line will be set invalid.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_CleanInvalidate(void)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    uint32_t status = 0;
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_CTRL |= DCACHE_CACHE_CTRL_CACHE_FLUSH_MASK;

    do {
        status =
            DCACHE->CACHE_STATUS & DCACHE_CACHE_STATUS_CACHE_FLUSH_DONE_MASK;
    } while (!status);

    DCACHE->CACHE_CTRL &= ~DCACHE_CACHE_CTRL_CACHE_FLUSH_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  enable performance measurement unit of dcache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_EnablePMU(void)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_CTRL |= DCACHE_CACHE_CTRL_CACHE_PMU_EN_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  disable performance measurement unit of dcache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_DisablePMU(void)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_CTRL &= (~DCACHE_CACHE_CTRL_CACHE_PMU_EN_MASK);

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  get current state of performance measurement unit in icache.
 * @param  stat: return the current state if success.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_GetPMU(struct CACHE_PMU_CNT *stat)
{
#if defined(HAL_DCACHE_MODULE_ENABLED) && defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    HAL_ASSERT(stat != NULL);

    flags = HAL_SYS_EnterCriticalSection();

    stat->rdNum = DCACHE->PMU_RD_NUM_CNT;
    stat->wrNum = DCACHE->PMU_WR_NUM_CNT;
    stat->sramRdHit = DCACHE->PMU_SRAM_RD_HIT_CNT;
    stat->hbRdHit = DCACHE->PMU_HB_RD_HIT_CNT;
    stat->stbRdHit = DCACHE->PMU_STB_RD_HIT_CNT;
    stat->rdHit = DCACHE->PMU_RD_HIT_CNT;
    stat->wrHit = DCACHE->PMU_WR_HIT_CNT;
    stat->rdMissPenalty = DCACHE->PMU_RD_MISS_PENALTY_CNT;
    stat->wrMissPenalty = DCACHE->PMU_WR_MISS_PENALTY_CNT;
    stat->rdLat = DCACHE->PMU_RD_LAT_CNT;
    stat->wrLat = DCACHE->PMU_WR_LAT_CNT;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  Enable the interrupt of dcache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_EnableInt(void)
{
#if defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_INT_EN |= DCACHE_CACHE_INT_EN_ERR_RECORD_EN_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  Disable the interrupt of dcache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_DisableInt(void)
{
#if defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_INT_EN &= ~DCACHE_CACHE_INT_EN_ERR_RECORD_EN_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  Get the interrupt status of dcache.
 * @return HAL_TRUE if ahb error occur.
 */
HAL_Check HAL_DCACHE_GetInt(void)
{
    uint32_t status = 0;

#if defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)

    status = DCACHE->CACHE_INT_ST & DCACHE_CACHE_INT_ST_AHB_ERROR_STATUS_MASK;

#endif

#endif

    return status ? HAL_TRUE : HAL_FALSE;
}

/**
 * @brief  Clear the interrupt status of dcache.
 * @return HAL_OK if success.
 */
HAL_Status HAL_DCACHE_ClearInt(void)
{
#if defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)
    unsigned long flags;

    flags = HAL_SYS_EnterCriticalSection();

    DCACHE->CACHE_INT_ST |= DCACHE_CACHE_INT_ST_AHB_ERROR_STATUS_MASK;

    HAL_SYS_ExitCriticalSection(flags);
#endif

#endif

    return HAL_OK;
}

/**
 * @brief  Get the ahb bus error address of dcache.
 * @return ahb buss error address if success.
 * @attention The return value is only valid if you get a ahb error from CACHE_INT_ST
 */
uint32_t HAL_DCACHE_GetErrAddr(void)
{
    uint32_t address = -1;

#if defined(DCACHE)

#if defined(CACHE_REVISION) && (CACHE_REVISION == 0x00000100U)

    address = DCACHE->CACHE_ERR_HADDR;

#endif

#endif

    return address;
}

/** @} */

/** @} */

/** @} */
