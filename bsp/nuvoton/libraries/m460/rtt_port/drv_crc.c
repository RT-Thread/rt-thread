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

#if (defined(BSP_USING_CRC) && defined(RT_HWCRYPTO_USING_CRC))

#include <string.h>

#include <rtdevice.h>
#include <rtdbg.h>

#include "NuMicro.h"
#include "drv_pdma.h"

/* Private define ---------------------------------------------------------------*/
#define NU_CRYPTO_CRC_NAME  "nu_CRC"

#define CRC_32_POLY     0x04C11DB7
#define CRC_CCITT_POLY  0x00001021
#define CRC_16_POLY     0x00008005
#define CRC_8_POLY      0x00000007

/* Private variables ------------------------------------------------------------*/

static struct rt_mutex s_CRC_mutex;

static rt_uint32_t nu_crc_run(
    uint32_t u32OpMode,
    uint32_t u32Seed,
    uint32_t u32Attr,
    uint8_t *pu8InData,
    uint32_t u32DataLen
)
{
    uint32_t u32CalChecksum = 0;
    uint32_t i = 0;
    rt_err_t result;

    result = rt_mutex_take(&s_CRC_mutex, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Configure CRC controller  */
    CRC_Open(u32OpMode, u32Attr, u32Seed, CRC_CPU_WDATA_8);

    uint8_t *pu8InTempData = pu8InData;

    while (i < u32DataLen)
    {
        if (((((uint32_t)pu8InTempData) % 4) != 0) || (u32DataLen - i < 4))
        {
            CRC->CTL &= ~CRC_CTL_DATLEN_Msk;
            CRC_WRITE_DATA((*pu8InTempData) & 0xFF);
            pu8InTempData ++;
            i++;
        }
        else
        {
            CRC->CTL &= ~CRC_CTL_DATLEN_Msk;
            CRC->CTL |= CRC_CPU_WDATA_32;
#if defined (NU_CRC_USE_PDMA)
            int32_t i32PDMATransCnt = (u32DataLen - i) / 4 ;

            i32PDMATransCnt = nu_pdma_mempush((void *)&CRC->DAT, pu8InTempData, 32, i32PDMATransCnt);

            if (i32PDMATransCnt > 0)
            {
                pu8InTempData += (i32PDMATransCnt * 4);
                i += (i32PDMATransCnt * 4);
            }
#else
            CRC_WRITE_DATA(CRC, *(uint32_t *)pu8InTempData);
            pu8InTempData += 4;
            i += 4;
#endif
        }
    }

    /* Get checksum value */
    u32CalChecksum = CRC_GetChecksum();

    result = rt_mutex_release(&s_CRC_mutex);
    RT_ASSERT(result == RT_EOK);

    return u32CalChecksum;
}

rt_err_t nu_crc_init(void)
{
    SYS_ResetModule(CRC_RST);
    return rt_mutex_init(&s_CRC_mutex, NU_CRYPTO_CRC_NAME, RT_IPC_FLAG_PRIO);
}

rt_uint32_t nu_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    uint32_t u32OpMode;
    uint32_t u32CRCAttr = 0;
    rt_uint32_t crc_result = 0;

    //select CRC operation mode
    switch (ctx->crc_cfg.poly)
    {
    case CRC_32_POLY:
        u32OpMode = CRC_32;
        break;
    case CRC_CCITT_POLY:
        u32OpMode = CRC_CCITT;
        break;
    case CRC_16_POLY:
        u32OpMode = CRC_16;
        break;
    case CRC_8_POLY:
        u32OpMode = CRC_8;
        break;
    default:
        return 0;
    }

    u32CRCAttr |= (ctx->crc_cfg.flags & CRC_FLAG_REFOUT) ? CRC_CHECKSUM_RVS : 0; //CRC Checksum Reverse
    u32CRCAttr |= (ctx->crc_cfg.flags & CRC_FLAG_REFIN) ? CRC_WDATA_RVS : 0;  //CRC Write Data Reverse

    //Calculate CRC checksum, using config's last value as CRC seed
    crc_result = nu_crc_run(u32OpMode, ctx->crc_cfg.last_val, u32CRCAttr, (uint8_t *)in, length);

    //update CRC result to config's last value
    ctx->crc_cfg.last_val = crc_result;
    return crc_result ^ 0x00 ^ ctx->crc_cfg.xorout;
}

#endif //#if (defined(BSP_USING_CRC) && defined(RT_HWCRYPTO_USING_CRC))
