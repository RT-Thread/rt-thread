/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Change Logs:
* Date            Author           Notes
* 2020-3-4        CHChen           First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_TRNG)

#include <rtdevice.h>
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


#endif
