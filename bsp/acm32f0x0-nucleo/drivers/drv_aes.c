/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-10-13   AisinoChip    first add to bsp
 */

#include "board.h"
#include <rtdevice.h>

#if defined(RT_USING_HWCRYPTO) && defined(RT_HWCRYPTO_USING_AES) && defined(BSP_USING_AES)

#define AES_MUTEX_NAME      "aes_mutex"

static struct rt_mutex aes_mutex;

rt_err_t rt_hw_aes_init(void)
{
    return rt_mutex_init(&aes_mutex, AES_MUTEX_NAME, RT_IPC_FLAG_PRIO);
}

rt_err_t rt_hw_aes_crypto(struct hwcrypto_symmetric *ctx, struct hwcrypto_symmetric_info *info)
{
    RT_ASSERT(ctx != RT_NULL);
    RT_ASSERT(info != RT_NULL);

    rt_mutex_take(&aes_mutex, RT_WAITING_FOREVER);

    HAL_AES_Set_Key_U8(ctx->key, (ctx->key_bitlen - 128) >> 6, AES_SWAP_ENABLE);

    HAL_AES_Crypt_U8((uint8_t*)info->in,
            info->out,
            info->length / RT_HWCRYPTO_IV_MAX_SIZE,
            info->mode == HWCRYPTO_MODE_ENCRYPT ? AES_ENCRYPTION : AES_DECRYPTION,
            (ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK|HWCRYPTO_SUB_TYPE_MASK)) == HWCRYPTO_TYPE_AES_CBC ? AES_CBC_MODE : AES_ECB_MODE,
            ctx->iv,
            AES_NORMAL_MODE);

    rt_mutex_release(&aes_mutex);

    return RT_EOK;
}

#endif /* defined(RT_USING_HWCRYPTO) && defined(RT_HWCRYPTO_USING_AES) && defined(BSP_USING_AES) */

