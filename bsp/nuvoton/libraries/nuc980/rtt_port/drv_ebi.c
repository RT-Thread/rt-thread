/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-12-12      Wayne            First version
*
******************************************************************************/
#include <drv_ebi.h>
#include <drv_sys.h>

#if defined(BSP_USING_EBI)

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

    if (!nu_ebi_bank_mask)
    {
        nu_sys_ipclk_enable(EBICKEN);
        nu_sys_ip_reset(EBIRST);
    }

    /* Initialize EBI */
    EBI_Open(u32Bank, u32DataWidth, u32TimingClass, u32BusMode, u32CSActiveLevel);

    nu_ebi_bank_mask |= (1 << u32Bank);

    return RT_EOK;
}

#endif //BSP_USING_EBI
