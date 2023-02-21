/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2022-3-15       Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_TRNG) && defined(RT_HWCRYPTO_USING_RNG))

#include <rtdevice.h>
#include "NuMicro.h"

#define NU_CRYPTO_TRNG_NAME "nu_TRNG"

#define LOG_TAG         "TRNG"
#define DBG_ENABLE
#define DBG_SECTION_NAME "TRNG"
#define DBG_LEVEL DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

/* Private variables ------------------------------------------------------------*/
rt_err_t nu_trng_init(void)
{
    CLK_EnableModuleClock(TRNG_MODULE);
    SYS_ResetModule(TRNG_RST);

    TRNG_Open();

    return RT_EOK;
}

rt_uint32_t nu_trng_rand(struct hwcrypto_rng *ctx)
{
    uint32_t u32RNGValue;

    TRNG_GenWord(&u32RNGValue);

    return u32RNGValue;
}

#endif //#if (defined(BSP_USING_TRNG) && defined(RT_HWCRYPTO_USING_RNG))
