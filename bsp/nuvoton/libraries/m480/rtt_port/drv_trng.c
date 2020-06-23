/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-3-4        CHChen           First version
*
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_TRNG) && defined(RT_HWCRYPTO_USING_RNG))

#include <rtdevice.h>
#include <stdlib.h>
#include "NuMicro.h"

#define NU_CRYPTO_TRNG_NAME "nu_TRNG"

/* Private variables ------------------------------------------------------------*/
static struct rt_mutex s_TRNG_mutex;
static int s_i32TRNGEnable = 0;

static rt_uint32_t nu_trng_run(void)
{
    uint32_t u32RNGValue;

    rt_mutex_take(&s_TRNG_mutex, RT_WAITING_FOREVER);

    TRNG_Open();

    if (TRNG_GenWord(&u32RNGValue) < 0)
    {
        //Failed, use software rand
        u32RNGValue = rand();
    }

    rt_mutex_release(&s_TRNG_mutex);
    return u32RNGValue;
}

rt_err_t nu_trng_init(void)
{
    rt_mutex_init(&s_TRNG_mutex, NU_CRYPTO_TRNG_NAME, RT_IPC_FLAG_FIFO);

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
    {
        rt_kprintf("This chip does not support TRNG!\n");
        return -RT_ERROR;
    }

    s_i32TRNGEnable = 1;
    SYS_ResetModule(TRNG_RST);
    return RT_EOK;
}

void nu_trng_open(void)
{
#if defined(NU_PRNG_USE_SEED)
    srand(NU_PRNG_SEED_VALUE);
#else
    srand(rt_tick_get());
#endif
}

rt_uint32_t nu_trng_rand(struct hwcrypto_rng *ctx)
{
    if (!s_i32TRNGEnable)
    {
        uint32_t u32RNGValue;
        //use software rand
        u32RNGValue = rand();
        return u32RNGValue;
    }

    return nu_trng_run();
}

#endif //#if (defined(BSP_USING_TRNG) && defined(RT_HWCRYPTO_USING_RNG))
