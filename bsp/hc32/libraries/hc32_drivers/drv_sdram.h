/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-14     CDT          first version
 */

#ifndef __DRV_SDRAM_H__
#define __DRV_SDRAM_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#if defined (HC32F4A0)
#define EXMC_EXCLK_DMC_MAX_FREQ             (40UL * 1000000UL)
#elif defined (HC32F4A8)
#define EXMC_EXCLK_DMC_MAX_FREQ             (120UL * 1000000UL)
#endif

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
int rt_hw_sdram_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SDRAM_H__ */
