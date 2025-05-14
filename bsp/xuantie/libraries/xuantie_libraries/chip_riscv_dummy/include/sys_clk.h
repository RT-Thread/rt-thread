 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     sys_clk.h
 * @brief    header file for setting system frequency.
 * @version  V1.0
 * @date     9. April 2020
 ******************************************************************************/
#ifndef _SYS_CLK_H_
#define _SYS_CLK_H_

#include <stdint.h>
#include <soc.h>
#include <drv/clk.h>
#include <drv/porting.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PMU_REG_BASE            (wj_pmu_reg_t *)WJ_PMU_BASE

typedef enum {
    IHS_CLK       = 0U,        /* internal high speed clock */
    EHS_CLK,                   /* external high speed clock */
    ILS_CLK,                   /* internal low  speed clock */
    ELS_CLK,                   /* external low  speed clock */
    PLL_CLK                    /* PLL clock */
} clk_src_t;

typedef enum {
    CPU_24MHZ     = 24000000U
} sys_freq_t;


/* pllclkout : ( pllclkin / 2)*( FN + Frac/4096 ) */
typedef struct {

    uint32_t pll_is_used;          /* pll is used */

    uint32_t pll_source;           /* select pll input source clock */

    uint32_t pll_src_clk_divider;  /* ratio between pll_srcclk clock and pll_clkin clock */

    uint32_t fn;                   /* integer value of frequency division */

    uint32_t frac;                 /* decimal value of frequency division */

} pll_config_t;


typedef struct {
    uint32_t system_clk;            /* system clock */

    pll_config_t pll_config;        /* pll config struct */

    uint32_t sys_clk_source;        /* select sysclk source clock */

    uint32_t rtc_clk_source;        /* select rtcclk source clock */

    uint32_t mclk_divider;          /* ratio between fs_mclk clock and mclk clock */

    uint32_t apb0_clk_divider;      /* ratio between mclk clock and apb0 clock */

    uint32_t apb1_clk_divider;      /* ratio between mclk clock and apb1 clock */

} system_clk_config_t;

typedef enum {
    CLK_DIV1 = 0U,
} apb_div_t;

typedef enum {
    PLL_FN_18 = 0U,
} pll_fn_t;

typedef enum {
    UART0_CLK,
} clk_module_t;


/**
  \brief       Set the system clock according to the parameter
  \param[in]   config    system clock config.
  \return      error code
*/
csi_error_t soc_sysclk_config(system_clk_config_t *config);

/**
  \brief       Set iic reset
  \param[in]   idx    iic idx.
  \return      Null
*/
void soc_reset_iic(uint32_t idx);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_CLK_H_ */

