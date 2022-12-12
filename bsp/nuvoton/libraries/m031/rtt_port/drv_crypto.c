/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author         Notes
* 2021-02-26      klcheng        First version
*
******************************************************************************/

#include <rtconfig.h>

#if ((defined(BSP_USING_CRC)) && defined(RT_USING_HWCRYPTO))

#include <rtdevice.h>
#include <rtdbg.h>
#include <board.h>
#include "NuMicro.h"
#include <nu_bitutil.h>

#if defined(BSP_USING_CRC)
    #include "drv_crc.h"
#endif

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_hwcrypto_create(struct rt_hwcrypto_ctx *ctx);
static void nu_hwcrypto_destroy(struct rt_hwcrypto_ctx *ctx);
static rt_err_t nu_hwcrypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src);
static void nu_hwcrypto_reset(struct rt_hwcrypto_ctx *ctx);

/* Private variables ------------------------------------------------------------*/
static const struct rt_hwcrypto_ops nu_hwcrypto_ops =
{
    .create = nu_hwcrypto_create,
    .destroy = nu_hwcrypto_destroy,
    .copy = nu_hwcrypto_clone,
    .reset = nu_hwcrypto_reset,
};


/* CRC operation ------------------------------------------------------------*/
#if defined(BSP_USING_CRC)

static const struct hwcrypto_crc_ops nu_crc_ops =
{
    .update = nu_crc_update,
};

#endif

/* Register crypto interface ----------------------------------------------------------*/
static rt_err_t nu_hwcrypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        ctx->contex = RT_NULL;
        //Setup CRC operation
        ((struct hwcrypto_crc *)ctx)->ops = &nu_crc_ops;
        break;
    }
#endif /* BSP_USING_CRC */

    default:
        res = -RT_ERROR;
        break;
    }

    return res;
}

static void nu_hwcrypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    if (ctx->contex)
        rt_free(ctx->contex);
}

static rt_err_t nu_hwcrypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    if (des->contex && src->contex)
    {
        rt_memcpy(des->contex, src->contex, sizeof(struct rt_hwcrypto_ctx));
    }
    else
        return -RT_EINVAL;
    return res;
}

static void nu_hwcrypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    /* no need to implement */
    return;
}

/* Init and register nu_hwcrypto_dev */
int nu_hwcrypto_device_init(void)
{
    static struct rt_hwcrypto_device nu_hwcrypto_dev;

    nu_hwcrypto_dev.ops = &nu_hwcrypto_ops;
    nu_hwcrypto_dev.id = 0;
    nu_hwcrypto_dev.user_data = &nu_hwcrypto_dev;

#if defined(BSP_USING_CRC)
    nu_crc_init();
#endif

    // register hwcrypto operation
    if (rt_hwcrypto_register(&nu_hwcrypto_dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_hwcrypto_device_init);

#endif //#if ((defined(BSP_USING_CRC)) && defined(RT_USING_HWCRYPTO))
