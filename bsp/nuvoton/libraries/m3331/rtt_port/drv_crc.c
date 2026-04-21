/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_CRC)

#include "NuMicro.h"
#include "drv_crc.h"
#include "drv_pdma.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.crc"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define NU_CRYPTO_CRC_NAME  "nu_crc"
#define CRC_32_POLY     0x04C11DB7
#define CRC_CCITT_POLY  0x00001021
#define CRC_16_POLY     0x00008005
#define CRC_8_POLY      0x00000007

/* Types / Structures ---------------------------------------------------------*/

/* Static Function Prototypes ------------------------------------------------*/
static rt_uint32_t nu_crc_run(uint32_t u32OpMode,
                              uint32_t u32Seed,
                              uint32_t u32Attr,
                              uint8_t *pu8InData,
                              uint32_t u32DataLen);

/* Static Variables ----------------------------------------------------------*/
static struct rt_mutex s_CRC_mutex;

/* Functions Implementation --------------------------------------------------*/
void CRC_IRQHandler(void)
{
    uint32_t u32CRCDMAStatus;

    /* enter interrupt */
    rt_interrupt_enter();

    u32CRCDMAStatus = CRC_GET_DMA_STATUS();
    CRC->DMASTS = u32CRCDMAStatus;

    if (u32CRCDMAStatus & CRC_DMASTS_FINISH_Msk)
        rt_kprintf("\tIRQ - CRC DMA Finish\n\n");

    if (u32CRCDMAStatus & CRC_DMASTS_ABORTED_Msk)
        rt_kprintf("\tIRQ - CRC DMA Abort\n");

    if (u32CRCDMAStatus & CRC_DMASTS_CFGERR_Msk)
        rt_kprintf("\tIRQ - CRC DMA CFG Error\n\n");

    if (u32CRCDMAStatus & CRC_DMASTS_ACCERR_Msk)
        rt_kprintf("\tIRQ - CRC DMA Access Error\n\n");

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * @brief  Run CRC calculation on input data buffer.
 * @param  u32OpMode: CRC operation mode (CRC_32, CRC_CCITT, etc.)
 * @param  u32Seed:   Initial CRC seed value
 * @param  u32Attr:   CRC attribute flags (reverse, etc.)
 * @param  pu8InData: Pointer to input data buffer
 * @param  u32DataLen: Length of input data in bytes
 * @return Calculated CRC checksum
 */
static rt_uint32_t nu_crc_run(
    uint32_t u32OpMode,
    uint32_t u32Seed,
    uint32_t u32Attr,
    uint8_t *pu8InData,
    uint32_t u32DataLen)
    {
    uint32_t u32CalChecksum = 0;
    uint32_t i = 0;
    rt_err_t result;

    // Take mutex to ensure exclusive access to CRC hardware
    result = rt_mutex_take(&s_CRC_mutex, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    // Configure CRC controller
    CRC_Open(u32OpMode, u32Attr, u32Seed, CRC_CPU_WDATA_8);

    uint8_t *pu8InTempData = pu8InData;

    while (i < u32DataLen)
    {
        // If address is not 4-byte aligned or less than 4 bytes left, write byte-by-byte
        if ((((uintptr_t)pu8InTempData) % 4 != 0) || (u32DataLen - i < 4))
        {
            CRC->CTL &= ~CRC_CTL_DATLEN_Msk;
            CRC_WRITE_DATA((*pu8InTempData) & 0xFF);
            pu8InTempData++;
            i++;
        }
        else
        {
            CRC->CTL &= ~CRC_CTL_DATLEN_Msk;
            CRC->CTL |= CRC_CPU_WDATA_32;
#if defined (NU_CRC_USE_DEDICATED_DMA)
            // Use Dedicated DMA for efficient transfer if enabled
            int32_t i32Remain = (u32DataLen - i);
            int32_t i32Remain_WordAligned = i32Remain & ~0x3;

            uint32_t u32CRCDMAStatus = 0;

            /* Enable CRC IRQ */
            //NVIC_EnableIRQ(CRC_IRQn);

            CRC_ENABLE_DMA_INT();

            CRC_SET_DMA_SADDR((uint32_t)pu8InTempData);
            CRC_SET_DMA_SIZE(i32Remain_WordAligned);
            CRC_DMA_START();

            while ((u32CRCDMAStatus = CRC_GET_DMA_STATUS()) == 0);
            CRC->DMASTS = u32CRCDMAStatus;

            if (u32CRCDMAStatus != CRC_DMASTS_FINISH_Msk)
            {
                rt_kprintf("CRC DMA Address@0x%08X\n", (uint32_t)pu8InTempData);
                rt_kprintf("CRC DMA Length: %d\n", (uint32_t)i32Remain_WordAligned);

                if (u32CRCDMAStatus & CRC_DMASTS_ABORTED_Msk)
                    rt_kprintf("CRC DMA Abort\n");

                if (u32CRCDMAStatus & CRC_DMASTS_CFGERR_Msk)
                    rt_kprintf("CRC DMA CFG Error\n");

                if (u32CRCDMAStatus & CRC_DMASTS_ACCERR_Msk)
                    rt_kprintf("CRC DMA Access Error\n");
            }
            else
            {
                pu8InTempData += (i32Remain_WordAligned);
                i += (i32Remain_WordAligned);
            }
#elif defined (NU_CRC_USE_PDMA)
            // Use PDMA for efficient transfer if enabled
            int32_t i32DMATransCnt = (u32DataLen - i) / 4;
            i32DMATransCnt = nu_pdma_mempush((void *)&CRC->DAT, pu8InTempData, 32, i32DMATransCnt);
            if (i32DMATransCnt > 0)
            {
                pu8InTempData += (i32DMATransCnt * 4);
                i += (i32DMATransCnt * 4);
            }
#else
            // Write 4 bytes at a time
            CRC_WRITE_DATA(*(uint32_t *)pu8InTempData);
            pu8InTempData += 4;
            i += 4;
#endif
        }
    }
    u32CalChecksum = CRC_GetChecksum();

    // Release mutex
    result = rt_mutex_release(&s_CRC_mutex);
    RT_ASSERT(result == RT_EOK);

    return u32CalChecksum;
}

/**
 * @brief  Initialize CRC hardware and mutex.
 * @return RT_EOK on success, error code otherwise.
 */
rt_err_t nu_crc_init(void)
{
    SYS_ResetModule(CRC_RST);
    return rt_mutex_init(&s_CRC_mutex, NU_CRYPTO_CRC_NAME, RT_IPC_FLAG_PRIO);
}

/**
 * @brief  Update CRC calculation with new data.
 * @param  ctx:    Pointer to CRC context/config structure
 * @param  in:     Pointer to input data buffer
 * @param  length: Length of input data in bytes
 * @return Calculated CRC checksum
 */
rt_uint32_t nu_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    uint32_t u32OpMode;
    uint32_t u32CRCAttr = 0;
    rt_uint32_t crc_result = 0;

    // Select CRC operation mode based on polynomial
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
        LOG_E("Unsupported CRC polynomial: 0x%08X", ctx->crc_cfg.poly);
        return 0;
    }

    if (ctx->crc_cfg.flags & CRC_FLAG_REFOUT)
        u32CRCAttr |= CRC_CHECKSUM_RVS; // CRC Checksum Reverse

    if (ctx->crc_cfg.flags & CRC_FLAG_REFIN)
        u32CRCAttr |= CRC_WDATA_RVS;    // CRC Write Data Reverse

    // Calculate CRC checksum, using config's last value as CRC seed
    crc_result = nu_crc_run(u32OpMode, ctx->crc_cfg.last_val, u32CRCAttr, (uint8_t *)in, length);

    // Update CRC result to config's last value for possible chained calls
    ctx->crc_cfg.last_val = crc_result;

    // Apply xorout (final xor value)
    return crc_result ^ ctx->crc_cfg.xorout;
}
#endif //#if defined(BSP_USING_CRC)
