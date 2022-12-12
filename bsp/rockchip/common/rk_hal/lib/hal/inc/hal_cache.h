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

#ifndef _HAL_CACHE_H_
#define _HAL_CACHE_H_

#include "hal_def.h"
#include "hal_debug.h"

/***************************** MACRO Definition ******************************/
/** @defgroup CACHE_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/***************************** Structure Definition **************************/

/**
 *  performance measurement count for icache & dcache
 *
 */
struct CACHE_PMU_CNT {
    uint32_t rdNum; /**< PMU read number counter */
    uint32_t wrNum; /**< PMU write number counter */
    uint32_t sramRdHit; /**< PMU SRAM hit counter */
    uint32_t hbRdHit; /**< PMU hot buffer hit */
    uint32_t stbRdHit; /**< PMU store buffer hit */
    uint32_t rdHit; /**< PMU read hit counter */
    uint32_t wrHit; /**< PMU write hit counter */
    uint32_t rdMissPenalty; /**< PMU read miss penalty counter */
    uint32_t wrMissPenalty; /**< PMU write miss penalty counter */
    uint32_t rdLat; /**< PMU read latency */
    uint32_t wrLat; /**< PMU write latency */
};

/** @} */
/********************* Public Function Definition ****************************/
/** @defgroup CACHE_Exported_Functions_Group5 Other Functions
 *  @attention these APIs allow direct use in the HAL layer
 *  @{
 */

uint32_t HAL_CpuAddrToDmaAddr(uint32_t cpuAddr);
HAL_Status HAL_ICACHE_Enable(void);
HAL_Status HAL_ICACHE_Disable(void);
HAL_Status HAL_ICACHE_Invalidate(void);
HAL_Status HAL_ICACHE_InvalidateByRange(uint32_t address, uint32_t sizeByte);
HAL_Status HAL_ICACHE_EnablePMU(void);
HAL_Status HAL_ICACHE_DisablePMU(void);
HAL_Status HAL_ICACHE_GetPMU(struct CACHE_PMU_CNT *stat);
HAL_Status HAL_ICACHE_EnableInt(void);
HAL_Status HAL_ICACHE_DisableInt(void);
HAL_Check HAL_ICACHE_GetInt(void);
uint32_t HAL_ICACHE_GetErrAddr(void);
HAL_Status HAL_ICACHE_ClearInt(void);
HAL_Status HAL_DCACHE_Enable(void);
HAL_Status HAL_DCACHE_Disable(void);
HAL_Status HAL_DCACHE_Invalidate(void);
HAL_Status HAL_DCACHE_InvalidateByRange(uint32_t address, uint32_t sizeByte);
HAL_Status HAL_DCACHE_CleanByRange(uint32_t address, uint32_t sizeByte);
HAL_Status HAL_DCACHE_CleanInvalidateByRange(uint32_t address, uint32_t sizeByte);
HAL_Status HAL_DCACHE_CleanInvalidate(void);
HAL_Status HAL_DCACHE_EnablePMU(void);
HAL_Status HAL_DCACHE_DisablePMU(void);
HAL_Status HAL_DCACHE_GetPMU(struct CACHE_PMU_CNT *stat);
HAL_Status HAL_DCACHE_EnableInt(void);
HAL_Status HAL_DCACHE_DisableInt(void);
HAL_Check HAL_DCACHE_GetInt(void);
HAL_Status HAL_DCACHE_ClearInt(void);
uint32_t HAL_DCACHE_GetErrAddr(void);

/** @} */

#endif

/** @} */

/** @} */
