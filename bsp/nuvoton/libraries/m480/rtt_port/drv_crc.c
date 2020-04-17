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

#if defined(BSP_USING_CRC)
#include <string.h>

#include <rtdevice.h>
#include <rtdbg.h>

#include "NuMicro.h"
#include "drv_pdma.h"

/* Private define ---------------------------------------------------------------*/
#define NU_CRYPTO_CRC_NAME  "nu_CRC"

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

    rt_mutex_take(&s_CRC_mutex, RT_WAITING_FOREVER);

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
            CRC_WRITE_DATA(*(uint32_t *)pu8InTempData);
            pu8InTempData += 4;
            i += 4;
#endif
        }
    }

    /* Get checksum value */
    u32CalChecksum = CRC_GetChecksum();
    rt_mutex_release(&s_CRC_mutex);

    return u32CalChecksum;
}


rt_err_t nu_crc_init(void)
{
    SYS_ResetModule(CRC_RST);

    rt_mutex_init(&s_CRC_mutex, NU_CRYPTO_CRC_NAME, RT_IPC_FLAG_FIFO);
    return RT_EOK;
}

rt_uint32_t nu_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    uint32_t u32OpMode;
    uint32_t u32CRCAttr = 0;
    rt_uint32_t crc_result = 0;

    //select CRC operation mode
    switch (ctx->crc_cfg.poly)
    {
    case 0x04C11DB7:
        u32OpMode = CRC_32;
        break;
    case 0x00001021:
        u32OpMode = CRC_CCITT;
        break;
    case 0x00008005:
        u32OpMode = CRC_16;
        break;
    case 0x00000007:
        u32OpMode = CRC_8;
        break;
    default:
        return 0;
    }


    u32CRCAttr |= ctx->crc_cfg.flags & CRC_FLAG_REFOUT ? CRC_CHECKSUM_RVS : 0; //CRC Checksum Reverse
    u32CRCAttr |= ctx->crc_cfg.flags & CRC_FLAG_REFIN ? CRC_WDATA_RVS : 0;  //CRC Write Data Reverse

    //Calcluate CRC checksum, using config's last value as CRC seed
    crc_result = nu_crc_run(u32OpMode, ctx->crc_cfg.last_val, u32CRCAttr, (uint8_t *)in, length);

    //update CRC result to config's last vaule
    ctx->crc_cfg.last_val = crc_result;
    return crc_result ^ 0x00 ^ ctx->crc_cfg.xorout;
}


#endif
