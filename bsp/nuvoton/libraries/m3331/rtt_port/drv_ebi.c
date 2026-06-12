/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_EBI)

#include "drv_ebi.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.ebi"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define MAX_BANK    EBI_BANK2

/* Types / Structures ---------------------------------------------------------*/

/* Static Function Prototypes ------------------------------------------------*/

/* Static Variables ----------------------------------------------------------*/
static uint8_t nu_ebi_bank_mask = 0;

/* Functions Implementation --------------------------------------------------*/
rt_err_t nu_ebi_init(uint32_t u32Bank,
                     uint32_t u32DataWidth,
                     uint32_t u32TimingClass,
                     uint32_t u32BusMode,
                     uint32_t u32CSActiveLevel)
{
    if (u32Bank > MAX_BANK)
        return -(RT_ERROR);

    /* Check this bank is not used */
    if ((1 << u32Bank) & nu_ebi_bank_mask)
        return -(RT_ERROR);

    /* Initialize EBI */
    EBI_Open(u32Bank, u32DataWidth, u32TimingClass, u32BusMode, u32CSActiveLevel);

    nu_ebi_bank_mask |= (1 << u32Bank);

    return RT_EOK;
}

#endif //#if defined(BSP_USING_EBI)
