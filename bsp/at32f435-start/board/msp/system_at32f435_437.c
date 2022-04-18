/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2022-04-18     Dozingfiretruck     first version
 */

#include <board.h>

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
// #define SYSCLK_FREQ_20MHz_HSI     20000000
// #define SYSCLK_FREQ_35MHz_HSI     35000000
// #define SYSCLK_FREQ_60MHz_HSI     60000000
// #define SYSCLK_FREQ_100MHz_HSI    100000000
// #define SYSCLK_FREQ_150MHz_HSI    150000000
// #define SYSCLK_FREQ_250MHz_HSI    250000000
#define SYSCLK_FREQ_288MHz_HSI    288000000
#endif

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#ifdef SYSCLK_FREQ_20MHz_HSI
uint32_t SystemCoreClock         = EMAC_HCLK_BORDER_20MHZ;
#elif defined SYSCLK_FREQ_35MHz_HSI
uint32_t SystemCoreClock         = EMAC_HCLK_BORDER_35MHZ;
#elif defined SYSCLK_FREQ_60MHz_HSI
uint32_t SystemCoreClock         = EMAC_HCLK_BORDER_60MHZ;
#elif defined SYSCLK_FREQ_100MHz_HSI
uint32_t SystemCoreClock         = EMAC_HCLK_BORDER_100MHZ;
#elif defined SYSCLK_FREQ_150MHz_HSI
uint32_t SystemCoreClock         = EMAC_HCLK_BORDER_150MHZ;
#elif defined SYSCLK_FREQ_250MHz_HSI
uint32_t SystemCoreClock         = EMAC_HCLK_BORDER_250MHZ;
#elif defined SYSCLK_FREQ_288MHz_HSI
uint32_t SystemCoreClock         = EMAC_HCLK_BORDER_288MHZ;
#endif
