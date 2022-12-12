/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-02-18      klcheng          First version
*
******************************************************************************/
#include <drv_ebi.h>

#ifdef  BSP_USING_EBI
#define MAX_BANK    EBI_BANK1

/* Private variables ------------------------------------------------------------*/
static uint8_t nu_ebi_bank_mask = 0;

/* Public functions -------------------------------------------------------------*/
rt_err_t nu_ebi_init(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel)
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

#endif //BSP_USING_EBI
